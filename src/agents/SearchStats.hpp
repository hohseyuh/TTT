#pragma once
#include <cstdint>

struct SearchStats {
    int64_t nodesExplored = 0;
    int64_t pruned        = -1;   // -1 = not applicable
    int     value         = 0;
    int     maxDepthReached = 0;
    bool    isExact       = true;
};
