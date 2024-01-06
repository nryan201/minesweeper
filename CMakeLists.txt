cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp
        Game.cpp
        "Header File/Game.h"
        States/State.cpp
        "States/State.h"
        States/GameState.cpp
        States/GameState.h
        States/GameState.cpp
        Entity/Entity.cpp
        Entity/Entity.h
        States/MainMenuState.cpp
        States/MainMenuState.h
        "RessourceFile/Gui.cpp"
        Entity/Player.h
        Entity/Player.cpp
        Component/MouvementComponent.h
        Component/MouvementComponent.cpp
        Component/AnimationComponent.h
        Component/AnimationComponent.cpp
        States/EditorState.h
        States/EditorState.h
        States/EditorState.cpp
        Component/HitboxComponent.h
        Component/HitboxComponent.cpp
        Tile/Tile.cpp
        Tile/Tile.h
        GUI/PauseMenu.h
        GUI/PauseMenu.cpp
        States/SettingState.cpp
        States/SettingState.h
        States/SettingState.h
        Map/TileMap.cpp
        Map/TileMap.h
        Map/TileMap.h
        pch.h
        pch.cpp
        RessourceFile/GraphicSettings.cpp
        RessourceFile/GraphicSettings.h)

target_precompile_headers(minesweeper PRIVATE "pch.h")

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/nedye/CLionProjects/untitled9/SFML/include/SFML)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)