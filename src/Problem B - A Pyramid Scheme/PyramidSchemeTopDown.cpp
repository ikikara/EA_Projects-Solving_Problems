#include <array>
#include <iostream>
#include <string>
//#include <time.h>          // to measure time
#include <unordered_map>
#include <algorithm>
#include <vector>


std::unordered_map<int,std::array<int,3>> indexation;
std::vector<std::vector<int>> tree; 

std::vector<int> split_int(std::string nums_string){
    std::vector<int> nums;
    std::string aux = "";
    int size = nums_string.size();

    for(int i=0; i < size; i++){
        if(nums_string[i] != ' '){            
            aux += nums_string[i];
            if(i == size-1){
                nums.emplace_back(stoi(aux));
            }
        }
        else{
            nums.emplace_back(stoi(aux));
            aux = "";
        }
    }

    return nums;
}

std::array<int,2> PyramidScheme(int node){
    if(indexation[node][2] != -1){
        //std::cout << "OPAH JA TEMOS SOLUÇÃO\n";
        return {indexation[node][1], indexation[node][2]};
    }

    int index = indexation[node][0];
    int nrnode = 0;
    int nrnode2 = 0;
    int cost = 0;
    int cost2 = 0;
    int size = tree[index].size(), size2;
    int selfcost = tree[index][size-1];

    std::array<int,2> pre_solution, pre_solution2;
    int bestnodes=0, bestcosts=0;

    if(size > 2){
        for(int i=1; i < size-1; i++){
            // vai usar o filho
            pre_solution = PyramidScheme(tree[index][i]);
            nrnode = pre_solution[0];
            cost = pre_solution[1];
            //std::cout << node << " passes to " << tree[tree[node][i]][0] << " with jump of " << 1 << "\n";
            
            // vai usar o filho dos filhos
            // Filhos do nó percorrido -> tree[indexation[tree[index][i]]];
            size2 = tree[indexation[tree[index][i]][0]].size();
            if(size2 > 2){
                for(int j=1; j < size2-1; j++){
                    pre_solution2 = PyramidScheme(tree[indexation[tree[index][i]][0]][j]); 
                    nrnode2 += pre_solution2[0];
                    cost2 += pre_solution2[1];
                    //std::cout << node << " passes to " << tree[tree[tree[tree[node][i]][0]][j]][0] << " with jump of " << 2 << "\n";
                }
            }

            if(nrnode == nrnode2){
                bestnodes += nrnode2;
                bestcosts += std::max(cost, cost2);
            }
            else{
                if(nrnode2 > nrnode){
                    bestnodes += nrnode;
                    bestcosts += cost;
                }
                else{
                    bestnodes += nrnode2;
                    bestcosts += cost2;
                }
            }

            cost2 = 0;
            nrnode2 = 0;
        }
        indexation[node][1] = bestnodes + 1;
        indexation[node][2] = bestcosts + selfcost;

        return {indexation[node][1], indexation[node][2]};
    }
    else{
        indexation[node][1] = 1;
        indexation[node][2] = selfcost;
        return {indexation[node][1], indexation[node][2]};
    }


    return {};
}

int main(){
    /*std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);*/

    //clock_t time = clock();                       // to measure time
    std::string line;
    std::vector<int> aux;
    int count = 0;

    while(getline(std::cin, line)){
        aux = split_int(line);
        if(aux[0]!=-1){            
            tree.emplace_back(aux);
            indexation[aux[0]] = {count++, -1, -1};
        }
        else{
            int max=tree[0][0];
            for(int i=1; i < (int)tree.size(); i++){
                if(tree[i][0] > max){
                    max = tree[i][0];
                }
            }

            tree.emplace_back(std::vector<int>{max+1, 0, 0});
            indexation[max+1] = {count, -1, -1};

            std::array<int,2> solution = PyramidScheme(max+1);

            std::cout << solution[0]-1 << " " << solution[1] << "\n";

            tree = {};
            indexation = {};
            count = 0;
        }
    }
    //std::cout << "\n\nTime taken: " << (double)(clock() - time)/CLOCKS_PER_SEC << "s\n";      // to measure time
}