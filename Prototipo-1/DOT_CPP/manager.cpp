#include <GL/glut.h>
#include "BezierCurve.h"
#include "bezierSurface.h"
#include "nurbsSurface.h"
#include "manager.h"
#include "render.h"
#include "object.h"
#include "grid.h"
#include "cube.h"
#include <wx/event.h>

/*table of the events*/
/* tabela de eventos referente a canvas*/

BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)


EVT_MOTION(BasicGLPane::mouseMoved)
EVT_LEFT_DOWN(BasicGLPane::mouseDown)
EVT_LEFT_UP(BasicGLPane::mouseReleased)
EVT_RIGHT_DOWN(BasicGLPane::rightClick)
EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
EVT_SIZE(BasicGLPane::resized)
EVT_KEY_DOWN(BasicGLPane::keyPressed)
EVT_KEY_UP(BasicGLPane::keyReleased)
EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
EVT_MIDDLE_DCLICK(BasicGLPane::mouseMiddleDclick)
EVT_MIDDLE_DOWN(BasicGLPane::mouseMiddleDown)
EVT_MIDDLE_UP(BasicGLPane::mouseMiddleUp)
EVT_PAINT(BasicGLPane::render)


END_EVENT_TABLE()

//To Opengl
static float obsP[] =  { -50, 100, 250, 0, 0, 0, 0, 1, 0 };

//To objects
vector <Object *> world;
//vector<int > obj_selected;
int last_object_selected = 0;
bool render_mode = true;
vector <float > ROTATION(3, 0);
float SCALE = 1.0;

/*Variaveis de rotacao do cenario*/
int start_x, start_y, start_angle_x, start_angle_y, angle_x = 0, angle_y = 0;

BasicGLPane::BasicGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    //Render::viewport3D(0,0, getWidth(), getHeight(), obsP);
    m_context = new wxGLContext(this);
    //No construtor na funcionou
    //Render::viewport3D(0,0, getWidth(), getHeight(), obsP);

     // To avoid flashing on MSW

    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc, argv);

    vector <float *> vertex;
    vector <float *> vertex2;

    float  c[] = {0, 0, 1} ;
    float  r[] = {0, 45, 0};
    float  s[] = {20.5, 20.5, 20.5};
    float  t[] = {-80.0, 4.0, 0.0};
    float  t2[] = {80.0, 4.0, 0.0};
    vector<float> rotate (r, r + sizeof(r) / sizeof(float));
    vector<float > color (c, c + sizeof(c) / sizeof(float) );
    vector<float > scale (s, s + sizeof(s) / sizeof(float) );
    vector<float > trans (t, t + sizeof(t) / sizeof(float) );
    vector<float > trans2 (t2, t2 + sizeof(t2) / sizeof(float) );


    Object *grid = new Grid[1];
    Object *cube = new Cube[1];
    Object *cube2 = new Cube[1];
    Object *cube3 = new Cube[1];

    cube2->translateObject(trans);
    cube2->scaleObject(scale);
    cube2->setColor(color);
    cube->scaleObject(scale);
    cube3->scaleObject(scale);
    cube3->translateObject(trans2);
    //grid->setColor(color);

    Object *bezier = new BezierCurve(0,0,0);
    Object *bezier2 = new BezierCurve(-50,0,0);
    Object *bspline = new BSplines(0,50,0);
<<<<<<< HEAD
    Object *surfaceBezier = new SurfaceBezier() ;
    Object *surfaceNurbs = new SurfaceNurbs() ;
    surfaceNurbs->translateObject(trans);
    surfaceBezier->translateObject(trans2);




    world.push_back(grid);
    world.push_back(bezier);
    //world.push_back(bezier2);
    //world.push_back(bspline);
    world.push_back(surfaceBezier);
    world.push_back(surfaceNurbs);

=======
    Object *nurb = new Nurbs(-50,50,0);

    world.push_back(grid);
    world.push_back(bezier);
    world.push_back(bezier2);
    world.push_back(bspline);
    world.push_back(nurb);
>>>>>>> bbfd4a67c9642c4b2152a6acee094a528b7ae1aa
    //world.push_back(cube);
    //world.push_back(cube2);
    //world.push_back(cube3);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

BasicGLPane::~BasicGLPane()
{
    delete m_context;
}

void BasicGLPane::mouseMiddleUp(wxMouseEvent& event)

{

    displayScene();

}


void BasicGLPane::mouseMiddleDown(wxMouseEvent& event)

{

    cout << "Botao do meio para baixo" << endl;
    //quando o botao do mouse abaixa seta as variaveis para a logica da rotacao//
    start_angle_x = angle_x;
    start_angle_y = angle_y;

    start_x = event.GetX();
    start_y = event.GetY();
    //------------------------------------------------------------------------//
}


void BasicGLPane::mouseMiddleDclick(wxMouseEvent &event)

