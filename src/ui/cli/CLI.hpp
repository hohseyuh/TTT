#pragma once
#include "../../agents/agent.hpp"
#include <memory>

namespace ui {
    class CLI {
    public:
        CLI();

        // Run the interactive loop
        void run();

    private:
        void printBoard(const Board& board) const;
        Move readHumanMove(const Board& board) const;

        void playHumanVsAI();
        void playAIVsHuman();
        void playAIVsAI();

        // Helper: choose an agent type for AI
        unique_ptr<agents::Agent> selectAgent(int m) const;

        void waitForEnter() const;
    };
}
