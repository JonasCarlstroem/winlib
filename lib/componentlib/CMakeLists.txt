cmake_minimum_required(VERSION 3.28.0)

project(componentLib
		VERSION 1.0.0
		LANGUAGES CXX)

include("G:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(tinyxml2 CONFIG REQUIRED)

add_executable(generator "generator.cpp" "string_output.h")
set_property(TARGET generator PROPERTY CXX_STANDARD 17)
target_link_libraries(generator PRIVATE tinyxml2::tinyxml2)

set_target_properties(generator 
	PROPERTIES CMAKE_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(componentLib INTERFACE)
add_library(comp::componentLib ALIAS componentLib)

target_sources(componentLib PRIVATE src)

target_compile_features(componentLib INTERFACE cxx_std_17)

target_precompile_headers(componentLib INTERFACE pch.h)

include(GNUInstallDirs)

target_include_directories(componentLib
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bindings>
			  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS componentLib EXPORT componentLib-config)

install(
	EXPORT componentLib-config
	NAMESPACE comp::
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/componentlib
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/componentlib/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/componentlib
)