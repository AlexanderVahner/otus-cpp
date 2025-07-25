cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "3" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(custom_allocator VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(custom_allocator
    main.cpp)

add_library(lib
    lib.cpp
    HwAllocator.cpp
    Sequence.cpp)

set_target_properties(custom_allocator lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(custom_allocator PRIVATE
    lib
)

# if (MSVC)
#     target_compile_options(custom_allocator PRIVATE
#         /W4
#     )
#     target_compile_options(lib PRIVATE
#         /W4
#     )
# else ()
#     target_compile_options(custom_allocator PRIVATE
#         -Wall -Wextra -pedantic -Werror
#     )
#     target_compile_options(lib PRIVATE
#         -Wall -Wextra -pedantic -Werror
#     )
# endif()

install(TARGETS custom_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

