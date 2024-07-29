#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() error");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.22");
    serv_addr.sin_port = htons(8080);
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("connect() error");
        exit(1);
    }
    while (1) 
    {
        printf("Input message: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0'; // remove newline character
        printf("Message sent: %s\n", buf);
        if (send(sock, buf, strlen(buf), 0) == -1) {
            perror("send() error");
            exit(1);
        }

        if (strcmp(buf, "quit") == 0) {
            printf("Quit.\n");
            break;
        }
    }

    close(sock);
    return 0;
}