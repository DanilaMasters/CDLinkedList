#ifndef TEST_H
#define TEST_H
#include <iostream>

template<typename T, typename C>
void AssertEqual(const T& t, const C& c, const std::string& hint);

void TestInsert();
void TestRemove();
void TestAll();

#include "test.cpp"

#endif