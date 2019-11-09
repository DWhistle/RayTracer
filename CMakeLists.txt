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

<<<<<<< HEAD
add_executable(RT
        srcs/main.c
        srcs/raymarching.c
=======
add_executable(rtv1
        srcs/add_func.c
        srcs/antialiasing.c
        srcs/cl_objects_converter.c
        srcs/cl_vector_converter.c
        srcs/converter.c
        srcs/converter_2.c
        srcs/converter_3.c
        srcs/converter_4.c
        srcs/converter_5.c
        srcs/converter_6.c
        srcs/converter_7.c
        srcs/effects.c
        srcs/ft_opencl_files.c
        srcs/ft_opencl_func.c
        srcs/ft_opencl_getters.c
        srcs/ft_opencl_params.c
        srcs/get_next_line.c
        srcs/len_obj.c
        srcs/len_obj_2.c
        srcs/len_obj_3.c
        srcs/len_obj_4.c
        srcs/light.c
        srcs/light_2.c
        srcs/light_3.c
        srcs/main.c
        srcs/parser.c
        srcs/parser_logic.c
        srcs/parser_utils.c
        srcs/quaternion_1.c
        srcs/quaternion_2.c
        srcs/ray_tracing.c
        srcs/raymarching.c
        srcs/raymarching_2.c
        srcs/raymarching_3.c
        srcs/reflaction.c
        srcs/render_effects.c
        srcs/transparency.c
        srcs/vec_math.c
>>>>>>> 8bbe9fa77796456c4316ca7118d8538ad98f2680
        srcs/vec_mul.c
        srcs/vec_mul_2.c
        srcs/vec_sum.c
        srcs/vector.c
<<<<<<< HEAD
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
=======
>>>>>>> 8bbe9fa77796456c4316ca7118d8538ad98f2680
        )