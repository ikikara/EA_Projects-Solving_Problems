#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
//#include <time.h>
#include <unordered_map>
#include <vector>

struct node{
    int t;                       //time to execute the task
    int d;                       //number of dependencies
    int outdegree;               //number of "childs"
    int time_to = 0;
    bool deleted = false;        //if node can or will be definitely deleted
    bool queued = false;         //if is already in queue
    bool final_node = false;
    std::array<int,2> marks;     //mark the nodes: 0 - disconnected or not | 1 - to see cycles
    std::vector<int> arcs;       //"childs"
    std::vector<bool> independ;  //link between him and "children" exist or not
};


int n;
int initial_node, final_node;
int time_op1 = 0, time_op2 = 0;
int count_final_nodes = 0;
node* pipeline;

bool DFS(int v){
    if(pipeline[v].marks[0] == 0){
        pipeline[v].marks[0] = 1;
        pipeline[v].marks[1] = 1;
        
        if(pipeline[v].outdegree != 0){
            for(int i=0; i < pipeline[v].outdegree; i++){
                if(pipeline[pipeline[v].arcs[i]].marks[0] == 0){
                    if(!DFS(pipeline[v].arcs[i])){
                        return false;
                    }
                }
                else if(pipeline[pipeline[v].arcs[i]].marks[1] == 1){
                    return false;
                }
            }
        }
        //count the number of final nodes
        else{
            if(!pipeline[v].final_node){
                count_final_nodes++;
                if(count_final_nodes == 2){
                    return false;
                }

                final_node = v;
                pipeline[v].final_node = true;
            }
        }
    }
    pipeline[v].marks[1] = 0;
    
    return true;
}


void op1_2(int op){
    std::deque<int> Q;
    std::vector<int> S;
    int u, v;
    
    Q.emplace_back(initial_node);
    
    while (!Q.empty()){
        u = Q.front();
        Q.pop_front();
        if(op == 1){
            S.emplace_back(u);
        }

        for(int i=0; i < pipeline[u].outdegree; i++){
            v = pipeline[u].arcs[i];
            
            if(op == 2){
                if(pipeline[u].time_to + pipeline[v].t > pipeline[v].time_to){
                    pipeline[v].time_to = pipeline[u].time_to + pipeline[v].t;
                }
            }

            pipeline[v].d--;
            if(pipeline[v].d == 0){       
                Q.emplace_back(v);
            }
        }

        if(op == 1){
            std::sort(Q.begin(), Q.end());
        }
    }
    
    if(op == 1){
        std::cout << time_op1 << "\n";

        for(int i=0; i<n; i++){
            std::cout << S[i]+1 << "\n";
        }    
    }
    else{
        std::cout << pipeline[final_node].time_to + pipeline[initial_node].t << "\n";
    }
}

void op3(){
    std::deque<int> Q;
    int u, v, size = 1;
    
    Q.emplace_back(initial_node);
    
    while (!Q.empty()){
        u = Q.front();   
        Q.pop_front();

        if(size == 1){
            std::cout << u+1 << "\n";
        }

        if(u == final_node){
            break;
        }
        
        for(int i=0; i < pipeline[u].outdegree; i++){
            v = pipeline[u].arcs[i];
            
            if(pipeline[u].independ[i]){
                pipeline[u].independ[i] = false;
                pipeline[v].d--;
            }

            if(pipeline[v].d == 0){  
                if(!pipeline[v].queued){
                    Q.emplace_back(v);
                    pipeline[v].queued = true;
                    size++;
                }

                if(!pipeline[u].deleted){
                    pipeline[u].deleted = true;
                    size--;
                }
            }
        }

        if(!pipeline[u].deleted){
            Q.emplace_back(u);
        }
    }
}

bool validate_pipeline(){
    //see if there are cycles OR if exist more than 1 final node
    if(!DFS(initial_node)){
        return false;
    }

    //see if pipeline is disconnected
    for(int i=0; i < n; i++){
        //if node wasn't colored then the graph is disconneted
        if(pipeline[i].marks[0] == 0){
            return false;
        }
    }

    return true;
}

void Pipelining(int op){
    if(op == 1){
        op1_2(1);
    }
    else if(op == 2){
        op1_2(2);
    }
    else if(op == 3){
        op3();
    }
    else{
        std::cout << "VALID\n";
    }
}   

int main(){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int d, op;
    int count_init_nodes = 0;

    while(std::cin >> n){
        //clock_t time = clock();                       // to measure time
        pipeline = (node*)malloc(sizeof(node)*n);

        for(int i=0; i < n; i++){
            std::cin >> pipeline[i].t;
            std::cin >> pipeline[i].d;
            if(pipeline[i].d == 0){
                count_init_nodes++;
                initial_node = i;
                if(count_init_nodes > 1){
                    std::cout << "INVALID\n";
                    return 0;
                }
            }

            for(int j=0; j < pipeline[i].d; j++){
                std::cin >> d;
                pipeline[d-1].arcs.emplace_back(i);
                pipeline[d-1].independ.emplace_back(true);
                pipeline[d-1].outdegree++;
            }

            time_op1 += pipeline[i].t;
        }
        std::cin >> op;

        if(count_init_nodes !=1 || !validate_pipeline()){
            std::cout << "INVALID\n";
        }
        else{
            Pipelining(op);
        }

        pipeline = {};
        time_op1 = 0;
        time_op2 = 0;
        //std::cout << "\n\nTime taken: " << (double)(clock() - time)/CLOCKS_PER_SEC << " s\n";      // to measure time
    }


    return 0;
}

//---------------USEFUL PRITNS---------------------------------
/*  Print(arcs from all nodes)
    for(int i=0; i < n; i++){
        std::cout << i << ": ";
        for(int j=0; j < pipeline[i].arcs; j++){
            std::cout << pipeline[i].to_go[j] << " ";
        }
        std::cout << "\n";
    }
*/