#include <iostream>
#include <vector>
#include <algorithm>

int algoritmo (std::vector<std::vector<int>> P, int n){
    int max = -1;

    if(n==1){
        return P[0][0];
    }

    //1st level
    P[1][0] += P[0][0]; 
    P[1][1] += P[0][0];

    for(int i=2; i<n; i++){
        for(int j=0; j<i+1; j++){
            if(j==0){
                P[i][j] += P[i-1][j];
            }
            else if(j==i){
                P[i][j] += P[i-1][j-1];
            }
            else{
                P[i][j] += std::max(P[i-1][j-1], P[i-1][j]);
            }
        }
    }

    for(int i=0; i<n; i++){
        if(P[n-1][i]> max){
            max = P[n-1][i];
        }
    }

    return max;
}

int main(){
    int n;
    int levels;
    int num;
    std::vector<std::vector<int>> mountain;
    std::vector<int> aux;

    std::cin >> n;

    for(int i=0; i<n; i++){
        mountain = {};

        std::cin >> levels;

        for(int j=0; j<levels; j++){
            aux = {};

            for(int k=0; k<j+1; k++){
                std::cin >> num;
                aux.push_back(num);

            }
            mountain.push_back(aux);

        }

        std::cout << algoritmo(mountain, levels) << "\n";
    }
}