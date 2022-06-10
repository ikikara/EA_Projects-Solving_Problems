#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> list(n);
    for(int i=0; i<n; i++){
        std::cin >> list[i];
    }

    for(int i=n-1; i>=0; i--){
        std::cout << list[i];
        if(i==0){
            std::cout << "\n";
        }
        else{
            std::cout << " ";
        }
    }
}
