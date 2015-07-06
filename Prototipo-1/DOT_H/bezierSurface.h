/* 
 * File:   lista.h
 * Author: leandro
 *
 * Created on 28 de Dezembro de 2013, 13:43
 */


#ifndef BEZIER_SURFACE_H
#define BEZIER_SURFACE_H
#include "object.h"
#include <vector>

using namespace std;

class SurfaceBezier: public Object

{

public:

    SurfaceBezier(int ni, int nj, int resolutioni, int resolutionj );
    SurfaceBezier();
    ~SurfaceBezier();
    double combination(int n, int d);
    void preencheMatrizPesos();
    void movePointControlSurfaceBspline(double *p, int index);
    void createControlPoints(void);
    void movePointControlCurveBsplines(double *point, int indexCircleClicked);
    double fatorial(int number);
    void movePointControlSurface(double *point, int position);
    void surface3dBezierRenderNUBRS();
    vector <double *> getControlPoints();
    void draw(int index_load,  bool is_selecting);
    void drawControlPoint(int hit);
    void drawGlQuadStripVector(vector <double *> array , int n, int m, int type);


private:

    vector <double *> surfaceBezier;

    vector<vector <double > > weight;
    vector<vector<vector<double > > > controlPoints;
    
    int NI;  //dimensao na direcao de u
    int NJ; // dimensao na direcao de v

    int  RESOLUTIONI; //resolucao na direcao I
    int  RESOLUTIONJ; // resolucao na direcao J


};

#endif  /* BEZIER_H */
