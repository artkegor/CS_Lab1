include_directories(../src)

add_executable(test_vector
        test_vector.c
)

target_link_libraries(test_vector vector_lib)

add_test(NAME vector_tests COMMAND test_vector)