#pragma once

#include "common.hpp"

#include <string>
#include <unordered_map>

class Edge
{
public:
	std::string type;
	std::unordered_map<std::string,std::string> properties;

	NodePK from;
	NodePK to;
};
