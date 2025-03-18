#pragma once

#include <vector>
#include <set>

#include "graph.hpp"

using MatchNode = Node;
using MatchEdge = Edge;
using MatchMapping = std::vector<NodePK>;
using MatchResult = std::set<MatchMapping>;
using MatchResults = std::vector<Graph>;
using MatchPattern = Graph;
using WhereExp = void*;
using MatchResultFmt = void*;
// using OrderExp = void*;
// using LimitType = int;
