#include "Segment.h"
#include <iostream>

// Construtor
Segment::Segment(void)
{
	c.push_back(0);
	c.push_back(0);
	c.push_back(0);
	c.push_back(0);

	p1.push_back(0);
	p1.push_back(0);
	p1.push_back(0);
	p1.push_back(0);

	p2.push_back(0);
	p2.push_back(0);
	p2.push_back(0);
	p2.push_back(0);

	pontoSelecionado = -1;
}

// Destrutor
Segment::~Segment(void)
{}

// Retorna o Ponto Central do Segmento
vector<float> Segment::getC()
{
	return c;
}

// Retorna o Ponto Inicial do Segmento
vector<float>  Segment::getP1()
{
	return p1;
}

// Retorna o Ponto Final do Segmento
vector<float> Segment::getP2()
{
	return p2;
}

// Retorna 0 para indicar que o Ponto Central está selecionado
// Retorna 1 para indicar que o Ponto Inicial está selecionado
// Retorna 2 para indicar que o Ponto Final está selecionado
int Segment::getPtSelect()
{
	return pontoSelecionado;
}

// Define um valor para o Ponto Central do Segmento
void Segment::setC(float x,float y,float z)
{
	// Diferença entre o ponto central
	// e o novo ponto central
	float difX = x - c[0];
	float difY = y - c[1];
	float difZ = z - c[2];

	c[0] = x;
	c[1] = y;
	c[2] = z;	

	// Atualiza os demais pontos para deixa-los colineares
	// e manter a forma do segmento
	p1[0] = p1[0] + difX;
	p1[1] = p1[1] + difY;
	p1[2] = p1[2] + difZ;

	p2[0] = p2[0] + difX;
	p2[1] = p2[1] + difY;
	p2[2] = p2[2] + difZ;
}

// Define um valor para o Ponto Inicial do Segmento
void Segment::setP1(float x,float y,float z)
{
	vector<float> novoptExtremo;

	p1[0] = x;
	p1[1] = y;
	p1[2] = z;	

	novoptExtremo = atualiza(p1,p2,c);
	p2[0] = novoptExtremo[0];
	p2[1] = novoptExtremo[1];
	p2[2] = novoptExtremo[2];
}

// Define um valor para o Ponto Final do Segmento
void Segment::setP2(float x,float y,float z)
{	
	vector<float> novoptExtremo;

	p2[0] = x;
	p2[1] = y;
	p2[2] = z;	

	novoptExtremo = atualiza(p2,p1,c);
	p1[0] = novoptExtremo[0];
	p1[1] = novoptExtremo[1];
	p1[2] = novoptExtremo[2];
}

// Define o estado de uso do Ponto C
void Segment::setCStatus(float status)
{
	c[3] = status;
}

// Define o estado de uso do Ponto P1
void Segment::setP1Status(float status)
{
	p1[3] = status;
}

// Define o estado de uso do Ponto P2
void Segment::setP2Status(float status)
{
	p2[3] = status;
}

// Define qual ponto do Segmento está selecionado
void Segment::setPtSelect(int tp)
{
	pontoSelecionado = tp;
}

// Modulos Privados

// Calcula Distância entre dois Pontos
float Segment::distancia(vector<float> p1, vector<float> p2)
{
	float d = sqrt(pow(p1[0]-p2[0],2)+pow(p1[1]-p2[1],2)+pow(p1[2]-p2[2],2));

	return d;
}

// Atualiza um Ponto Extremo do segmento
vector<float> Segment::atualiza(vector<float> novoPt, 
					  			vector<float> ptExtremo,
					  			vector<float> ptcentral)
{
	// Ponto Extremo
	vector<float> novoptExtremo;

	// Distancia entre ptcentral e ptExtremo
	float d = distancia(ptExtremo,ptcentral);

	// Vetor V ,não normalizado
	float vX = ptcentral[0] - novoPt[0];
	float vY = ptcentral[1] - novoPt[1];
	float vZ = ptcentral[2] - novoPt[2];

	// Norma do Vetor
	float normaV = sqrt(pow(vX,2)+pow(vY,2)+pow(vZ,2));

	// Vetor V normalizado
	vX = vX / normaV;
	vY = vY / normaV;
	vZ = vZ / normaV;

	// Calculo do Novo Ponto Extremo
	novoptExtremo.push_back(ptcentral[0]+(vX*d) ) ;
	novoptExtremo.push_back(ptcentral[1]+(vY*d) );
	novoptExtremo.push_back(ptcentral[2]+(vZ*d) );

	return novoptExtremo;
}