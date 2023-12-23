cmake_minimum_required(VERSION 3.22)
project(Bookstore)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bookstore
        account.h
        bookdata.h
        main.cpp)
