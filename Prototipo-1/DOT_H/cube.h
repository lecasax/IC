/*classe projetada para auxiliar a classe BasciPlane*/

#ifndef CUBE_H
#define CUBE_H


#include "object.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>


using namespace std;

/*classe para dar suporte a parte de desenho ou primitivas */

class Cube: public Object

{

public:

	Cube();
	Cube(vector < float * > vertex);
	~Cube();
	void draw(int index_load);

};




#endif
