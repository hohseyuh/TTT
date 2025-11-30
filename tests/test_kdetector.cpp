#include <catch2/catch_all.hpp>
#include "../src/game/KDetector.hpp"
#include "../src/game/Board.hpp"

using namespace game;

TEST_CASE("KDetector detects horizontal win") {
    Board b(3,3);
    b = b.place(0,0,'X').place(0,1,'X').place(0,2,'X');
    REQUIRE(KDetector::findWinner(b) == 'X');
}

TEST_CASE("KDetector detects vertical win") {
    Board b(3,3);
    b = b.place(0,1,'O').place(1,1,'O').place(2,1,'O');
    REQUIRE(KDetector::findWinner(b) == 'O');
}

TEST_CASE("KDetector detects diagonal win") {
    Board b(3,3);
    b = b.place(0,0,'X').place(1,1,'X').place(2,2,'X');
    REQUIRE(KDetector::findWinner(b) == 'X');
}

TEST_CASE("KDetector detects anti-diagonal win") {
    Board b(3,3);
    b = b.place(0,2,'O').place(1,1,'O').place(2,0,'O');
    REQUIRE(KDetector::findWinner(b) == 'O');
}
