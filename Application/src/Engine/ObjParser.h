#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "../Entities/Vertex.h"
#include <vector>

class Parser {
public:
	Parser(const char* path);
private:
	std::stringstream ReadFile(const char* path) const;
	void Parse(std::stringstream code);
	std::vector<Vertex> vertices;
};