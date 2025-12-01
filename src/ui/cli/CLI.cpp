#include "CLI.hpp"

#include <limits>

using namespace std;
using namespace game;

namespace ui {

// Constructor
CLI::CLI()
    : board(Rules::initialState(3,3)),
      showStats(true) {
}

// Entry point
void CLI::run() {
    cout << "\nTIC TAC TOE AI ENGINE\n";

    while (true) {
        int choice = showMainMenu();
        switch (choice) {
            case 1: playGame(); break;
            case 2: configure(); break;
            case 3: benchmark(); break;
            case 4: help(); break;
            case 5:
                cout << "Exiting.\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

// Main menu
int CLI::showMainMenu() {
    cout << "\n1. Play Game\n";
    cout << "2. Configure Game\n";
    cout << "3. Benchmark AI\n";
    cout << "4. Help\n";
    cout << "5. Exit\n";
    cout << "Choice: ";
    return readInt(1,5);
}

// Configuration
void CLI::configure() {
    cout << "\nCONFIGURATION\n";

    cout << "Board size m: ";
    int m = readInt(2, 1000);

    cout << "Win condition k: ";
    int k = readInt(2, m);

    board = Rules::initialState(m,k);

    cout << "\nChoose Player X:\n";
    playerX = chooseAgent();

    cout << "\nChoose Player O:\n";
    playerO = chooseAgent();

    cout << "Show AI statistics? (1 yes, 0 no): ";
    showStats = (readInt(0,1) == 1);

    cout << "Configuration saved.\n";
}

// Agent selection
unique_ptr<Agent> CLI::chooseAgent() {
    cout << "1. Human\n";
    cout << "2. Minimax\n";
    cout << "3. Alpha Beta\n";
    cout << "4. Depth Limited\n";
    cout << "5. Random\n";
    cout << "Choice: ";

    while (true) {
        int c = readInt(1,5);
        switch (c) {
            case 1: return nullptr;

            case 2:
                warnIfSlow("Minimax");
                return make_unique<MinimaxAgent>();

            case 3:
                warnIfSlow("Alpha Beta");
                return make_unique<AlphaBetaAgent>();

            case 4: {
                cout << "Depth (1 to 20): ";
                int d = readInt(1,20);
                return make_unique<DepthAgent>(d);
            }

            case 5:
                return make_unique<RandomAgent>();
        }
    }
}

// Warn user about expensive algorithms on m>3
void CLI::warnIfSlow(const string& name) {
    if (board.m > 3) {
        cout << "Warning: " << name
             << " may be very slow on boards larger than 3.\n";
    }
}

// Game loop
void CLI::playGame() {
    board = Rules::initialState(board.m, board.k);

    cout << "\nGAME START\n";

    while (!Rules::terminal(board)) {
        printBoard();

        char p = Rules::player(board);
        Agent* agent = (p == 'X') ? playerX.get() : playerO.get();

        cout << "\nPlayer " << p << " turn.\n";

        Move move;

        if (!agent) {
            move = readHumanMove();
        } else {
            cout << agent->name() << " is thinking...\n";

            move = agent->chooseMove(board);

            if (showStats) {
                printStats(agent);
            }
        }

        board = Rules::result(board, move);
    }

    printBoard();

    if (auto w = Rules::winner(board); w.has_value()) {
        cout << "Winner: " << *w << "\n";
    } else {
        cout << "Draw.\n";
    }
}

// Board printing
void CLI::printBoard() const {
    int m = board.m;

    cout << "\n   ";
    for (int c = 0; c < m; c++) cout << c << " ";
    cout << "\n";

    for (int r = 0; r < m; r++) {
        cout << r << "  ";
        for (int c = 0; c < m; c++) {
            char ch = board.at(r,c);
            if (ch == ' ') ch = '.';
            cout << ch << " ";
        }
        cout << "\n";
    }
}

// Human input
Move CLI::readHumanMove() {
    while (true) {
        cout << "Enter row and column: ";
        int r, c;
        cin >> r >> c;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (!board.inBounds(r,c)) {
            cout << "Out of bounds.\n";
            continue;
        }

        if (!board.isEmpty(r,c)) {
            cout << "Cell is not empty.\n";
            continue;
        }

        return Move{r,c};
    }
}

// Statistics
void CLI::printStats(const Agent* agent) const {
    if (!agent) return;
    if (auto* s = agent->stats()) {
        cout << "Nodes: " << s->nodesExplored << "\n";
        if (s->pruned >= 0) cout << "Pruned: " << s->pruned << "\n";
        cout << "Evaluation: " << s->value << "\n";
    }
}

// Benchmark
void CLI::benchmark() {
    cout << "\nBenchmarking on 3x3...\n";

    Board b = Rules::initialState(3,3);

    auto runTest = [&](const string& name, Agent& agent) {
        auto t0 = chrono::steady_clock::now();
        agent.chooseMove(b);
        auto t1 = chrono::steady_clock::now();

        long long ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
        cout << name << ": " << ms << " ms\n";
    };

    MinimaxAgent mm;
    AlphaBetaAgent ab;
    DepthAgent dl(6);

    runTest("Minimax", mm);
    runTest("Alpha Beta", ab);
    runTest("Depth Limited 6", dl);
}

// Help
void CLI::help() {
    cout << "\nHELP\n";
    cout << "This is a generalised m k game.\n";
    cout << "Minimax is optimal but extremely slow for large boards.\n";
    cout << "Alpha Beta is more efficient but still expensive.\n";
    cout << "Depth Limited uses heuristics and scales well.\n";
    cout << "Random Agent is for testing.\n";
}

// Integer reader
int CLI::readInt(int min, int max) {
    while (true) {
        int v;
        cin >> v;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again: ";
            continue;
        }

        if (v >= min && v <= max) {
            return v;
        }

        cout << "Enter a number in range " << min << " to " << max << ": ";
    }
}

}