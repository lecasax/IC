#include "modifier.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
using namespace std;


Modifier::Modifier(){}
Modifier::Modifier(float x, float y, float z)
{
    //vector <float > v(3, 0);
    globalScale = vector <float > (3, 1);
    globaRotation = vector <float > (3, 0);
    setPosition(x,y,z);
    setModifierType(1);
}
Modifier::~Modifier(){}

void Modifier::setModifierType(int modifierType)
{
    this->modifierType = modifierType;
}

int  Modifier::getModifierType()
{
    return this->modifierType;
}

void Modifier::setGlobalScale( float x, float y, float z)
{

    this->globalScale[0] = x;
    this->globalScale[1] = y;
    this->globalScale[2] = z;
}

void Modifier::setGlobalRotation( float x, float y, float z)
{
    this->globaRotation[0] = x;
    this->globaRotation[1] = y;
    this->globaRotation[2] = z;
}


void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void Modifier::drawModifierTranslation(int index_load)
{
    float size_axi = 10;
    float cone_base = 0.8;
    float cone_height = 3;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1.5);

    glPushMatrix();

    //Eixo 1
    glLoadName(index_load+1);
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size_axi, 0, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(size_axi, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(cone_base, cone_height,16,16);
    glPopMatrix();

    /*----------------------------------------------------------------------- */

    //Eixo 2
    glLoadName(index_load+2);
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, size_axi, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(0, size_axi, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(cone_base, cone_height, 16,16);
    glPopMatrix();

    /*----------------------------------------------------------------------- */

    //Eixo 3
    glLoadName(index_load+3);
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, 0.0, size_axi);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 0, size_axi);
    glRotatef(90, 0, 0, 1);
    glutSolidCone(cone_base, cone_height ,16,16);
    glPopMatrix();

    /*------------------------------------------------------------------------*/
    glPopMatrix();
    glLineWidth(1.0);

}

void Modifier::drawModifierRotation(int index_load)
{
    float ray = 8;
    float cx = 0.0;
    float cy = 0.0;
    int num_segments  = 36;

    //Circulo 1
    glPushMatrix();
    glLoadName(index_load+1);
    glColor4f(BLUE);
    glRotatef(90, 1, 0, 0);
    drawCircle(cx, cy, ray, num_segments);
    glPopMatrix();

    //Circulo 2
    glPushMatrix();
    glLoadName(index_load+2);
    glColor4f(GREEN);
    glRotatef(90, 0, 1, 0);
    drawCircle(cx, cy, ray, num_segments);
    glPopMatrix();

    //Circulo 3
    glPushMatrix();
    glLoadName(index_load+3);
    glColor4f(RED);
    glRotatef(90, 0, 0, 1);
    drawCircle(cx, cy, ray, num_segments);
    glPopMatrix();
    /*------------------------------------------------------------------------*/
    glPopMatrix();

}
void Modifier::drawModifierScale(int index_load)
{
    float size_axi = 10;
    float size_cube = 1.3;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1.5);
    glPushMatrix();

    //Eixo 1
    glLoadName(index_load+1);
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size_axi, 0, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(size_axi, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCube(size_cube);
    glPopMatrix();

    /*----------------------------------------------------------------------- */

    //Eixo 2
    glLoadName(index_load+2);
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, size_axi, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(0, size_axi, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCube(size_cube);
    glPopMatrix();

    /*----------------------------------------------------------------------- */

    //Eixo 3
    glLoadName(index_load+3);
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, 0.0, size_axi);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 0, size_axi);
    glRotatef(90, 0, 0, 1);
    glutSolidCube(size_cube);
    glPopMatrix();

    /*------------------------------------------------------------------------*/

    glPopMatrix();
    glLineWidth(1.0);
}
void Modifier::setPosition(float x, float y, float z)
{
    vector <float > position(3, 0);
    position[0] = x; position[1] = y; position[2] = z;
    this->position = position;
}
vector <float > Modifier::getPosition()
{
    return this->position;
}

void Modifier::draw(int index_load, bool is_selecting)
{
    //switch(this->modifierType)
    switch(1)
    {
        //desenha o cursor de Translacao
        case 1:
            //cout << "Desenhando o modificador de translacao..." << endl;
            drawModifierTranslation(index_load);
        break;

        //desenha o cursor de Rotacao
        case 2:
            drawModifierRotation(index_load);
        break;

        //desenha o cursor de Escala
        case 3:
            drawModifierScale(index_load);
        break;
    }
}