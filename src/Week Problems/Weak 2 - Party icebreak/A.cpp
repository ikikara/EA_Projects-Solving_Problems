#include <iostream>
#include <vector>
#include <algorithm>

bool algorithm(std::vector<int> list, int size){
    int k, l;
    int sum;

    std::sort(list.begin(), list.begin() + size);

    for(int j=0; j<size-2; j++){
        k=j+1;
        l=size-1;

        while( k < l){
            sum = list[j] + list[k] + list[l];

            if(sum==0){
                return true;
            }
            else if(sum>0){
                l--;
            }
            else{
                k++;
            }
        }
    }
    
    return false;
}

int main(){
    int n, card;
    std::vector<int> aux;

    while(std::cin >> n){
        if(n!=0){
            aux = {};

            for(int i=0; i<n; i++){
                std::cin >> card;
                aux.push_back(card);
            }

            if(algorithm(aux, n)){
                std::cout << "Fair\n";
            }
            else{
                std::cout << "Rigged\n";
            }
        }
    }
}