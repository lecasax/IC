/*
 * File:   lista.h
 * Author: leandro
 *
 * Created on 28 de Dezembro de 2013, 13:43
 */


#ifndef NURBS_SURFACE_H
#define NURBS_SURFACE_H
#include "object.h"
#include "modifier.h"
#include <vector>

using namespace std;

class SurfaceNurbs: public Object

{

public:

    SurfaceNurbs();
    ~SurfaceNurbs();
    int verify_two_vectors_oriented(double *v, double *v2);
    double Bspline(int i, int m, double *knots, double u);
    double combination(int n, int d);
    void preencheMatrizPesos();
    void movePointControlSurfaceBspline(double *p, int index);
    void splineKnotsDouble(double *u,int n,int t);
    void createControlPoints(void);
    void movePointControlCurveBsplines(double *point, int indexCircleClicked);
    double fatorial(int number);
    void movePointControlSurface(double *point, int position);
    void drawGlQuadStripVector(vector <double *> array , int n, int m, int type);
    void draw(int index_load,  bool is_selecting, int size_world);
    void drawControlPoint(int hit);
    void drawControlPolygon();
    void surface3dBsplineRenderNURBS();
    vector <double *> createControlPointsSpehere();
    vector <double *> getControlPoints();
    void setPtControle(float x, float y, float z);
    void setGlobalScale( float x, float y, float z);
    void setPtControleModifier(float x, float y, float z);
    int getSizeControlPoints();
    vector <float > getControlPointSelected();

private:

    vector <double *> surfaceNurbs;

    vector<vector <double > > weight;
    vector<vector<vector<double > > > controlPoints;

    int  RESOLUTIONI; //resolucao na direcao I
    int  RESOLUTIONJ; // resolucao na direcao J

    int NI;  //dimensao na direcao de u
    int NJ; // dimensao na direcao de v

    int TI; //Ordem 4 e grau 3 na direcao de U
    int TJ; //Ordem 4 e grau 3 na direcao de V

    //vector <double > uknots;
    //vector <double > vknots;
    double *uknots;
    double *vknots;

    Modifier modifier;


};

#endif  /* NURBS_H */
