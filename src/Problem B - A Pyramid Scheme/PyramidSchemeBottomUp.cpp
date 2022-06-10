#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <string>
//#include <time.h>          // to measure time   
#include <unordered_map>
#include <vector>

struct node{
    int nr_childs;
    int depth;
    int cost;
    std::array<int,2> DP;
    std::vector<int> childs;
};

std::unordered_map<int,node> indexation;
int MAX = 0;

int split_int(std::string nums_string){
    std::string aux = "";
    int size = nums_string.size();
    int himself = -1;

    for(int i=0; i < size; i++){
        if(nums_string[i] != ' '){            
            aux += nums_string[i];
            if(aux == "-1"){
                return -1;
            }
            if(i == size-1){
                indexation[himself].cost = stoi(aux);
            }
        }
        else{
            if(himself == -1){
                himself = stoi(aux);
                indexation[himself];
            }
            else{
                indexation[himself].childs.emplace_back(stoi(aux));
                indexation[himself].nr_childs++;
            }
            aux = "";
        }
    }

    if(himself > MAX){
        MAX = himself;
    }

    return 0;
}

void depth(int node, int d){
    if(indexation[node].nr_childs != 0){
        for(int i=0; i< indexation[node].nr_childs; i++){
            depth(indexation[node].childs[i], d+1);
        }

    }
    
    indexation[node].depth = d;
}

void PyramidScheme(){
    int nr_fathers=0, son, grandchild;
    int node = 0, cost = 0, node2 = 0, cost2 = 0;
    std::vector<int> Q;

    for(auto it: indexation){
        //see which nodes are the leafs
        if(it.second.nr_childs == 0){
            //save subsolution for all leafs (that's him self)
            indexation[it.first].DP[0] = 1;
            indexation[it.first].DP[1] = it.second.cost;
        }
        else{
            Q.emplace_back(it.first);
            nr_fathers++;
        }
    }
    
    depth(MAX+1, 0);

    sort(Q.begin(), Q.end(), [](int num1, int num2) {
            return indexation[num1].depth > indexation[num2].depth;
        });

    for(int i=0; i<nr_fathers; i++){
        for(int j=0; j < indexation[Q[i]].nr_childs; j++){
            son = indexation[Q[i]].childs[j];
            node = indexation[son].DP[0];
            cost = indexation[son].DP[1];

            for(int k=0; k < indexation[son].nr_childs; k++){
                grandchild = indexation[son].childs[k];
                node2 += indexation[grandchild].DP[0];
                cost2 += indexation[grandchild].DP[1];
            }

            if(node == node2){
                indexation[Q[i]].DP[0] += node;
                indexation[Q[i]].DP[1] += std::max(cost, cost2);
            }
            else if(node < node2){
                indexation[Q[i]].DP[0] += node;
                indexation[Q[i]].DP[1] += cost;
            }
            else{
                indexation[Q[i]].DP[0] += node2;
                indexation[Q[i]].DP[1] += cost2;
            }
            
            node2 = 0; cost2 = 0;
        }

        indexation[Q[i]].DP[0] += 1;
        indexation[Q[i]].DP[1] += indexation[Q[i]].cost;
    }
    
    std::cout << indexation[MAX+1].DP[0]-1 << " " << indexation[MAX+1].DP[1] << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    //clock_t time = clock();                       // to measure time
    std::string line;
    int aux;

    while(getline(std::cin, line)){
        if((aux = split_int(line)) == -1){
            indexation[MAX+1].nr_childs = 1;
            indexation[MAX+1].cost = 0;
            indexation[MAX+1].childs = {0};

            PyramidScheme();

            indexation = {};
            MAX = 0;
        }
    }
    //std::cout << "\n\nTime taken: " << (double)(clock() - time)/CLOCKS_PER_SEC << " s\n";      // to measure time
}

//---------------USEFUL PRITNS---------------------------------
/*  Print(Indexation)
    for(auto it: indexation){
        std::cout << it.first << ": " << it.second.father << "\n";
    }
    std::cout << "\n";

    Print(DP array)
    for(auto it: indexation){
        std::cout << it.first << ": " << indexation[it.first].DP[0] << " " << indexation[it.first].DP[1] << "\n";
    }
    std::cout << "\n";

    Print(Queue)
    for(int num: Q){
        std::cout << num << "\n";
    }
    std::cout << "\n";
*/