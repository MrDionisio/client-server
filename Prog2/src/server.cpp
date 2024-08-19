#include "server.H"

server::server(int Port, int domain, int type, int protocol, int backlog){
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;
    this->backlog = backlog;

    sockfd = Socket();
    addr = {0};

    addr.sin_family = domain;
    addr.sin_port = htons(Port);


    Bind();
    Listen();
    addrlen = sizeof addr;
    fd = Accept();
}

server::~server(){
    close(fd);
    close(sockfd);
}


int server::getFD(){
    return this->fd;
}


void server::Reconnect(){
    printf( "ERROR : Connection lost. Waiting for client ...\n");
    this->fd = Accept();
}