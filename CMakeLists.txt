cmake_minimum_required(VERSION 3.13)
project(DarkOrbit VERSION 0.1.0)

find_package(sfml   REQUIRED COMPONENTS Graphics)
find_package(spdlog REQUIRED)

add_executable(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-graphics
        spdlog::spdlog
)

if(CMAKE_CXX_COMPILER_ID IN_LIST "GNU;Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra
            $<$<NOT:$<STREQUAL:${CMAKE_CXX_SIMULATE_ID},MSVC>>:-pedantic-errors>
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /EHsc # Enable exception stack unwinding
    )
endif()

set(SOURCES
        src/main.cpp
        src/core/Constants.cpp
        src/core/Exception.cpp
        src/engine/ScreenManager.cpp
        src/engine/TextureManager.cpp
        src/game/Formulas.cpp
        src/screens/SpaceMap.cpp
        src/utils/Factories.cpp
        src/utils/SfmlDebug.cpp
        src/utils/SfmlText.cpp
)
set(HEADERS
        src/core/Constants.hpp
        src/core/Exception.hpp
        src/engine/Screen.hpp
        src/engine/ScreenManager.hpp
        src/engine/TextureManager.hpp
        src/game/Formulas.hpp
        src/game/PlayerStats.hpp
        src/game/ShipStats.hpp
        src/screens/SpaceMap.hpp
        src/utils/Factories.hpp
        src/utils/SfmlDebug.hpp
        src/utils/SfmlText.hpp
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
