cmake_minimum_required(VERSION 3.28.0)

project(controlLib
		VERSION 1.0.0
		LANGUAGES CXX)

add_library(controlLib INTERFACE)
add_library(ctrl::controlLib ALIAS controlLib)

target_sources(controlLib PRIVATE src)

target_compile_features(controlLib INTERFACE cxx_std_17)

target_precompile_headers(controlLib INTERFACE pch.h)

include(GNUInstallDirs)

target_include_directories(controlLib
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS controlLib EXPORT controlLib-config)

install(
	EXPORT controlLib-config
	NAMESPACE ctrl::
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/controllib
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/controllib/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/controllib
)