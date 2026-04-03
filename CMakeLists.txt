cmake_minimum_required(VERSION 3.10)
project(dli-sdk VERSION 1.6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# SDK Library Target (STATIC Core)
# -----------------------------------------------------------------------------
add_library(dli STATIC
    src/protocol/Dispatcher.cpp
    src/session/DliSession.cpp
)

target_include_directories(dli PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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
    add_executable(transport_test tests/transport_test.cpp examples/adapters/udp/UdpTransport.cpp)
    target_include_directories(transport_test PRIVATE examples/adapters/udp)
    target_link_libraries(transport_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME TransportTest COMMAND transport_test)

    # Session Test
    add_executable(session_test tests/session_test.cpp)
    target_link_libraries(session_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME SessionTest COMMAND session_test)
    
    # Protocol Round-trip Test
    add_executable(protocol_test tests/protocol_test.cpp)
    target_link_libraries(protocol_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME ProtocolTest COMMAND protocol_test)
endif()

# -----------------------------------------------------------------------------
# Examples & Adapters (External to Core SDK)
# -----------------------------------------------------------------------------

# UDP Adapter (Reference Implementation)
add_executable(multicast_bridge 
    examples/multicast_bridge.cpp 
    examples/adapters/udp/UdpTransport.cpp
)
target_include_directories(multicast_bridge PRIVATE examples/adapters/udp)
target_link_libraries(multicast_bridge PRIVATE dli pthread)

# Profile Conformance Example
add_executable(profile_test examples/profile_test.cpp)
target_link_libraries(profile_test PRIVATE dli)

# -----------------------------------------------------------------------------
# Installation (Professional SDK Structure)
# -----------------------------------------------------------------------------
install(TARGETS dli DESTINATION lib)
install(DIRECTORY include/dli DESTINATION include)
