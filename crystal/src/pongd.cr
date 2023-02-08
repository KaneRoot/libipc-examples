require "ipc"

ipc = IPC.new
ipc.timer 5000 # timer event every 5 seconds
fd = ipc.service_init "pong"

ipc.loop do |event|
  case event.type
  when LibIPC::EventType::MessageRx
    m = event.message
    if m.nil?
      puts "No message"
    else
      received = String.new(m.to_unsafe, m.size)
      pp! received
      ipc.schedule event.fd, m, m.size
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
