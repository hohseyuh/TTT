#include <catch2/catch_all.hpp>
#include "../src/search/minimax.hpp"
#include "../src/search/alphaBeta.hpp"
#include "../src/game/Rules.hpp"

using namespace game;
using namespace search;

TEST_CASE("AlphaBeta produces identical value to Minimax on 3x3") {
    Board b = Rules::initialState(3, 3);

    auto m1 = Minimax::run(b).value;
    auto m2 = AlphaBeta::run(b).value;

    REQUIRE(m1 == m2);
}
