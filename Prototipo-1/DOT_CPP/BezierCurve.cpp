#include "BezierCurve.h"
#include <iostream>




// Construtor

BezierCurve::BezierCurve(BezierCurve *BezierCurve):Object()
{
	this->translation = BezierCurve->translation;
    this->rotation = BezierCurve->rotation;
    this->scale = BezierCurve->scale;
	// Todos os Pontos da Curva de Bezier
	// Pontos da Curva de Bezier Cubica
	// A Cada 3 elementos tem-se um ponto representando
	// px,py,pz
	this->ptsCurv = BezierCurve->getPtsCurva();;

	// Lista de Segmentos de Controle da Curva
	this->segments = BezierCurve->getSegments();;

	// Quantidade de Vertices que compem a curva
	this->quant = BezierCurve->getQuant();;

	this->updatePtsCurv();

    this->setTipo("BezierCurve");
}

BezierCurve::BezierCurve(float x, float y,float z):Object()
{
	// Inicialização da Curva
	Segment s1,s2;

	s1.setC(x,y,z);
	s1.setCStatus(1);

	s1.setP1(x,y-20,z);
	s1.setP1Status(0);

	s1.setP2(x,y+20,z);
	s1.setP2Status(1);

	s2.setC(x+40,y,z);
	s2.setCStatus(1);

	s2.setP1(x+40,y-20,z);
	s2.setP1Status(1);

	s2.setP2(x+40,y+20,z);
	s2.setP2Status(0);

	segments.push_back(s1);
	segments.push_back(s2);

	selectSegments = -1;
	quant = 80;

	setTipo("BezierCurve");
	this->updatePtsCurv();
}

// Destrutor
BezierCurve::~BezierCurve(void)
{
}

// Atualiza os pontos da Curva
void BezierCurve::updatePtsCurv()
{
	int i = 0;
	float p1[3];
	float p2[3];
	float p3[3];
	float p4[3];

	vector< vector<float> > ptsControle;
	vector<float> aux;

	ptsCurv.clear();

	ptsControle = usedControlPts();

	while(i < (int) ptsControle.size()){

		// Carrega os 4 pontos de Controles usados
		// para gerar a curva de bezier cubica
		p1[0] = ptsControle[i][0];
		p1[1] = ptsControle[i][1];
		p1[2] = ptsControle[i][2];
		i++;

		p2[0] = ptsControle[i][0];
		p2[1] = ptsControle[i][1];
		p2[2] = ptsControle[i][2];
		i++;

		p3[0] = ptsControle[i][0];
		p3[1] = ptsControle[i][1];
		p3[2] = ptsControle[i][2];
		i++;

		p4[0] = ptsControle[i][0];
		p4[1] = ptsControle[i][1];
		p4[2] = ptsControle[i][2];

		if(i+1 == (int) ptsControle.size()){
			i++;
		}

		// Define os 4 pontos de controle usados para gerar a curva
		bzcubic.setPtControles(p1,p2,p3,p4);

		// Processa a curva de bezier cubica
		aux = bzcubic.processaPontoControle(quant);

		// Acrescenta a curva gerada com a lista geral das curvas
		ptsCurv.reserve(ptsCurv.size()+aux.size());
		ptsCurv.insert(ptsCurv.end(), aux.begin(), aux.end());

		// Limpa a lista auxiliar
		aux.clear();
	}
}

// Retorna os pontos da Curva
vector<float> BezierCurve::getPtsCurva()
{
	return ptsCurv;
}

// Retorna a Lista de Segmentos
vector<Segment> BezierCurve::getSegments()
{
	return segments;
}

// Retorna o indice do segmento selecionado
int BezierCurve::getSelectSegments()
{
	return selectSegments;
}

// Define o Segmento e o Ponto do Segmento, selecionado
void BezierCurve::setSelectSegments(int seg, int point)
{
	if(selectSegments != -1){

		segments[selectSegments].setPtSelect(-1);
	}

	selectSegments = seg;

	if(seg != -1){

		segments[selectSegments].setPtSelect(point);
	}
}

// Retorna a quantidade de Vertices que compem a curva
int BezierCurve::getQuant()
{
	return quant;
}

// Define a quantidade de Vertices que compem a curva
void BezierCurve::setQuant(int valor)
{
	quant = valor;
}

