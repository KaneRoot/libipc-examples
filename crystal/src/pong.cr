require "ipc"

ipc = IPC.new
ipc.timer 5000 # timer event every 5 seconds
fd = ipc.connect "pong" # 'pong' service

# Schedule a message to send to a particular file descriptor
ipc.schedule fd, "Hello this is me!"

ipc.loop do |event|
  case event.type
  when LibIPC::EventType::MessageRx
    m = event.message
    if m.nil?
      puts "Err, should have received smth :("
      exit 1
    else
      received = String.new(m.to_unsafe, m.size)
      puts "msg received: #{received}"
      if "Hello this is me!".compare(received) == 0
        puts "All good! Goodbye!"
        exit 0
      end
      puts "Received message isn't what was expected!"
      exit 1
    end
  when LibIPC::EventType::MessageTx
    puts "A message has been sent"
  when LibIPC::EventType::Connection
    puts "A client just connected #JOY"
  when LibIPC::EventType::Disconnection
    puts "A client just disconnected #SAD"
  when LibIPC::EventType::Timer
    STDOUT.write "\rTimer!".to_slice
  else
    puts "Unexpected: #{event.type}"
    exit 1
  end
end
