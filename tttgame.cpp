#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>

using namespace std;

class TTT {

private:
int size, win_cond;
char** board;
char player='X', ai='O';

public:
TTT() { board=nullptr; }
~TTT(){
     if (board!=nullptr)
        {
    for (int i = 0; i < size; ++i) {
    delete[] board[i];
    }
    delete[] board;
        }
}

void init()
{
    board = new char*[size];
    for (int i = 0; i < size; ++i) {
        board[i] = new char[size];
    }
    // Fill the array
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = ' '; 
        }
    }
}

void print()
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) cout << " ---";  
        cout << endl; 
        for (int j = 0; j < size; ++j) cout << "| "<< board[i][j] << " ";
        cout << "|" << endl; 
    }
    for (int j = 0; j < size; ++j) cout << " ---";
     cout << endl;
}

//wiersz
bool check_row(char who){
for(int i=0; i<size; i++){
    int count=0;
    for(int j=0; j<size; j++)
    {
        if(board[i][j]==who) count++;
        else if (board[i][j]!=who) count=0;
        else if(count==0 && size-j<win_cond) break;
        if (count>=win_cond) return true;
    }
}
return false;
}

//kolumna
bool check_col(char who){   
for(int j=0;j<size;j++){
    int count=0;
    for(int i=0;i<size;i++){
        if(board[i][j]==who) count++;
        else if (board[i][j]!=who) count=0;
        else if(count==0 && size-i<win_cond) break;
        if (count>=win_cond) return true;
    }
}
return false;
}

//skosy

bool check1(){
for(int j = 0; j <= size-win_cond; ++j)
{
int count=0;
   for(int i = 1; i < size-j; ++i)
   {
      if(board[i][i+j]==board[i - 1][i+j - 1] && board[i][i+j]!=' ') count++;
      else if (board[i][i+j]!=board[i - 1][i+j - 1]) count=0;
      else if(count==0 && size-i-j<win_cond) break;
      if (count>=win_cond-1) return true;
   } 
count=0;
   for(int i = 1; i < size-j; ++i)
   {
      if(board[i+j][i]==board[i+j - 1][i - 1] && board[i+j][i]!=' ') count++;
      else if (board[i+j][i]!=board[i+j - 1][i - 1]) count=0;
      else if(count==0 && size-i-j<win_cond) break;
      if (count>=win_cond-1) return true;
   } 
}
   return false;
}

bool check2(){
for(int j = 0; j <= size-win_cond; ++j)
{
int count=0;
   for(int i = 1; i < size-j; ++i)
   {
      if(board[i][size-i-j-1]==board[i - 1][size -i-j] && board[i][size-i-j-1]!=' ') count++;
      else if (board[i][size-i-j-1]!=board[i - 1][size -i-j]) count=0;
      else if(count==0 && size-i-j<win_cond) break;
      if (count>=win_cond-1) return true;
   } 
count=0;
   for(int i = 1; i < size-j; ++i)
   {
      if(board[i+j][size-i-1]==board[i+j - 1][size-i] && board[i+j][size-i-1]!=' ') count++;
      else if (board[i+j][size-i-1]!=board[i+j - 1][size-i]) count=0;
      else if(count==0 && size-i-j<win_cond) break;
      if (count>=win_cond-1) return true;
   } 
}
   return false;
}


bool win(){
    if(check_row(player) || check_col(player) || check_row(ai) || check_col(ai) || check1() || check2()) return true; 
   return false;
}

bool tie(){

    if (win()) return false;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////
int minimax(int depth, int alpha, int beta, bool maximizing){

    int eval;

    if(win()){
        if (maximizing) {
            eval= -depth-1;
        } else {
            eval = depth+1;
        }
        return eval;
    } else if (tie() || depth==0) {
        eval = 0;
        return eval;
    }

    if (maximizing)
    {
        int best = -1000; //nie jest to najwieksze mozliwe minimum, ale starczy
 
        for (int i = 0; i < size; i++){
            for(int j=0; j<size; j++){

                if (board[i][j]==' ')
                {
                //ruch komputera
                    board[i][j] = ai;

                    eval = minimax(depth-1, alpha, beta, false);
                    board[i][j] = ' ';
                    best = max(best, eval);
                //ciecie alfa-beta
                alpha = max(alpha, best);
                if (beta <= alpha)  break;
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < size; i++){
            for(int j=0; j<size; j++){

            if (board[i][j]==' ')
                {
                //ruch gracza - minimalizowanie szans
                    board[i][j] = player;

                    eval = minimax(depth-1, alpha, beta, true);
                    board[i][j] = ' ';
                    best = min(best, eval);
                //ciecie alfa-beta
                beta = min(beta, best);
                if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

int aiturn(int index){
    int best=-1000, x = -1, y = -1, move;
    for (int i = 0; i < size; i++){
        for(int j=0; j<size; j++){
            if (board[i][j] == ' ')
			{
				board[i][j] = ai;
				move = minimax(index+1,-1000,1000,false);
				board[i][j] = ' ';
				if(move > best)
				{
					best = move;
					x = i;
					y = j;
				}
			}
        }
    } return x*size+y;
}

void aimove(){
    int cell;
	int depth=10-size;
    cell=aiturn(depth);
    int r = cell/size;
    int c = cell % size;
    board[r][c] = ai;
}
///////////////////////////////////////////////////////////////////////////

void playermove(){
    cout << "Wybierz puste pole (1 - " << size*size << "): \n";
       int cell;
       cin >> cell;
       int r = (cell - 1)/size;
       int c = (cell - 1) % size;
    if(cell >= 1 && cell <= size*size && board[r][c] == ' '){
           board[r][c] = player;
    }
}


void game(){
    char who=player;
    init(); print();

    while(!win() && !tie())
    {
        if(who==player){
            playermove();
            print();
            who=ai;
        }
        else{
            aimove();
            print();
            who=player;
        }
    }

    if(tie()) cout<<"Remis\n";
    else if(win()){
        if(who==player){
            cout<<"Przegrales :(\n";
        } else {
            cout<<"Wygrywasz :)\n";
        }
    }
}

void menu(){

    cout << "Witaj w grze kolko i krzyzyk!\nWybierz rozmiar planszy (3-6)" << endl;
    cin >> size;
    if (size > 7 || size < 3) {
    cout<<"Zla wartosc\nKonczenie pracy programu...\n"; 
    exit(1);}
    cout << endl;

    cout << "Wybierz ile symboli w jednej linii oznacza wygrana (3-6, nie moze byc wieksza od zadanego rozmiaru)" << endl;
    cin >> win_cond; 
    if (win_cond > 7|| win_cond > size || win_cond < 3){
        cout<<"Zla wartosc\nKonczenie pracy programu...\n"; exit(1);
    }
    cout<<"Gracz - X, Komputer - O, zaczyna gracz\n";
    //init(); print();
    game();
}


};

int main()
{
    TTT gra;
    gra.menu();

    return 0;
}