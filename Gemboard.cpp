#include "Gemboard.h"


Gemboard::Gemboard(int r, int c){ 
        srand(time(NULL));
        int** p;
        p = new int*[r];
        for(int i = 0; i < r; i++){
                p[i] = new int[c];
                for(int j = 0; j < c; j++){
                        p[i][j] = rand()%6;
                }
        }                 
        Xlines = r+1;
        Ylines = c+1;
        X_Arr = new int[Xlines];
        Y_Arr= new int[Ylines];
        rows = r; 
        cols = c;
        board = new Gem* [rows];
        for (int i = 0; i < rows; i++){
                board[i] = new Gem[cols];
                for(int j = 0; j < cols; j++){
                        board[i][j] = Gem(p[i][j]);
                 }
       }
       lives = 3;
       startScore();
       gamelevel.setPts(50);
}
void Gemboard::chainChecker(){
        chainArr.clear(); 
        numOfChains = 0;
        //horizontal checker
        for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols-2; j++){
                        int jump = 0;
                        for(int k = 1; getBoard()[i][j].getType() == getBoard()[i][j+k].getType() && (j+k)<cols; k++){
                                jump++;
                                if(k>=2){
                                        if(j+k==cols-1){
                                                numOfChains++;
                                                chainArr.push_back(Chain(k+1,'H',i,j));
                                                setHint(getBoard()[i][j].getType());
                                                break;
                                        }
                                        
                                        if(getBoard()[i][j].getType() != getBoard()[i][j+k+1].getType()){
                                                numOfChains++;
                                                chainArr.push_back(Chain(k+1,'H',i,j));
                                                setHint(getBoard()[i][j].getType());
                                         }
                                }
                        }
                        j+=jump;
                 }
       }
                        
       //vertical checker
       for(int i = 0; i < cols ; i++){
                for( int j = 0; j < rows-2; j++){
                        int jump = 0;
                        for(int k = 1; getBoard()[j][i].getType() == getBoard()[j+k][i].getType() && (k+j)<rows; k++){    
                                jump++;
                                
                                if(k>=2){
                                        if(j+k==rows-1){
                                                numOfChains++;
                                                chainArr.push_back(Chain(k+1,'V',j,i));
                                                break;
                                        }
                                        if(getBoard()[j][i].getType() != getBoard()[j+k+1][i].getType()){
                                                numOfChains++;
                                                chainArr.push_back(Chain(k+1,'V',j,i));
                                         }
                                }
                        }
                        j+=jump;
                }
       }
     
}
Menu Gemboard::getMenu(){
        return gameMenu;
}
void Gemboard::chainRemover(){
           
        for(int i = 0; i < chainArr.size();i++){
                if(chainArr[i].getType() == 'H'){
                        switch(chainArr[i].getSize()){
                                case 3:
                                case 4:
                                        board[chainArr[i].getRowPos()][chainArr[i].getColPos()+1].setType(5-board[chainArr[i].getRowPos()][chainArr[i].getColPos()+1].getType());
                                       break;
                                case 5:     
                                        board[chainArr[i].getRowPos()][chainArr[i].getColPos()+2].setType(5-board[chainArr[i].getRowPos()][chainArr[i].getColPos()+2].getType());
                                       break;   
                        }
                }
                if(chainArr[i].getType() == 'V'){
                        switch(chainArr[i].getSize()){
                                case 3:
                                case 4:
                                        board[chainArr[i].getRowPos()+1][chainArr[i].getColPos()].setType(5-board[chainArr[i].getRowPos()+1][chainArr[i].getColPos()].getType());
                                       break;
                                case 5:     
                                        board[chainArr[i].getRowPos()+2][chainArr[i].getColPos()].setType(5-board[chainArr[i].getRowPos()+2][chainArr[i].getColPos()].getType());
                                       break;   
                        }
                }
        }
}
void Gemboard::RandomChainReplacer(){
        srand(time(NULL));
        int** p;
        p = new int*[chainArr.size()];
        for(int i = 0; i < chainArr.size(); i++){
                p[i] = new int[chainArr[i].getSize()];
                for(int j = 0; j < chainArr[i].getSize(); j++){
                        p[i][j] = rand()%6;
                }
        } 
        for(int i = 0; i < chainArr.size();i++){
                if(chainArr[i].getType() == 'H'){
                        for(int j = 0; j < chainArr[i].getSize(); j++){
                                board[chainArr[i].getRowPos()][chainArr[i].getColPos()+j].setType(p[i][j]);
                        }
                }
                if(chainArr[i].getType() == 'V'){
                        for(int j = 0; j < chainArr[i].getSize(); j++){
                                board[chainArr[i].getRowPos()+j][chainArr[i].getColPos()].setType(p[i][j]);
                        }
                }
        }
}

