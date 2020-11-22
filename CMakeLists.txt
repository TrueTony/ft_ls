cmake_minimum_required(VERSION 3.17)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

set(SRC
        main.c sort.c add_func.c parse.c checks.c prints.c)

add_executable(ft_ls
        ${SRC} )


add_subdirectory(libft)
target_link_libraries(ft_ls libft)