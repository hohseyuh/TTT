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
include_directories(src)


# ============================================
# Game Library
# ============================================
add_library(game
        src/game/Board.cpp
        src/game/KDetector.cpp
        src/game/Rules.cpp
)

target_include_directories(game PUBLIC src)


# ============================================
# Search Library
# ============================================
add_library(search
        src/search/minimax.cpp
        src/search/alphaBeta.cpp
        src/search/depthLimited.cpp
        src/search/heuristics.cpp
        src/search/moveOrdering.cpp
)

target_include_directories(search PUBLIC src)
target_link_libraries(search PUBLIC game)


# ============================================
# Agents Library
# ============================================
add_library(agents
        src/agents/minimaxAgent.cpp
        src/agents/alphaBetaAgent.cpp
        src/agents/depthAgent.cpp
)

target_include_directories(agents PUBLIC src)
target_link_libraries(agents PUBLIC game search)


# ============================================
# CLI UI Library
# ============================================
add_library(ui_cli
        src/ui/cli/CLI.cpp
)

target_include_directories(ui_cli PUBLIC src)
target_link_libraries(ui_cli PUBLIC game search agents)


# ============================================
# Main Executable
# ============================================
add_executable(gt_main
        src/main.cpp
)

target_link_libraries(gt_main PRIVATE
        game
        search
        agents
        ui_cli
)
