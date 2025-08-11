cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "4" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(print_ip
    main.cpp)

add_library(lib
    lib.cpp ip_printer.cpp)

set_target_properties(print_ip lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(print_ip PRIVATE
    lib
)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

