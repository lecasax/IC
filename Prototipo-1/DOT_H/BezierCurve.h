#include "Segment.h"
#include "BezierCubic.h"
#include "Nurbs.h" // Inclusão do Objeto em Nurbs->BSpliens->Objeto

//Object *bezier = new BezierCurve(0,0,0);
//world.push_back(bezier);

using namespace std;

class BezierCurve: public Object
{

public:

	// Construtores
	BezierCurve(float x, float y,float z);
	~BezierCurve(void);

	// Atualiza os pontos da Curva 
	void updatePtsCurv();

	// Retorna os pontos da Curva
	vector<float> getPtsCurva();

	// Retorna a Lista de Segmentos
	vector<Segment> getSegments();

	// Retorna o indice do segmento selecionado
	int getSelectSegments();

	// Retorna a quantidade de Vertices que compem a curva
	int getQuant();

	// Define a quantidade de Vertices que compem a curva
	void setQuant(int valor);

	// Define o Segmento e o Ponto do Segmento, selecionado
	void setSelectSegments(int seg, int point);

	// Altera a posição do ponto de um segmento que está
	// selecionado
	void setPtControle(float x, float y,float z);

	// Adciona um Segmento extremo da curva, 
	// os Segmentos extremos da Curva
	// tem de estar selecionados
	int addSegment();

	// Remove um Segmento extremo da curva, 
	// os Segmentos extremos da Curva
	// tem de estar selecionados
	int removeSegment();

	// draw
	void draw(int index_load,  bool is_selecting);
	
private:

	// Bezier Cubica
	BezierCubic bzcubic;

	// Todos os Pontos da Curva de Bezier 
	// Pontos da Curva de Bezier Cubica
	// A Cada 3 elementos tem-se um ponto representando 
	// px,py,pz 	
	vector<float> ptsCurv;

	// Lista de Segmentos de Controle da Curva
	vector<Segment> segments;

	// Indice que representa o Segmento de controle selecionado
	int selectSegments;

	// Quantidade de Vertices que compem a curva
	int quant;

	// Retorna os Pontos de Controle do Segmento que serão usados
	// para gerar a curva de Bezier
	vector< vector<float> > usedControlPts();

	void ponteiro(float x,float y,float z, int size);
};