#include "nurbsSurface.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>





using namespace std;


SurfaceNurbs::SurfaceNurbs():Object()

{

    setTipo("nurbsSurface");

    this->RESOLUTIONI = 16; //resolucao na direcao I
    this->RESOLUTIONJ = 16; // resolucao na direcao J

    this->NI = 5;  //dimensao na direcao de u
    this->NJ = 5; // dimensao na direcao de v

    this->TI = 4; //Ordem 4 e grau 3 na direcao de U
    this->TJ = 4; //Ordem 4 e grau 3 na direcao de V

    vector<vector <double > > w(NI+1,vector <double >(NJ+1, 0));
    weight = w;

    vector<vector<vector <double > > > cP(NI+1,vector<vector<double> >(NJ+1,vector <double>(3,0)));
    controlPoints  = cP;

    uknots = new double[NI + TI + 1];
    vknots = new double[NJ + TJ + 1];

    splineKnotsDouble(uknots, NI, TI);
    splineKnotsDouble(vknots, NJ, TJ);

    createControlPoints();
    //createControlPointsSpehere();
    preencheMatrizPesos();
    surface3dBsplineRenderNURBS();
}

SurfaceNurbs::~SurfaceNurbs()

{
    cout << "Limpando a memoria...\n";
    delete uknots;
    delete vknots;
}




// Recursive computation of B-spline functions. By Sumanta
double SurfaceNurbs::Bspline(int i, int m, double *knots, double u)
{
   double coef1, coef2;
   if ( m == 1 )
   {
      if ( i == 0 ) if ( ( knots[i] <= u ) && ( u <= knots[i+1] ) ) return 1.0;
      if ( ( knots[i] < u ) && ( u <= knots[i+1] ) ) return 1.0;
      else return 0.0;
   }
   else
   {
      if ( knots[i+m-1] == knots[i] )
      {
         if ( u == knots[i] ) coef1 = 1;
         else coef1 = 0;
      }
      else coef1 = (u - knots[i])/(knots[i+m-1] - knots[i]);

      if ( knots[i+m] == knots[i+1] )
      {
         if ( u == knots[i+m] ) coef2 = 1;
         else coef2 = 0;
      }
      else coef2 = (knots[i+m] - u)/(knots[i+m] - knots[i+1]);

      return ( coef1 * Bspline(i, m-1, knots, u) + coef2 * Bspline(i+1 ,m-1 , knots, u) );
   }
}


void SurfaceNurbs::splineKnotsDouble(double *u,int n,int t)
{

   for (int j = 0; j<= n + t; j++) {
      if (j < t)
         u[j] = 0.0;
      else if (j <= n)
         u[j] = (double) (j - t + 1);
      else if (j > n)
         u[j] = (double) (n - t + 2);
   }
}

vector <double *>  SurfaceNurbs::getControlPoints()

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

void SurfaceNurbs::surface3dBsplineRenderNURBS()

{

    vector <double *> surface;

    double  STEP_I = (NI - TI + 2) / ((double)RESOLUTIONI);
    double  STEP_J = (NJ - TJ + 2) / ((double)RESOLUTIONJ);
    double INTER_I =0.0, INTER_J = 0.0;
    double bi, bj;

    for (int i = 0; i < RESOLUTIONI + 1; i++){
        INTER_J = 0;
        for (int j = 0; j < RESOLUTIONJ + 1; j++){
            double *output = new double[3];
            output[0] = 0.0;
            output[1] = 0.0;
            output[2] = 0.0;
            double w = 0.0;
            for (int ci = 0; ci <= NI ; ci++ ){
                for (int cj = 0; cj <= NJ ; cj++) {
                    bi = Bspline(ci, TI, uknots, INTER_I);//SplineBlend(ci, TI, uknots, INTER_I); //Bspline(ci, TI, uknots[i] + IU);
                    bj = Bspline(cj, TJ, vknots, INTER_J);//Bspline(cj, TJ, vknots[j] + IV);
                    output[0] +=  bi  * bj * controlPoints[ci][cj][0] * weight[ci][cj];
                    output[1] +=  bi  * bj * controlPoints[ci][cj][1] * weight[ci][cj];
                    output[2] +=  bi  * bj * controlPoints[ci][cj][2] * weight[ci][cj];
                    w+= (bi * bj * weight[ci][cj]);
                }
            }
            output[0] /=w ;
            output[1] /=w ;
            output[2] /=w ;
            INTER_J += STEP_J;
            surface.push_back(output);
        }
        INTER_I += STEP_I;
        cout << endl;
    }
     surfaceNurbs = surface;
}

// Reset control points.
void SurfaceNurbs::createControlPoints(void)
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
            controlPoints[i][j][2] = Z1; //+ (double) ( rand() % 100 );
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

void SurfaceNurbs::movePointControlSurfaceBspline(double *p, int index)
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

void SurfaceNurbs::preencheMatrizPesos(){


    srand(10);
    for (int i = 0; i <= NI; i++){

        for (int j = 0; j <= NJ; j++) {

            //weight[i][j] = (double) ( rand() % 100 );
            weight[i][j] =  1.0;
            cout << weight[i][j] << ", ";
        }
        cout << endl;
    }
}

void SurfaceNurbs::setPtControle(float x, float y, float z)
{

    int i = ( (hit_index_internal-1) / (NI + 1) );
    int j = ( (hit_index_internal-1) % (NJ + 1) );
    controlPoints[i][j][0] = (x-translation[0])/scale[0];
    controlPoints[i][j][1] = (y-translation[1])/scale[1];
    controlPoints[i][j][2] = (z-translation[2])/scale[2];
    surface3dBsplineRenderNURBS();
}

void SurfaceNurbs::drawGlQuadStripVector(vector <double *> array , int n, int m, int type)

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

void  SurfaceNurbs::drawControlPoint(int hit)
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

void SurfaceNurbs::drawControlPolygon()

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


void SurfaceNurbs::draw(int index_load,  bool is_selecting)

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
    glPushMatrix();
    glTranslatef(t[0],t[1],t[2]);
    glScalef(s[0], s[1], s[2]);
    //drawControlPoint(getControlPoints());
    //glColor3f(0, 0, 0);

    //modo objeto
    if(render_mode){
        glLoadName(index_load);

        if (is_selected){
            glColor4f(GREEN);
        } else {
            glColor4f(GRAY1);
        }

        drawGlQuadStripVector( surfaceNurbs, RESOLUTIONI+1, RESOLUTIONJ+1, 1);

    //modo Edicao
    } else if (!render_mode && is_selected){
        glColor4f(GREEN);
        if (!is_selecting){
            drawGlQuadStripVector( surfaceNurbs, RESOLUTIONI+1, RESOLUTIONJ+1, 1);
            drawControlPolygon();
        }
        drawControlPoint(hit_index_internal);

    } else if (!render_mode && !is_selected) {

        if (!is_selecting){
            glColor4f(GRAY1);
            drawGlQuadStripVector( surfaceNurbs, RESOLUTIONI+1, RESOLUTIONJ+1, 1);
        }
    }
    glPopMatrix();
}