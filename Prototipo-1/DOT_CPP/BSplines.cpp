#include "BSplines.h"


/* Public */

// Construtores
BSplines::BSplines(float x, float y, float z):Object()
{
	vector<float> p1,p2,p3,p4;

	quant = 80;
	ordCurva = 4;
	ptcSelec = -1;
	noSelec = -1;

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


	// Tipo Curva BSpline
	setTipo("BSplines");
	iniNo();

	this->updatePtsCurv();
}

//Construtor
BSplines::BSplines(void)
{
	quant = 80;
	ordCurva = 4;
	ptcSelec = -1;
	noSelec = -1;
}

// Destrutor
BSplines::~BSplines(void)
{}

// Duplica um Ponto de Controle Extremo
// Um dos Pontos de Controles Extremos
// tem de estarem selecionados
int BSplines::addPtControle(void)
{
	vector<float> aux;

	if( ptcSelec == 0  ){

		aux = ptControle[0];

		ptControle.insert(ptControle.begin(), aux);

		insertNode(0);

	} else if(ptcSelec == ((int) ptControle.size()) -1) {

		aux = ptControle[ptcSelec];

		ptControle.push_back(aux);

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
int BSplines::addPtControle(float x, float y, float z)
{
	vector<float> aux;

	aux.push_back(x);
	aux.push_back(y);
	aux.push_back(z);

	if( ptcSelec == 0  ){

		ptControle.insert(ptControle.begin(), aux);

		insertNode(0);

	} else if(ptcSelec == ((int) ptControle.size()) -1) {

		ptControle.push_back(aux);

		insertNode(1);

		ptcSelec++;

	} else {

		return 0;
	}

	return 1;
}

// Retorna as Imagens dos Nós na Curva
// As imagens dos nós são os pontos iniciais
// de cada segmento da curva B-Spline
vector<float> BSplines::getImgNo()
{
	int i = 0,j = 0;
	double coefs = 0;
	float x = 0, y = 0, z = 0;

	vector<float> pts;

	for(i = ordCurva-1; i <= ((int) nos.size())-ordCurva; i++){

		x = y = z = 0;

		for(j = 0; j < (int) ptControle.size(); j++)
		{
			coefs = bspline(j,ordCurva,nos[i]);

			x = x + (coefs * ptControle[j][0]);

			y = y + (coefs * ptControle[j][1]);

			z = z + (coefs *ptControle[j][2]);
		}
		pts.push_back(x);
		pts.push_back(y);
		pts.push_back(z);

	}

	return pts;
}

// Retorna os Nós
vector<double> BSplines::getNo()
{
	return nos;
}

// Retorna o identificador do Nó selecionado
int BSplines::getNoSelec()
{
	return noSelec;
}

// Retorna a ordem da Curva B-Spline
int BSplines::getOrdCurva()
{
	return ordCurva;
}

// Retorna a lista bi-dimensional dos pontos de controle
vector< vector<float> > BSplines::getPtControle()
{
	return ptControle;
}

// Retorna o identificador do Ponto de Controle selecionado
int BSplines::getPtcSelec()
{
	return ptcSelec;
}

// Retorna os pontos da curva B-Spline
// A Cada 3 elementos da lista tem-se um ponto representando
// px,py,pz
vector<float> BSplines::getPtsCurva()
{
	return ptsCurv;
}

// Retorna a quantidade de pontos gerados para a curva
// B-Spline
int BSplines::getQuant()
{
	return quant;
}

// Incrementa/Decrementa o valor de um nó selecionado
int BSplines::incNo(double inc)
{
	int i = 0;
	int j = 0;

	vector<double> noscopia = nos;

	if(noSelec != -1){

		if(inc < 0){

			nos[noSelec] = nos[noSelec] + inc;

			for(i = noSelec; i > 0; i--){

				if(nos[i-1] >= nos[i]){

					nos[i-1] = nos[i];
					j++;

				} else {

					break;
				}
			}

		} else if(inc > 0){

			nos[noSelec] = nos[noSelec] + inc;

			for(i = noSelec; i < (int) nos.size()-1; i++){

				if(nos[i+1] <= nos[i]){

					nos[i+1] = nos[i];
					j++;

				} else {

					break;
				}
			}
		}

		if(j + 1 > ordCurva){

			nos = noscopia;

			return 0;

		} else {

			return 1;
		}

	} else {

		return 0;
	}
}

// Remove o Ponto de Controle Selecionado
int BSplines::rmvPtControle()
{
	if(ptcSelec == 0) {

		ptControle.erase(ptControle.begin());

		rmvNode(0);

	} else if(ptcSelec == (int) ptControle.size()-1) {

		ptControle.erase(ptControle.begin()+ptcSelec);

		ptcSelec--;

		rmvNode(1);

	} else if(ptcSelec > 0 && ptcSelec < (int) ptControle.size()-1){

		ptControle.erase(ptControle.begin()+ptcSelec);

		rmvNode(2);

	} else {

		return 0;
	}

	return 1;
}

// Define o identificador do Nó Selecionado
void BSplines::setNoSelec(int id)
{
	noSelec = id;
}

// Define o valor da ordem da curva B-Spline
void BSplines::setOrdCurva(int ord)
{
	int dif = ord - ordCurva;

	ordCurva = ord;

	if(dif < 0){

		while(dif < 0){

			rmvNode(1);
			gerencNo();

			dif++;
		}

	} else if(dif > 0){

		while(dif > 0){

			insertNode(1);
			dif--;
		}
	}

	normaNos();
}

// Define as coordenadas do Ponto de Controle Selecionado
void BSplines::setPtControle(float x, float y, float z)
{
	if(ptcSelec >= 0){

		ptControle[ptcSelec][0] = x-translation[0];
		ptControle[ptcSelec][1] = y-translation[1];
		ptControle[ptcSelec][2] = z-translation[2];
	}
}

// Define o identificador do Ponto de Controle Selecionado
void BSplines::setPtcSelec(int id)
{
	ptcSelec = id;
}

// Define a quantide de Pontos que terá a curva B-Spline
void BSplines::setQuant(int valor)
{
	quant = valor;
}

// Atualiza/Processa os Pontos da Curva B-Spline
void BSplines::updatePtsCurv()
{
	int i = 0;
	double t = 0, inic = nos[ordCurva-1], fim = nos[ ((int)nos.size())-ordCurva];
	double inc = ( fim - inic ) / quant;
	float x = 0, y = 0, z = 0;
	float coefbs = 0;
	vector<float> pts;

	if(inic == fim){

		inic = nos[ordCurva-1];
		fim = nos[((int) nos.size())-(ordCurva-1)];
		inc = ( fim - inic ) / quant;
	}

	for(t = inic; t <= fim; t+=inc){

		x = y = z = 0;

		for(i = 0; i < (int) ptControle.size(); i++){

			coefbs = bspline(i,ordCurva,t);

			x = x + (coefbs * ptControle[i][0]);

			y = y + (coefbs * ptControle[i][1]);

			z = z + (coefbs * ptControle[i][2]);
		}

		pts.push_back(x);
		pts.push_back(y);
		pts.push_back(z);

	}

	ptsCurv = pts;
}

/* Private */

// Gerencia os Nos
void BSplines::gerencNo()
{
	int i = 0;
	int j = 0;
	float dif = 0;
	int k = 0;

	while(j < (int) nos.size()){

		i = 0;

		while(nos[i+j] == nos[i+1+j] && (i+j) < (int) nos.size() -1){

			i++;
		}

		if( i + 1 > ordCurva){

			 if (i + j < (int) nos.size() -1){

				dif = nos[i+1+j] - nos[i+j];

				for(k = i+j; k < (int) nos.size(); k++){
					nos[k] = nos[k] + dif;
				}

			} else {

				dif = nos[j] - nos[j-1];

				for(k = j; k >= 0; k--){

					nos[k] = nos[k] - dif;
				}
			}

		}

		if( i+1 - ordCurva < 2){

			j = j + i + 1;
		}
	}
}

// Insere um novo nó
void BSplines::insertNode(int tipo)
{
	double dif = 0;
	int i,j,inc;
	j = 0;

	if(tipo == 0){

		i = 0;
		inc = 1;

	} else {

		i = ((int) nos.size())-1;
		inc = -1;
	}

	while(nos[i] == nos[i+inc]){

		i = i + inc ;
	}

	if(tipo == 0){

		dif = nos[i+inc] - nos[i];
		nos.insert(nos.begin() + i, nos[i+inc] - dif );

	} else {

		dif = nos[i] - nos[i+inc];
		nos.insert(nos.begin() + i, nos[i+inc] + dif );
	}

	if(tipo == 0){

		for(j = i; j >= 0; j--){

			nos[j] = nos[j] - dif;
		}

		for(j = 0; j < (int) nos.size(); j++){

			nos[j] = nos[j] + dif;
		}

	} else {

		for(j = i+1; j < (int) nos.size(); j++){

			nos[j] = nos[j]+dif;
		}
	}

	normaNos();
}

// Remove um nó
void BSplines::rmvNode(int tipo)
{
	int j = 0;
	int i = 0;
	double dif = 0;

	if(tipo == 0){

		while(nos[i] == nos[i+1]){
			i++;
		}

		i++;

		dif = nos[i+1] - nos[i];

		nos.erase(nos.begin()+i);

		for(j = i; j > 0; j--){

			nos[j] = nos[j] + dif;
		}

	} else if(tipo == 1) {

		i = nos.size();
		while(nos[i] == nos[i-1]){
			i--;
		}

		i--;

		dif = nos[i] - nos[i-1];

		nos.erase(nos.begin()+i);

		for(j = i; j < (int) nos.size(); j++){

			nos[j] = nos[j] - dif;
		}

	} else if(tipo == 2) {

		i = ptcSelec + ordCurva - 2;

		dif = nos[i+1] - nos[i];

		nos.erase(nos.begin()+i);

		for(j = i-1; j >= 0; j--){

			nos[j] = nos[j] + dif;
		}
	}

	normaNos();
}

// Normaliza a lista de nós
void BSplines::normaNos(){
/*
	int i = 0;
	int n = nos.size();
	double dif = 0 - nos[0];
	double coef = 1 / (nos[n-1]+dif);

	for(i = 0; i < n; i++){

		nos[i] = (nos[i]+dif) * coef;
	}*/
}

// Inicializa os Nos
void BSplines::iniNo()
{
	int i = 0, aux = 0;

	for(i = 0; i < (int) ptControle.size()+ordCurva; i++){

		nos.push_back(aux);
		aux = aux + 10;
	}

	normaNos();
}

// Funcao Base Splines
// i é o indice
// k é a ordem de continuidade da curva
// u é o parametro
double BSplines::bspline(int i, int k, double u)
{
   double coef1, coef2;
   if ( k == 1 )
   {
	  if ( i == 0 ) if ( ( nos[i] <= u ) && ( u <= nos[i+1] ) ) return 1.0;
      if ( ( nos[i] < u ) && ( u <= nos[i+1] ) ) return 1.0;
	  else return 0.0;
   }
   else
   {
      if ( nos[i+k-1] == nos[i] )
	  {
	     if ( u == nos[i] ) coef1 = 1;
		 else coef1 = 0;
	  }
	  else coef1 = (u - nos[i])/(nos[i+k-1] - nos[i]);

      if ( nos[i+k] == nos[i+1] )
	  {
		 if ( u == nos[i+k] ) coef2 = 1;
		 else coef2 = 0;
	  }
	  else coef2 = (nos[i+k] - u)/(nos[i+k] - nos[i+1]);

      return ( coef1 * bspline(i, k-1, u) + coef2 * bspline(i+1 ,k-1 ,u) );
   }
}

void BSplines::draw(int index_load,  bool is_selecting)
{
	int i,k,j;
	int sizePtc = (int) ptControle.size();
	int sizeCur = (int) ptsCurv.size();
	vector<float> pt;

	GLfloat m[16];
	vector <float > c = getColor();
    vector <float > r = getRotation();
    vector <float > t = getTranslation();
    vector <float > s = getScale();

    glm::quat quat (glm::vec3(r[0]*PI/BASE, r[1]*PI/BASE, r[2]*PI/BASE));
    glm::quat quaternion = quat ;
    glm::mat4 mat  = glm::toMat4(quaternion);

    int count = 0;
    for ( k = 0; k < 4; ++k){
        for ( j = 0; j < 4; ++j){
            m[count] = mat[k][j];
            count++;
        }
    }

    glPushMatrix();
    // Aplicar Transformações Geométricas
    glColor3f(c[0],c[1],c[2]);
    glScalef(s[0], s[1], s[2]);
    glTranslatef(t[0],t[1],t[2]);
    glMultMatrixf(m);

    if( !render_mode && this->is_selected){

    	// Modo Edição
    	index_internal = 0;

    	for(i = 0; i < sizePtc; i++){

    		index_internal++;

    		glLoadName(index_internal);
    		glColor4f(BLACK);
    		if(index_internal == hit_index_internal){
    			glColor4f(ORANGE);
    			this->setPtcSelec(i);
    		}

    		glPushMatrix();
    		glTranslatef(ptControle[i][0],ptControle[i][1],ptControle[i][2]);
    		glutSolidCube(2);
    		glPopMatrix();
    	}

    	if(!is_selecting){

			this->updatePtsCurv();

			if(this->is_selected){
				glColor4f(GREEN);
			} else {
				glColor4f(RED);
			}
			// Desenha Curva
			glPushMatrix();
				glBegin(GL_LINE_STRIP);
				for(j = 0; j < sizeCur; j+=3){
					glVertex3f(ptsCurv[j],ptsCurv[j+1],ptsCurv[j+2]);
				}
				glEnd();
			glPopMatrix();

			// Linha entre cada Ponto de Controle
			glColor4f(BLACK);
			glLineStipple(1,0xAAAA);
			glEnable(GL_LINE_STIPPLE);
			glBegin(GL_LINE_STRIP);
			for(j = 0; j < sizePtc; j++){
				glVertex3f(ptControle[j][0],ptControle[j][1],ptControle[j][2]);
			}
			glEnd();
			glDisable(GL_LINE_STIPPLE);

			// Nós
			pt = getImgNo();
			glColor4f(SKY);
			glPointSize(5);
			glBegin(GL_POINTS);
			for(j = 0; j < (int) pt.size(); j+= 3){

				glVertex3f(pt[j],pt[j+1],pt[j+2]);
			}

			glEnd();
		}

    } else {

		// Modo Objeto
		if(render_mode){

	    	glLoadName(index_load);

			if(this->is_selected){
				glColor4f(GREEN);
			} else {
				glColor4f(RED);
			}

			glPushMatrix();
				glBegin(GL_LINE_STRIP);
				for(i = 0; i < sizeCur; i+=3){
					glVertex3f(ptsCurv[i],ptsCurv[i+1],ptsCurv[i+2]);
				}
				glEnd();
			glPopMatrix();

		} else if(!is_selecting){
			// Modo Edição nao selecionado
	    	glLoadName(index_load);

			if(this->is_selected){
				glColor4f(GREEN);
			} else {
				glColor4f(RED);
			}

			glPushMatrix();
				glBegin(GL_LINE_STRIP);
				for(i = 0; i < sizeCur; i+=3){
					glVertex3f(ptsCurv[i],ptsCurv[i+1],ptsCurv[i+2]);
				}
				glEnd();
			glPopMatrix();
		}
    }

    glPopMatrix();
}