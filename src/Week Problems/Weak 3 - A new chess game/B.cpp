#include "iostream"
#include "vector"

int board[401][401];

int algorithm(int x, int y, int m){
    int count = 0;

    if(board[x+200][y+200]==0){
        board[x+200][y+200]=1;
        count++;
    }

    if(m>0){
        count += algorithm(x+1, y+2, m-1)
                    + algorithm(x+1, y-2, m-1)
                    + algorithm(x-1, y+2, m-1)
                    + algorithm(x-1, y-2, m-1)
                    + algorithm(x+2, y+1, m-1)
                    + algorithm(x-2, y+1, m-1)
                    + algorithm(x+2, y-1, m-1)
                    + algorithm(x-2, y-1, m-1);
    }       
    return count;

}


int main(){
    int n;
    int x, y, m;
    int count_moves = 0;

    std::cin >> n;

    for(int i=0; i<n; i++){
        std::cin >> x >> y >> m;
        count_moves += algorithm(x, y, m) ;
        /*    for(int j=191; j<207; j++){
                for(int k=191; k<207; k++){
                    std::cout << board[j][k] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        std::cout << "\n";*/
    }

    std::cout << count_moves << "\n";

}