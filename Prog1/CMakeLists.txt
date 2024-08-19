cmake_minimum_required(VERSION 3.10)

project(TestTask)

#Добавление директории в область видимости сборки
include_directories(
    ${PROJECT_SOURCE_DIR}/src
                    )


# Указание пути для исполняемых файлов
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

#Добавление библиотеки
add_library(TCP src/TCP.cpp)
add_library(client src/client.cpp)


#Сборка клиента - Программы №1
add_executable(Prog_1_client src/Prog_1_client.cpp)
target_link_libraries(client PRIVATE TCP)
target_link_libraries(Prog_1_client client)




