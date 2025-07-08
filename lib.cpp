#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "lib.h"

#include "version.h"

int version() {
	return PROJECT_VERSION_PATCH;
}

const int IP_PARTS_COUNT = 4;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

// Convert IP string parts to uint
unsigned int ip_string_to_uint(const std::string& ip_string)
{

    std::vector<std::string> ip_parts = split(ip_string, '.');
    if (ip_parts.size() != IP_PARTS_COUNT)
    {
        throw std::invalid_argument("The number of ip's parts is not equal to 4.");
    }

    unsigned int result = 0;

    for (int i = 0; i < IP_PARTS_COUNT; i++)
    {
        int byte = std::stoi(ip_parts.at(i));
        if (byte < 0 || byte > 255)
        {
            throw std::invalid_argument("The byte of the ip is invalid.");
        }

        result |= byte << (IP_PARTS_COUNT - i - 1) * 8;
    }

    return result;
}

// Get the ip byte by number
unsigned char ip_byte(unsigned int ip, short byte_number)
{
    auto p = (unsigned char*)&ip;
    return *(p + byte_number);
}

// Print the IP-address
void print_ip_number(unsigned int ip)
{
    auto p = (unsigned char*)&ip;
    std::cout << (short)*(p + 3) << '.' << (short)*(p + 2) << '.' << (short)*(p + 1) << '.' << (short)*p << std::endl;
}
