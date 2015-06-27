/*classe projetada para auxiliar a classe BasciPlane*/

#ifndef RENDER_H
#define RENDER_H

#include <cmath>
#include <iostream>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include "object.h"

using namespace std;

/*classe para dar suporte a parte de desenho ou primitivas */

class Render

{

public:

	/*metodos que auxiliam no set do ambiente opengl e desenhos de primitvas basicas*/
	static bool status_projection;
	static void viewport3D(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y, const float *obsP);
	void drawGlQuadStripVector(vector <double *> array , int n, int m);
	static void renderObjects(vector <Object *> objects, bool render_mode);
	static unsigned int render(vector <Object *> objects,  vector <float > proj,  int x, int y, bool render_mode);
	static vector <float > worldPoint(int x, int y);



};




#endif
