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

    this->index_internal = 0;
    this->is_selected = false;
    this->rotation.insert(this->rotation.end(), r, r+3);
    this->translation.insert(this->translation.end(), t, t+3);
    this->scale.insert(this->scale.end(), s, s+3 );
    this->color.insert(this->color.end(), c, c+3);

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

void Object::setColor(float r, float g, float b)

{
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
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

void Object::translateObject(float x, float y, float z)

{
    this->translation[0] = x;
    this->translation[1] = y;
    this->translation[2] = z;
}

vector <float > Object::getTranslation()
{
    return this->translation;
}

void Object::rotateObject(float x, float y, float z)
{
    this->rotation[0] = x;
    this->rotation[1] = y;
    this->rotation[2] = z;
}

vector <float > Object::getRotation()
{
    return this->rotation;
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

void Object::draw(int index_load,  bool is_selecting)
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
void Object::setPtControle(float x, float y, float z){}

void Object::updatePtsCurv(){}


// Duplica um Ponto de Controle Extremo
// Um dos Pontos de Controles Extremos
// tem de estarem selecionados
int Object::addPtControle()
{
    return -1;
}

// Adiciona um Ponto de Controle Extremo
// Um dos Pontos de Controles Extremos
// tem de estarem selecionados
int Object::addPtControle(float x, float y, float z)
{
    return -1;
}

// Retorna as Imagens dos Nós na Curva
// As imagens dos nós são os pontos iniciais
// de cada segmento da curva B-Spline
vector<float> Object::getImgNo()
{   
    vector<float> nulo;
    return nulo;
}

float Object::getPesoSelec()
{
    return -1;
}

// Retorna o identificador do Nó selecionado
int Object::getNoSelec()
{
    return -1;
}

// Retorna a ordem da Curva B-Spline
int Object::getOrdCurva()
{
    return -1;
}

// Retorna o identificador do Ponto de Controle selecionado
int Object::getPtcSelec()
{
    return -1;
}

// Retorna a quantidade de pontos gerados para a curva
// B-Spline
int Object::getQuant()
{
    return -1;
}

// Incrementa/Decrementa o valor de um nó selecionado
int Object::incNo(double inc)
{
    return -1;
}

// Remove o Ponto de Controle Selecionado
int Object::rmvPtControle()
{
    return -1;
}

// Define o valor da ordem da curva B-Spline
void Object::setOrdCurva(int ord){}

// Define a quantide de Pontos que terá a curva B-Spline
void Object::setQuant(int valor){}

// Nurbs
// Retorna a lista de Pesos
vector<float> Object::getPesos()
{
    vector<float> nulo;
    return nulo;
}

// Nurbs
// Altera o peso de um ponto de Controle selecionado
void Object::setPeso(float valor){}

// Adciona um Segmento extremo da curva, 
// os Segmentos extremos da Curva
// tem de estar selecionados
int Object::addSegment()
{
    return -1;
}

// Remove um Segmento extremo da curva, 
// os Segmentos extremos da Curva
// tem de estar selecionados
int Object::removeSegment()
{
    return -1;
} 

vector<double> Object::getNo()
{
    vector<double> nulo;
    return nulo;
}

void Object::setNoSelec(int id){}