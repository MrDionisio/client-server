#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "server.H"

using namespace std;

int main(){

    ssize_t n_read;
    server serv(34543);
    int sum = 0;
    int l_sum;
    while(true){

        n_read = serv.Read(sum);

        if(n_read == -1){
            perror("ERROR : Read Failured");   // Обработка со стороны пользователя
            exit(EXIT_FAILURE);
        }
        if(n_read == 0){
            serv.Reconnect();
        }
        else{
            l_sum = (sum == 0) ? 1 : log10(abs(sum)) + 1;
            if( l_sum >2 && sum%32 == 0)
                printf("Полученные данные : %i\n", sum);
            else
                printf("ERROR : Bad data. %i не кратно 32 и состоит из не больше двух символов \n", sum);
        }
    }  

    return 0;
}