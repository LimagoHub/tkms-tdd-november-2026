cmake_minimum_required(VERSION 3.14)

# Abhaengigkeiten: googletest/googlemock liegen lokal in tests/google (kein Internet noetig)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows/MSVC: gleiche CRT wie das Projekt
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(google)

foreach(dep gtest gmock gtest_main gmock_main)
	set_target_properties(${dep} PROPERTIES FOLDER Dependencies)
endforeach()

add_executable(SchweinProjectTest test.cpp
        tiere/SchweinTest.h
		tiere/SchweinTest.cpp
		services/MyServiceUsingDependencyTest.cpp
		services/MyServiceUsingDependencyTest.h)
target_link_libraries(SchweinProjectTest PRIVATE core GTest::gtest_main GTest::gmock)

# Jeder TEST() erscheint einzeln in ctest und in der IDE
include(GoogleTest)
gtest_discover_tests(SchweinProjectTest)

set_target_properties(SchweinProjectTest PROPERTIES FOLDER Tests)
