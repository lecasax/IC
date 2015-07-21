#include "BSplines.h"

using namespace std;

class Nurbs: public BSplines
{

public:

	// Construtores
	Nurbs(float x, float y, float z);
	~Nurbs(void);

	// Retorna a lista de Pesos
	vector<float> getPesos();
	float getPesoSelec();

	// Altera o peso de um ponto de Controle selecionado
	void setPeso(float valor);

	// Atualiza/Processa os pontos da curva Nurbs
	void updatePtsCurv();

	// Duplica um Ponto de Controle Extremo
	// Um dos Pontos de Controles Extremos
	// tem de estarem selecionados
	int addPtControle();

	// Adiciona um Ponto de Controle Extremo
	// Um dos Pontos de Controles Extremos
	// tem de estarem selecionados
	int addPtControle(float x, float y, float z);

	// Remove o Ponto de Controle Selecionado
	int rmvPtControle();

	// draw
	//void draw(int index_load,  bool is_selecting);

	//void draw(int index_load,  bool is_selecting);	

private:

	// Lista de Pesos
	vector<float> pesos;

	// Inicializa a lista de nós
	void iniNo();
};