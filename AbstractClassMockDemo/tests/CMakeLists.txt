cmake_minimum_required(VERSION 3.14)

# Abhaengigkeiten: googletest/googlemock liegen lokal in tests/google (kein Internet noetig)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows/MSVC: gleiche CRT wie das Projekt
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(google)

foreach(dep gtest gmock gtest_main gmock_main)
	set_target_properties(${dep} PROPERTIES FOLDER Dependencies)
endforeach()

add_executable(AbstractClassMockDemoTest report_generator_test.cpp)
target_link_libraries(AbstractClassMockDemoTest PRIVATE core GTest::gtest_main GTest::gmock)

# Jeder TEST() erscheint einzeln in ctest und in der IDE
include(GoogleTest)
gtest_discover_tests(AbstractClassMockDemoTest)

set_target_properties(AbstractClassMockDemoTest PROPERTIES FOLDER Tests)
