#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class IOHandler {
private:
	int num_arrs;
	std::vector<int>* arrs;
	std::vector<int>* sort_answer;
public:
	IOHandler(std::string addr);
	~IOHandler();

	std::vector<int> get_arr(int index);
	std::vector<int> get_ans(int index);
	int get_num_arrs() {return num_arrs;}
	void print_out_results();
	void print_arrs();
};

std::string check_input_type(std::string addr);