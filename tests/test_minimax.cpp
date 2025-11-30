#include <catch2/catch_all.hpp>
#include "../src/search/minimax.hpp"
#include "../src/game/Rules.hpp"

using namespace game;
using namespace search;

TEST_CASE("Minimax selects valid move on empty board") {
    Board b = Rules::initialState(3, 3);
    auto result = Minimax::run(b);

    REQUIRE(result.move.r >= 0);
    REQUIRE(result.move.r < 3);
    REQUIRE(result.move.c >= 0);
    REQUIRE(result.move.c < 3);
}

TEST_CASE("Minimax ensures that X never loses from start") {
    Board b = Rules::initialState(3, 3);
    auto result = Minimax::run(b);

    // Value must be >= 0 in optimal play (draw or X win)
    REQUIRE(result.value >= 0);
}
