#ifndef server_H
#define server_H

#include "TCP.H"



class server : private TCP{
public:

    server(int Port, int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0, int backlog = 1);
    ~server();

    int getFD();
    void Reconnect();

    template <typename T>
    int Read(T& buffer);

private:

    int fd;

};

template <typename T>
int server::Read(T& buffer){
    int tmp = read(this->fd, &buffer, sizeof buffer);
    
    write(this->fd, &buffer, sizeof buffer);

    return tmp;

}

#endif