#include <GL/glut.h>
#include <vector>
#include "object.h"
#include "modifier.h"


using namespace std;

class BSplines: public Object 
{

public:

	// Construtores
	BSplines(BSplines * bspline);
	BSplines(float x, float y, float z);
	BSplines(void);
	~BSplines(void);


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
	vector<float> getImgNo();

	// Retorna os Nós
	vector<double> getNo();

	// Retorna o identificador do Nó selecionado
	int getNoSelec();

	// Retorna a ordem da Curva B-Spline
	int getOrdCurva();

	// Retorna a lista bi-dimensional dos pontos de controle
	vector< vector<float> > getPtControle();

	// Retorna o identificador do Ponto de Controle selecionado
	int getPtcSelec();

	// Retorna os pontos da curva B-Spline
	// A Cada 3 elementos da lista tem-se um ponto representando 
	// px,py,pz 	
	vector<float> getPtsCurva();

	// Retorna a quantidade de pontos gerados para a curva
	// B-Spline
	int getQuant();

	// Incrementa/Decrementa o valor de um nó selecionado
	int incNo(double inc);

	// Remove o Ponto de Controle Selecionado
	virtual int rmvPtControle();

	// Define o identificador do Nó Selecionado
	void setNoSelec(int id);

	// Define o valor da ordem da curva B-Spline
	void setOrdCurva(int ord);

	// Define as coordenadas do Ponto de Controle Selecionado
	void setPtControle(float x, float y, float z);

	// Define o identificador do Ponto de Controle Selecionado
	void setPtcSelec(int id);

	// Define a quantide de Pontos que terá a curva B-Spline
	void setQuant(int valor);

	// Atualiza/Processa os Pontos da Curva B-Spline
	virtual void updatePtsCurv();

	// draw
	void draw(int index_load,  bool is_selecting, int size_world);

	int getSizeControlPoints();

	void setModifier(int tp);

	vector <float > getControlPointSelected();

	void setPtControleModifier(float x, float y, float z);

protected:

	Modifier modifier;

	// Quantidade de Pontos da Curva
	int quant;

	// Identificador do Nó Selecionado
	int noSelec;

	// Ordem da Curva B-Spline
	int ordCurva;

	// Identificador do Ponto de Controle Selecionado
	int ptcSelec;

	// Lista de Nos usados para geração da curva B-Spline	
	vector<double> nos;

	// Lista de Pontos da Curva B-Spline
	// A Cada 3 elementos da lista tem-se um ponto representando 
	// px,py,pz 	
	vector<float> ptsCurv;

	// Lista Bidimensional Representando os Pontos de Controle
	vector< vector<float> > ptControle;

	// Gerencia os Nos
	void gerencNo();

	// Insere um novo nó
	void insertNode(int tipo);

	// Remove um nó 
	void rmvNode(int tipo);

	// Normaliza a lista de nós
	void normaNos();

	// Inicializa os Nos
	virtual void iniNo();

	// Funcao Base Splines
	// i é o indice
	// k é a ordem de continuidade da curva
	// u é o parametro
	double bspline(int i, int k, double u);
};
