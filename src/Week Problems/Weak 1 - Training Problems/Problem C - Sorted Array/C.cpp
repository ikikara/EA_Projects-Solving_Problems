#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    int size=0;
    std::vector<int> list;

    while(std::cin >> n){
        list.push_back(n);
        size++;
    }

    std::sort(list.begin(), list.begin() + size);

    for(int i=0; i<size; i++){
        std::cout << list[i] << "\n";
    }
}