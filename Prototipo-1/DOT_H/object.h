/*classe projetada para auxiliar a classe BasciPlane*/

#ifndef OBJECT_H
#define OBJECT_H

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define BASE 180
#define GLM_FORCE_RADIANS

#define BLUE	0.0, 0.0, 1.0, 1.0
#define PURPLE	0.52, 0.12, 0.47, 1.0
#define CYAN	0.0, 1.0, 1.0, 1.0
#define RED		1.0, 0.0, 0.0, 1.0
#define YELLOW	1.0, 1.0, 0.0, 1.0
#define GREENF	0.14, 0.56, 0.14, 1.0
#define GREEN	0.0, 1.0, 0.0, 1.0
#define ORANGE	1.0, 0.40, 0.0, 1.0
#define WHITE	1.0, 1.0, 1.0, 1.0
#define BLACK	0.0, 0.0, 0.0, 0.0
#define DAY		1.0, 1.0, 0.98, 1.0
#define NIGHT	0.030, 0.030, 0.08, 1.0
#define GRAY1	0.7, 0.7, 0.7, 1.0
#define GRAY2	0.93, 0.93, 0.93, 1.0
#define COBRE	0.85, 0.52, 0.1, 1.0
#define SKY		0.22, 0.70, 0.87, 1.0
#define AQUA	0.19, 0.80, 0.6, 1.0
#define PINK	1.0, 0.10, 0.68, 1.0
#define GOLD	0.85, 0.85, 0.09, 1.0
#define ESC		0.55, 0.09, 0.09, 1.0
#define SILVER	0.90, 0.91, 0.98, 1.0

#include  <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include <string>

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
	void scaleObject(float x, float y, float z);
	vector <float > getScale();
	vector <float >getTranslation();
	vector <float >getRotation();
	virtual void rotateObject(vector <float > newRotation);
	virtual void setGlobalScale( float x, float y, float z);
	virtual void setGlobalRotation( float x, float y, float z);
	virtual void draw(int index_load, bool is_selecting, int size_world);
	void setTipo(const char * val);
	string getTipo();
	void setSelected(bool is_selected);
	void setRenderMode(bool mode);
	bool getRenderMode();
	float getDepth();
	void setGlobalTranslation(vector <float > newTranslation);
	vector <float > getGlobalTranslation();

	void setHitIndexInternal(int val);
	int  getHitIndexInternal();

	virtual int getSizeControlPoints();

	virtual vector <float > getControlPointSelected();

	virtual void setPtControleModifier(float x, float y, float z);

	virtual void translateObject( vector <float > newTranslation);	

	/*****************************************************/
	// Metodos das Curvas
	// Altera a posição do ponto de um segmento que está
	// selecionado
	virtual void setPtControle(float x, float y, float z);

	// Atualiza os pontos da Curva
	virtual void updatePtsCurv();

	// Duplica um Ponto de Controle Extremo
	// Um dos Pontos de Controles Extremos
	// tem de estarem selecionados
	virtual int addPtControle();

	// Adiciona um Ponto de Controle Extremo
	// Um dos Pontos de Controles Extremos
	// tem de estarem selecionados
	virtual int addPtControle(float x, float y, float z);

	// Retorna as Imagens dos Nós na Curva
	// As imagens dos nós são os pontos iniciais
	// de cada segmento da curva B-Spline
	virtual vector<float> getImgNo();

	// Retorna o identificador do Nó selecionado
	virtual int getNoSelec();

	// Retorna a ordem da Curva B-Spline
	virtual int getOrdCurva();

	// Retorna o identificador do Ponto de Controle selecionado
	virtual int getPtcSelec();

	// Retorna a quantidade de pontos gerados para a curva
	// B-Spline
	virtual int getQuant();

	// Incrementa/Decrementa o valor de um nó selecionado
	virtual int incNo(double inc);

	// Remove o Ponto de Controle Selecionado
	virtual int rmvPtControle();

	// Define o valor da ordem da curva B-Spline
	virtual void setOrdCurva(int ord);

	// Define a quantide de Pontos que terá a curva B-Spline
	virtual void setQuant(int valor);

	// Nurbs
	// Retorna a lista de Pesos
	virtual vector<float> getPesos();
	virtual float getPesoSelec();

	// Retorna os Nós
	virtual vector<double> getNo();

	// Define o identificador do Nó Selecionado
	virtual void setNoSelec(int id);

	// Nurbs
	// Altera o peso de um ponto de Controle selecionado
	virtual void setPeso(float valor);

	// Adciona um Segmento extremo da curva, 
	// os Segmentos extremos da Curva
	// tem de estar selecionados
	virtual int addSegment();

	// Remove um Segmento extremo da curva, 
	// os Segmentos extremos da Curva
	// tem de estar selecionados
	virtual int removeSegment();

	virtual void setModifier(int tp);	

protected:

	/*metodos que auxiliam no set do ambiente opengl e desenhos de primitvas basicas*/
	vector < float * > vertex;
	vector < float  > position;
	vector < float  > rotation;
	vector < float  > translation;
	vector < float  > scale;
	vector < float  > color;
	vector < float  > global_translation;

	bool is_selected;

	// Indice dos Objetos Interno no Modo Edição
	int index_internal;
	// Valor do Indice do objeto interno selecionado
	int hit_index_internal;

	int render_mode;

	bool visible;
	int GL_PRIMITIVE;
	string tipo;

	vector <float > globalScale;
	vector <float > globaRotation;
};




#endif
