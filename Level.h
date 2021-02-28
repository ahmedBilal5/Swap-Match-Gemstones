#ifndef LEVEL_H
#define LEVEL_H

class Level{
        int level;
        int ptsRequired;
        int movesAllowed;
        int movesMinus;
        public:
                Level();
                void levelUp();
                int getLevel();
                int getPts();
                void setPts(int);
                int getMovesAllowed();
                void moveMade();
};
#endif
