#include "bezierSurface.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
using namespace std;

SurfaceBezier::SurfaceBezier():Object()

{

    setTipo("Bezier Surface");

    modifier = Modifier(translation[0], translation[1], translation[2]);

    this->NI = 3;  //dimensao na direcao de u
    this->NJ = 3; // dimensao na direcao de v

    this->RESOLUTIONI = 4; //resolucao na direcao I
    this->RESOLUTIONJ = 4; // resolucao na direcao J

    weight = vector<vector <double > > (NI+1,vector <double >(NJ+1, 0));

    controlPoints = vector<vector<vector <double > > > (NI+1,vector<vector<double> >(NJ+1,vector <double>(3,0)));

    createControlPoints();

    preencheMatrizPesos();

    surface3dBezierRenderNUBRS();


}

SurfaceBezier::SurfaceBezier(int ni, int nj, int resolutioni, int resolutionj):Object()

{

    setTipo("Bezier Surface");
    this->NI = ni-1;  //dimensao na direcao de u
    this->NJ = nj-1; // dimensao na direcao de v

    this->RESOLUTIONI = resolutioni; //resolucao na direcao I
    this->RESOLUTIONJ = resolutionj; // resolucao na direcao J


    vector<vector <double > > w(NI+1,vector <double >(NJ+1, 0));
    weight = w;

    vector<vector<vector <double > > > cP(NI+1,vector<vector<double> >(NJ+1,vector <double>(3,0)));
    controlPoints  = cP;

    createControlPoints();

    preencheMatrizPesos();

    surface3dBezierRenderNUBRS();

}

SurfaceBezier::~SurfaceBezier()

{
}


double SurfaceBezier::combination(int n, int d)

{
    /*retorna o a comibação de um numero binomial*/
    return (double) ( fatorial(n) / ( fatorial(d) * fatorial(n-d) ) );

}

double SurfaceBezier::fatorial(int number)

{
    double fat = 1;

    if (number == 0 || number == 1){

        return 1;
    } else {

        for (int i = 2; i <= number; i++) {

            fat = fat * i;

        }
    }
    /*retorna o fatorial de um dado numero*/
    return fat;
}

/*metodo para renderizar os pontos de controle para os pontos finais da superficie*/
void  SurfaceBezier::surface3dBezierRenderNUBRS()

{
    vector <double *> surface;
    double STEP_I = 1.0 / ((double)RESOLUTIONI);
    double STEP_J = 1.0/  ((double)RESOLUTIONJ);
    double INTER_I =0.0, INTER_J = 0.0;
    double bi, bj;
    //vector<vector<vector<int> > > controlPoints (NI+1,vector<vector<int> >(NJ+1,vector <int>(3,0)));
    /*faz variar o paremtro u */
    for (int i = 0; i < RESOLUTIONI + 1 ; i++) {
        INTER_J = 0;
        /*faz variar o parametro v*/
        for (int j = 0; j < RESOLUTIONJ + 1 ; j++) {
            double *output = new double[3];
            output[0] = 0.0;
            output[1] = 0.0;
            output[2] = 0.0;
            double w = 0.0;
            /*calcula os pontos da superficie*/
            for (int k = 0; k <= NI ; k++) {
                for (int l = 0; l <= NJ ; l++){
                    bi =(combination(NI, k)  *  pow( (1.00-INTER_I), (double) (NI-k))  *  pow(INTER_I, double(k))) ;
                    bj =(combination(NJ, l)  *  pow( (1.00-INTER_J), (double) (NJ-l))  *  pow(INTER_J, double(l))) ;
                    output[0] += bi * bj  * controlPoints[k][l][0] * weight[k][l];
                    output[1] += bi * bj  * controlPoints[k][l][1] * weight[k][l];
                    output[2] += bi * bj  * controlPoints[k][l][2] * weight[k][l];
                    w += bi * bj * weight[k][l];
                }
            }
            output[0] /= w;
            output[1] /= w;
            output[2] /= w;
            surface.push_back(output);
            INTER_J += STEP_J;
        }

        INTER_I += STEP_I;
    }
    surfaceBezier = surface;
}
void SurfaceBezier::translateObject( vector <float > newTranslation)

{
    this->translation = newTranslation;
}

void SurfaceBezier::rotateObject(vector <float > newRotation)
{
    this->rotation = newRotation;

}


void SurfaceBezier::setGlobalScale( float x, float y, float z)
{

    this->globalScale[0] = x;
    this->globalScale[1] = y;
    this->globalScale[2] = z;
}

