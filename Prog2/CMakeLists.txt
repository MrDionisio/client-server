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
add_library(server src/server.cpp)


#Сборка сервера - Программы №2
add_executable(Prog_2_server src/Prog_2_server.cpp)
target_link_libraries(server PRIVATE TCP)
target_link_libraries(Prog_2_server server)




