/*classe projetada para auxiliar a classe BasciPlane*/

#ifndef OBJECT_H
#define OBJECT_H

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define BASE 180
#define GLM_FORCE_RADIANS 

#include  <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

using namespace std;

/*classe para dar suporte a parte de desenho ou primitivas */

class Object

{

public:

	Object();
	Object(vector < float * > vertex);
	~Object();

	vector < float * > getVertex();
	static float *point3f(float x, float y, float z);
	static float *point4f(float x, float y, float z, float w);
	void setPrimitive(int GL_PRIMITIVE);
	int  getPrimitive();
	void setColor( vector <float > color);
	vector <float >  getColor();
	void scaleObject(vector <float > newScale);
	vector <float > getScale();
	void translateObject( vector <float > newTranslation);
	vector <float >getTranslation();
	void rotateObject(vector <float > newRotation);
	vector <float >getRotation();
	virtual void draw(int index_load);
	void setSelected(bool is_selected);
	void setRenderMode(int mode);
	float getDepth();

protected:

	/*metodos que auxiliam no set do ambiente opengl e desenhos de primitvas basicas*/
	vector < float * > vertex;
	vector < float  > position;
	vector < float  > rotation;
	vector < float  > translation;
	vector < float  > scale;
	vector < float  > color;
	bool is_selected;
	bool render_mode;

	bool visible;
	int GL_PRIMITIVE;
};




#endif
