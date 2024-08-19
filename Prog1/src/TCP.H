#ifndef TCP_H
#define TCP_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>

class TCP{
public:

    int Socket();

    int Bind();

    void Listen();

    int Accept();

protected:

    int domain;
    int type;
    int protocol;
    int sockfd;
    int backlog;
    struct sockaddr_in addr;
    socklen_t addrlen;
};

#endif