string Gemboard::getHint(){
        return hint;
}

void Gemboard::setHint(int type){
        switch(type){
                case 0:
                         hint = "Look out for red chains!";
                         break;
                case 1:
                         hint = "Try searching for any yellow chains!";
                         break;
                case 2:
                         hint = "Hmmmm, do you see any possible square chains?";
                        break;
                case 3:
                         hint = "Blue Gems are the most fun to match!";
                         break;
                case 4:
                         hint = "Scan for a green chain!";
                         break;
                case 5:
                         hint = "Purple chains are waiting to be formed!";
                        break;
      }
}

bool Gemboard::matchFinder(){
       
        bool match = false;
        srand(time(NULL));
        int r = rand()%6+1;
        int c = rand()%6+1;
        while(match==false){
        if(r>0 && r<7){
        //upward checking
                int t2 = board[r][c].getType();
                int t = board[r+1][c].getType();
                board[r+1][c].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        match = true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r+1][c].setType(t);
                }
                
                
                //downward checking
                t2 = board[r][c].getType();
                t = board[r-1][c].getType();
                board[r-1][c].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        match = true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r-1][c].setType(t);
                }   
        }
        if(c > 0 && c < 7){
                            //right checking
                int t2 = board[r][c].getType();
                int t = board[r][c+1].getType();
                board[r][c+1].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        match = true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r][c+1].setType(t);
                }
                
                
                //downward checking
                t2 = board[r][c].getType();
                t = board[r][c-1].getType();
                board[r][c-1].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        match = true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r][c-1].setType(t);
                }   
            }
       }
       return match;
       
}

void Gemboard::lifeLost(){
        if(gamelevel.getMovesAllowed()==0){
                lives--;
                randomise();
        }
        if(lives==0)
                gameOver = true;
}

bool Gemboard::matchAllower(int x, int y){
        bool moveDone = false;
        int spaceLength  = 0;
        spaceLength = abs(X_Arr[1] -X_Arr[0])/3;
        int r, c;
        for( int i = 0; i < cols; i++){
                if(x > Y_Arr[i] && x < Y_Arr[i+1])
                        c = i;
        }
        for(int i = 0; i < rows; i++){
                if(y > X_Arr[i]+(spaceLength)+spaceLength/2 && y < X_Arr[i+1]+(spaceLength)+spaceLength/2-10){
                        if(rows-1-i<5)
                             r = (rows-1)-i;
                        if(rows-1-i>=5)
                                r = (rows-i);
                        
                                
                 }
        }
        cout << "Mouse is being pressed in: " << r << ',' << c << endl;
        
        
        if(r>0 && r<7){
        //upward checking
                int t2 = board[r][c].getType();
                int t = board[r+1][c].getType();
                board[r+1][c].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        RandomChainReplacer();
                        scoreUpdate();
                        //setHint(r,c);
                        gamelevel.moveMade();
                        lifeLost();
                        return true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r+1][c].setType(t);
                }
                
                
                //downward checking
                t2 = board[r][c].getType();
                t = board[r-1][c].getType();
                board[r-1][c].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        RandomChainReplacer();
                        scoreUpdate();
                        //setHint(r,c);
                        gamelevel.moveMade();
                        lifeLost();
                        return true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r-1][c].setType(t);
                }   
        }
        if(c > 0 && c < 7){
                            //right checking
                int t2 = board[r][c].getType();
                int t = board[r][c+1].getType();
                board[r][c+1].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        RandomChainReplacer();
                        scoreUpdate();
                        //setHint(r,c);
                        gamelevel.moveMade();
                        lifeLost();
                        return true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r][c+1].setType(t);
                }
                
                
                //downward checking
                t2 = board[r][c].getType();
                t = board[r][c-1].getType();
                board[r][c-1].setType(board[r][c].getType());
                board[r][c].setType(t);
                
                chainChecker();
                if(!(chainArr.empty())){
                        RandomChainReplacer();
                        scoreUpdate();
                        //setHint(r,c);
                        gamelevel.moveMade();
                        lifeLost();
                        return true;
                }        
                else{
                        board[r][c].setType(t2);
                        board[r][c-1].setType(t);
                }   
       }
       
}
int Gemboard::getLives(){
        return lives;
}
        
