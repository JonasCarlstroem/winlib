cmake_minimum_required(VERSION 3.28.0)

project(winLib
		VERSION 1.0.0
		LANGUAGES CXX)

add_subdirectory(nativelib)
add_subdirectory(componentlib)
add_subdirectory(utilitylib)

add_library(winLib INTERFACE winlib.h)

target_compile_features(winLib INTERFACE cxx_std_17)

include(GNUInstallDirs)

target_link_libraries(winLib
		INTERFACE natlib::nativeLib
		INTERFACE util::utilityLib
		INTERFACE comp::componentLib
)

target_link_libraries(componentLib
		INTERFACE natlib::nativeLib
		INTERFACE util::utilityLib
)

target_include_directories(winLib
	INTERFACE $<BUILD_INTERFACE:${CMAKGE_CURRENT_SOURCE_DIR}/include>
			  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS winLib EXPORT winLib-config)

install(
	EXPORT winLib-config
	NAMESPACE winlib::
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cmake/winlib
)

install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/winlib
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/winlib
)