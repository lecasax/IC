#include "BezierCurve.h"
#include "bezierSurface.h"
#include "nurbsSurface.h"
#include "manager.h"
#include "render.h"
#include "object.h"
#include "grid.h"
#include "cube.h"
#include "modifier.h"

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

BasicGLPane::BasicGLPane(wxWindow* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{

    RENDER_MODE = true;
    MODIFIER_TYPE = 1;
    SCALE = 1.0;
    ROTATION  = vector<float > (3, 0);
    CURSOR_POSITION = vector <float> (3, 0);
    LAST_MOUSE_POSITION_DRAGG = vector <float > (3, 0);
    LAST_OBJECT_SELECTED = 0;
    LAST_CLICK_OBJECT = 0;
    ANGLE_X = 0;
    ANGLE_Y = 0;
    m_context = new wxGLContext(this);

     // To avoid flashing on MSW

    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc, argv);


    Object *grid = new Grid[1];
    WORLD.push_back(grid);

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
    START_ANGLE_X = ANGLE_X;
    START_ANGLE_Y = ANGLE_Y;

    START_X = event.GetX();
    START_Y = event.GetY();
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
    vector<float > worldC(3, 0);
    vector<float > worldC2(3, 0);

    // Nome do Objeto Selecionado
    string name;

    if(event.Dragging() && event.LeftIsDown()){

        // Convertendo Coordenadas do mouse em coordenadas no Mundo
        x = event.GetX();
        y = event.GetY();
        worldC = Render::worldPoint(x,y);
        name = WORLD[LAST_OBJECT_SELECTED]->getTipo();
        cout << "LAST_CLICK_OBJECT: " << LAST_CLICK_OBJECT << "---" << "LAST_OBJECT_SELECTED: " << LAST_OBJECT_SELECTED << endl;

        /*Modo objeto */
        if(RENDER_MODE){

            //if(name == "BSplines" || name == "Nurbs" || name == "BezierCurve" || "bezierSurface" || "nurbsSurface"){
                if (LAST_OBJECT_SELECTED && LAST_OBJECT_SELECTED == (int)LAST_CLICK_OBJECT){

                    vector <float > object_position =  WORLD[LAST_OBJECT_SELECTED]->getTranslation();
                    worldC2[0] = object_position[0] + worldC[0] - LAST_MOUSE_POSITION_DRAGG[0];
                    worldC2[1] = object_position[1] + worldC[1] - LAST_MOUSE_POSITION_DRAGG[1];
                    worldC2[2] = object_position[2] + worldC[2] - LAST_MOUSE_POSITION_DRAGG[2];
                    LAST_MOUSE_POSITION_DRAGG = worldC;
                    WORLD[LAST_OBJECT_SELECTED]->translateObject(worldC2);
                }

                /* Se o Modificador de translacao estiver setado para a transalacao. */
                else if (LAST_CLICK_OBJECT >= WORLD.size() && MODIFIER_TYPE == 1){
                    vector <float > object_position =  WORLD[LAST_OBJECT_SELECTED]->getTranslation();
                    worldC2 = object_position;
                    switch(1 + LAST_CLICK_OBJECT - WORLD.size()){
                        case 1:
                            worldC2[0] = (object_position[0] + worldC[0] - LAST_MOUSE_POSITION_DRAGG[0]);
                        break;

                        case 2:
                            worldC2[1] = object_position[1] + worldC[1] - LAST_MOUSE_POSITION_DRAGG[1];
                        break;

                        case 3:
                            worldC2[2] = object_position[2] + worldC[2] - LAST_MOUSE_POSITION_DRAGG[2];
                        break;

                    }
                    LAST_MOUSE_POSITION_DRAGG = worldC;
                    WORLD[LAST_OBJECT_SELECTED]->translateObject(worldC2);
                }
                else if (LAST_CLICK_OBJECT >= WORLD.size() && MODIFIER_TYPE == 2){
                    vector <float > rotation =  WORLD[LAST_OBJECT_SELECTED]->getRotation();
                    worldC2 = rotation;
                    switch(1 + LAST_CLICK_OBJECT - WORLD.size()){
                        case 1:
                            worldC2[1] = rotation[1] + (worldC[0] - LAST_MOUSE_POSITION_DRAGG[0])*10;
                        break;

                        case 2:
                            worldC2[0] = rotation[0] + (worldC[1] - LAST_MOUSE_POSITION_DRAGG[1])*10;
                        break;

                        case 3:
                            worldC2[2] = rotation[2] + (worldC[2] - LAST_MOUSE_POSITION_DRAGG[2])*10;
                        break;

                    }
                    LAST_MOUSE_POSITION_DRAGG = worldC;
                    WORLD[LAST_OBJECT_SELECTED]->rotateObject(worldC2);
                }

                /* Se o Modificador de Escala estiver setado deve proceder da seguinte forma abaixo... */
                if (LAST_CLICK_OBJECT >= WORLD.size() && MODIFIER_TYPE == 3){
                    vector <float > object_scale =  WORLD[LAST_OBJECT_SELECTED]->getScale();
                    worldC2 = object_scale;
                    switch(1 + LAST_CLICK_OBJECT - WORLD.size()){

                        case 1:
                            worldC2[0] = object_scale[0] + (worldC[0] - LAST_MOUSE_POSITION_DRAGG[0])/5;
                        break;

                        case 2:
                            worldC2[1] = object_scale[1] + (worldC[1] - LAST_MOUSE_POSITION_DRAGG[1])/5;
                        break;

                        case 3:
                            worldC2[2] = object_scale[2] + (worldC[2] - LAST_MOUSE_POSITION_DRAGG[2])/5;
                        break;

                    }
                    LAST_MOUSE_POSITION_DRAGG = worldC;
                    WORLD[LAST_OBJECT_SELECTED]->scaleObject(worldC2[0], worldC2[1], worldC2[2]);
                }
            //}

        /*Modo edicao...*/
        } else {

            if (LAST_OBJECT_SELECTED &&  (int)LAST_CLICK_OBJECT == WORLD[LAST_OBJECT_SELECTED]->getHitIndexInternal()){
                WORLD[LAST_OBJECT_SELECTED]->setPtControle(worldC[0],worldC[1],worldC[2]);
            }
            else if ((int)LAST_CLICK_OBJECT > WORLD[LAST_OBJECT_SELECTED]->getSizeControlPoints()){
                vector <float > selectedPoint =  WORLD[LAST_OBJECT_SELECTED]->getControlPointSelected();
                worldC2 = selectedPoint;
                cout << "selectedPoint: "    <<"X: " <<selectedPoint[0] << "   Y: " << selectedPoint[1] <<"  Z: " <<selectedPoint[2] << endl;
                switch(LAST_CLICK_OBJECT - WORLD[LAST_OBJECT_SELECTED]->getSizeControlPoints()){

                    case 1:
                        worldC2[0] = (selectedPoint[0] + worldC[0] - LAST_MOUSE_POSITION_DRAGG[0]);
                    break;

                    case 2:
                        worldC2[1] = (selectedPoint[1] + worldC[1] - LAST_MOUSE_POSITION_DRAGG[1]);

                    break;

                    case 3:
                        worldC2[2] = (selectedPoint[2] + worldC[2] - LAST_MOUSE_POSITION_DRAGG[2]);
                    break;
                }
                LAST_MOUSE_POSITION_DRAGG = worldC;
                WORLD[LAST_OBJECT_SELECTED]->setPtControleModifier(worldC2[0], worldC2[1], worldC2[2]);
            }
        }

        displayScene();
        GetParent()->GetEventHandler()->ProcessEvent(event);
    }

    if(event.Dragging() && event.MiddleIsDown()){
        //Rotaca geral do cenario
        ANGLE_X = START_ANGLE_X + (event.GetX() - START_X);
        ANGLE_Y = START_ANGLE_Y + (event.GetY() - START_Y);
        ROTATION[0] = ANGLE_Y;
        ROTATION[1] = ANGLE_X;
        displayScene();
        GetParent()->GetEventHandler()->ProcessEvent(event);
    }

}

