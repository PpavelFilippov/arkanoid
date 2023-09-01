cmake_minimum_required(VERSION 3.25)
project(arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_CXX_STANDARD 17)
include_directories(D:\\JetBrains\\CLionProjects\\arkanoid\\include)
include_directories(D:\\JetBrains\\CLionProjects\\arkanoid\\source)
add_executable(arkanoid
        source/main.cpp
        source/Game.cpp
        include/Game.h
        source/Ball.cpp
        source/Block.cpp
        source/Bonus.cpp
        include/Bonus.h
        include/GameObjects.h
        source/Interactions.cpp
        source/Object.cpp
        include/Object.h
        source/Builder.cpp
        include/Builder.h
        source/Initializer.cpp
        include/Initializer.h
        source/Paddle.cpp
        include/Preference.h
        source/Interface.cpp
        include/Interface.h)

set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")

target_link_libraries(arkanoid sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)