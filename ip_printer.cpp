#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <stdint.h>

namespace ip_printer 
{
    /**
     * @brief Print IP as string with no changes.
     * @tparam T Must be std::string
     * @param str String value
     * @return
     */
    template<typename T>
    typename std::enable_if<std::is_same_v<T, std::string>>::type
    print_ip(const T str)
    {
        std::cout << str << std::endl;
    }

    /**
     * @brief Print IP as bytes of integer value.
     * @tparam T Any of integer type.
     * @param intValue Integer value.
     * @return
     */
    template<typename Integer>
    typename std::enable_if<std::is_integral_v<Integer>>::type
    print_ip(Integer intValue)
    {
        // from big endian
        uint8_t* ptr = ((uint8_t*)(&intValue + 1)) - 1;

        std::cout << (int)*ptr;
        for (int i = 0; i < sizeof(Integer) - 1; i++)
        {
            std::cout << "." << (int)*(--ptr);
        }
        std::cout << std::endl;
    }

    /**
     * @brief Print container's elements as IP bytes.
     * @tparam T Any of integer type.
     * @param container vector or list.
     */
    template <
        template <typename, typename> typename Container,
        typename T,
        typename Allocator = std::allocator<T>,
        typename = std::enable_if_t<
            std::is_same_v<Container<T, Allocator>, std::vector<T, Allocator>> ||
            std::is_same_v<Container<T, Allocator>, std::list<T, Allocator>>>>
    void print_ip(const Container<T, Allocator>& container)
    {
        auto ptr = std::begin(container);
        std::cout << *ptr;
        while (++ptr != std::end(container))
        {
            std::cout << "." << *ptr;
        }
        std::cout << std::endl;
    }

    template<typename... Ts>
    constexpr bool all_same = std::conjunction_v<std::is_same<Ts, typename std::tuple_element<0, std::tuple<Ts...>>::type>...>;

    /**
     * @brief Print tuple's elements as IP bytes.
     * @param tuple Tuple item types must be the same.
     * @return
     */
    template<typename... Ts>
    std::enable_if_t<all_same<Ts...>>
    print_ip(const std::tuple<Ts...>& tuple)
    {
        std::apply([](const auto&... args)
            {
                std::size_t n{ 0 };
                ((std::cout << args << (++n != sizeof...(Ts) ? "." : "")), ...);
            }, tuple);
        std::cout << std::endl;
    }
}
