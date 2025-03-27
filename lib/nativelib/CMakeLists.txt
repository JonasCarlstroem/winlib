cmake_minimum_required(VERSION 3.8)

project(nativeLib
		VERSION 1.0.0
		LANGUAGES CXX)

add_library(nativeLib INTERFACE)
add_library(natlib::nativeLib ALIAS nativeLib)

target_sources(nativeLib PRIVATE src)

target_compile_features(nativeLib INTERFACE cxx_std_17)

target_precompile_headers(nativeLib INTERFACE pch.h)

include(GNUInstallDirs)

target_include_directories(nativeLib
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS nativeLib EXPORT nativeLib-config)

install(
	EXPORT nativeLib-config
	NAMESPACE nat::
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/nativelib
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/nativelib/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nativelib
)