// Altera a posição do ponto de um segmento que está
// selecionado
void BezierCurve::setPtControle(float x, float y,float z)
{


	if(selectSegments != -1 ){

		//int count = 0;
	    vector <float > r = getRotation();
	    //GLfloat matrix[16];
	    glm::quat quat (glm::vec3(r[0]*PI/BASE, r[1]*PI/BASE, r[2]*PI/BASE));
	    glm::quat quaternion = quat ;
	    glm::mat4 mat  = glm::toMat4(quaternion);
	  /*  for (int k = 0; k < 4; ++k){
	        for (int j = 0; j < 4; ++j){
	            matrix[count] = mat[k][j];
	            count++;
	        }
	    }*/

	    glm::mat4 INVERSE_ROTATE = glm::inverse(mat);
	    glm::vec4 reverse_point = INVERSE_ROTATE * glm::vec4(
	    	(x-translation[0])/scale[0],
			(y-translation[1])/scale[1],
			(z-translation[2])/scale[2],
			1.0f
		);

		if(segments[selectSegments].getPtSelect() == 0){
			segments[selectSegments].setC(
				reverse_point[0],
				reverse_point[1],
				reverse_point[2]
			);
		}

		if(segments[selectSegments].getPtSelect() == 1){
			segments[selectSegments].setP1(
				reverse_point[0],
				reverse_point[1],
				reverse_point[2]
			);
		}

		if(segments[selectSegments].getPtSelect() == 2){
			segments[selectSegments].setP2(
				reverse_point[0],
				reverse_point[1],
				reverse_point[2]
			);
		}
	}
}

// Retorna os Pontos de Controle do Segmento que serão usados
// para gerar a curva de Bezier
vector< vector<float> > BezierCurve::usedControlPts()
{
	vector< vector<float> > usedCPts;

	vector<float> pts;
	int i;

	for(i = 0; i < (int) segments.size() ; i++)
	{

		pts = segments[i].getP1();
		if(pts[3] == 1){
			usedCPts.push_back(pts);
		}

		pts = segments[i].getC();
		if(pts[3] == 1){
			usedCPts.push_back(pts);
		}

		pts = segments[i].getP2();
		if(pts[3] == 1){
			usedCPts.push_back(pts);
		}
	}

	return usedCPts;
}

// Adciona um Segmento extremo da curva,
// os Segmentos extremos da Curva
// tem de estar selecionados
int BezierCurve::addSegment()
{
	if(selectSegments == 0){

		Segment newSegment = segments[selectSegments];

		segments[selectSegments].setP1Status(1);

		segments.insert(segments.begin(),newSegment);

	} else if(selectSegments == (int) segments.size()-1){

		Segment newSegment = segments[selectSegments];

		segments[selectSegments].setP2Status(1);

		segments.push_back(newSegment);

	} else {

		return 0;
	}

	return 1;
}

// Remove um Segmento extremo da curva,
// os Segmentos extremos da Curva
// tem de estar selecionados
int BezierCurve::removeSegment()
{
	if(selectSegments != -1 && (int) segments.size() > 2){

		if(selectSegments == 0) {

			segments[1].setP1Status(0);
			segments.erase(segments.begin()+selectSegments);

		} else if(selectSegments == (int) segments.size()-1){

			segments[segments.size()-2].setP2Status(0);
			segments.erase(segments.begin()+selectSegments);
			selectSegments--;

		} else {

			segments.erase(segments.begin()+selectSegments);
		}

	} else {

		return 0;
	}

	return 1;
}

void BezierCurve::ponteiro(float x,float y,float z, int size)
{
	glBegin(GL_POLYGON);
	glVertex3f(x+size,y+size,z);
	glVertex3f(x+size,y-size,z);
	glVertex3f(x-size,y-size,z);
	glVertex3f(x-size,y+size,z);
	glEnd();
}

