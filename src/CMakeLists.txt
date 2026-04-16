add_library(vector_lib
        vector.c
        real_type.c
        int_type.c
        complex_type.c
)

target_include_directories(vector_lib PUBLIC .)

add_executable(vector_app main.c)

target_link_libraries(vector_app vector_lib)