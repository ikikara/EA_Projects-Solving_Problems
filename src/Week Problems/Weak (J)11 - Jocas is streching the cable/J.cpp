#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

int n, m;
std::vector<std::array<double,2>> coordenates;
std::vector<std::array<double,3>> E;
std::vector<int> set;
std::vector<int> rank;

int find(int a){
    if(set[a] != a){
        set[a] = find(set[a]);
    }

    return set[a];
}

void link(int a, int b){
    if(rank[a] > rank[b]){
        set[b] = a;
    }
    else{
        set[a] = b;
    }

    if(rank[a] == rank[b]){
        rank[b]++;
    }
}

double algorithm(int nr_edges){
    double min_links = 0;

    std::sort(E.begin(), E.end(), [](std::array<double,3> e1, std::array<double,3> e2) {
                 return e1[2] < e2[2];
             });

    for(int i=0; i<nr_edges; i++){
        if(find(E[i][0]) != find(E[i][1])){
            min_links += E[i][2];
            link(find(E[i][0]), find(E[i][1]));
        }
    }

    return min_links;
}

int main(){
    int a, b, nr_edges = 0;
    double cost;

    while(std::cin >> n){
        coordenates = std::vector<std::array<double,2>> (n);
        set = std::vector<int> (n);
        rank = std::vector<int> (n);

        for(int i=0; i<n; i++){
            std::cin >> coordenates[i][0];
            std::cin >> coordenates[i][1];
            set[i] = i;
            rank[i] = 0;
        }

        std::cin >> m;
        for(int i=0; i<m; i++){
            std::cin >> a >> b;
            link(find(a-1), find(b-1));
        }

        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                cost = (double) sqrt( fabs(coordenates[i][0] - coordenates[j][0]) * 
                                      fabs(coordenates[i][0] - coordenates[j][0]) + 
                                      fabs(coordenates[i][1] - coordenates[j][1]) * 
                                      fabs(coordenates[i][1] - coordenates[j][1]));
                E.emplace_back(std::array{(double)i, (double)j, cost});
                nr_edges++;
            }
        }

        printf("%.2f\n", algorithm(nr_edges));

        E = {};
        nr_edges = 0;
    }

    
}