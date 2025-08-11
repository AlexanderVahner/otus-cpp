#include "ip_printer.cpp"
using namespace ip_printer;

int main(int, char const**)
{
    print_ip(int8_t{ -1 }); // 255 
    print_ip(int16_t{ 0 }); // 0.0 
    print_ip(int32_t{ 2130706433 }); // 127.0.0.1 
    print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41 
    print_ip(std::string{ "Hello, World!" }); // Hello, World! 
    print_ip(std::vector<int>{ 100, 200, 300, 400 }); // 100.200.300.400 
    print_ip(std::list<short>{ 400, 300, 200, 100 }); // 400.300.200.100 
    print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0

    return 0;
}

/*

  Добавить в пайплайн сборки на Github Actions вызов `doxygen` и публикацию html-версии документации на github-pages. Пара инструкций по тому, как это можно сделать:
  1. <https://ntamonsec.blogspot.com/2020/06/github-actions-doxygen-documentation.html>
  2. <https://dev.to/denvercoder1/using-github-actions-to-publish-doxygen-docs-to-github-pages-177g>
  3. <https://wiki.jlab.org/epsciwiki/images/a/aa/HostingDocsOnGithub.pdf>

  Включить в репозиторий файл `Doxyfile` с включенными опциями `HAVE_DOT` и `EXTRACT_ALL`.
*/
