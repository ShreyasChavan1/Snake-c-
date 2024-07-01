#include<iostream>
#include<vector>
#include<windows.h>
#include<random>
#include<sstream>
#include<fstream>
#include<conio.h> //for _kbhit() and _getch()

int SPEED = 100;
int Score;
using namespace std;
void creategame(vector<vector<char>>& board){
    system("cls");
    for(int i = 0 ; i < 21; ++i){
        for(int j = 0 ; j < 21 ; ++j){
            if(i==0||i == 20 || j == 0 || j==20){
                board[i][j] = 'O';
            }
            cout<<board[i][j]<<" ";
        }
            cout<<endl;
    }
}
void createsnake(vector<vector<char>>& board , vector<pair<int,int>>& snake){
    for(const auto& snk : snake){
        board[snk.first][snk.second] = '0';
     }
}
void createfood(vector<vector<char>>& board , mt19937& gen){
    uniform_int_distribution<> dis(1,19);
    int x,y;
    do{
        x = dis(gen);
        y = dis(gen);
    }while(board[x][y] !=' ');
    board[x][y] = '*';
}
void movement(char input, vector<vector<char>>& board, vector<pair<int,int>>& snake, bool& over){
    pair<int,int> new_head = snake.front();
    board[snake.back().first][snake.back().second] = ' ';
    snake.pop_back();
    if(input == 'd'){
        new_head.second += 1;
    }
    else if(input == 'a'){
        new_head.second -= 1;
    }
    else if(input == 'w'){
        new_head.first -= 1;
    }
    else if(input == 's'){
        new_head.first += 1;
    }

    for(auto& segment : snake){
        if(segment==new_head){
            over = true;
        }
    }
    if(board[new_head.first][new_head.second] == '*'){
        random_device rd;
        mt19937 gen(rd());
        Score +=1;
        createfood(board,gen);
        snake.push_back(new_head);
    }
    snake.insert(snake.begin(),new_head);
    board[new_head.first][new_head.second] = '0';
    createsnake(board,snake);
    if(new_head.first == 0 || new_head.first == 20 || new_head.second == 0 || new_head.second == 20){
        over = true;
    }
}
int main(){
    vector<vector<char>> board(21,vector<char>(21,' '));
    vector<pair<int,int>> snk = {{10,10}};
    createsnake(board,snk);
    random_device rd;
    mt19937 gen(rd());
    createfood(board,gen);
    creategame(board);
    bool over = false;
    char input = 'd';
    while(!over){
        if(_kbhit()){ //checks if user has given any input
             input = _getch(); // given input is stored in getch untill other input is given
            if(input == 'q') over = true;
        }
        movement(input,board,snk,over);
        creategame(board);

        Sleep(SPEED);
    }
    cout<<"Total Score: "<<Score<<endl;
    string highscore;
    stringstream ss;
    ss << "highscore"<<Score;
    highscore =  ss.str();
    ofstream out("snake_highscore.txt");
    out<<highscore;
    out.close();


    return 0;          
}