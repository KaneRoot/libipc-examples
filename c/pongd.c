#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char**argv) {
	int ret = 0;
	int servicefd = 0;
	char message[MAX_MSG_SIZE];
	size_t size = MAX_MSG_SIZE;
	char event_type;
	size_t index = 0;
	int originfd = 0;
	void *ctx = NULL;

	int max_count = 0;

	if (argc > 1) {
		max_count = atoi(argv[1]);
		printf ("Wait for %d timer events.\n", max_count);
	}

	printf ("Init context.\n");
	ret = ipc_context_init (&ctx);

	if (ret != 0) {
		printf ("Cannot init context.\n");
		return 1;
	}

	printf ("Create a 'pong' service.\n");
	ret = ipc_service_init (ctx, &servicefd, SERVICE, SERVICE_LEN);

	if (ret != 0) {
		return err (ctx, "Cannot create a service.");
	}

	printf ("Set the timer to two seconds.\n");
	ipc_context_timer (ctx, 2000);

	printf ("Loop over events.\n");
	char should_continue = 1;
	size_t count = 0;
	size_t count_timer = 0;
	while(should_continue) {
		size = MAX_MSG_SIZE;
		ret = ipc_wait_event (ctx, &event_type, &index, &originfd, message, &size);
		if (ret != 0) {
			return err (ctx, "Error while waiting for an event.");
		}

		if ((enum event_types) event_type != TIMER) {
			printf ("EVENT %lu\t", count++);
		}

		switch ((enum event_types) event_type) {
		case ERROR:         return err(ctx, "Error.");
		case EXTERNAL:      return err(ctx, "External (shouldn't happen).");
		case SWITCH_RX:     return err(ctx, "Switch RX (shouldn't happen).");
		case SWITCH_TX:     return err(ctx, "Switch TX (shouldn't happen).");
		case CONNECTION:    { printf ("New connection.\n");    break; }
		case DISCONNECTION: { printf ("User disconnected.\n"); break; }

		case TIMER: {
				printf ("\rTIMER (%lu).", count_timer++);
				fflush(stdout);
				if (max_count && count_timer >= (size_t) max_count) {
					printf ("waited for %lu timer events: quitting\n", count_timer);
					should_continue = 0;
				}
				break;
			}

		case MESSAGE_TX: {
				printf ("Message sent.\n");
				break;
			}

		case MESSAGE_RX: {
				if (size == 0) {
					return err(ctx, "Error: no message returned.");
				}
				else {
					message[size+1] = '\0';
					printf ("Message received (size %lu): %s.\n", size, message);
					printf ("Scheduling this message.\n");
					ret = ipc_schedule (ctx, originfd, message, size);
					if (ret != 0) {
						return err(ctx, "Cannot schedule a message.");
					}
				}
				break;
			}
		}
	}

	printf ("Deinit context\n");
	ipc_context_deinit (&ctx);

	printf ("Context freed.\n");
	return 0;
}
