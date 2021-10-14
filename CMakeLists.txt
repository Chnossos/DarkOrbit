cmake_minimum_required(VERSION 3.13)
project(DarkOrbit)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "Missing ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake, run conan install first")
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    set(CONAN_SYSTEM_INCLUDES ON)
    conan_basic_setup(TARGETS)
endif()

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_EXTENSIONS OFF
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
conan_target_link_libraries(${PROJECT_NAME})
