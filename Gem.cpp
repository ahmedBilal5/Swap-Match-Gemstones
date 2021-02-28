#include "Gem.h"
#include <ctime>
#include <cstdlib>

//Type will be an integer 0-5. Hence, there can be 6 different types of gems.
void Gem::setType(int t){
        type = t;
}

int Gem::getType(){
        return type;
}

Gem::Gem(){
        srand(time(NULL));
        setType(rand()%6);
}

Gem::Gem(int t){
        setType(t);
}
