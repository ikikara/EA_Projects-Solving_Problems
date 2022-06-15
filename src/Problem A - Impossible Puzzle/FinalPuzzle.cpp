#include <iostream>
#include <math.h>
//#include <time.h>          // to measure time
#include <unordered_map>
#include <vector>
#include <array>

/* LIST
[x] - Input
[x] - Rotate a piece
[x] - Algorithm
[x] - Print board*/


/* ENCRYPT AND DECRYPT PIECE POSITION BY THE NUMBER OF PIECES
On a board 2x3

1st index (row) -> division (e.g 5/3 = 1.something => 1)
2nd index (column) -> division remainder (e.g 5%3 = 2 => 2)

0 -> 0 0
1 -> 0 1
2 -> 0 2
3 -> 1 0
4 -> 1 1
5 -> 1 2
  (...)
*/

struct array_hash2 {
    std::size_t operator()(const std::array<int, 2>& a) const {
        std::size_t h = 0;

        for (auto e : a) {
            h ^= std::hash<int>{}(e)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
        }
        return h;
    }   
};

struct array_hash4 {
    std::size_t operator()(const std::array<int, 4>& a) const {
        std::size_t h = 0;

        for (auto e : a) {
            h ^= std::hash<int>{}(e)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
        }
        return h;
    }   
};

int N, R, C;
std::vector<std::vector<std::array<int,4>>> board;                                                    // board of the puzzle
std::vector<int> used;                                                                                // to see what pieces are being used
std::unordered_map<int, int> color_count;                                                             // count colors presented in pieces
std::vector<std::array<int,4>> pieces;                                                                // pieces for puzzle
std::unordered_map<std::array<int,4>, std::vector<std::array<int,2>>, array_hash4> intersetions;      // "intersetions" of sides and their correspondent pieces (by index) 
std::unordered_map<std::array<int,2>, std::vector<std::array<int,2>>, array_hash2> sides;             // sides and their correspondent pieces (by index)
std::unordered_map<int, std::array<int,4>> rotations = {{1, {3, 0, 1, 2}},                            // rotations
                                                        {2, {2, 3, 0, 1}},
                                                        {3, {1, 2, 3, 0}}};


void imprimir(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            std::cout << board[i][j][0] << " " << board[i][j][1];

            if(j!=C-1){
                std::cout << "  ";
            }
        }

        std::cout << "\n";

        for (int k=0; k < C; k++){
            std::cout << board[i][k][3] << " " << board[i][k][2];

            if(k!=C-1){
                std::cout << "  ";
            }
        }

        if (i != R-1) {
            std::cout << "\n\n";
        } 
        else {
            std::cout << "\n";
        }
    }
}


bool puzzle(int nr_pieces, int index){ 
    int piece_on_board = N-nr_pieces;
    int r = floor(piece_on_board/C), c = piece_on_board%C;
    int where = 0;
    int rotate;
    std::vector<std::array<int,2>> *indexs;
    
    board[r][c] = pieces[index];

    if(nr_pieces-1==0){
        return true;
    }

    used[index] = 1;

    if(c==C-1){
        where = 1;
        indexs = &sides[{board[r][0][3], board[r][0][2]}];
    }
    else{
        if(r!=0){
            indexs = &intersetions[{board[r][c][2], board[r][c][1], board[r-1][c+1][3], board[r-1][c+1][2]}];
            where = 1;
        }
        else{
            indexs = &sides[{board[r][c][2], board[r][c][1]}];
        }
    }

    for(auto index: *indexs){
        if(!used[index[0]]){                   
            rotate = 3+where-index[1];

            // pre-rotation
            if(index[1] != (3+where)%4){
                pieces[index[0]] = {pieces[index[0]][rotations[rotate][0]], 
                                       pieces[index[0]][rotations[rotate][1]], 
                                       pieces[index[0]][rotations[rotate][2]], 
                                       pieces[index[0]][rotations[rotate][3]]};
            }

            if(puzzle(nr_pieces-1, index[0])){
                return true;
            }

            // rotation back to original
            if(index[1] != (3+where)%4){
                pieces[index[0]] = {pieces[index[0]][rotations[3-rotate+1][0]], 
                                       pieces[index[0]][rotations[3-rotate+1][1]], 
                                       pieces[index[0]][rotations[3-rotate+1][2]], 
                                       pieces[index[0]][rotations[3-rotate+1][3]]};
            }
        }
    }

    used[index] = 0;
    
    return false;
}


