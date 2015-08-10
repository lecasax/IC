#include <vector>
#include <cmath>

using namespace std;

class BezierCubic
{

public:

	// Construtores 
	BezierCubic(void);
	~BezierCubic(void);

	// Função que calcula e retorna os pontos da curva de Beizer 
	// Recebe o paramêtro quant, que representa a a quantidade de pontos 
	vector<float> processaPontoControle(int quant);

	// Define os 4 pontos de controle da curva de Bezier Cubica 
	// Recebe como paramêtro os 4 pontos de controle 
	void setPtControles(float p1[], float p2[], float p3[], float p4[]);

private:

	// Pontos da Curva de Bezier Cubica
	// A Cada 3 elementos tem-se um ponto representando 
	// px,py,pz 
	vector<float> pontosCurva;
	
	// Pontos de Controle da Curva de Bezier Cubica 
	float ptC1[3];
	float ptC2[3];
	float ptC3[3];
	float ptC4[3];
};