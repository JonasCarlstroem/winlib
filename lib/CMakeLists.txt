cmake_minimum_required(VERSION 3.28.0)

project(winLib
		VERSION 1.0.0
		LANGUAGES CXX)

include("G:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(tinyxml2 CONFIG REQUIRED)

add_executable(generator "gen/generator.cpp")
target_link_libraries(generator PRIVATE tinyxml2::tinyxml2)

add_subdirectory(nativelib)
add_subdirectory(controllib)
add_subdirectory(utilitylib)

add_library(winLib INTERFACE winlib.h)

target_compile_features(winLib INTERFACE cxx_std_17)

include(GNUInstallDirs)

target_link_libraries(winLib
		INTERFACE tinyxml2::tinyxml2
)

target_link_libraries(winLib
		INTERFACE natlib::nativeLib
		INTERFACE util::utilityLib
		INTERFACE ctrl::controlLib
		INTERFACE tinyxml2::tinyxml2
)

target_link_libraries(controlLib
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