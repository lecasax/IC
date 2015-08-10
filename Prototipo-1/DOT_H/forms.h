
#ifndef FORMS_H
#define FORMS_H
#include "object.h"
#include <vector>

using namespace std;

class Forms: public Object

{

public:

    Forms();
    ~Forms();
    static vector< vector<float > > getCircle(float cx, float cy, float r, int num_segments);
    static vector< vector<float > > getElipse();
    static vector< vector<float > > getRecatangle();

};

#endif  /* FORMS_H */
