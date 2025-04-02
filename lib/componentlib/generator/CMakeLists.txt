cmake_minimum_required(VERSION 3.28.0)

project(generator
		VERSION 1.0.0
		LANGUAGES CXX)

include("G:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(tinyxml2 CONFIG REQUIRED)

add_executable(generator "generator.cpp" "string_output.h" "parser.cpp")
set_property(TARGET generator PROPERTY CXX_STANDARD 17)
target_link_libraries(generator PRIVATE tinyxml2::tinyxml2)