#include "graphdb.hpp"

#include <iostream>

// TODO: Also store the state of AliasToPKMap
// Or implement Txs using another approach

void GraphDB::beginTransaction() {
	graphState = std::make_unique<Graph>(graph);
}

void GraphDB::commitTransaction() {
	if (!graphState) {
		std::cerr << "ERROR: No ongoing transaction found." << std::endl;
		return;
	}

	graphState = nullptr;
}

void GraphDB::rollbackTransaction() {
	if (!graphState) {
		std::cerr << "ERROR: No ongoing transaction found." << std::endl;
		return;
	}

	graph = *graphState;
	graphState = nullptr;
}
