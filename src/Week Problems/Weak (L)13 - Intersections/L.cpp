#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::array<int,4>> cubes;
std::vector<std::array<int,2>> min_max (3);    //0 - max_min | 1 - min_max

int algorithm(int n){
    for(int i=0; i<n; i++){
       for(int j=0; j<3; j++){
           min_max[j][0] = std::max(cubes[i][j], min_max[j][0]);
           min_max[j][1] = std::min(cubes[i][j] + cubes[i][3], min_max[j][1]);
       }
    }

    return std::max(0,min_max[0][1] - min_max[0][0])*std::max(0,min_max[1][1] - min_max[1][0])*std::max(0,min_max[2][1] - min_max[2][0]);
}

int main(){
    int n, num;

    while(std::cin >> n){
        cubes = std::vector<std::array<int,4>> (n);
        
        for(int i=0; i<n; i++){
            for(int j=0; j<4; j++){
                std::cin >> num;
                cubes[i][j] = num;
            }
        }

        min_max = std::vector<std::array<int,2>> (3, {-100000, 100000});
        std::cout << algorithm(n) << "\n";
    }
}