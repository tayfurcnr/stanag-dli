cmake_minimum_required(VERSION 3.10)
project(dli-sdk VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# SDK Library Target (STATIC Core)
# -----------------------------------------------------------------------------
add_library(dli STATIC
    idl/cpp/dli/protocol/Dispatcher.cpp
    idl/cpp/dli/session/DliSession.cpp
    idl/cpp/dli/transport/MulticastTransport.cpp
)

target_include_directories(dli PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/idl/cpp>
    $<INSTALL_INTERFACE:include>
)

# -----------------------------------------------------------------------------
# Find Dependencies (e.g., GTest for tests)
# -----------------------------------------------------------------------------
option(DLI_BUILD_TESTS "Build SDK unit tests" ON)

if(DLI_BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    # Transport Test
    add_executable(transport_test idl/cpp/tests/transport_test.cpp)
    target_link_libraries(transport_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME TransportTest COMMAND transport_test)

    # Session Test
    add_executable(session_test idl/cpp/tests/session_test.cpp)
    target_link_libraries(session_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME SessionTest COMMAND session_test)
    
    # Protocol Round-trip Test
    add_executable(protocol_test idl/cpp/tests/protocol_test.cpp)
    target_link_libraries(protocol_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME ProtocolTest COMMAND protocol_test)
endif()

# -----------------------------------------------------------------------------
# Examples (External to Core SDK)
# -----------------------------------------------------------------------------

# Multicast Bridge (Reference Implementation)
add_executable(multicast_bridge idl/cpp/examples/multicast_bridge.cpp)
target_link_libraries(multicast_bridge PRIVATE dli pthread)

# Profile Conformance Example
add_executable(profile_test idl/cpp/examples/profile_test.cpp)
target_link_libraries(profile_test PRIVATE dli)

# -----------------------------------------------------------------------------
# Installation (Professional SDK Structure)
# -----------------------------------------------------------------------------
install(TARGETS dli DESTINATION lib)
install(DIRECTORY idl/cpp/dli DESTINATION include)
