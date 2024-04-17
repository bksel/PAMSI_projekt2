cmake_minimum_required(VERSION 3.27)
project(miniprojekt2)



add_compile_options(
        -std=gnu++23
        -Wall
        -Wextra
        -pedantic
        -Werror=return-type
        -Werror=parentheses
        -Werror=vla
        -Werror=array-bounds
        -Wcast-qual
        -Wmaybe-uninitialized

#        -fmodules-ts


)




add_executable(miniprojekt2
        src/abstract_data_type/vector/vector.cpp


        main.cpp
        src/movie_entry/MovieEntry.h
        src/data_reader/DataReader.cpp
        src/data_reader/DataReader.h

        src/abstract_data_type/sorting_algorithms/bubble_sort.cpp
        src/abstract_data_type/sorting_algorithms/bubble_sort.cpp
        src/abstract_data_type/sorting_algorithms/merge_sort.cpp
        src/abstract_data_type/lib.h
        src/abstract_data_type/vector/print_inline.h
        src/abstract_data_type/vector/copy.h
        src/abstract_data_type/sorting_algorithms/sorting_utils.h
        src/abstract_data_type/vector/vector.h
        src/abstract_data_type/sorting_algorithms/merge_sort.h
        src/abstract_data_type/list/UnilateralList.h


)

find_package(fmt REQUIRED)
target_link_libraries(miniprojekt2 fmt::fmt)
#target_link_libraries(miniprojekt2 )