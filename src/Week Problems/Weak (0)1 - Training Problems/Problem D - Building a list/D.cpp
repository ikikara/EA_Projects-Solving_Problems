#include <iostream>
#include <list>

int main() {
    std::list<int> array = { 0 };
    std::list<int>::iterator it = array.begin();
    std::string cmd, dir;
    int n, size=0;


    while(std::cin >> cmd >> dir ){
        if(cmd.compare("INSERT") == 0){
            std::cin >> n;
            if(dir.compare("RIGHT")==0){
                ++it;
                array.insert(it, n);
                --it;
                --it;
            }
            else{
                array.insert(it, n);
            }
            size++;
        }
        else{
            if(dir.compare("RIGHT")==0){
                it++;
            }
            else{
                it--;
            }
        }
    }

    for(int n: array){
        std::cout << n << "\n";
    }

}