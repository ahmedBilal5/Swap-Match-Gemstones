#ifndef GEMBOARD_H
#define GEMBOARD_H

#include "Gem.cpp"
#include "Chain.cpp"
#include "Center.cpp"
#include "Level.cpp"
#include "Menu.cpp"
#include <vector>
#include <cmath>
class Gemboard{
        Gem** board;
        //int** matches;
        int rows;
        int cols;
        int Xlines;
        int Ylines;
        int* Y_Arr;
        int* X_Arr;
        int numOfChains;
        vector <Chain> chainArr;
        Center** gemCoord;
        int score;
        Level gamelevel;
        string hint;
        Menu gameMenu;
        int lives;
        bool gameOver;
        public:
                //Gemboard();
                Gemboard(int r = 0, int c = 0);
                const Gem& getGem(int, int);
                int getRows();
                void setRows(int);
                int getCols();
                void setCols(int);
                int getXlines();
                int getYlines();
                void setY_Arr(int, int);
                void setX_Arr(int, int);
                int* getX_Arr();
                int* getY_Arr();
                Gem** getBoard();
                Center** getGemCoord();
                int getNumOfChains();
                void setGemCoord();
                void chainChecker();
                void chainRemover();
                Chain* getChainArr();
                void randomise();
                void scoreUpdate();
                int getScore();
                void startScore();
                bool matchAllower(int, int);
                bool matchFinder();
                void RandomChainReplacer();
                void moveToNextLevel();
                Level getGameLevel();
                string getHint();
                void setHint(int);
                void allowHint(bool);
                Menu getMenu();
                void lifeLost();
                int getLives();
                void hintUsed();
                //bool swapAllower(char,int int);
                //int** matchesMade();
                //void scoreUpdate();
                //void refillBoard();
                //int getScore();
                ~Gemboard();
};
#endif

                
                
                
                
                
