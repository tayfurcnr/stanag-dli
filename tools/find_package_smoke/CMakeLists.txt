cmake_minimum_required(VERSION 3.10)
project(dli-find-package-smoke LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(dli REQUIRED CONFIG)

add_executable(dli_find_package_smoke main.cpp)
target_link_libraries(dli_find_package_smoke PRIVATE dli::dli)
