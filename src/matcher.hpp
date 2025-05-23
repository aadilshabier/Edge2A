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

class VF2Matcher {
private:
    const Graph& g1;
    const MatchPattern& g2;

    AdjList g1InEdges; // Given node, get all incoming edges
    AdjList g2InEdges;

    MatchMapping currentMapping;  // Maps nodes from g2 to g1
    MatchResult mappings; // Contains all valid mappings
    std::vector<bool> usedNodes; // Tracks used nodes in g1

public:
    VF2Matcher(const Graph& graph1, const MatchPattern& graph2);

    auto match() {
        backtrack(0);
        return mappings;
    }

private:
    void backtrack(size_t depth);
    bool isFeasible(NodePK n1, NodePK n2);
    bool checkSemanticMatch(NodePK n1, NodePK n2);
    bool checkDegreeConstraint(NodePK n1, NodePK n2);
    bool checkStructuralMatch(NodePK n1, NodePK n2);
    bool matchEdges(const std::vector<EdgePK> &edges1, const std::vector<EdgePK> &edges2);
};
