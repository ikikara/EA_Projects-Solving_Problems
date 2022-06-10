#include <iostream>
#include <unordered_map>

int main(){
    std::unordered_map<int, int> list;
    std::string cmd;
    int x, y;
    while(std::cin >> cmd >> x){
        if(!cmd.compare("QUERY")){
            std::cout << list[x] << "\n";
        }
        else{
            std::cin >> y;
            if(!cmd.compare("ADD")){
                list[y] += x; 
            }
            else{
                if(list[y]-x < 0){
                    std::cout << "removal refused\n";
                }
                else{
                    list[y] -= x;
                    if(list[y]==0){
                        list.erase(list.find(y));
                    }
                }
            }
        }
    }
}