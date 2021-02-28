#include "Chain.h"
Chain::Chain(){
        size = row_pos = col_pos = 0;
        type = '\0';
}
Chain::Chain(int s,char t,int r,int c){
        size = s;
        type = t;
        row_pos = r;
        col_pos = c;
}
int Chain::getSize(){
        return size;
}
void Chain::setSize(int s){
        size = s;
}
char Chain::getType(){
        return type;
}
void Chain::setType(char t){
        type = t;
}

int Chain::getRowPos(){
        return row_pos;
}
void Chain::setRowPos(int r){
        row_pos = r;
}
int Chain::getColPos(){
        return col_pos;
}
void Chain::setColPos(int c){
        col_pos = c;
}

