#include <catch2/catch_all.hpp>
#include "../src/search/minimax.hpp"
#include "../src/search/alphaBeta.hpp"
#include "../src/search/depthLimited.hpp"
#include "../src/game/Rules.hpp"

using namespace game;
using namespace search;

TEST_CASE("Minimax is deterministic") {
    Board b = Rules::initialState(3, 3);

    auto r1 = Minimax::run(b).move;
    auto r2 = Minimax::run(b).move;

    REQUIRE(r1.r == r2.r);
    REQUIRE(r1.c == r2.c);
}

TEST_CASE("AlphaBeta is deterministic") {
    Board b = Rules::initialState(3, 3);

    auto r1 = AlphaBeta::run(b).move;
    auto r2 = AlphaBeta::run(b).move;

    REQUIRE(r1.r == r2.r);
    REQUIRE(r1.c == r2.c);
}

TEST_CASE("DepthLimited is deterministic for fixed depth") {
    Board b = Rules::initialState(5, 4);

    auto r1 = DepthLimited::run(b, 3).move;
    auto r2 = DepthLimited::run(b, 3).move;

    REQUIRE(r1.r == r2.r);
    REQUIRE(r1.c == r2.c);
}
