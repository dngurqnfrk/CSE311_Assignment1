#include "IOHandler.h"

IOHandler::IOHandler(std::string addr) {
    /*
    if (addr.find('/') == std::string::npos)
        addr = "../input/" + addr;
        */
    std::ifstream file(addr);
    if (!file.is_open())
        throw std::runtime_error("Error : File is not found.\n");

    file >> num_arrs;

    std::string *str_arr = new std::string[num_arrs];
    for (int i = 0; i < num_arrs; i++) {
        std::getline(file, str_arr[i]);
        if (str_arr[i] == "" || str_arr[i] == "\n") {
            i--;
            continue;
        }
    }

    arrs = new std::vector<int>[num_arrs];
    for(int i = 0; i < num_arrs; i++) {
        std::string input_line_array = str_arr[i];
        std::stringstream ss(input_line_array);
        std::string num;
        while (std::getline(ss, num, ' '))
            arrs[i].push_back(std::stoi(num));
    }

    sort_answer = new std::vector<int>[num_arrs];
    for(int i = 0; i < num_arrs; i++) {
        sort_answer[i] = arrs[i];
    }
}

IOHandler::~IOHandler() {
    delete[] arrs;
}

void IOHandler::print_arrs() {
    for(int i = 0; i < num_arrs; i++) {
        std::cout << "Array [" << i << "] : ";
        for (auto iter = arrs[i].begin(); iter != arrs[i].end(); iter++) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }
}

std::string check_input_type(std::string addr) {
    if (addr.find('/') == std::string::npos)
        addr = "../input/" + addr;
    std::ifstream file(addr); 
    if (!file.is_open())
        throw std::runtime_error("Error : File is not found.\n");

    int num_arrs;
    file >> num_arrs;

    std::string *str_arr = new std::string[num_arrs];
    bool is_double = false;
    for(int i = 0; i < num_arrs; i++) {
        std::getline(file, str_arr[i]);
        if (str_arr[i].find('.') != std::string::npos) {
            is_double = true;
            break;
        }
    }

    if (is_double)
        return "double";
    else
        return "int";
}

std::vector<int> IOHandler::get_arr(int index) {
    if (index < 0 || index >= num_arrs)
        throw std::runtime_error("Error :(IOHandler::get_arr) paremeter is wrong.\n");
    
    return arrs[index];
}

std::vector<int> IOHandler::get_ans(int index) {
    if (index < 0 || index >= num_arrs)
        throw std::runtime_error("Error :(IOHandler::get_arr) paremeter is wrong.\n");

    return sort_answer[index];
}