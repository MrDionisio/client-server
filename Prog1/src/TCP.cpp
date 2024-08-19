#include "TCP.H"

using namespace std;

int TCP::Socket(){

    int res = socket(this->domain, this->type, this->protocol);
    if(res == -1){
        perror("ERROR : Socket Failed !\t");
        exit(EXIT_FAILURE);
    }
    return res;
}

int TCP::Bind(){
    int res = bind(this->sockfd, (struct sockaddr *) &this->addr, sizeof addr);
    if(res == -1){
        perror("ERROR : Bind Failed !\t");
        exit(EXIT_FAILURE);
    }
    return res;
}

void TCP::Listen(){
    int res = listen(this->sockfd, this->backlog);
    if(res == -1){
        perror("ERROR : Listen Failed!\t");
        exit(EXIT_FAILURE);
    }
}

int TCP::Accept(){
    int res = accept (this->sockfd, (struct sockaddr *) &this->addr, &this->addrlen);
    if(res == -1){
        perror("ERROR : Accept Failed!\n");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection sucsessful!" << std::endl;
    return res;
}





/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/