void Gemboard::moveToNextLevel(){
        if(score >= gamelevel.getPts()){
                gamelevel.levelUp();
                randomise();
                chainRemover();
        }
}
int Gemboard::getScore(){
        return score;
}
void Gemboard::startScore(){
        score = 0;
}

void Gemboard::scoreUpdate(){
        for(int i =0; i< chainArr.size(); i++){
          switch(chainArr[i].getSize()){
                case 3:
                        score+=10;
                        break;
                case 4: score+=30;
                        break;
                case 5:
                        score+=50;
                        break;
           }
         }
}
Level Gemboard::getGameLevel(){
        return gamelevel;
}                      
                
void Gemboard::randomise(){
        srand(time(NULL));
        int** p;
        p = new int*[rows];
        for(int i = 0; i < rows; i++){
                p[i] = new int[cols];
                for(int j = 0; j < cols; j++){
                        p[i][j] = rand()%6;
                }
        } 
        board = new Gem* [rows];
        for (int i = 0; i < rows; i++){
                board[i] = new Gem[cols];
                for(int j = 0; j < cols; j++){
                        board[i][j] = Gem(p[i][j]);
                 }
      }
}       

int Gemboard::getNumOfChains(){
        return numOfChains;
}
Chain* Gemboard::getChainArr(){
        int size = chainArr.size();
        Chain* C = new Chain[size];
        for(int i = 0; i < size; i++)
                C[i] = chainArr[i];
        return C;
}

Center** Gemboard::getGemCoord(){
        return gemCoord;
}

void Gemboard::setGemCoord(){
        gemCoord = new Center*[rows];
        for(int i = 0; i < rows; i++){
                        gemCoord[i] = new Center[cols];
                        for(int j = 0; j < cols; j++)
                                gemCoord[i][j] = Center((Y_Arr[j]+Y_Arr[j+1])/2,(X_Arr[i]+X_Arr[i+1])/2);
        }
}
void Gemboard::hintUsed(){
        score-=20;
}

void Gemboard::allowHint(bool b){
        gameMenu.setHintOption(b);
}

                        
const Gem& Gemboard::getGem(int i, int j){
        return board[i][j];
}
int Gemboard::getRows(){
        return rows;
}
void Gemboard::setRows(int r){
        rows = r;
        Xlines = r+1;
}
int Gemboard::getCols(){
        return cols;
}
void Gemboard::setCols(int c){
        cols = c;
        Ylines = c+1;
}
int Gemboard::getYlines(){
        return Ylines;
}

int Gemboard::getXlines(){
        return Xlines;
}

void Gemboard::setX_Arr(int start, int space){
        for(int i = 0; i < Xlines; i++)
                X_Arr[i] = start+(i*space);
}
void Gemboard::setY_Arr(int start, int space){
        for(int i = 0; i < Ylines; i++)
                Y_Arr[i] = start+(i*space);
}

int* Gemboard::getY_Arr(){
        return Y_Arr;
}

int* Gemboard::getX_Arr(){
        return X_Arr;
}
Gem** Gemboard::getBoard(){
        return board;
}

Gemboard::~Gemboard(){
        //for (int i = 0; i < rows; i++)
          //      delete board[i];
        //delete board;
}
        
                        
