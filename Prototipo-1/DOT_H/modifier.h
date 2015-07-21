/*
Julho de 2015
*/


#ifndef MODIFIER_H
#define MODIFIER_H
#include "object.h"
#include <vector>

using namespace std;

class Modifier: public Object

{

public:

    Modifier(float x, float y, float z);
    Modifier();
    ~Modifier();
    void setModifierType(int modifierType);
    int getModifierType();
    void setGlobalScale( float x, float y, float z);
    void setGlobalRotation( float x, float y, float z);
    void drawModifierTranslation(int index_load);
    void drawModifierRotation(int index_load);
    void drawModifierScale(int index_load);
    void draw(int index_load, bool is_selecting);
    void setPosition(float x, float y, float z);
    vector <float > getPosition();
    vector <float > getInverseMatrixRotation();

private:

    int modifierType;
    vector <float > position;

};

#endif  /* MODIFIER_H */
