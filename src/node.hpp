#pragma once

#include "common.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Node
{
public:
	std::unordered_set<std::string> labels;
	std::unordered_map<std::string,std::string> properties;
	std::vector<EdgePK> edges;
};
