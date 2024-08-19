#include "client.H"
#include "TCP.H"

client::client(int Port, std::string IP, int domain, int type, int protocol, int backlog){
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;
    this->backlog = backlog;

    sockfd = Socket();
    addr = {0};

    addr.sin_family = domain;
    addr.sin_port = htons(Port);

    inet_pton(AF_INET,IP.c_str(), &this->addr.sin_addr);

    addrlen = sizeof addr;
    std::cout<< "Connection ..." << std::endl;
    Connect();
}

client::~client(){
    close(sockfd);
}


int client::getFD(){
    return this->sockfd;
}


void client::Reconnect(){
    close(sockfd);
    sockfd = Socket();
    Connect();    

}

void client::Connect(){
    int res = connect(this->sockfd, (struct sockaddr *) &this->addr, this->addrlen);
    if(res == -1){

        printf("ERROR : Connection Failed! Try connect every 5 seconds ...\n");
        while(res == -1){
            res = connect(this->sockfd, (struct sockaddr *) &this->addr, this->addrlen);
            sleep(5);
        }
    }
    perror("\nConnection");

}