#include <gtest/gtest.h>
#include "lib.h"

unsigned int ip_to_uint(int b3, int b2, int b1, int b0)
{
    unsigned int result = 0;
    result |= b0;
    result |= b1 << 8;
    result |= b2 << 16;
    result |= b3 << 24;

    return result;
};

TEST(IpFilterTests, ip_string_to_uint_Should_Succ_When_VaildIp)
{
    // Arrange
    std::vector<std::tuple<std::string, unsigned int>> valid_ips
    {
        std::make_tuple("192.168.0.1", ip_to_uint(192, 168, 0, 1)),
        std::make_tuple("127.0.0.1", ip_to_uint(127, 0, 0, 1)),
        std::make_tuple("8.8.8.8", ip_to_uint(8, 8, 8, 8)),
        std::make_tuple("10.0.0.1", ip_to_uint(10, 0, 0, 1))
    };

    for (auto ip = valid_ips.cbegin(); ip != valid_ips.cend(); ++ip)
    {

        auto [string_present, uint_present] = *ip;

        // Act
        unsigned int result = ip_string_to_uint(string_present);

        // Assert
        EXPECT_EQ(result, uint_present) << "IP "<< string_present << " should be " << uint_present << " but result is " << result;
    }
}

TEST(IpFilterTests, ip_string_to_uint_Should_Throw_When_InvaildIp)
{
    // Arrange
    std::vector<std::string> invalid_ips
    {
        ".34.0.1",
        "192..0.1",
        "3.4..1",
        "44.55.0.",
        "56...3",
        "256.168.0.1",
        "127.45435.0.1",
        "8.8.345.8",
        "10.0.0.1000",
        "192.168.0.1.192",
        "127.0.0.-1",
        "8888"
    };

    for (auto ip = invalid_ips.cbegin(); ip != invalid_ips.cend(); ++ip)
    {
        // Act
        // Assert
        EXPECT_THROW(ip_string_to_uint(*ip), std::invalid_argument) << "Invalid IP '" << *ip << " didn't throw the std::invalid_argument exception";
    }
}

TEST(IpFilterTests, ip_byte_Should_Return_ValidValue)
{
    // Arrange
    unsigned int ip_value = ip_to_uint(192, 168, 0, 1);

    // Act
    // Assert
    EXPECT_EQ(ip_byte(ip_value, 3), 192);
    EXPECT_EQ(ip_byte(ip_value, 2), 168);
    EXPECT_EQ(ip_byte(ip_value, 1), 0);
    EXPECT_EQ(ip_byte(ip_value, 0), 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
