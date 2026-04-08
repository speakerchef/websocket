# Simple POSIX WebSocket

```bash
# Build
cd websocket
cmake -S . -B build/
cd build
cmake --build .

# Run the server
./websocket

# On another window/session
# Connect client to server at port 8080
nc localhost 8080
#$<Enter any message>
# your message will print on the server side session window.
# Type `exit` in the client to close the socket

```
