#pragma once
#include <iostream>
#include <vector>

int version();


std::vector<std::string> split(const std::string& str, char d);
unsigned int ip_string_to_uint(const std::string& ip_string);
unsigned char ip_byte(unsigned int ip, short byte_number);
void print_ip_number(unsigned int ip);
