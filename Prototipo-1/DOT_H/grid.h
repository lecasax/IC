/*classe projetada para auxiliar a classe BasciPlane*/

#ifndef GRID_H
#define GRID_H


#include "object.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>


using namespace std;

/*classe para dar suporte a parte de desenho ou primitivas */

class Grid: public Object

{

public:

	Grid();
	Grid(vector < float * > vertex);
	~Grid();
	void draw(int index_load,  bool is_selecting);

};




#endif
