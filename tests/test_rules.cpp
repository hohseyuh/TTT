#include <catch2/catch_all.hpp>
#include "../src/game/Rules.hpp"
#include "../src/game/Board.hpp"

using namespace game;

TEST_CASE("initialState creates correct empty board") {
    Board b = Rules::initialState(4, 3);

    REQUIRE(b.m == 4);
    REQUIRE(b.k == 3);

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            REQUIRE(b.at(r, c) == ' ');
}

TEST_CASE("player() returns correct turn") {
    Board b = Rules::initialState(3, 3);
    REQUIRE(Rules::player(b) == 'X');

    b = b.place(0,0,'X');
    REQUIRE(Rules::player(b) == 'O');

    b = b.place(1,1,'O');
    REQUIRE(Rules::player(b) == 'X');
}

TEST_CASE("actions() returns all empty cells") {
    Board b = Rules::initialState(3, 3);
    auto moves = Rules::actions(b);

    REQUIRE(moves.size() == 9);
    REQUIRE(moves[0].r == 0);
    REQUIRE(moves[0].c == 0);
    REQUIRE(moves[8].r == 2);
    REQUIRE(moves[8].c == 2);
}

TEST_CASE("result() applies moves correctly") {
    Board b = Rules::initialState(3, 3);
    Move mv{1,1};
    Board nb = Rules::result(b, mv);

    REQUIRE(nb.at(1,1) == 'X');
    REQUIRE(Rules::player(nb) == 'O');
}

TEST_CASE("terminal() detects draw") {
    Board b(3,3);
    char seq[9] = {'X','O','X','X','X','O','O','X','O'};

    int i = 0;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            b = b.place(r, c, seq[i++]);

    REQUIRE(Rules::terminal(b));
    REQUIRE(!Rules::winner(b).has_value());
}

TEST_CASE("utility() returns correct values") {
    Board xwin(3,3);
    xwin = xwin.place(0,0,'X').place(0,1,'X').place(0,2,'X');
    REQUIRE(Rules::utility(xwin) == 1);

    Board owin(3,3);
    owin = owin.place(2,0,'O').place(2,1,'O').place(2,2,'O');
    REQUIRE(Rules::utility(owin) == -1);
}
