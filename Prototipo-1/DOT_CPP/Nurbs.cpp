#include "Nurbs.h"
#include <iostream>

// Construtor
Nurbs::Nurbs(float x, float y, float z):BSplines()
{
	vector<float> p1,p2,p3,p4;

	p1.push_back(x);
	p1.push_back(y);
	p1.push_back(z);

	p2.push_back(x+20);
	p2.push_back(y+20);
	p2.push_back(z);

	p3.push_back(x+40);
	p3.push_back(y+20);
	p3.push_back(z);

	p4.push_back(x+60);
	p4.push_back(y);
	p4.push_back(z);

	ptControle.push_back(p1);
	ptControle.push_back(p2);
	ptControle.push_back(p3);
	ptControle.push_back(p4);

	pesos.push_back(1);
	pesos.push_back(1);
	pesos.push_back(1);
	pesos.push_back(1);
	
	iniNo();

	// Tipo Curva Nurbs
	setTipo(2);
}

// Destrutor
Nurbs::~Nurbs(void)
{
}


void Nurbs::setTipo(int val)
{
	tipo = val;
}

// Retorna a lista de Pesos
vector<float> Nurbs::getPesos()
{
	return pesos;
}

// Altera o peso de um ponto de Controle selecionado
void Nurbs::setPeso(float valor)
{
	if(ptcSelec >= 0){

		pesos[ptcSelec] = valor;
	}
}

// Atualiza/Processa os pontos da curva Nurbs
void Nurbs::updatePtsCurv()
{
	int i = 0;
	double t = 0, inic = nos[ordCurva-1], fim = nos[((int)nos.size())-ordCurva];
	double inc = ( fim - inic ) / quant;
	float x = 0, y = 0, z = 0;
	float x2 = 0, y2 = 0, z2 = 0;

	float coefbs = 0;
	vector<float> pts;
			
	if(inic == fim){

		inic = nos[ordCurva-1];
		fim = nos[((int)nos.size())-(ordCurva-1)];
		inc = ( fim - inic ) / quant;
	}

	for(t = inic; t <= fim; t+=inc){

		x = y = z = 0;
		x2 = y2 = z2 = 0;
		
		for(i = 0; i < (int) ptControle.size(); i++){

			coefbs = bspline(i,ordCurva,t);			

			x = x + (coefbs * ptControle[i][0] * pesos[i]);			
			x2 = x2 + (coefbs * pesos[i]);

			y = y + (coefbs * ptControle[i][1] * pesos[i]);
			y2 = y2 + (coefbs * pesos[i]);	

			z = z + (coefbs * ptControle[i][2] * pesos[i]);
			z2 = z2 + (coefbs * pesos[i]);			
		}
		
		pts.push_back(x/x2);
		pts.push_back(y/y2);
		pts.push_back(z/z2);
	}
	
	cout << "nos" <<endl;
	for(i = 0; i < (int) nos.size(); i++){
		cout << nos[i] << endl;
	}
	cout << endl;


	ptsCurv = pts;	
}

// Duplica um Ponto de Controle Extremo
// Um dos Pontos de Controles Extremos
// tem de estarem selecionados
int Nurbs::addPtControle()
{
	vector<float> aux;

	if( ptcSelec == 0  ){

		aux = ptControle[0];

		ptControle.insert(ptControle.begin(), aux);

		pesos.insert(pesos.begin(),1);

		insertNode(0);		

	} else if(ptcSelec == (int) ptControle.size() -1) {

		aux = ptControle[ptcSelec];

		ptControle.push_back(aux);

		pesos.push_back(1);

		insertNode(1);

		ptcSelec++;

	} else {

		return 0;
	}


	return 1;
}

// Adiciona um Ponto de Controle Extremo
// Um dos Pontos de Controles Extremos
// tem de estarem selecionados
int Nurbs::addPtControle(float x, float y, float z)
{
	vector<float> aux;

	aux.push_back(x);
	aux.push_back(y);
	aux.push_back(z);

	if( ptcSelec == 0  ){

		ptControle.insert(ptControle.begin(), aux);

		pesos.insert(pesos.begin(),1);

		insertNode(0);

	} else if(ptcSelec == ((int) ptControle.size()) -1) {

		ptControle.push_back(aux);

		ptControle.push_back(aux);

		insertNode(1);

		ptcSelec++;

	} else {

		return 0;
	}

	return 1;
}

// Remove o Ponto de Controle Selecionado
int Nurbs::rmvPtControle()
{	
	if(ptcSelec == 0) {

		ptControle.erase(ptControle.begin());
		
		pesos.erase(pesos.begin()+ptcSelec);

		rmvNode(0);

	} else if(ptcSelec == ((int) ptControle.size())-1) {

		ptControle.erase(ptControle.begin()+ptcSelec);

		pesos.erase(pesos.begin()+ptcSelec);

		ptcSelec--;

		rmvNode(1);

	} else if(ptcSelec > 0 && ptcSelec < ((int) ptControle.size())-1){

		ptControle.erase(ptControle.begin()+ptcSelec);

		pesos.erase(pesos.begin()+ptcSelec);

		rmvNode(2);	

	} else {
		
		return 0;
	}
	
	return 1;
}

// Inicializa a lista de nós
void Nurbs::iniNo()
{
	int i = 0;

	nos.assign(ptControle.size()+ordCurva,0);

	for(i = 0; i < ordCurva; i++){	
		nos[i] = 0;
		nos[((int)nos.size())-i-1] = (ordCurva * (ordCurva-1));
	}

	for(i = ordCurva; i < ((int) nos.size())-ordCurva; i++){		
		nos[i] = nos[i-1] + i * ordCurva;
	}

	normaNos();
}

void Nurbs::draw(int index_load,  bool is_selecting)
{

}