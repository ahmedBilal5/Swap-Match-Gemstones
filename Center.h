#ifndef CENTER_H
#define CENTER_H

class Center{
        int x;
        int y;
        public:
                Center();
                Center(int, int);
                int getX();
                void setX(int);
                int getY();
                void setY(int);
                void setXnY(int, int);
};
#endif
