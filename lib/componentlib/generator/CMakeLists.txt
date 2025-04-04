cmake_minimum_required(VERSION 3.28.0)

project(generator
		VERSION 1.0.0
		LANGUAGES CXX)

include("G:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(tinyxml2 CONFIG REQUIRED)

set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/xerces-c/cmake")

find_package(XercesC CONFIG REQUIRED)

include_directories(${XercesC_INCLUDE_DIRS})

add_executable(generator "generator.h" "string_output.h" "parser.h" "main.cpp" "validator.h" "xml_char_map.h" "types.h" "utils.h" "xsd_schema.h")
set_property(TARGET generator PROPERTY CXX_STANDARD 17)

target_link_libraries(generator 
					PRIVATE tinyxml2::tinyxml2
					${XercesC_LIBRARIES}
)