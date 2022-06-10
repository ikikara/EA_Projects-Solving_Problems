#include <iostream>
#include <vector>

int main(){
    int n;
    std::cin >> n;

    int arr, proc;
    std::vector<std::vector<int>> tasks;
    std::vector<int> task;
    
    int time = 0;
    
    for(int i=0 ; i<n; i++){
        task = {};
        std::cin >> arr >> proc;
        task.push_back(arr);
        task.push_back(proc);
        tasks.push_back(task);
    }

    int i=0;
    while(i!=n){
        if(tasks[i][0]<=time){
            time += tasks[i][1];
            i++;
        }
        else{
            time++;
        }
    }
    
    std::cout << time << "\n";

}