void BasicGLPane::mouseDown(wxMouseEvent& event)
{
    vector <float > proj;
    proj.push_back(45.0); proj.push_back((float)getWidth()/(float)getHeight());
    proj.push_back(0.1); proj.push_back(400);

    //pegando o objeto que atingido pelo ultimo clique do botao esquerdo...
    cout << "Mouse down event..." << endl;
    LAST_CLICK_OBJECT = Render::selectNearObject(WORLD,  proj,  event.GetX(), event.GetY(), RENDER_MODE, ROTATION, SCALE);

    //PEGA A ULTIMA POSICAO CLICADA COM O BOTAO ESQUERDO PARA USA NO DRAGG---//
    LAST_MOUSE_POSITION_DRAGG = Render::worldPoint(event.GetX(),event.GetY());
    CURSOR_POSITION = LAST_MOUSE_POSITION_DRAGG;
    GetParent()->GetEventHandler()->ProcessEvent(event);
}


void BasicGLPane::mouseWheelMoved(wxMouseEvent& event)
{
    //Escala geral do cenario
    event.GetWheelRotation()  > 0 ? SCALE+=0.0625 : SCALE-=0.0625;
    if(SCALE == 0){
        SCALE = 0.0625;
    }
    displayScene();
}


void BasicGLPane::mouseReleased(wxMouseEvent& event)
{
    cout << "mouseReleased" << endl;
}


