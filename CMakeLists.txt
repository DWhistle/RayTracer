cmake_minimum_required(VERSION 3.13)
project(rtv1)

set(CMAKE_CXX_STANDARD 14)
include_directories(incs)
include_directories(libs/libft)
include_directories(libs/SDL2/include)
include_directories(srcs)
find_library(GL_LIB GL
        PATH
        /)
find_library(SDL_LIB SDL2
        PATH
        libs/SDL2/lib)
find_library(FT_LIB ft
        PATH
        libs/libft)

add_compile_options(-Wall -Wextra -Werror)
link_libraries(${SDL_LIB} ${FT_LIB})

add_executable(rtv1
        main.c)