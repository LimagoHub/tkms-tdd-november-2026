cmake_minimum_required(VERSION 3.14)

project(SchweinProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

# Produktionscode als Bibliothek, damit Anwendung und Tests ihn gemeinsam nutzen
add_library(core STATIC
	source/greeting.cpp
		source/tiere/Schwein.h
		source/services/IDependency.h
		source/services/Dependency.h
		source/services/MyServiceUsingDependency.h
		source/services/ToDelete.h
)
target_include_directories(core PUBLIC source)

add_executable(SchweinProject source/main.cpp)
target_link_libraries(SchweinProject PRIVATE core)

# Tests
add_subdirectory(tests)
