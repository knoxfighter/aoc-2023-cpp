CMAKE_MINIMUM_REQUIRED(VERSION 3.26)
PROJECT(aoc_2023_cpp CXX)

#set(CMAKE_CXX_STANDARD 23)

FIND_PACKAGE(magic_enum CONFIG REQUIRED)
FIND_PACKAGE(nlohmann_json CONFIG REQUIRED)
FIND_PACKAGE(CURL REQUIRED)
FIND_PACKAGE(GTest CONFIG REQUIRED)

INCLUDE(GoogleTest)

ADD_EXECUTABLE(aoc_2023_cpp)

# Use -MT / -MTd runtime library (ignored on non-windows)
SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

ADD_COMPILE_DEFINITIONS(
		MAGIC_ENUM_RANGE_MAX=256
)

TARGET_SOURCES(${PROJECT_NAME} INTERFACE
		FILE_SET HEADERS
		FILES
)

TARGET_SOURCES(${PROJECT_NAME}
		PRIVATE
		day1.cpp
		day2.cpp
)

TARGET_COMPILE_FEATURES(${PROJECT_NAME} PUBLIC cxx_std_23)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE magic_enum::magic_enum)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE CURL::libcurl)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE GTest::gtest_main)

GTEST_DISCOVER_TESTS(${PROJECT_NAME})

TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC TEST_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/test/\")
