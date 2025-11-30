#include "CLI.hpp"

#include "../../game/Rules.hpp"
#include "../../agents/minimaxAgent.hpp"
#include "../../agents/alphaBetaAgent.hpp"
#include "../../agents/depthAgent.hpp"

#include <iostream>
using namespace std;
using namespace game;
using namespace agents;

namespace ui {

CLI::CLI() {}

void CLI::printBoard(const Board& board) const {
    cout << "\nCurrent board:\n";
    cout << board.toString() << "\n\n";
}

game::Move CLI::readHumanMove(const Board& board) const {
    while (true) {
        cout << "Enter your move (row col): ";
        int r, c;
        cin >> r >> c;

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (!board.inBounds(r, c)) {
            cout << "Out of bounds. Try again.\n";
            continue;
        }

        if (!board.isEmpty(r, c)) {
            cout << "Cell not empty. Try again.\n";
            continue;
        }

        return {r, c};
    }
}

    std::unique_ptr<Agent> CLI::selectAgent(int m) const {
    cout << "Choose AI agent:\n";
    cout << "  1. Minimax (optimal 3x3)\n";
    cout << "  2. AlphaBeta (optimal 3x3)\n";
    cout << "  3. DepthLimited (recommended for m > 3)\n";

    while (true) {
        cout << "Selection (1/2/3): ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            if (m > 3) {
                cout << "\nWARNING: Minimax is computationally infeasible for m > 3.\n"
                     << "The AI may freeze, take extremely long, or fail to respond.\n\n";
            }
            return make_unique<MinimaxAgent>();
        }

        if (ch == 2) {
            if (m > 3) {
                cout << "\nWARNING: Alpha–Beta pruning is still infeasible for m > 3.\n"
                     << "Search tree size becomes astronomical. Use DepthLimited instead.\n\n";
            }
            return make_unique<AlphaBetaAgent>();
        }

        if (ch == 3) {
            cout << "Enter depth limit (>=1): ";
            int d;
            cin >> d;
            return make_unique<DepthAgent>(d);
        }

        cout << "Invalid selection. Try again.\n";
    }
}


void CLI::playHumanVsAI() {
    int m, k;
    cout << "Board size m: ";
    cin >> m;
    cout << "Win length k: ";
    cin >> k;

    Board board = Rules::initialState(m, k);

    cout << "\nYour mark is X by default (you move first).\n";

    auto ai = selectAgent(m);

    while (true) {
        printBoard(board);

        if (Rules::terminal(board)) break;

        // Human turn
        if (Rules::player(board) == 'X') {
            Move mv = readHumanMove(board);
            board = Rules::result(board, mv);
        }
        else {
            // AI turn
            cout << "AI thinking...\n";
            Move mv = ai->chooseMove(board);
            cout << "AI plays: " << mv.r << " " << mv.c << "\n";
            board = Rules::result(board, mv);
        }
    }

    printBoard(board);

    auto w = Rules::winner(board);
    if (w.has_value()) cout << "Winner: " << w.value() << "\n";
    else cout << "Result: Draw\n";
}

void CLI::playAIVsHuman() {
    int m, k;
    cout << "Board size m: ";
    cin >> m;
    cout << "Win length k: ";
    cin >> k;

    Board board = Rules::initialState(m, k);

    cout << "\nYour mark is O. AI (X) moves first.\n";

    auto ai = selectAgent(m);

    while (true) {
        printBoard(board);

        if (Rules::terminal(board)) break;

        if (Rules::player(board) == 'X') {
            cout << "AI thinking...\n";
            Move mv = ai->chooseMove(board);
            cout << "AI plays: " << mv.r << " " << mv.c << "\n";
            board = Rules::result(board, mv);
        }
        else {
            Move mv = readHumanMove(board);
            board = Rules::result(board, mv);
        }
    }

    printBoard(board);

    auto w = Rules::winner(board);
    if (w.has_value()) cout << "Winner: " << w.value() << "\n";
    else cout << "Result: Draw\n";
}

void CLI::playAIVsAI() {
    int m, k;
    cout << "Board size m: ";
    cin >> m;
    cout << "Win length k: ";
    cin >> k;

    Board board = Rules::initialState(m, k);

    cout << "\nSelect AI for X:\n";
    auto ax = selectAgent(m);

    cout << "\nSelect AI for O:\n";
    auto ao = selectAgent(m);

    while (true) {
        printBoard(board);
        if (Rules::terminal(board)) break;

        Agent* current = (Rules::player(board) == 'X') ? ax.get() : ao.get();

        cout << "AI (" << Rules::player(board) << ") thinking...\n";
        Move mv = current->chooseMove(board);

        cout << "AI plays: " << mv.r << " " << mv.c << "\n";
        board = Rules::result(board, mv);
    }

    printBoard(board);

    auto w = Rules::winner(board);
    if (w.has_value()) cout << "Winner: " << w.value() << "\n";
    else cout << "Result: Draw\n";
}

void CLI::waitForEnter() const {
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

void CLI::run() {
    while (true) {
        cout << "\n=== Tic Tac Toe (Generalised) ===\n";
        cout << "  1. Human vs AI\n";
        cout << "  2. AI vs Human\n";
        cout << "  3. AI vs AI\n";
        cout << "  4. Quit\n";

        cout << "Selection: ";
        int ch;
        cin >> ch;

        if (ch == 1) playHumanVsAI();
        else if (ch == 2) playAIVsHuman();
        else if (ch == 3) playAIVsAI();
        else if (ch == 4) break;
        else cout << "Invalid selection.\n";
    }
}

}