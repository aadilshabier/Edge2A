#include <iostream>
#include <vector>
#include <unordered_map>

#include "matcher.hpp"

// TODO: Implement adjLists using maps cause of missing keys after deletion
VF2Matcher::VF2Matcher(const Graph& graph1, const MatchPattern& graph2) \
	: g1(graph1)
	, g2(graph2)
	, currentMapping(g2.getMaxNodePK() + 1, -1)
	, usedNodes(g1.getMaxNodePK() + 1, 0) {

    // Obtaining g1 incoming edges mapping
    g1InEdges.resize(g1.getMaxNodePK() + 1);
    for (auto it = g1.edges.begin(); it != g1.edges.end(); ++it) {
        const Edge& edge = *it;
        g1InEdges[edge.to].push_back(edge.pk);
    }

    // Obtaining g2 incoming edges mapping
    g2InEdges.resize(g2.getMaxNodePK() + 1);
    for (auto it = g2.edges.begin(); it != g2.edges.end(); ++it) {
        const Edge& edge = *it;
        g2InEdges[edge.to].push_back(edge.pk);
    }
}

void VF2Matcher::backtrack(size_t depth) {
    if (depth == g2.numNodes()) {
        mappings.insert(currentMapping); // match found
        return;
    }

    // Iterate through all nodes in g2
    for (auto it2 = g2.nodes.begin(); it2 != g2.nodes.end(); ++it2) {
        NodePK n2 = (*it2).pk;

        if (currentMapping[n2] != -1) continue; // Already matched

        // Iterate through all nodes in g1 to find a match
        for (auto it1 = g1.nodes.begin(); it1 != g1.nodes.end(); ++it1) {
            NodePK n1 = (*it1).pk;

            if (usedNodes[n1]) continue; // Already mapped

            currentMapping[n2] = n1;
            usedNodes[n1] = true;
            if (isFeasible(n1, n2)) backtrack(depth + 1);
            currentMapping[n2] = -1;
            usedNodes[n1] = false;
        }
    }
}

bool VF2Matcher::isFeasible(NodePK n1, NodePK n2) {
    const Node& node1 = *g1.nodes.search(n1);
    const MatchNode& node2 = *g2.nodes.search(n2);

    // Semantic Check: Labels and properties should match
    if (!checkSemanticMatch(node1, node2)) return false;

    // Degree Constraint: g1 should have at least as many outgoing/incoming edges as g2
    if (!checkDegreeConstraint(node1, node2)) return false;

    // Structural Check: Edges must be consistent
    if (!checkStructuralMatch(node1, node2)) return false;

    return true;
}

bool VF2Matcher::checkSemanticMatch(const Node& node1, const MatchNode& node2) {
    // Labels must match
    if (node1.labels != node2.labels) return false;

    // Properties in node2 must be a subset of node1
    for (const auto& [key, value] : node2.properties) {
        if (node1.properties.count(key) == 0 || node1.properties.at(key) != value) {
            return false;
        }
    }
    return true;
}

bool VF2Matcher::checkDegreeConstraint(const Node& node1, const MatchNode& node2) {
	size_t outDegree1 = node1.edges.size(), outDegree2 = node2.edges.size();
    size_t inDegree1 = g1InEdges[node1.pk].size(), inDegree2 = g2InEdges[node2.pk].size();

    if (outDegree1 < outDegree2 || inDegree1 < inDegree2) return false;
    else return true;
}

bool VF2Matcher::checkStructuralMatch(const Node& node1, const MatchNode& node2) {
	// Outgoing edges must be consistent
    if (!matchEdges(node1.edges, node2.edges)) return false;

    // Incoming edges must be consistent
    if (!matchEdges(g1InEdges[node1.pk], g2InEdges[node2.pk])) return false;

    return true;
}

bool VF2Matcher::matchEdges(const std::vector<EdgePK> &edges1, const std::vector<EdgePK> &edges2) {
    // For all edges in edges2, there should be a corresponding edge in edges1
    for (EdgePK e2 : edges2) {
        const Edge& edge2 = *g2.edges.search(e2);

        // Ignore edges where either of the nodes is not mapped
        if ((currentMapping[edge2.from] == -1) || (currentMapping[edge2.to] == -1)) continue;

        bool found = false;
        for (EdgePK e1 : edges1) {
            const Edge& edge1 = *g1.edges.search(e1);

            if (!(edge2.type == "" || edge2.type == edge1.type) || currentMapping[edge2.from] != edge1.from || currentMapping[edge2.to] != edge1.to) {
                continue;
            }

            // Properties in edge2 must be a subset of edge1
            bool propertiesMatch = true;
            for (const auto& [key, value] : edge2.properties) {
                if (edge1.properties.count(key) == 0 || edge1.properties.at(key) != value) {
                    propertiesMatch = false;
                    break;
                }
            }
            if (!propertiesMatch) continue;

            found = true;
            break;
        }
        if (!found) return false; // Edge consistency violated
    }

    return true;
}
