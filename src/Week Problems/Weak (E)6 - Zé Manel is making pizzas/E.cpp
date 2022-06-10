#include <iostream>
#include <vector>
#include <math.h>

int sum;
int absolute_diff;

int algorithm(int n, std::vector<int> pizzas, int total_sum){
    int half = std::floor(total_sum/2);
    std::vector<std::vector<bool>> DP(n+1, std::vector<bool> (half+1, false));

    for(int i=0; i<n+1; i++){
        DP[i][0] = true;
    }
    
    for(int i=1; i<n+1; i++){
        for(int j=1; j<half+1; j++){
            if(pizzas[i-1] > j){
                DP[i][j] = DP[i-1][j];
            }
            else{
                DP[i][j] = (DP[i-1][j] || DP[i-1][j-pizzas[i-1]]);
            }
        }
    }

    for(int j=half; j>-1; j--){
        if(DP[n][j]){
            return std::abs(j-(total_sum-j));
        }
    }

    return 0;
}

int main(){
    int N, total_sum;
    int num;
    std::vector<int> pizzas;

    while(std::cin >> N){
        total_sum = 0;
        absolute_diff = 0;

        for(int i=0; i<N; i++){
            std::cin >> num;
            pizzas.push_back(num);
            total_sum += num;
        }

        std::cout << algorithm(N, pizzas, total_sum) << "\n";

        pizzas = {};
    }

}