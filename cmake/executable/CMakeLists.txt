cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall)
# 把 build/ 目录添加进模块搜索路径, 以支持 find_package 直接从 build/ 能查找成功
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

option(BUILD_TESTS "build unit tests" OFF)
option(BUILD_BENCHMARKS "build benchmarks" OFF)

find_package(spdlog REQUIRED)

set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set(PRIVATE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# XXX: CHANGE ME
project(demo VERSION "0.0.1")
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCS)
add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})

set(COMMON_LINK_LIBRARIES
    spdlog::spdlog
)
target_link_libraries(${PROJECT_NAME} ${COMMON_LINK_LIBRARIES})

# 以下用于单元测试和性能测试
# usage: add_unit_test(test_xxx, src0, src1, ...)
macro(add_unit_test name)
    set(sources ${ARGN})
    set(prefixed_sources)
    # 遍历每个源文件，并添加前缀路径
    foreach(source IN LISTS sources)
        list(APPEND prefixed_sources ${CMAKE_CURRENT_SOURCE_DIR}/${source})
    endforeach()
    message(STATUS "add_unit_test(${name} ${prefixed_sources})")

    add_executable(${name} ${prefixed_sources})
    target_include_directories(${name} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(
        ${name}
        GTest::gtest
        GTest::gtest_main
        spdlog::spdlog
    )
    # 添加到 ctest 数据库, cd build/ && ctest 能直接全部运行
    gtest_discover_tests(${name})
endmacro()

if(BUILD_TESTS)
    find_package(GTest REQUIRED) # 内置支持, 不需要指定 conan 依赖
    enable_testing()
    include(GoogleTest)
    # 此处添加单元测试
    add_unit_test(test_demo tests/demo.cpp)
endif()

macro(add_benchmark name)
    set(sources ${ARGN})
    set(prefixed_sources)
    # 遍历每个源文件，并添加前缀路径
    foreach(source IN LISTS sources)
        list(APPEND prefixed_sources ${CMAKE_CURRENT_SOURCE_DIR}/${source})
    endforeach()
    message(STATUS "add_benchmark(${name} ${prefixed_sources})")

    add_executable(${name} ${prefixed_sources})
    target_include_directories(${name}
        PRIVATE ${COMMON_INCLUDE_DIRS}
        #PRIVATE ${GTest_INCLUDE_DIR}
    )
    target_link_libraries(
        ${name}
        benchmark::benchmark
        spdlog::spdlog
    )
endmacro()

if(BUILD_BENCHMARKS)
    find_package(benchmark REQUIRED)
    add_benchmark(benchmark_demo benchmarks/demo.cpp)
endif()
