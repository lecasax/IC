#include <cmath>
#include <vector>

using namespace std;

class Segment
{

public:

	// Construtores 
	Segment(void);
	~Segment(void);

	// Retorna o Ponto Central do Segmento
	vector<float> getC();

	// Retorna o Ponto Inicial do Segmento
	vector<float> getP1();

	// Retorna o Ponto Final do Segmento
	vector<float> getP2();

	// Retorna 0 para indicar que o Ponto Central está selecionado
	// Retorna 1 para indicar que o Ponto Inicial está selecionado
	// Retorna 2 para indicar que o Ponto Final está selecionado
	int getPtSelect();

	// Define um valor para o Ponto Central do Segmento
	void setC(float x,float y,float z);

	// Define um valor para o Ponto Inicial do Segmento
	void setP1(float x,float y,float z);

	// Define um valor para o Ponto Final do Segmento
	void setP2(float x,float y,float z);

	// Define o estado de uso do Ponto C
	void setCStatus(float status);

	// Define o estado de uso do Ponto P1
	void setP1Status(float status);

	// Define o estado de uso do Ponto P2
	void setP2Status(float status);	

	// Define qual ponto do Segmento está selecionado
	void setPtSelect(int tp);

private:

	// Ponto Central do Segmento
	vector<float> c;

	// Ponto Inicial do Segmento
	vector<float> p1;

	// Ponto Final do Segmento
	vector<float> p2;

	// Indicador do Ponto Selecionado
	int pontoSelecionado;

	// Calcula Distância entre dois Pontos
	float distancia(vector<float> p1, vector<float> p2);

	// Atualiza um Ponto Extremo do segmento
	vector<float> atualiza(vector<float> novoPt, 
							vector<float> ptExtremo,
					 		vector<float> ptcentral);
};