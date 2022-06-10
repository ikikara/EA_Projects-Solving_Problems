#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::string line;
    std::string n, num;
    std::vector<int> stack;
    std::vector<int> results;
    int res, size;

    std::getline(std::cin, n);

    for(int i=0; i<stoi(n); i++){
        size = 0;
        stack = {};
        std::getline(std::cin, line);
        std::stringstream ss(line);
        while (ss >> num) {
            if(!num.compare("+")){
                res = stack[size-2] + stack[size-1];
                stack.pop_back();
                stack.pop_back();
                stack.push_back(res);
                size--;
            }
            else if (!num.compare("-")){
                res = stack[size-2] - stack[size-1];
                stack.pop_back();
                stack.pop_back();
                stack.push_back(res);
                size--;
            }
            else{
                stack.push_back(stoi(num));
                size++;
            }
        }
        results.push_back(stack[0]);
    }

    for(int i=0; i<stoi(n); i++){
        std::cout << results[i] << "\n";
    }
}