#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include <thread> 
#include <mutex> 
#include <condition_variable>

#include "client.H"

using namespace std;

class input{
public:

    void addData(){ // Добавление данных в буфер после первчиной обработки после ввода через консоль 

        printf("Введите строку из цифр! Если хотите выйти впишите: exit\n");

        while(true){

            cin >> inputStr;
            
            if(inputStr == "exit")
                break;

            if(checkSymbols(inputStr) || checkLength(inputStr)){ 
                printError();
                continue;
            }

            sort(inputStr.begin(), inputStr.end(), [](const char& left, const char& right){return int(left)>int(right);});

            
            changeEvenSymbols(inputStr, "KB");

            unique_lock<mutex> lock1(m1);
            this->data.push(inputStr);
            lock1.unlock();
            cv1.notify_one();
        }
    }
    
    void processingData(){ // Вторирчная обработка входных данных
        string tmp;
        int sum;
        while(true){

            unique_lock<mutex> lock1(m1);

            cv1.wait(lock1,[&](){ return !data.empty(); } );

            tmp = data.front();
            data.pop();
            lock1.unlock();

            printf("%s\n", tmp.c_str());
            printf("---------------------------------\n");

            sum = 0;
            for( auto el : tmp){
                if( !checkSymbols(string{el}))
                    sum += int(el - '0');
            }


            unique_lock<mutex> lock2(m2);
            this->dataOfSum.push(sum);
            lock2.unlock();
            cv2.notify_one();

        }

    }

    void sendSum(){ // Отправление данных на сервер
        
        int tmp;

        client cl(34543);


        while(true){

            unique_lock<mutex> lock2(m2);

            cv2.wait(lock2,[&](){ return !dataOfSum.empty(); } );

            tmp = dataOfSum.front();
            dataOfSum.pop();
            lock2.unlock();

            cl.Write(tmp);

        }



    }

private:
    queue<string> data;
    int maxStrSize = 64;
    string inputStr;
    queue<int> dataOfSum;




    bool checkLength(const string& str){
        return str.size()>maxStrSize; 
    }

    bool checkSymbols(const string& str){
        for(auto element : str){
            if((int(element - '0') > 9) || (int(element - '0') < 0)){
                return 1;
            }
        }
        return 0;
    }

    void printError(){
        printf("ERROR: \t Введенная строка содержит более %i цифр или в ней есть не только цифры.\n", maxStrSize);
        printf("---------------------------------\n");
    }

    void changeEvenSymbols(string& inputStr, const string& replacementStr){
        for(int i = 0; i < inputStr.size();){
            if (int(inputStr[i])%2==0){
                inputStr.replace(i, 1, replacementStr);
                i+=replacementStr.size();
            }
            else{ i++; }
        }
    }

    mutex m1, m2;
    condition_variable cv1, cv2;

};


int main(){

    input in;

    thread th1([&](){ in.addData(); }); // Поток для приема входных данных и запись их в очередь - буфер

    thread th2([&](){ in.processingData(); }); // Вторичная обработка данных с изъятием их из буфера и добавление их в очередь на отправление на сервер

    thread th3([&](){ in.sendSum();   }); // Этот поток можно встроить в функцию processingData(), но 
                                          // тогда при остановке сервера вторичная обработка происходить не будет, 
                                          // так как поток будет ожидать подключения. 
                                          // И чтобы второй поток не застаивался было принято решение о добавлении нового потока

    th1.join();
    th2.join();
    th3.join();

    return 0;
}

