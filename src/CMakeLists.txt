cmake_minimum_required(VERSION 3.16)
project(GeneralizedTicTacToe LANGUAGES CXX)

# ============================================
# Global Compiler Settings
# ============================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Top-level include folder
include_directories(.)


# ============================================
# Game Library
# ============================================
add_library(game
        game/Board.cpp
        game/KDetector.cpp
        game/Rules.cpp
)

target_include_directories(game PUBLIC .)


# ============================================
# Search Library
# ============================================
add_library(search
        search/Minimax.cpp
        search/AlphaBeta.cpp
        search/DepthLimited.cpp
        search/Heuristics.cpp
        search/MoveOrdering.cpp
)

target_include_directories(search PUBLIC .)
target_link_libraries(search PUBLIC game)


# ============================================
# Agents Library
# ============================================
add_library(agents
        agents/MinimaxAgent.cpp
        agents/AlphaBetaAgent.cpp
        agents/DepthAgent.cpp
)

target_include_directories(agents PUBLIC .)
target_link_libraries(agents PUBLIC game search)


# ============================================
# CLI UI Library
# ============================================
add_library(ui_cli
        ui/cli/CLI.cpp
)

target_include_directories(ui_cli PUBLIC .)
target_link_libraries(ui_cli PUBLIC game search agents)


# ============================================
# Main Executable
# ============================================
add_executable(gt_main
        main.cpp
)

target_link_libraries(gt_main PRIVATE
        game
        search
        agents
        ui_cli
)