void BezierCurve::draw(int index_load,  bool is_selecting, int size_world)
{
	int idselec;
	int i,k,j;
	int sizeSeg = (int) segments.size();
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
    glTranslatef(t[0],t[1],t[2]);
    glScalef(s[0], s[1], s[2]);
    glMultMatrixf(m);

    if( !render_mode && this->is_selected){

    	// Modo Edição
    	index_internal = 0;

    	if(!is_selecting){

			this->updatePtsCurv();

			if(this->is_selected){
				glColor4f(GREEN);
			} else {
				glColor4f(RED);
			}

			glPushMatrix();
				glBegin(GL_LINE_STRIP);
				for(j = 0; j < sizeCur; j+=3){
					glVertex3f(ptsCurv[j],ptsCurv[j+1],ptsCurv[j+2]);
				}
				glEnd();
			glPopMatrix();
		}

    	for(i = 0; i < sizeSeg; i++){

    		cout << " modo edição " << endl;
    		// Point 1
    		index_internal++;
    		glLoadName(index_internal);
    		glColor4f(BLACK);
    		if(index_internal == hit_index_internal){
    			cout << "que merda ta acontecendo aqui" << endl;
    			glColor4f(ORANGE);
    			this->setSelectSegments(i,1);
    		}
    		pt = segments[i].getP1();
    		glPushMatrix();
    		glPointSize(5);
    		glBegin(GL_POINTS);
    		glVertex3f(pt[0],pt[1],pt[2]);
    		glEnd();
    		glPopMatrix();

    		// Point C
    		index_internal++;
    		glLoadName(index_internal);
    		glColor4f(BLACK);
    		if(index_internal == hit_index_internal){
    			glColor4f(ORANGE);
    			this->setSelectSegments(i,0);
    		}
    		pt = segments[i].getC();
    		glPushMatrix();
    		glPointSize(5);
    		glBegin(GL_POINTS);
    		glVertex3f(pt[0],pt[1],pt[2]);
    		glEnd();
    		glPopMatrix();

    		// Pointe 2
    		index_internal++;
    		glLoadName(index_internal);
    		glColor4f(BLACK);
    		if(index_internal == hit_index_internal){
    			glColor4f(ORANGE);
    			this->setSelectSegments(i,2);
    		}
    		pt = segments[i].getP2();
    		glPushMatrix();
    		glPointSize(5);
    		glBegin(GL_POINTS);
    		glVertex3f(pt[0],pt[1],pt[2]);
    		glEnd();
    		glPopMatrix();


    		if(!is_selecting){
	    		//Line
				glColor4f(BLACK);
				glPushMatrix();
				glBegin(GL_LINES);
				pt = segments[i].getP1();
				glVertex3f(pt[0],pt[1],pt[2]);
				pt = segments[i].getP2();
				glVertex3f(pt[0],pt[1],pt[2]);
				glEnd();
				glPopMatrix();
			}
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

    //modificador
    if(render_mode && is_selected){

        glPushMatrix();
        glTranslatef(translation[0], translation[1]-20, translation[2]);
        glScalef(1/globalScale[0], 1/globalScale[1], 1/globalScale[2]);
        modifier.draw( size_world-1, true);
        glPopMatrix();

    } else if (!render_mode && is_selected && hit_index_internal >= 1){

        idselec = getSelectSegments();
    	if( idselec >= 0 ){
    		if(segments[idselec].getPtSelect() == 0){
        		pt = segments[idselec].getC();
        	}
    		if(segments[idselec].getPtSelect() == 1){
        		pt = segments[idselec].getP1();
        	}
    		if(segments[idselec].getPtSelect() == 2){
        		pt = segments[idselec].getP2();
        	}
        }
        //index_internal++;
        glPushMatrix();
        glTranslatef(t[0],t[1],t[2]);
        glScalef(s[0], s[1], s[2]);
        glMultMatrixf(m);
        glTranslatef(pt[0], pt[1], pt[2]);
        glScalef(0.8, 0.8, 0.8);
        glScalef(1/s[0], 1/s[1], 1/s[2]);
        glScalef(1/globalScale[0], 1/globalScale[1], 1/globalScale[2]);
        modifier.draw(index_internal, true);
        glPopMatrix();
    }

}

int BezierCurve::getSizeControlPoints()
{
	return ((int) segments.size())*3;
}

vector <float > BezierCurve::getControlPointSelected()
{

	vector<float> pt;
	int idselec =  getSelectSegments();

	if( idselec >= 0 ){
		if(segments[idselec].getPtSelect() == 0){
    		pt = segments[idselec].getC();
    	}
		if(segments[idselec].getPtSelect() == 1){
    		pt = segments[idselec].getP1();
    	}
		if(segments[idselec].getPtSelect() == 2){
    		pt = segments[idselec].getP2();
    	}
    }

    return pt;
}

void BezierCurve::setPtControleModifier(float x, float y, float z)
{
	vector<float> pt;
	int idselec =  getSelectSegments();

	if( idselec >= 0 ){
		if(segments[idselec].getPtSelect() == 0){
    		segments[idselec].setC(x,y,z);
    	}
		if(segments[idselec].getPtSelect() == 1){
    		segments[idselec].setP1(x,y,z);
    	}
		if(segments[idselec].getPtSelect() == 2){
    		segments[idselec].setP2(x,y,z);
    	}
    }

    updatePtsCurv();
}

void BezierCurve::setModifier(int tp)
{
    modifier.setModifierType(tp);
}
