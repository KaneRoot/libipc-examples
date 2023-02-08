#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Do not forget to install libipc.
#include <libipc.h>

#define SERVICE "pong"
#define SERVICE_LEN 4

#define MAX_MSG_SIZE 10000

int err(void *ctx, char *msg) {
	printf("error: %s\n", msg);
	printf("Free context\n");
	ipc_context_deinit (&ctx);
	return 1;
}

int main(void) {
	int ret = 0;
	int servicefd = 0;
	char message[MAX_MSG_SIZE];
	memset (message, 0, 1000);
	size_t size = MAX_MSG_SIZE;
	char event_type;
	size_t index = 0;
	int originfd = 0;
	void *ctx = NULL;

	printf ("Init context.\n");
	ret = ipc_context_init (&ctx);

	if (ret != 0) {
		printf ("Cannot init context.\n");
		return 1;
	}

	printf ("Connect to a 'pong' service.\n");
	ret = ipc_connect_service (ctx, &servicefd, SERVICE, SERVICE_LEN);

	if (ret != 0) {
		return err(ctx, "Cannot connect to a service.");
	}

	printf ("Let's schedule a message.\n");
	ret = ipc_schedule (ctx, servicefd, "hello, plz bounce me", 21);

	if (ret != 0) {
		return err(ctx, "Cannot schedule a message.");
	}

	printf ("Let's set the timer to one second.\n");
	ipc_context_timer (ctx, 1000);

	printf ("Let's loop over events.\n");
	char should_continue = 1;
	size_t count = 0;
	while(should_continue) {
		size = MAX_MSG_SIZE;
		ret = ipc_wait_event (ctx, &event_type, &index, &originfd, message, &size);
		if (ret != 0) {
			return err(ctx, "Error while waiting for an event.");
		}

		printf ("EVENT %lu\t", count++);

		switch ((enum event_types) event_type) {
		case ERROR:         return err(ctx, "Error.");
		case EXTERNAL:      return err(ctx, "External (shouldn't happen).");
		case SWITCH_RX:     return err(ctx, "Switch RX (shouldn't happen).");
		case SWITCH_TX:     return err(ctx, "Switch TX (shouldn't happen).");
		case CONNECTION:    return err(ctx, "Connection (shouldn't happen).");
		case DISCONNECTION: return err(ctx, "Disconnection (shouldn't happen).");
		case TIMER:      { printf ("TIMER.\n");                   break; }
		case MESSAGE_TX: { printf ("A message has been sent.\n"); break; }
		case MESSAGE_RX: {
				if (size == 0) {
					printf ("No message returned.\n");
					printf ("Deinit context\n");
					ipc_context_deinit (&ctx);
					return 1;
				}

				message[size] = '\0';
				printf ("Response (size %lu): %s.\n", size, message);
				// We received the response, quitting.
				should_continue = 0;
				break;
			}
		}
	}

	printf ("Deinit context\n");
	ipc_context_deinit (&ctx);

	printf ("Context freed.\n");
	return 0;
}