void SurfaceBezier::setPtControleModifier(float x, float y, float z)
{
    int i = ( (hit_index_internal-1) / (NI + 1) );
    int j = ( (hit_index_internal-1) % (NJ + 1) );
    controlPoints[i][j][0] = x;
    controlPoints[i][j][1] = y;
    controlPoints[i][j][2] = z;
    surface3dBezierRenderNUBRS();
}
void SurfaceBezier::setPtControle(float x, float y, float z)
{
    int i = ( (hit_index_internal-1) / (NI + 1) );
    int j = ( (hit_index_internal-1) % (NJ + 1) );

    vector <float > r = getRotation();
    glm::quat quat (glm::vec3(r[0]*PI/BASE, r[1]*PI/BASE, r[2]*PI/BASE));
    glm::quat quaternion = quat ;
    glm::mat4 mat  = glm::toMat4(quaternion);

    controlPoints[i][j][0] = (x-translation[0])/scale[0];
    controlPoints[i][j][1] = (y-translation[1])/scale[1];
    controlPoints[i][j][2] = (z-translation[2])/scale[2];

    glm::mat4 INVERSE_ROTATE = glm::inverse(mat);
    glm::vec4 reverse_point = INVERSE_ROTATE * glm::vec4(controlPoints[i][j][0],
                                                         controlPoints[i][j][1],
                                                         controlPoints[i][j][2],
                                                         1.0f
                                                         );
    controlPoints[i][j][0] = reverse_point[0];
    controlPoints[i][j][1] = reverse_point[1];
    controlPoints[i][j][2] = reverse_point[2];

    surface3dBezierRenderNUBRS();
}

vector <float > SurfaceBezier::getControlPointSelected()
{
    int i = ( (hit_index_internal-1) / (NI + 1) );
    int j = ( (hit_index_internal-1) % (NJ + 1) );
    vector <float > selectedPoint(3, 0);
    selectedPoint[0] = controlPoints[i][j][0];
    selectedPoint[1] = controlPoints[i][j][1];
    selectedPoint[2] = controlPoints[i][j][2];
    return  selectedPoint;
}

vector <double *>  SurfaceBezier::getControlPoints()

{
    vector <double *>v;

    for (int i = 0; i <= NI; i++){
        for (int j = 0; j <= NJ; j++)
        {
            double *vec = new double[3];
            vec[0] = controlPoints[i][j][0];
            vec[1] = controlPoints[i][j][1];
            vec[2] = controlPoints[i][j][2];

            v.push_back(vec) ;
        }
    }
    return v;
}


// Reset control points.
void SurfaceBezier::createControlPoints(void)
{
    srand(time(NULL));
    double X1 = -10.00 * (NI/2) ;
    double Z1 =  10.00;
    double xInitial = X1;
    double variation =   10.0 ;

    for (int i = 0; i <= NI; i++){
        for (int j = 0; j <= NJ; j++){
            controlPoints[i][j][0] = X1;
            //controlPoints[i][j][1] = 0.0;
            controlPoints[i][j][2] = Z1;; //+ (double) ( rand() % 100 );
            X1 += variation;
            if (i > 0 && j < NJ && i == j){
                controlPoints[i][j][1] = 10.0;
                controlPoints[i][NJ-j][1] = 10.0;
            }

        }
        Z1-=variation;
        X1 = xInitial;
    }

}

int SurfaceBezier::getSizeControlPoints()
{
    return (NI+1) * (NJ+1);
}
void SurfaceBezier::movePointControlSurfaceBspline(double *p, int index)
{

    int c = 0;
    for (int i = 0; i <= NI; i++){

        for (int j = 0; j <= NJ; j++){

            if (c == index){
                controlPoints[i][j][0] += p[0];
                controlPoints[i][j][1] += p[1];
                controlPoints[i][j][2] += p[2];
                return ;
            }
            c++;
        }
    }
}

void SurfaceBezier::preencheMatrizPesos(){


    srand(10);
    for (int i = 0; i <= NI; i++){

        for (int j = 0; j <= NJ; j++) {

            //weight[i][j] = (double) ( rand() % 100 );
            weight[i][j] =  1.0;
            //cout << weight[i][j] << ", ";
        }
        //cout << endl;
    }
}


void SurfaceBezier::drawGlQuadStripVector(vector <double *> array , int n, int m, int type)

