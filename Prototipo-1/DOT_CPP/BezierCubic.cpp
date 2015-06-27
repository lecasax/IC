#include "BezierCubic.h"

// Construtor 
BezierCubic::BezierCubic(void)
{
}

// Destrutor 
BezierCubic::~BezierCubic(void)
{
}

// Função que calcula e retorna os pontos da curva de Beizer 
// Recebe o paramêtro t, que representa a a quantidade de pontos 
vector<float> BezierCubic::processaPontoControle(int quant)
{
	double t = 0;
	double inc = 1;
	double px = 0;
	double py = 0;
	double pz = 0;

	inc = inc / quant;

	pontosCurva.clear();

	for(t = 0; t <= 1; t = t + inc)
	{
		px = (pow(1-t,3)*ptC1[0]) + (3*t*pow(1-t,2)*ptC2[0]) + (3*pow(t,2)*(1-t)*ptC3[0]) + (pow(t,3)*ptC4[0]);
		py = (pow(1-t,3)*ptC1[1]) + (3*t*pow(1-t,2)*ptC2[1]) + (3*pow(t,2)*(1-t)*ptC3[1]) + (pow(t,3)*ptC4[1]);
		pz = (pow(1-t,3)*ptC1[2]) + (3*t*pow(1-t,2)*ptC2[2]) + (3*pow(t,2)*(1-t)*ptC3[2]) + (pow(t,3)*ptC4[2]);

		pontosCurva.push_back(px);
		pontosCurva.push_back(py);
		pontosCurva.push_back(pz);

		px = 0;
		py = 0;
		pz = 0;
	}

	return pontosCurva;
}

// Define os 4 pontos de controle da curva de Bezier Cubica 
// Recebe como paramêtro os 4 pontos de controle 
void BezierCubic::setPtControles(float p1[], float p2[], float p3[], float p4[])
{
	ptC1[0] = p1[0];
	ptC1[1] = p1[1];
	ptC1[2] = p1[2];

	ptC2[0] = p2[0];
	ptC2[1] = p2[1];
	ptC2[2] = p2[2];

	ptC3[0] = p3[0];
	ptC3[1] = p3[1];
	ptC3[2] = p3[2];

	ptC4[0] = p4[0];
	ptC4[1] = p4[1];
	ptC4[2] = p4[2];
}