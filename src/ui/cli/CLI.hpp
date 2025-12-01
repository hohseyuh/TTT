#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <chrono>

#include "game/Board.hpp"
#include "game/Rules.hpp"

#include "agents/Agent.hpp"
#include "agents/RandomAgent.hpp"
#include "agents/MinimaxAgent.hpp"
#include "agents/AlphaBetaAgent.hpp"
#include "agents/DepthAgent.hpp"

using namespace std;

namespace ui {

    class CLI {
        Board board;

        unique_ptr<Agent> playerX;
        unique_ptr<Agent> playerO;

        bool showStats;

    public:
        CLI();
        void run();

    private:
        // Menus
        int showMainMenu();
        void configure();
        void playGame();
        void benchmark();
        void help();

        // Agent selection
        unique_ptr<Agent> chooseAgent();
        void warnIfSlow(const string& name);

        // Board and move handling
        void printBoard() const;
        game::Move readHumanMove();

        // Statistics
        void printStats(const Agent* agent) const;

        // Input utility
        int readInt(int min, int max);
    };

}