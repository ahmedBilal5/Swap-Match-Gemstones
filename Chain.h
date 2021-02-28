#ifndef CHAIN_H
#define CHAIN_H
class Chain{
        int size;
        char type;
        int row_pos;
        int col_pos;
        public:
                Chain();
                Chain(int,char,int,int);
                int getSize();
                void setSize(int);
                char getType();
                void setType(char);
                int getRowPos();
                void setRowPos(int);
                int getColPos();
                void setColPos(int);
};
#endif
