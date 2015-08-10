/*
Julho de 2015
*/
#include "forms.h"
#include <cmath>

Forms::Forms(){}
Forms::~Forms(){}

vector< vector<float > > Forms::getCircle(float cx, float cy, float r, int num_segments)
{
    vector< vector<float > > circle;
    vector <float > p0(3, 0), p1(3, 0), p2(3, 0), p3(3, 0), p4(3, 0), p5(3, 0), p6(3, 0), p7(3, 0), p8(3, 0);
    p0[0] =  0;            p0[1] = -10;             p0[2] = 0.0f;
    p1[0] = -10;           p1[1] = -10;             p1[2] = 0.0f;
    p2[0] = -10;           p2[1] =   0;             p2[2] = 0.0f;
    p3[0] = -10;           p3[1] =  10;             p3[2] = 0.0f;
    p4[0] =  0;            p4[1] =  10;             p4[2] = 0.f;
    p5[0] =  10;           p5[1] =  10;             p5[2] = 0.f;
    p6[0] = 10;            p6[1] =   0;             p6[2] = 0.f;
    p7[0] = 10;            p7[1] = -10;             p7[2] = 0.f;
    p8[0] = 0;             p8[1] = -10;             p8[2] = 0.f;

    circle.push_back(p0);

    circle.push_back(p1);

    circle.push_back(p2);

    circle.push_back(p3);

    circle.push_back(p4);

    circle.push_back(p5);

    circle.push_back(p6);

    circle.push_back(p7);

    circle.push_back(p8);


    /*for(int ii = 0; ii <= num_segments; ii++)
    {
        vector <float > point(3, 0);

        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        point[0] = r * cosf(theta);//calculate the x component
        point[1] = r * sinf(theta);//calculate the y component
        circle.push_back(point);
    }
    */
    return circle;
}


vector< vector<float > > Forms::getElipse()
{
    vector< vector<float > > elipse;
    vector <float > p0(3, 0), p1(3, 0), p2(3, 0), p3(3, 0), p4(3, 0), p5(3, 0), p6(3, 0), p7(3, 0), p8(3, 0);
    p0[0] =  -7.5;         p0[1] = 7.5;             p0[2] = 0.0f;
    p1[0] =   0;           p1[1] = 15;              p1[2] = 0.0f;
    p2[0] =  7.5;          p2[1] =  7.5;            p2[2] = 0.0f;
    p3[0] =  15;           p3[1] =  0;              p3[2] = 0.0f;
    p4[0] =  7.5;          p4[1] = -7.5;            p4[2] = 0.f;
    p5[0] =   0;           p5[1] =  -15;            p5[2] = 0.f;
    p6[0] =  -7.5;         p6[1] =  -7.5;           p6[2] = 0.f;
    p7[0] = -15;           p7[1] =   0;             p7[2] = 0.f;
    p8[0] =  -7.5;         p8[1] =   7.5;           p8[2] = 0.f;

    elipse.push_back(p0);

    elipse.push_back(p1);

    elipse.push_back(p2);

    elipse.push_back(p3);

    elipse.push_back(p4);

    elipse.push_back(p5);

    elipse.push_back(p6);

    elipse.push_back(p7);

    elipse.push_back(p8);


    /*for(int ii = 0; ii <= num_segments; ii++)
    {
        vector <float > point(3, 0);

        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        point[0] = r * cosf(theta);//calculate the x component
        point[1] = r * sinf(theta);//calculate the y component
        circle.push_back(point);
    }
    */
    return elipse;
}


vector< vector<float > > Forms::getRecatangle()
{
    vector< vector<float > > rectangle;
    vector <float > p0(3, 0), p1(3, 0), p2(3, 0), p3(3, 0), p4(3, 0), p5(3, 0), p6(3, 0), p7(3, 0), p8(3, 0);
    p0[0] =  0;            p0[1] = -10;             p0[2] = 0.0f;
    p1[0] = -10;           p1[1] = -10;             p1[2] = 0.0f;
    p2[0] = -10;           p2[1] =   0;             p2[2] = 0.0f;
    p3[0] = -10;           p3[1] =  10;             p3[2] = 0.0f;
    p4[0] =  0;            p4[1] =  10;             p4[2] = 0.f;
    p5[0] =  10;           p5[1] =  10;             p5[2] = 0.f;
    p6[0] = 10;            p6[1] =   0;             p6[2] = 0.f;
    p7[0] = 10;            p7[1] = -10;             p7[2] = 0.f;
    p8[0] = 0;             p8[1] = -10;             p8[2] = 0.f;

    rectangle.push_back(p0);

    rectangle.push_back(p1);

    rectangle.push_back(p2);

    rectangle.push_back(p3);

    rectangle.push_back(p4);

    rectangle.push_back(p5);

    rectangle.push_back(p6);

    rectangle.push_back(p7);

    rectangle.push_back(p8);


    /*for(int ii = 0; ii <= num_segments; ii++)
    {
        vector <float > point(3, 0);

        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        point[0] = r * cosf(theta);//calculate the x component
        point[1] = r * sinf(theta);//calculate the y component
        circle.push_back(point);
    }
    */
    return rectangle;
}
