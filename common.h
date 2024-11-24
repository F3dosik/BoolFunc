#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <iostream>

typedef unsigned long long ull;

std::string str_bin(ull n);
std::string str_bin(ull* arr, unsigned int size);

void print(std::string line);
void print(ull n);
void print_bin(ull n);
void print_bin(ull* n, unsigned int size);

void println(std::string line);
void println(ull n);

unsigned int weight(unsigned long long n);
unsigned int weight(unsigned long long* arr, unsigned int size);



#endif
