//
// Created by nikitabakunovich on 19.03.24.
//


#include "client.h"
#include "../utilities/func.h"
#include "../logicpart/logic.h"

#define PORT 8082
#define MAX_BUFFER 1024

int client_v2() {
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    char strData[MAX_BUFFER];
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    adr.sin_addr.s_addr = INADDR_ANY;

    std::string adressIP;
    std::cout << "Введите IP игры - ";
    std::cin >> adressIP;

    Inet_pton(AF_INET, adressIP.c_str(), &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
//    write(fd, "Privet Timoxa\n", 15);
//    char buf[256];
//    ssize_t nread;
//    nread = read(fd, buf, 256);
//    if (nread == -1) {
//        perror("read failed");
//        exit(EXIT_FAILURE);
//    }
//    if (nread == 0) {
//        printf("EOF occured\n");
//    }
//    write(STDOUT_FILENO, buf, nread);
    while (1) {
        game();
        printf("Enter message: ");
        fgets(strData, MAX_BUFFER, stdin);
        send(fd, strData, strlen(strData), 0);
        if (strncmp("exit", strData, 4) == 0) {
            printf("Client Exit...\n");
            break;
        }
        bzero(strData, MAX_BUFFER);
        recv(fd, strData, MAX_BUFFER, 0);
        printf("Message: %s\n", strData);
    }
    //sleep(10);
    close(fd);
    return 0;
}