void BasicGLPane::rightClick(wxMouseEvent& event)
{

    vector <float > proj;
    proj.push_back(45.0); proj.push_back((float)getWidth()/(float)getHeight());
    proj.push_back(0.1); proj.push_back(400);

    unsigned int obj_selected = Render::selectNearObject(WORLD,  proj,  event.GetX(), event.GetY(), RENDER_MODE, ROTATION, SCALE);
    cout << "Ponto retornando pela selecao: " << obj_selected << endl;

    //Modo ediciao
    if(!RENDER_MODE && obj_selected){
        if ( (int)obj_selected <= WORLD[LAST_OBJECT_SELECTED]->getSizeControlPoints() ){
            cout << "Modo edicao selecionando um ponto....." << ", " << WORLD[LAST_OBJECT_SELECTED]->getSizeControlPoints()<<endl;
            WORLD[LAST_OBJECT_SELECTED]->setHitIndexInternal((int)obj_selected);
            LAST_CLICK_OBJECT = (int)obj_selected;
        }
    //Modo objeto
    } else {

        if(obj_selected && obj_selected < WORLD.size()){
            WORLD[LAST_OBJECT_SELECTED]->setSelected(false);
            LAST_OBJECT_SELECTED = (int)obj_selected;
            WORLD[(int)obj_selected]->setSelected(true);
            //cout << "Antes de morrer...." << endl;
        }
    }
    cout << "Ultimo objeto selecionado: " << LAST_OBJECT_SELECTED << endl;
    displayScene();
    GetParent()->GetEventHandler()->ProcessEvent(event);

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
            if(WORLD.size() > 1 && LAST_OBJECT_SELECTED){
                cout << "Mudando o modo de renderezicao..." << endl;
                RENDER_MODE = !RENDER_MODE;
                //world[LAST_OBJECT_SELECTED]->setRenderMode(RENDER_MODE);
            }
        }

        if (uc == WXK_SPACE){
            cout << "Evendo do espaco...." << endl;
        }

        if (uc ==  a){
            cout << "Evento de A..." <<  endl;
        }
    }
    GetParent()->GetEventHandler()->ProcessEvent(event);
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
    Render::viewport3D(0,0, getWidth(), getHeight());

    //glScalef(100, 100, 100);
    Render::renderObjects(WORLD, RENDER_MODE, false, ROTATION, SCALE);

    glFlush();
    SwapBuffers();

}


//////////////////Metdos para conversar com objetos externos////////////////////
std::string BasicGLPane::createBezierSurface ()
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceBezier = new SurfaceBezier() ;
    surfaceBezier->translateObject(cursor);
    WORLD.push_back(surfaceBezier);
    displayScene();
    return surfaceBezier->getTipo();
}

std::string BasicGLPane::createSplineSurface ()
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceNurbs = new SurfaceNurbs() ;
    surfaceNurbs->translateObject(cursor);
    WORLD.push_back(surfaceNurbs);
    displayScene();
    return surfaceNurbs->getTipo();
}

std::string  BasicGLPane::createNurbsSurface ()
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceNurbs = new SurfaceNurbs() ;
    surfaceNurbs->translateObject(cursor);
    WORLD.push_back(surfaceNurbs);
    displayScene();
    return surfaceNurbs->getTipo();

}


vector <float > BasicGLPane::getCursorPosition()
{
    return CURSOR_POSITION;
}