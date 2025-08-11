#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <type_traits>

namespace ip_printer 
{
    /// <summary>
    /// Print IP as string with no changes.
    /// </summary>
    /// <typeparam name="T">Must be std::string.</typeparam>
    /// <param name="str">Value.</param>
    /// <returns></returns>
    template<typename T>
    typename std::enable_if<std::is_same_v<T, std::string>>::type
    print_ip(const T str)
    {
        std::cout << str << std::endl;
    }

    /// <summary>
    /// Print IP as bytes of integer value.
    /// </summary>
    /// <typeparam name="Integer">Must be integer.</typeparam>
    /// <param name="intValue">Value</param>
    /// <returns></returns>
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

    template <typename T, typename = void>
    struct is_container : std::false_type {};

    template <typename T>
    struct is_container<T, decltype(void(std::begin(std::declval<T>())))> : std::true_type {};

    /// <summary>
    /// Print container's elements as IP bytes.
    /// </summary>
    /// <typeparam name="Container">Container.</typeparam>
    /// <param name="container">Value</param>
    /// <returns></returns>
    template<typename Container>
    typename std::enable_if<is_container<Container>::value>::type
    print_ip(Container& container)
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

    /// <summary>
    /// Print tuple's elements as IP bytes.
    /// </summary>
    /// <typeparam name="...Ts">Tuple item types must be the same.</typeparam>
    /// <param name="tuple">Tuple</param>
    /// <returns></returns>
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
