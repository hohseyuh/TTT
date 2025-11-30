#include <catch2/catch_all.hpp>
#include "../src/search/heuristics.hpp"
#include "../src/game/Rules.hpp"

using namespace game;
using namespace search;

TEST_CASE("Heuristic never returns terminal values for non-terminal boards") {
    Board b = Rules::initialState(5, 4);

    auto w = Rules::winner(b);
    REQUIRE(!w.has_value());

    int h = search::evaluate(b);
    REQUIRE(h > -1000000);
    REQUIRE(h <  1000000);
}
