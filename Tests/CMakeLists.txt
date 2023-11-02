#cmake_minimum_required(VERSION 3.24)
project(Tests)


add_executable(Tests
#	TEST FILES
	LCA.cc

#	MVC OBJECTS
	../src/lca/lca.cpp
	../src/Model/Tree.cpp
	../src/Model/Node.cpp
	../src/Model/Trunk.cpp
        )


################################
# Property
################################
# Files to clean
set_property(
        DIRECTORY ${CMAKE_BINARY_DIR}
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES Tests
)

################################
# GTest
################################
ADD_SUBDIRECTORY(Google_tests)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
################################
# Unit test
################################
target_link_libraries(Tests gtest gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(Tests)
