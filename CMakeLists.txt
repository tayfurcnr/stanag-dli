cmake_minimum_required(VERSION 3.10)
project(dli-sdk VERSION 2.0.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

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

add_library(dli::dli ALIAS dli)

target_include_directories(dli PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/idl/cpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
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
    set_tests_properties(TransportTest PROPERTIES LABELS "integration;host_only")

    # Session Test
    add_executable(session_test idl/cpp/tests/session_test.cpp)
    target_link_libraries(session_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME SessionTest COMMAND session_test)
    set_tests_properties(SessionTest PROPERTIES LABELS "unit")
    
    # Protocol Round-trip Test
    add_executable(protocol_test idl/cpp/tests/protocol_test.cpp)
    target_link_libraries(protocol_test PRIVATE dli GTest::gtest GTest::gtest_main pthread)
    add_test(NAME ProtocolTest COMMAND protocol_test)
    set_tests_properties(ProtocolTest PROPERTIES LABELS "unit")
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
install(
    TARGETS dli
    EXPORT dliTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
    DIRECTORY idl/cpp/dli/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dli
    FILES_MATCHING
    PATTERN "*.hpp"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dliConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dliConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/dliConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dli
)

install(
    EXPORT dliTargets
    FILE dliTargets.cmake
    NAMESPACE dli::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dli
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dliConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dliConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dli
)
