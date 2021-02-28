#include "Center.h"

Center::Center(){
        x = y = 0;
}

Center::Center(int a, int b){
        x = a;
        y = b;
}
int Center::getX(){
       return x;
}
void Center::setX(int a){
        x = a;
}
int Center::getY(){
        return y;
}
void Center::setY(int b){
        y = b;
}
void Center::setXnY(int a, int b){
        x = a;
        y = b;
}
