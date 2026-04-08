#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <print>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* IP_ADDR = "127.0.0.1";
constexpr unsigned short PORT = htons(8080);

int main() {
    const int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    const int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (errno == -1) {
        std::println(stderr, "Socket open error");
    }

    sockaddr_in addr{};
    const int32_t ecode = inet_pton(AF_INET, IP_ADDR, &addr.sin_addr);
    if (ecode < 1) {
        std::println(stderr, "Error: Invalid IP Address");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = PORT;

    const int32_t bind_res = bind(sock, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
    if (bind_res == -1) {
        std::println(stderr, "Error: Unable to bind to socket; ERRNO: {}", strerror(errno));
        exit(EXIT_FAILURE);
    }
    const int32_t listen_res = listen(sock, 1);
    if (listen_res == -1) {
        std::println(stderr, "Error: Failed to listen at port: {}", PORT);
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    bool read_data = true;
    socklen_t sockln = sizeof(addr);
    auto conn = accept(sock,
                        reinterpret_cast<struct sockaddr*>(&addr),
                        &sockln);
    if (conn == -1) {
        std::println(stderr, "Error: Failed to read data; ERRNO: {}", strerror(errno));
        exit(EXIT_FAILURE);
    }
    std::println("Successful connection on port: {}!", PORT);

    while (read_data) {
        const size_t bytes_read = read(conn, buf, sizeof(buf));
        if (bytes_read < 1) {
            read_data = false;
        }

        if (!memcmp(buf, "exit", 4)) { read_data = false; }
        printf("MSG: %s", buf);
        memset(buf, '\0', 1024);
    }

    close(conn);
    close(sock);
    std::println("Connection closed!");
}
