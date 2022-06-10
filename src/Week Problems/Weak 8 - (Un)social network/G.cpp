#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

std::vector<std::vector<int>> edges;
std::vector<int> neighbor;
int n, best;

void algorithm(int v, int size){
    int UB = 0;

    if(size > best){
        best = size;
    }

    for(int i=v+1; i < n; i++){
        if(neighbor[i] == 0){
            UB++;
        }
    }

    if(size + UB <= best){
        return;
    }

    for(int i=v+1; i < n; i++){
        if(edges[i][v] == 1){
            neighbor[i]++;
        }
    }

    for(int i=v+1; i < n; i++){
        if(neighbor[i] == 0){
            algorithm(i, size + 1);
        }
    }

    for(int i=v+1; i < n; i++){
        if(edges[i][v] == 1){
            neighbor[i]--;
        }
    }

    
}


int main(){
    int m;
    int node1, node2;

    std::cin >> n >> m;

    edges = std::vector<std::vector<int>>(n, std::vector<int>(n,0));

    for(int i=0; i<m; i++){
        std::cin >> node1 >> node2;
        edges[node1][node2] = 1;
        edges[node2][node1] = 1;
    }
    
    for(int i=0; i<n; i++){
        neighbor.push_back(0);
    }

    for(int i=0; i<n; i++){    
        algorithm(i,1);
    }

    std::cout << best << "\n";

}