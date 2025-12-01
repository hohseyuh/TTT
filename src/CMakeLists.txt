# src/CMakeLists.txt

# -----------------------------
# Game Library
# -----------------------------
add_library(game
    game/Board.cpp
    game/KDetector.cpp
    game/Rules.cpp
)

target_include_directories(game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# -----------------------------
# Search Library
# -----------------------------
add_library(search
    search/Minimax.cpp
    search/AlphaBeta.cpp
    search/DepthLimited.cpp
    search/Heuristics.cpp
    search/MoveOrdering.cpp
)

target_include_directories(search PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(search PUBLIC game)

# -----------------------------
# Agents Library
# -----------------------------
add_library(agents
    agents/RandomAgent.cpp
    agents/MinimaxAgent.cpp
    agents/AlphaBetaAgent.cpp
    agents/DepthAgent.cpp
)

target_include_directories(agents PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(agents PUBLIC game search)

# -----------------------------
# CLI Library
# -----------------------------
add_library(ui_cli
    ui/cli/CLI.cpp
)

target_include_directories(ui_cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui_cli PUBLIC game search agents)

# -----------------------------
# Main Executable
# -----------------------------
add_executable(gt_main
    main.cpp
)

target_link_libraries(gt_main PRIVATE
    game search agents ui_cli
)
