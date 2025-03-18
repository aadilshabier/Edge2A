#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "graph.hpp"
#include "match.hpp"

class VF2Matcher {
private:
    const Graph& g1;
    const MatchPattern& g2;
    
    std::vector<std::vector<EdgePK>> g1InEdges; // Given node, get all incoming edges
    std::vector<std::vector<EdgePK>> g2InEdges;
    std::unordered_map<NodePK, NodePK> mapping;  // Maps nodes from g2 to g1
    std::unordered_set<NodePK> usedNodes;        // Tracks used nodes in g1

public:
    VF2Matcher(const Graph& graph1, const MatchPattern& graph2);

    bool match() {
        return backtrack(0);
    }

    // Get the mapping of a node from g2 to g1
    NodePK getMapping(NodePK nodePK) const {
        return mapping.at(nodePK);
    }

private:
    bool backtrack(size_t depth);
    bool isFeasible(NodePK n1, NodePK n2);
    bool checkSemanticMatch(const Node& node1, const MatchNode& node2);
    bool checkDegreeConstraint(const Node& node1, const MatchNode& node2);
    bool checkStructuralMatch(const Node& node1, const MatchNode& node2);
    bool matchEdges(const std::vector<EdgePK> &edges1, const std::vector<EdgePK> &edges2);
};
