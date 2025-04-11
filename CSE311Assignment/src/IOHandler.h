#pragma once
#include <fstream>
#include <string>
#include <vector>

class IOHandler {
private:
public:
	template <typename T>
	std::vector<T> get_input_txt(std::string addr);
	
	
	IOHandler() = default;
};