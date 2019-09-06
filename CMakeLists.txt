cmake_minimum_required(VERSION 3.13)
project(RT)

set(CMAKE_CXX_STANDARD 14)
include_directories(incs)
include_directories(libs/libft)
include_directories(libs/SDL2/include)

find_library(GL_LIB GL
        PATH
        /)

find_library(CL_LIB OpenCL
        PATH
        /)

find_library(SDL_LIB SDL2
        PATH
        libs/SDL2/lib)

find_library(FT_LIB ft
        PATH
        libs/libft)

find_library(UI_LIB ui
        PATH
        libs/libui)

add_compile_options(-Wall -Wextra -Werror)
link_libraries(${SDL_LIB} ${FT_LIB} ${CL_LIB} ${UI_LIB})

add_executable(RT
        srcs/main.c
        srcs/raymarching.c
        srcs/vec_mul.c
        srcs/vec_sum.c
        srcs/vector.c
        srcs/ray_tracing.c
        srcs/antialiasing.c
        srcs/len_obj.c
        srcs/ft_opencl_files.c
        srcs/ft_opencl_func.c
        srcs/ft_opencl_params.c
        srcs/quaternion_1.c
        srcs/quaternion_2.c
        srcs/light.c
        srcs/reflaction.c
        srcs/transparency.c
        srcs/parser.c
        srcs/parser_logic.c
        srcs/parser_utils.c
        srcs/vec_math.c
        srcs/get_next_line.c
        srcs/cl_objects_converter.c
        srcs/converter.c
        )