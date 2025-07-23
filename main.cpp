#include <map>
#include "HwAllocator.cpp"
#include "Sequence.cpp"

int factorial(int n)
{
    if(n < 0) return 0;
    if(n == 0) return 1;
    return n * factorial(n - 1);
}

template <typename TCompare, typename TAlloc>
void fill_map(std::map<int, int, TCompare, TAlloc>& map)
{
    for (int i = 0; i < 10; i++)
    {
        map[i] = factorial(i);
    }
}

template <typename TCompare, typename TAlloc>
void print_map(std::map<int, int, TCompare, TAlloc>& map)
{
    for (const auto& [key, value] : map)
    {
        std::cout << key << " " << value << std::endl;
    }
}

template <typename TAlloc>
void fill_seq(Sequence<int, TAlloc>& seq)
{
    for (int i = 0; i < 10; i++)
    {
        seq.append(i);
    }
}

template <typename TAlloc>
void print_seq(Sequence<int, TAlloc>& seq)
{
    seq.seek_start();
    while(auto item = seq.next())
    {
        std::cout << *item << std::endl;
    }
}

void print_line(const char* line = nullptr)
{
    if (line)
        std::cout << line;
    std::cout << std::endl;
}

int main(int, char const**)
{

    try
    {

        {
            print_line("==================== MALLOC MAP ====================");
            std::map<int, int> malloc_map;

            print_line("Adding elements to malloc map...");
            fill_map(malloc_map);

            print_line();
            print_line("Result is:");
            print_map(malloc_map);

            print_line();
            print_line("==================== CUSTOM ALLOC MAP ====================");

            std::map<int, int, std::less<int>, HwAllocator<int>> custom_alloc_map;

            print_line("Adding elements to HwAllocator map...");
            fill_map(custom_alloc_map);

            print_line();
            print_line("Result is:");
            print_map(malloc_map);
        }

        {
            print_line();
            print_line("==================== MALLOC SEQ ====================");

            Sequence<int> malloc_seq;

            print_line("Adding elements to malloc Sequence...");
            fill_seq(malloc_seq);

            print_line();
            print_line("Result is:");
            print_seq(malloc_seq);

            print_line();
            print_line("==================== CUSTOM ALLOC SEQ ====================");

            Sequence<int, HwAllocator<int>> custom_alloc_seq;

            print_line("Adding elements to malloc map...");
            print_line("Adding elements to HwAllocator Sequence...");
            fill_seq(custom_alloc_seq);

            print_line();
            print_line("Result is:");
            print_seq(custom_alloc_seq);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


