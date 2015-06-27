#include "object.h"
#include <iostream>
using namespace std;
float *Object::point3f(float x, float y, float z)
{
    float *p = new float[3];
    p[0] = x; p[1] = y; p[2] = z;
    return p;
}

float *Object::point4f(float x, float y, float z, float w)
{
    float *p = new float[4];
    p[0] = x; p[1] = y; p[2] = z; p[3] = w;
    return p;
}


Object::Object()
{

    float r[]={0, 0, 0};
    float s[]={1, 1, 1};
    float t[]={0, 0, 0};
    float c[]={1, 1, 1};
    this->is_selected = false;
    this->render_mode = true;
    this->rotation.insert(this->rotation.end(), r, r+3);
    this->translation.insert(this->translation.end(), t, t+3);
    this->scale.insert(this->scale.end(), s, s+3 );
    this->color.insert(this->color.end(), c, c+3);
    
}
Object::Object(vector < float *> vertex)
{

    is_selected = false;
    this->render_mode = true;
    this->vertex      =  vertex;
    float r[]={0, 0, 0};
    float s[]={1, 1, 1};
    float t[]={0, 0, 0};
    float c[]={1, 1, 1};

    this->rotation.insert(this->rotation.end(), r, r+3);
    this->translation.insert(this->translation.end(), t, t+3);
    this->scale.insert(this->scale.end(), s, s+3 );
    this->color.insert(this->color.end(), c, c+3);
    
}


Object::~Object()
{
    
}

vector <float *> Object::getVertex()
{
    return vertex;
}

vector <float > Object::getColor()
{
    return color;
}

int Object::getPrimitive()
{
    return GL_PRIMITIVE;
}

void Object::setColor(  vector <float > color)

{
    this->color = color;
}
void Object::setPrimitive(int GL_PRIMITIVE)
{
    this->GL_PRIMITIVE = GL_PRIMITIVE;
}


void Object::scaleObject(vector <float > newScale)
{
    this->scale = newScale;
}

vector <float > Object::getScale()
{
    return this->scale;
}
    
void Object::translateObject( vector <float > newTranslation)

{
    this->translation = newTranslation;
}
vector <float > Object::getTranslation()
{
    return this->translation;
}

void Object::rotateObject(vector <float > newRotation)
{
    this->rotation = newRotation;
}

vector <float > Object::getRotation()
{
    return this->rotation;
}

float Object::getDepth()
{
    return this->translation[2];
}

void Object::setSelected(bool is_selected)
{
    this->is_selected = is_selected;
}


void Object::setRenderMode(int mode)
{
    this->render_mode = mode;
}

void Object::draw(int index_load)
{
    cout << "Funcao virtual chamada...." << endl;
}