{

}
void BasicGLPane::mouseMoved(wxMouseEvent& event )
{

    /*Move os pontos de controle das curvas */
    // Capturando Coordenadas do Mouse na Tela
    int x = 0, y = 0;

    // Cordenadas do Mouse no Mundo
    vector<float> worldC;

    // Nome do Objeto Selecionado
    string name;

    if(event.Dragging() && event.LeftIsDown()){

        // Convertendo Coordenadas do mouse em coordenadas no Mundo
        x = event.GetX();
        y = event.GetY();
        worldC = Render::worldPoint(x,y);

        if(render_mode){

            name = world[last_object_selected]->getTipo();

            if(name == "BSplines" || name == "Nurbs" || name == "BezierCurve"){

                world[last_object_selected]->translateObject(worldC);
            }

        } else {
            name = world[last_object_selected]->getTipo();

            if(name == "BSplines" || name == "Nurbs" || name == "BezierCurve"){

                world[last_object_selected]->setPtControle(worldC[0],worldC[1],worldC[2]);
            }
        }

        displayScene();
    }


    //displayScene();
    if(event.Dragging() && event.MiddleIsDown()){

        //cout << "R_X: " << rotation_x << ", " << "R_Y: " << rotation_y << endl;
        angle_x = start_angle_x + (event.GetX() - start_x);
        angle_y = start_angle_y + (event.GetY() - start_y);
        ROTATION[0] = angle_y;
        ROTATION[1] = angle_x;
        displayScene();

    }

}

void BasicGLPane::mouseDown(wxMouseEvent& event)
{
    //criar aqui o evento do cursor
}


void BasicGLPane::mouseWheelMoved(wxMouseEvent& event)
{

    event.GetWheelRotation()  > 0 ? SCALE+=0.0625 : SCALE-=0.0625;
    if(SCALE == 0){
        SCALE = 0.0625;
    }
    if (SCALE >= 1.0){
        SCALE = 1.0;
    }
    cout << "SCALE---" << SCALE << endl;
    displayScene();
}


void BasicGLPane::mouseReleased(wxMouseEvent& event)
{
    cout << "mouseReleased" << endl;
}


void BasicGLPane::rightClick(wxMouseEvent& event)
{

    //simulando a criacao de objetos
    //vector <float > pointWorld = Render::worldPoint(event.GetX(), event.GetY());
    //cout << "X: " << pointWorld[0] << "Y: " << pointWorld[1] << "Z: " << pointWorld[2] << endl;
    //world[1].translateObject(pointWorld);
    vector <float > proj;
    proj.push_back(45.0); proj.push_back((float)getWidth()/(float)getHeight());
    proj.push_back(0.1); proj.push_back(400);

    unsigned int obj_selected = Render::render(world,  proj,  event.GetX(), event.GetY(), render_mode, ROTATION, SCALE);
    //int obj_sel = getMinDepth(obj_selected, world) ;
    cout << "Objeto selecionado: " << obj_selected << endl;
    //modificando o estado do objeto selecionado
    if(!render_mode && obj_selected){
        cout << "Modo edicao selecionando um ponto....." << endl;
        world[last_object_selected]->setHitIndexInternal((int)obj_selected);

    } else {

        if(obj_selected){
            cout << "Modo objeto selecionando um objeto...." << endl;
            world[last_object_selected]->setSelected(false);
            last_object_selected = (int)obj_selected;
            world[(int)obj_selected]->setSelected(true);

        }
    }
    cout << "Ultimo objeto selecionado: " << last_object_selected << endl;
    displayScene();

}
void BasicGLPane::mouseLeftWindow(wxMouseEvent& event)
{

    cout << "mouseLeftWindow\n";

}
void BasicGLPane::keyPressed(wxKeyEvent& event)
{
    //Por aqui a logica dos modos objetos e edicao, como no blender, apertar o tab deve alternar entre os modos;
    //WXK_TAB <-- tecla tab
    //cout <<"Chave A: " <<WXK_CONTROL_A << endl;
    char a = 65;
    wxChar uc = event.GetUnicodeKey();
    cout << uc << endl;
    if (uc != WXK_NONE){
        if ( uc == WXK_TAB){
            //modo edicao e objeto....
            cout << "Evento de tab..." <<  endl;
            if(world.size() > 1 && last_object_selected){
                cout << "Mudando o modo de renderezicao..." << endl;
                render_mode = !render_mode;
                //world[last_object_selected]->setRenderMode(render_mode);
            }
        }

        if (uc == WXK_SPACE){
            cout << "Evendo do espaco...." << endl;
        }

        if (uc ==  a){
            cout << "Evento de A..." <<  endl;
        }
    }
    displayScene();
}
void BasicGLPane::keyReleased(wxKeyEvent& event)
{



}


void BasicGLPane::optionsActions(int id)

{

    displayScene();
}

void BasicGLPane::getCoordenateWorldMouse(int mouseX, int mouseY, double *pointStart)

{


}

void BasicGLPane::resized(wxSizeEvent& evt)
{
//  wxGLCanvas::OnSize(evt);

    Refresh();
}


int BasicGLPane::getWidth()
{
    return GetSize().x;
}

int BasicGLPane::getHeight()
{
    return GetSize().y;
}


void BasicGLPane::render( wxPaintEvent& evt )
{
    displayScene();

}


void BasicGLPane::displayScene()

{

    if(!IsShown()) return;

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

    //toda as vezes tem que definir a projecao......
    Render::viewport3D(0,0, getWidth(), getHeight(), obsP);

    //glScalef(100, 100, 100);
    Render::renderObjects(world, render_mode, false, ROTATION, SCALE);

    glFlush();
    SwapBuffers();

}