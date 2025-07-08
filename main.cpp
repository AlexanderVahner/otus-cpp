#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "lib.h"

void print(const std::vector<unsigned int>& vec)
{
    for (auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
    {
        print_ip_number(*ip);
    }
}

int main(int, char const**)
{
    try
    {
        std::vector<unsigned int> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ip_string_to_uint(v.at(0)));
        }

        // TODO reverse lexicographically sort
        // Sort the vector in descending order

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<unsigned int>());
        print(ip_pool);

        // TODO filter by first byte and output

        std::vector<unsigned int> filtered;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered),
            [](unsigned int ip)
            {
                return ip_byte(ip, 3) == 1;
            });

        // TODO filter by first and second bytes and output

        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered),
            [](unsigned int ip)
            {
                return ip_byte(ip, 3) == 46 && ip_byte(ip, 2) == 70;
            });

        // TODO filter by any byte and output

        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered),
            [](unsigned int ip)
            {
                return ip_byte(ip, 3) == 46 || ip_byte(ip, 2) == 46 || ip_byte(ip, 1) == 46 || ip_byte(ip, 0) == 46;
            });

        print(filtered);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
