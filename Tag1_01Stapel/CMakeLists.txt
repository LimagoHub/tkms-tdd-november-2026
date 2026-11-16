cmake_minimum_required(VERSION 3.14)

project(StapelProjekt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

# Produktionscode als Bibliothek, damit Anwendung und Tests ihn gemeinsam nutzen
add_library(core STATIC
	source/greeting.cpp
	source/collections/Stapel.cpp
)
target_include_directories(core PUBLIC source)
if(MSVC)
	target_compile_options(core PRIVATE /W4)
else()
	target_compile_options(core PRIVATE -Wall -Wextra)
endif()

add_executable(StapelProjekt source/main.cpp
		source/collections/WagnerStack.h)
target_link_libraries(StapelProjekt PRIVATE core)

# Tests
add_subdirectory(tests)
