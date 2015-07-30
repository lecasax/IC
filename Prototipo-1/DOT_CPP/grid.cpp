#include "grid.h"

Grid::Grid(vector <float *> obj):Object(obj)
{

}

Grid::Grid():Object()

{
    setTipo("Grid");
    vector <float *> vertex;

    for (int i = 0; i < 170 ; i+=10){

        vertex.push_back(Object::point3f(-80+i, 0,  100));
        vertex.push_back(Object::point3f(-80+i, 0, -100));
    }

    for (int i = 0; i < 220 ; i+= 20){
        vertex.push_back(Object::point3f( -80, 0,  100-i ));
        vertex.push_back(Object::point3f(  80, 0,  100-i ));
    }

    this->vertex  =  vertex;

}

Grid::~Grid(){}


void Grid::draw(int index_load,  bool is_selecting, int size_world)

{

    if(!is_selecting){
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

            //glColor3f(c[0],c[1],c[2]);
            glScalef(s[0], s[1], s[2]);
            glTranslatef(t[0],t[1],t[2]);
            glMultMatrixf(m);
            glBegin(GL_LINES);
            vector < float * > vertex = getVertex();

            for (int j = 0; j < (int) vertex.size(); ++j){
                if(j == 16 || j == 17){
                    glColor3f(1, 0, 0);
                }
                else if (j == 44 || j == 45){
                     glColor3f(0, 1, 0);
                }  else {
                    glColor3f(c[0],c[1],c[2]);
                }
                glVertex3fv(vertex[j]);
            }
            glEnd();

        glPopMatrix();
    }
    //glPopName();
}