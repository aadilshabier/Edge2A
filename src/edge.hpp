#pragma once

#include "common.hpp"

#include <string>
#include <unordered_map>

class Edge
{
public:
	std::string type;
	std::unordered_map<std::string, Data> properties;

	NodePK from;
	NodePK to;
};
