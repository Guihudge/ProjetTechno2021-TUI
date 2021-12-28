cmake_minimum_required(VERSION 3.0)

project(Stack C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall")

add_library(stack stack.c)

add_executable(stack_test stack_test.c)

target_link_libraries(stack_test stack)

add_test(stack_test_new_empty ./stack_test stack_new_empty)
add_test(stack_test_is_empty ./stack_test stack_is_empty)
add_test(stack_test_push_head ./stack_test stack_push_head)
add_test(stack_test_pop_head ./stack_test stack_pop_head)
add_test(stack_test_peek_head ./stack_test stack_peek_head)
add_test(stack_test_clear ./stack_test stack_clear)
add_test(stack_test_free ./stack_test stack_free)