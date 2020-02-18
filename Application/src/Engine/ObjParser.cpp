#include "ObjParser.h"

std::stringstream Parser::ReadFile(const char* path) const {
	std::ifstream vstream("resources/BasicVertexShader.shader");
	std::stringstream vbuffer;
	vbuffer << vstream.rdbuf();
	return vbuffer;
}

void Parser::Parse(std::stringstream code) {
	for(std::string line; std::getline(code, line);) {
	}
}