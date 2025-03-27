# CMakeList.txt : CMake project for win-main, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.28.0)

project (win-main
		 VERSION 1.0.0
		 LANGUAGES CXX)

set(CMAKE_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED True)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(lib)

add_executable (win-main WIN32 win-main.cpp)

target_link_libraries(win-main
		PUBLIC winLib
)

target_include_directories(win-main 
		PUBLIC "${PROJECT_BINARY_DIR}"
			   "${PROJECT_SOURCE_DIR}/lib"
)