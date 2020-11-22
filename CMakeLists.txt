cmake_minimum_required(VERSION 3.17)
project(ft_ls C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
include_directories(libft)
include_directories(libft/inc)
include_directories(libft/libft)
include_directories(libft/printf)

add_executable(ft_ls
		inc/ft_ls.h
		add_func.c
		checks.c
		main.c
		parse.c
		prints.c
		sort.c)

add_subdirectory(libft)
target_link_libraries(ft_ls libft)