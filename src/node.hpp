#pragma once

#include "common.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Node
{
public:
	NodePK pk;
	std::unordered_set<std::string> labels;
	std::unordered_map<std::string, Data> properties;
	std::vector<EdgePK> edges;
};