int main(){ 
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    //clock_t time = clock();                       // to measure time
    int n;                                          
    int color;                                      // to push to a piece
    int odds;                                       // to count how many counts are odd
    int c1, c2;                                     // gonna compare the right or bottom side of first piece?
    int where;                                      // where I gonna insert the piece?
    int rotate;                                     // which rotation I gonna apply?                                          
    bool possible;                                  // to save the result of puzzle(...)
    std::array<int,4> piece;                        // to push to pieces
    std::vector<std::array<int,2>> *indexs;         // indexs of the pieces that I compare with first piece

    std::cin >> n;

    for(int i=0; i<n; i++){      
        std::cin >> N >> R >> C;

        std::vector<std::vector<std::array<int,4>>> vec(R, std::vector<std::array<int,4>> (C));
        std::vector<int> vec2(N, 0);
        board = vec;
        used = vec2;
        color_count = {};
        pieces = {};
        sides = {};
        intersetions = {};
        odds = 0;

        //insert N pieces
        for(int j=0; j<N; j++){
            piece = {};
            //each piece has 4 colors(number)
            for(int k=0; k<4; k++){
                //colors
                std::cin >> color;
                color_count[color]++;
                piece[k] = color;
            }

            sides[{piece[0], piece[1]}].emplace_back(std::array{j,0});
            sides[{piece[1], piece[2]}].emplace_back(std::array{j,1});
            sides[{piece[2], piece[3]}].emplace_back(std::array{j,2});
            sides[{piece[3], piece[0]}].emplace_back(std::array{j,3});

            intersetions[{piece[3], piece[0], piece[0], piece[1]}].emplace_back(std::array{j,0});
            intersetions[{piece[0], piece[1], piece[1], piece[2]}].emplace_back(std::array{j,1});
            intersetions[{piece[1], piece[2], piece[2], piece[3]}].emplace_back(std::array{j,2});
            intersetions[{piece[2], piece[3], piece[3], piece[0]}].emplace_back(std::array{j,3});

            pieces.emplace_back(piece);
        }

        if(N==1){
            board[0][0] = pieces[0];
            imprimir();
        }
        else{
            // corner technique
            for(auto it: color_count){
                if(it.second%2!=0){
                    odds++;
                }
                if(odds>4){
                    break;
                }
            }

            if(odds>4){
                std::cout << "impossible puzzle!\n";
            }
            else{
                board[0][0] = pieces[0];
                possible = false;
                used[0] = 1;

                if(C==1){
                    where = 1;
                    c1 = 2; c2 = 3;
                }
                else{
                    where = 0;
                    c1 = 1; c2 = 2;
                }

                indexs = &sides[{board[0][0][c2], board[0][0][c1]}];

                for(auto index: *indexs){
                    if(!used[index[0]]){                   
                        rotate = 3+where-index[1];

                        // pre-rotation
                        if(index[1] != (3+where)%4){
                            pieces[index[0]] = {pieces[index[0]][rotations[rotate][0]], 
                                                pieces[index[0]][rotations[rotate][1]], 
                                                pieces[index[0]][rotations[rotate][2]], 
                                                pieces[index[0]][rotations[rotate][3]]};
                        }

                        if(puzzle(N-1, index[0])){
                            possible = true;
                            break;
                        }

                        // rotation back to original
                        if(index[1] != (3+where)%4){
                            pieces[index[0]] = {pieces[index[0]][rotations[3-rotate+1][0]], 
                                                pieces[index[0]][rotations[3-rotate+1][1]], 
                                                pieces[index[0]][rotations[3-rotate+1][2]], 
                                                pieces[index[0]][rotations[3-rotate+1][3]]};
                        }
                    }
                }

                if(possible){
                    imprimir();
                }
                else{
                    std::cout << "impossible puzzle!\n";
                }
            }
        }
    }
    //std::cout << "\n\nTime taken: " << (double)(clock() - time)/CLOCKS_PER_SEC << "s\n";      // to measure time
}
