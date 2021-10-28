cmake_minimum_required(VERSION 3.13)
project(DarkOrbit)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "Missing ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake, run conan install first")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CONAN_SYSTEM_INCLUDES ON)
conan_basic_setup(TARGETS)

set(SOURCES src/main.cpp
        src/core/Constants.cpp
        src/core/Exception.cpp
        src/engine/ScreenManager.cpp
        src/engine/TextureManager.cpp
        src/screens/SpaceMap.cpp
)
set(HEADERS
        src/core/Constants.hpp
        src/core/Exception.hpp
        src/engine/Screen.hpp
        src/engine/ScreenManager.hpp
        src/engine/TextureManager.hpp
        src/screens/SpaceMap.hpp
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
conan_target_link_libraries(${PROJECT_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()
