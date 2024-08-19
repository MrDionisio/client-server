#ifndef client_H
#define client_H

#include "TCP.H"

class client : private TCP{
public:
    client(int Port, std::string IP ="127.0.0.1", int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0, int backlog = 1);
    ~client();

    int getFD();
    void Reconnect();
    void Connect();

    template <typename T>
    int Write(T& buffer);

private:

};

template <typename T>
int client::Write(T& buffer){
    
    int res;
    write(this->sockfd, &buffer, sizeof buffer);
    res = read(this->sockfd, &buffer, sizeof buffer);
    if(res == 0){
        Reconnect();
        write(this->sockfd, &buffer, sizeof buffer);
        res = read(this->sockfd, &buffer, sizeof buffer);
    }

    return 1;

};

#endif