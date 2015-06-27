#include "cube.h"
#include <iostream>
using namespace std;
Cube::Cube(vector <float *> obj):Object(obj)
{

}

Cube::Cube():Object()

{

	vector <float *> v;

    v.push_back(point3f(0.0f, 0.0f, 0.0f));
    v.push_back(point3f(1.0f, 0.0f, 0.0f));
    v.push_back(point3f(1.0f, 1.0f, 0.0f));
    v.push_back(point3f(0.0f, 1.0f, 0.0f));
    // back
    v.push_back(point3f(0.0f, 0.0f, -1.0f));
    v.push_back(point3f(1.0f, 0.0f, -1.0f));
    v.push_back(point3f(1.0f, 1.0f, -1.0f));
    v.push_back(point3f(0.0f, 1.0f, -1.0f));
    // right
    v.push_back(point3f(1.0f, 0.0f, 0.0f));
    v.push_back(point3f(1.0f, 0.0f, -1.0f));
    v.push_back(point3f(1.0f, 1.0f, -1.0f));
    v.push_back(point3f(1.0f, 1.0f, 0.0f));
    // left
    v.push_back(point3f(0.0f, 0.0f, 0.0f));
    v.push_back(point3f(0.0f, 0.0f, -1.0f));
    v.push_back(point3f(0.0f, 1.0f, -1.0f));
    v.push_back(point3f(0.0f, 1.0f, 0.0f));
    // top
    v.push_back(point3f(0.0f, 1.0f, 0.0f));
    v.push_back(point3f(1.0f, 1.0f, 0.0f));
    v.push_back(point3f(1.0f, 1.0f, -1.0f));
    v.push_back(point3f(0.0f, 1.0f, -1.0f));
    // bottom
    v.push_back(point3f(0.0f, 0.0f, 0.0f));
    v.push_back(point3f(1.0f, 0.0f, 0.0f));
    v.push_back(point3f(1.0f, 0.0f, -1.0f));
    v.push_back(point3f(0.0f, 0.0f, -1.0f));

    this->vertex      =  v;

}

Cube::~Cube(){}


void Cube::draw(int index_load)

{
	
	GLfloat m[16];
	vector <float > c = getColor();
    vector <float > r = getRotation();
    vector <float > t = getTranslation();
    vector <float > s = getScale();

    glm::quat quat (glm::vec3(r[0]*PI/BASE, r[1]*PI/BASE, r[2]*PI/BASE));
    glm::quat quaternion = quat ; 
    glm::mat4 mat  = glm::toMat4(quaternion);

    int count = 0;
    for (int k = 0; k < 4; ++k){
        for (int j = 0; j < 4; ++j){
            m[count] = mat[k][j];
            count++;
        }   
    }
    glLoadName(index_load); // register object.
    glPushMatrix();

    	if (this->is_selected){
        	c[0] = 1; c[1] = 0; c[2] = 0;
        }
        glColor3f(c[0],c[1],c[2]);
        glScalef(s[0], s[1], s[2]);
        glTranslatef(t[0],t[1],t[2]);
        glMultMatrixf(m);
        glBegin(GL_QUADS);
        vector < float * > vertex = getVertex();

        for (int j = 0; j < (int) vertex.size(); ++j){
            
            glVertex3fv(vertex[j]);
        }
        glEnd();
    glPopMatrix();
    //glPopName();
    this->is_selected = false;
}