cmake_minimum_required(VERSION 3.14)

project(AbstractClassMockDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

# Produktionscode als Bibliothek, damit Anwendung und Tests ihn gemeinsam nutzen
add_library(core STATIC
	source/report_generator.cpp
	source/csv_report_generator.cpp
)
target_include_directories(core PUBLIC source)

add_executable(AbstractClassMockDemo source/main.cpp)
target_link_libraries(AbstractClassMockDemo PRIVATE core)

# Tests
add_subdirectory(tests)
