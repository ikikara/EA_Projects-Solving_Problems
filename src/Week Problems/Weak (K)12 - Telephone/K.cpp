#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>

int n, t, CP;
std::vector<int> dfs, low, parent, CP_marked;
std::vector<std::vector<int>> links;

int split_int(std::string nums_string){
    std::string aux = "";
    int size = nums_string.size();
    int num, place = -1;

    for(int i=0; i < size; i++){
        if(nums_string[i] != ' '){            
            aux += nums_string[i];
            
            if(aux == "0"){
                return -1;
            }

            if(i == size-1){
                num = stoi(aux)-1;

                links[place].emplace_back(num);
                links[place][0]++;
                links[num].emplace_back(place);
                links[num][0]++;
            }
        }
        else{
            num = stoi(aux)-1;

            if(place == -1){
                place = num;
            }
            else{
                links[place].emplace_back(num);
                links[place][0]++;
                links[num].emplace_back(place);
                links[num][0]++;
            }
            
            aux = "";
        }
    }

    return 0;
}

void algorithm(int v){
    int w;
    low[v] = dfs[v] = t++;
    
    for(int i=1; i<links[v][0]+1; i++){
        w = links[v][i];
        if(dfs[w] == -1){
            parent[w] = v;
            algorithm(w);
            low[v] = std::min(low[v], low[w]);
            if(CP_marked[v] != 1){
                if(dfs[v] == 1 && dfs[w] != 2){
                    CP_marked[v] = 1;
                    CP++;
                }
                if(dfs[v] != 1 && low[w] >= dfs[v]){
                    CP_marked[v] = 1;
                    CP++;
                }
            }
        }
        else if(parent[v] != w){
            low[v] = std::min(low[v], dfs[w]);
        }
    }
}

int main(){
    std::string line;

    while(std::cin >> n){
        if(n == 0){
            return 0;
        }

        getline(std::cin, line);

        CP = 0;
        t = 1;
        dfs = low = parent = CP_marked = std::vector<int>(n);
        links = std::vector<std::vector<int>> (n);

        for(int i=0; i<n; i++){
            dfs[i] = low[i] = parent[i] = CP_marked[i] = -1;
            links[i].emplace_back(0);
        }

        while(getline(std::cin, line) && (split_int(line) != -1));

        /*for(int i=0; i<n; i++){
            std::cout << "[" << i+1 << "]: ";
            for(int j=0; j<links[i].size(); j++){
                if(j==0){
                    std::cout << "(" << links[i][j] << ") ";
                }
                else{
                    std::cout << links[i][j]+1 << " ";
                }
            }
            std::cout << "\n";
        }*/
        
        algorithm(0);
        
        std::cout << CP << "\n";
    }
    
}