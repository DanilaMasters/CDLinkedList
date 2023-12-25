cmake_minimum_required(VERSION 3.14)

project(CDLinkedList)

set(Sources
    CDLinkedList.inl
    CDLinkedListS.inl
    ListIterator.inl
    ListIteratorS.inl
    test.cpp
)

set(Headers
    CDLinkedList.h
)

add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC ${PROJECT_NAME})