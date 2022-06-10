#include <iostream>
#include <map>

int main(){
    std::string cmd;
    int num, lower;
    std::map<int, int> list;

    while(std::cin >> cmd >> num){
        if(!cmd.compare("ADD")){
            list[num]++; 
        }
        else{
            auto it = list.lower_bound(num);
            if(it == list.end()){
                std::cout << "impossible\n";
            }
            else{
                lower = it->first;
                it->second--;
                if(it->second==0){
                    list.erase(it);
                }
                std::cout << lower << "\n";
            }
        }
    }
}