{

    if (type) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    for (int i = 0; i < n -1 ; i++) {

        glPushMatrix();
        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j < m ; j++) {


            glVertex3f(array[i*m+j][0], array[i*m+j][1], array[i*m+j][2] );
            glVertex3f(array[(1+i)*m+j][0], array[(1+i)*m+j][1], array[(1+i)*m+j][2] );

        }
        glEnd();
        glPopMatrix();
    }

}

void SurfaceBezier::drawControlPoint(int hit)
{
    int count_object = 0;
    glEnable( GL_POINT_SMOOTH );
    glPointSize(6.0f);

    for (int i = 0; i <= NI; i++) {

        for (int j = 0; j <= NJ; ++j){
            count_object++;

            glLoadName(count_object);

            glPushMatrix();
                if ( ( (hit-1) /(NI + 1) ) == i && ( (hit-1) % (NJ + 1) ) == j ){
                     glColor4f(ORANGE);
                } else {
                     glColor4f(BLACK);
                }
            glBegin(GL_POINTS);
            glVertex3f(controlPoints[i][j][0], controlPoints[i][j][1], controlPoints[i][j][2] );
            glEnd();
            glPopMatrix();
        }
    }
}


void SurfaceBezier::drawControlPolygon()

{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(BLACK);


    //desenahdo o poligono de controle
    for (int i = 0; i < NI; i++) {

        glPushMatrix();
        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j < NJ+1 ; j++) {


            glVertex3f(controlPoints [i][j][0],controlPoints [i][j][1],controlPoints [i][j][2]);
            glVertex3f(controlPoints [i+1][j][0],controlPoints [i+1][j][1],controlPoints [i+1][j][2]);

        }
        glEnd();
        glPopMatrix();
    }
}

void SurfaceBezier::draw(int index_load,  bool is_selecting, int size_world)

{
    GLfloat m[16];
    vector <float > c = getColor();
    vector <float > r = getRotation();
    vector <float > t = getTranslation();
    vector <float > s = getScale();

    glm::quat quat (glm::vec3(r[0]*PI/BASE, r[1]*PI/BASE, r[2]*PI/BASE));
    glm::quat quaternion = quat ;
    glm::mat4 mat  = glm::toMat4(quaternion);

    int count = 0;
    for (int k = 0; k < 4; ++k){
        for (int j = 0; j < 4; ++j){
            m[count] = mat[k][j];
            count++;
        }
    }

    //modificador
    if(render_mode && is_selected){
        glPushMatrix();
        glTranslatef(translation[0], translation[1]-20, translation[2]);
        glScalef(1/globalScale[0], 1/globalScale[1], 1/globalScale[2]);
        modifier.draw( size_world-1, true);
        glPopMatrix();
    }

    else if (!render_mode && is_selected && hit_index_internal >= 1){
        int i = ( (hit_index_internal-1) / (NI + 1) );
        int j = ( (hit_index_internal-1) % (NJ + 1) );
        glPushMatrix();
        glTranslatef(t[0],t[1],t[2]);
        glScalef(s[0], s[1], s[2]);
        glMultMatrixf(m);
        glTranslatef(controlPoints[i][j][0], controlPoints[i][j][1], controlPoints[i][j][2]);
        glScalef(0.8, 0.8, 0.8);
        glScalef(1/s[0], 1/s[1], 1/s[2]);
        glScalef(1/globalScale[0], 1/globalScale[1], 1/globalScale[2]);
        modifier.draw( (NI+1)*(NJ+1), true);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(t[0],t[1],t[2]);
    glScalef(s[0], s[1], s[2]);
    glMultMatrixf(m);

    //modo objeto
    if(render_mode){

        if (is_selected){
            //modifier.draw( ( ( index_load-1 ) * 4 ) + 1, true);
            glColor4f(GREEN);
        } else {
            glColor4f(GRAY1);
        }

        glLoadName(index_load);
        //glLoadName(  index_load );
        drawGlQuadStripVector(surfaceBezier, RESOLUTIONI+1, RESOLUTIONJ+1, 1);

    //modo Edicao
    } else if (!render_mode && is_selected){
        glColor4f(GREEN);
        if (!is_selecting){
            drawGlQuadStripVector(surfaceBezier, RESOLUTIONI+1, RESOLUTIONJ+1, 1);
            drawControlPolygon();
        }
        drawControlPoint(hit_index_internal);

    } else if (!render_mode && !is_selected) {

        if (!is_selecting){
            glColor4f(GRAY1);
            drawGlQuadStripVector(surfaceBezier, RESOLUTIONI+1, RESOLUTIONJ+1, 1);
        }
    }
    glPopMatrix();
}