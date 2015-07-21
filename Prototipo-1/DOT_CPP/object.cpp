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

    this->hit_index_internal = 0;
    this->index_internal = 0;
    this->is_selected = false;
    this->rotation.insert(this->rotation.end(), r, r+3);
    this->translation.insert(this->translation.end(), t, t+3);
    this->scale.insert(this->scale.end(), s, s+3 );
    this->color.insert(this->color.end(), c, c+3);
    this->globalScale = vector <float > (3, 1);
}
Object::Object(vector < float *> vertex)
{

    this->vertex      =  vertex;
    float r[]={0, 0, 0};
    float s[]={1, 1, 1};
    float t[]={0, 0, 0};
    float c[]={1, 1, 1};

    this->is_selected = false;
    this->index_internal = 0;

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


void Object::scaleObject(float x, float y, float z)
{
    this->scale[0] = x;
    this->scale[1] = y;
    this->scale[2] = z;
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

void Object::setGlobalScale( float x, float y, float z)
{
    this->globalScale[0] = x;
    this->globalScale[1] = y;
    this->globalScale[2] = z;
}
void Object::setGlobalRotation( float x, float y, float z)
{
    this->globaRotation[0] = x;
    this->globaRotation[1] = y;
    this->globaRotation[2] = z;
}

void Object::setGlobalTranslation(vector <float > newTranslation)
{
    this->global_translation = newTranslation;
}

vector <float > Object::getGlobalTranslation()
{
    return this->global_translation;
}


float Object::getDepth()
{
    return this->translation[2];
}

void Object::setSelected(bool is_selected)
{
    this->is_selected = is_selected;
}


void Object::setRenderMode(bool mode)
{
    this->render_mode = mode;
}

bool Object::getRenderMode()
{
    return this->render_mode;
}

void Object::setHitIndexInternal(int val)
{
    hit_index_internal = val;
}
int Object::getHitIndexInternal()
{
    return hit_index_internal;
}

void Object::draw(int index_load,  bool is_selecting, int size_world)
{
    cout << "Funcao virtual chamada...." << endl;
}

void Object::setTipo(const char * val)
{
    string nome(val);
    tipo = nome;
}

string Object::getTipo()
{
    return tipo;
}

// Metodos da Curva
void Object::setPtControle(float x, float y, float z) {}

void Object::updatePtsCurv() {}


int Object::getSizeControlPoints()
{
    return 0;
}

vector <float > Object::getControlPointSelected()
{
    return vector <float > (3, 0);
}

void Object::setPtControleModifier(float x, float y, float z){}