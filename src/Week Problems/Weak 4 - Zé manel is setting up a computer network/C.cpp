#include "iostream"
#include "vector"

std::vector<int> visited;
std::vector<int> nlig;
std::vector<std::vector<int>> costs;
int n, m, k;
int best;

std::vector<std::vector<int>> costs_matrix(std::vector<std::vector<int>> edges){
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for(int i=0; i < m; i++){
        matrix[edges[i][0]-1][edges[i][1]-1] = edges[i][2];
        matrix[edges[i][1]-1][edges[i][0]-1] = edges[i][2];
    }

    return matrix;
}

std::vector<std::vector<int>> visited_and_nlig_matrix(){
    std::vector<int> visited_matrix (n);
    std::vector<int> nlig_matrix (n);
    std::vector<std::vector<int>> two_matrixes = {visited_matrix, nlig_matrix};

    return two_matrixes;
}

void algorithm(int nr_visited, int cost){
    if(cost >= best){
        return;
    }

    if(nr_visited == n){
        best = cost;
        return;
    }

    for(int i=0; i<n; i++){
        if(!visited[i]){
            for(int j=0; j<n; j++){
                if(visited[j] && costs[i][j] > 0 && nlig[j] < k){
                    nlig[i]++;
                    nlig[j]++;
                    visited[i]=1;
                    algorithm(nr_visited + 1, cost + costs[i][j]);
                    visited[i]=0;
                    nlig[i]--;
                    nlig[j]--;
                }
            }
        }
    }
}


int main(){
    int n1, n2, cost;
    std::vector<int> edge;
    std::vector<std::vector<int>> edges;
    int worst = 0;

    while(std::cin >> n >> m >> k){
        edges = {};
        for(int i=0; i<m; i++){
            edge = {};
            std::cin >> n1 >> n2 >> cost;
            edge.push_back(n1);
            edge.push_back(n2);
            edge.push_back(cost);
            edges.push_back(edge);
            worst += cost;
        }

        costs = costs_matrix(edges);

        std::vector<std::vector<int>> two_matrixes = visited_and_nlig_matrix();
        visited = two_matrixes[0];
        visited[0] = 1;
        nlig = two_matrixes[1];
        best = worst;

        algorithm(1, 0);

        if(best == worst){
            std::cout << "NO WAY!\n";
        }
        else{
            std::cout << best << "\n";
        }

    }


}