cmake_minimum_required(VERSION 3.28.0)

project(utilityLib
		VERSION 1.0.0
		LANGUAGES CXX)

add_library(utilityLib INTERFACE)
add_library(util::utilityLib ALIAS utilityLib)

target_sources(utilityLib PRIVATE src)

target_compile_features(utilityLib INTERFACE cxx_std_17)

target_precompile_headers(utilityLib INTERFACE pch.h)

include(GNUInstallDirs)

target_include_directories(utilityLib
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS utilityLib EXPORT utilityLib-config)

install(
	EXPORT utilityLib-config
	NAMESPACE util::
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/utilitylib
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/utilitylib/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/utilitylib
)