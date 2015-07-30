#include "BezierCurve.h"
#include "bezierSurface.h"
#include "nurbsSurface.h"
#include "manager.h"
#include "render.h"
#include "object.h"
#include "grid.h"
#include "cube.h"
#include "modifier.h"
#include <algorithm>    // std::find
#include <sstream>

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

    LAST_EVENT = 0;
    POINTER_BACKUP = 0;
    RENDER_MODE = true;
    MODIFIER_TYPE = 1;
    SCALE = 1.0;
    ROTATION  = vector<float > (3, 0);
    CURSOR_POSITION = vector <float> (3, 0);
    LAST_MOUSE_POSITION_DRAGG = vector <float > (3, 0);
    LAST_OBJECT_SELECTED = 0;
    LAST_CLICK_OBJECT = 0;
    ANGLE_X = 45;
    ANGLE_Y = 45;
    LIST_INDEX_OBJECT.push_back(0);
    m_context = new wxGLContext(this);

     // To avoid flashing on MSW

    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    glutInit(&argc, argv);


    Object *grid = new Grid[1];
    WORLD.push_back(grid);
    ROTATION[0] = 45;
    ROTATION[1] = 45;
    BACKUP.push_back(WORLD);
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
                    LAST_EVENT = 1;
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
                    LAST_EVENT = 1;
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
                    LAST_EVENT = 1;
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
                    LAST_EVENT = 1;
                }
            //}

        /*Modo edicao...*/
        } else {

            if (LAST_OBJECT_SELECTED &&  (int)LAST_CLICK_OBJECT == WORLD[LAST_OBJECT_SELECTED]->getHitIndexInternal()){
                WORLD[LAST_OBJECT_SELECTED]->setPtControle(worldC[0],worldC[1],worldC[2]);
                LAST_EVENT = 1;
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
                LAST_EVENT = 1;
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
    cout << "X: " << event.GetX() << endl;
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
    switch(LAST_EVENT){

        case 1:
            cout << "Adicionando novo estado....." << endl;
            addNewState();
        break;
    }

    LAST_EVENT = 0;
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
        cout << "Dentro da condicao testada..." << endl;
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
std::string BasicGLPane::createBezierSurface (int symbolicIndex, int u, int v, int ru, int rv)
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceBezier = new SurfaceBezier(u, v, ru, rv) ;
    surfaceBezier->translateObject(cursor);
    LIST_INDEX_OBJECT.push_back(symbolicIndex);
    WORLD.push_back(surfaceBezier);
    displayScene();
    addNewState();
    return surfaceBezier->getTipo();
}

std::string BasicGLPane::createSplineSurface (int symbolicIndex, int u, int v, int ru, int rv, int degree)
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceNurbs = new SurfaceNurbs(u, v, ru, rv, degree,  1) ;
    surfaceNurbs->translateObject(cursor);
    LIST_INDEX_OBJECT.push_back(symbolicIndex);
    WORLD.push_back(surfaceNurbs);
    displayScene();
    addNewState();
    return surfaceNurbs->getTipo();
}

std::string  BasicGLPane::createNurbsSurface (int symbolicIndex, int u, int v, int ru, int rv, int degree)
{
    vector <float > cursor = getCursorPosition();
    Object *surfaceNurbs = new SurfaceNurbs(u, v, ru, rv, degree,  2) ;
    surfaceNurbs->translateObject(cursor);
    LIST_INDEX_OBJECT.push_back(symbolicIndex);
    WORLD.push_back(surfaceNurbs);
    displayScene();
    addNewState();
    return surfaceNurbs->getTipo();

}


vector <float > BasicGLPane::getCursorPosition()
{
    return CURSOR_POSITION;
}

void  BasicGLPane::setCursorPosition(int x, int y, int z)
{
    CURSOR_POSITION[0] = x;
    CURSOR_POSITION[1] = y;
    CURSOR_POSITION[2] = z;
}
void BasicGLPane::selectObject(int symbolicIndex)
{
    std::vector<int>::iterator it = find (LIST_INDEX_OBJECT.begin(), LIST_INDEX_OBJECT.end(), symbolicIndex);
    size_t offset = it - LIST_INDEX_OBJECT.begin();

    if (offset < WORLD.size()) {
        WORLD[LAST_OBJECT_SELECTED]->setSelected(false);
        WORLD[offset]->setSelected(true);
        LAST_OBJECT_SELECTED = offset;
    }
    //cout << "Tipossss: " <<  WORLD[idexObject]->getTipo() <<"Idex: " << idexObject <<endl;
    displayScene();
}
void BasicGLPane::deleteObject(int symbolicIndex)
{

    std::vector<int>::iterator it = find (LIST_INDEX_OBJECT.begin(), LIST_INDEX_OBJECT.end(), symbolicIndex);
    size_t offset = it - LIST_INDEX_OBJECT.begin();

    WORLD.erase(WORLD.begin() + offset);
    LIST_INDEX_OBJECT.erase(it);
    LAST_OBJECT_SELECTED = 0;
    if (WORLD.size() == 1){
        RENDER_MODE = true;
    }
    displayScene();

}

//Isso na e legal....
vector <float > BasicGLPane::getPositionLastObjectSelected()
{
    return WORLD[LAST_OBJECT_SELECTED]->getTranslation();
}

vector <float > BasicGLPane::getRotationLastObjectSelected()
{
    return WORLD[LAST_OBJECT_SELECTED]->getRotation();
}

vector <float > BasicGLPane::getScaleLastObjectSelected()
{
    return WORLD[LAST_OBJECT_SELECTED]->getScale();
}

std::string BasicGLPane::getTipoLastObjectSelected()
{
    return WORLD[LAST_OBJECT_SELECTED]->getTipo();
}

void BasicGLPane::newScene()
{
    WORLD.erase(WORLD.begin()+1, WORLD.begin() + WORLD.size());
    LIST_INDEX_OBJECT.erase(LIST_INDEX_OBJECT.begin()+1, LIST_INDEX_OBJECT.begin()+
                            LIST_INDEX_OBJECT.size());
    BACKUP.clear();
    BACKUP.push_back(WORLD);
    POINTER_BACKUP = 0;
    setCursorPosition(0, 0, 0);
    RENDER_MODE = true;
    ROTATION[0] = 45;
    ROTATION[1] = 45;
    ANGLE_X = 45;
    ANGLE_Y = 45;
    displayScene();
}

std::string BasicGLPane::duplicateObject(int oldIndex, int newIndex)
{
    std::string strResult = "";
    std::vector<int>::iterator it = find (LIST_INDEX_OBJECT.begin(), LIST_INDEX_OBJECT.end(), oldIndex);
    size_t offset = it - LIST_INDEX_OBJECT.begin();

    if (offset < WORLD.size()) {
        strResult = WORLD[offset]->getTipo();
        LIST_INDEX_OBJECT.push_back(newIndex);
        Object* object;
        if (strResult.compare("BezierSurface") == 0){
            object = new SurfaceBezier( (SurfaceBezier * ) WORLD[offset] );
        }else if (strResult.compare("BSplineSurface") == 0){
            object = new SurfaceNurbs( (SurfaceNurbs * ) WORLD[offset] );
        }else if (strResult.compare("NurbsSurface") == 0){
            object = new SurfaceNurbs( (SurfaceNurbs * ) WORLD[offset] );
        }else if (strResult.compare("BezierCurve") == 0){
             object = new BezierCurve( (BezierCurve * ) WORLD[offset] );
        }else if (strResult.compare("BSplines") == 0){
             object = new BSplines( (BSplines * ) WORLD[offset] );
        }else if (strResult.compare("Nurbs") == 0){
             object = new Nurbs( (Nurbs * ) WORLD[offset] );
        }
        WORLD.push_back(object);
        WORLD[WORLD.size()-1]->translateObject(getCursorPosition());
    }
    displayScene();
    return strResult;
}

std::string BasicGLPane::InterpolateNurbs( int indexCurve1, int indexCurve2, int symbolicIndex)
{
    std::vector<int>::iterator it = find (LIST_INDEX_OBJECT.begin(), LIST_INDEX_OBJECT.end(), indexCurve1);
    size_t offset = it - LIST_INDEX_OBJECT.begin();

    std::vector<int>::iterator it1 = find (LIST_INDEX_OBJECT.begin(), LIST_INDEX_OBJECT.end(), indexCurve2);
    size_t offset1 = it1 - LIST_INDEX_OBJECT.begin();

    Nurbs *nurb=  (Nurbs * ) WORLD[offset];
    Nurbs *nurb1=  (Nurbs * ) WORLD[offset1];

    vector< vector< float> > ptControle  =  nurb->getPtControle();
    vector< vector <float > > ptControle1  =  nurb1->getPtControle();
    vector <float > t = nurb->getTranslation();
    vector <float > t1 = nurb1->getTranslation();
    vector <float > pontos = nurb->getPtsCurva();
    vector <float > pontos1 = nurb1->getPtsCurva();

    vector<vector<vector <double > > > cP(2,vector<vector<double> >((int)pontos.size()/3,vector <double>(3,0)));
    int c = 0;
    for (int i = 0; i < 1; ++i){

        for (int j = 0; j < (int)pontos.size()/3; j++){
            cP[i][j][0] = pontos[c]     + t[0];
            cP[i][j][1] = pontos[c + 1] + t[1];
            cP[i][j][2] = pontos[c + 2] + t[2];

            cP[i+1][j][0] = pontos1[c]      +  t1[0];
            cP[i+1][j][1] = pontos1[c + 1]  +  t1[1];
            cP[i+1][j][2] = pontos1[c + 2 ] +  t1[2];

            c+=3;
        }
    }
    vector <float > cursor = getCursorPosition();
    Object *surfaceNurbs = new SurfaceNurbs(1, ((int)pontos.size()/3)-1, 20, 20, 3,  1, cP) ;
    surfaceNurbs->translateObject(cursor);
    LIST_INDEX_OBJECT.push_back(symbolicIndex);
    WORLD.push_back(surfaceNurbs);
    displayScene();
    return std::string(surfaceNurbs->getTipo());
}

void BasicGLPane::setGlobalRotation( float x, float y, float z)
{
    ROTATION[0] = x;
    ROTATION[1] = y;
    ROTATION[2] = z;

    ANGLE_X = y;
    ANGLE_Y = x;
    displayScene();
}
vector < Object *> BasicGLPane::createTempPointer(vector < Object *> WORLD)
{
     vector <Object *> WORLD_TEMP (WORLD.size());
    //vector <Object *> WORLD;
    for (int i = 0; i < (int)WORLD.size(); ++i){
        std::string strResult = WORLD[i]->getTipo();
        Object* object;
        if (strResult.compare("BezierSurface") == 0){
            object = new SurfaceBezier( (SurfaceBezier * ) WORLD[i] );
        }else if (strResult.compare("BSplineSurface") == 0){
            object = new SurfaceNurbs( (SurfaceNurbs * ) WORLD[i] );
        }else if (strResult.compare("NurbsSurface") == 0){
            object = new SurfaceNurbs( (SurfaceNurbs * ) WORLD[i] );
        }else if (strResult.compare("BezierCurve") == 0){
             object = new BezierCurve( (BezierCurve * ) WORLD[i] );
        }else if (strResult.compare("BSplines") == 0){
             object = new BSplines( (BSplines * ) WORLD[i] );
        }else if (strResult.compare("Nurbs") == 0){
             object = new Nurbs( (Nurbs * ) WORLD[i] );
        }else if (strResult.compare("Grid") == 0){
             object = new  Grid[1];
        }
        WORLD_TEMP[i] = object;
    }
    cout << "Tam dentro do create: " << WORLD_TEMP.size() << endl;
    return WORLD_TEMP;
}

vector <std::string > BasicGLPane::ctrZ()
{
    vector <std::string > listObjectsName;
    if (POINTER_BACKUP ){

        cout << "Aqui no BACKUP: " << POINTER_BACKUP <<" SIZE: " << BACKUP.size() <<"size_world: "<< WORLD.size()<<endl;
        POINTER_BACKUP -= 1;
        WORLD = createTempPointer(BACKUP[POINTER_BACKUP]);

    }
    for (int i = 1; i < (int)WORLD.size(); ++i){
        std::ostringstream ss;
        ss << LIST_INDEX_OBJECT[i];
        listObjectsName.push_back( WORLD[i]->getTipo() + std::string(" ") + ss.str() );
    }
    cout << "POINTER_BACKUP: " << POINTER_BACKUP << endl;
    displayScene();
    return listObjectsName;
}

vector <std::string > BasicGLPane::ctrY()
{
    //POINTER_BACKUP += 1;
    vector <std::string > listObjectsName;
    if (POINTER_BACKUP < (int) (BACKUP.size() - 1) ){
        POINTER_BACKUP += 1;
        WORLD = createTempPointer(BACKUP[POINTER_BACKUP]);

    }

    for (int i = 1; i < (int)WORLD.size(); ++i){
        std::ostringstream ss;
        ss << LIST_INDEX_OBJECT[i];
        listObjectsName.push_back( WORLD[i]->getTipo() + std::string(" ") + ss.str());
    }
    cout << "POINTER_BACKUP ctrY: " << POINTER_BACKUP << endl;
    displayScene();
    return listObjectsName;
}

void BasicGLPane::addNewState()
{
    vector <Object *> WORLD_TEMP = createTempPointer(WORLD);
    //cout << "Topos: "<<WORLD[0]->getTipo() << ", " << WORLD_TEMP[0]->getTipo() << endl;
    BACKUP.push_back(WORLD_TEMP);

    POINTER_BACKUP = BACKUP.size()-1;
}

// Cria uma Curva
std::string BasicGLPane::createCurve(int tp, long symbolicIndex)
{
    vector <float > cursor = getCursorPosition();
    Object *curve;

    if(tp == 0){
        curve = new BezierCurve(0,0,0);
    }
    if(tp == 1){
        curve = new BSplines(0,0,0);
    }
    if(tp == 2){
        curve = new Nurbs(0,0,0);
    }

    curve->translateObject(cursor);
    WORLD.push_back(curve);
    LIST_INDEX_OBJECT.push_back(symbolicIndex);
    displayScene();
    addNewState();
    return curve->getTipo();
}

void BasicGLPane::setNodeCurve(int idNode,double inc)
{
    string name;
    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "BSplines" || name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->setNoSelec(idNode);
            WORLD[LAST_OBJECT_SELECTED]->incNo(inc);
        }
    }
}

void BasicGLPane::setOrdCurve(int ord)
{
    string name;
    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "BSplines" || name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->setOrdCurva(ord);
        }
    }
}

void BasicGLPane::setQuantCurv(int quant)
{
    string name;
    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "BSplines" || name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->setQuant(quant);
        }
    }
}

void BasicGLPane::setPesoCurv(float val)
{
    string name;
    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->setPeso(val);
        }
    }
}

// EVENTOS PARA EDIÇÃO DE UMA CURVA
void BasicGLPane::addPtC()
{
    string name;

    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "BSplines" || name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->addPtControle();
        }

        if(name == "BezierCurve"){
            WORLD[LAST_OBJECT_SELECTED]->addSegment();
        }
    }
}

void BasicGLPane::rmvPtC()
{
    string name;

    if(!RENDER_MODE){

         name = WORLD[LAST_OBJECT_SELECTED]->getTipo();

        if(name == "BSplines" || name == "Nurbs"){
            WORLD[LAST_OBJECT_SELECTED]->rmvPtControle();
        }

        if(name == "BezierCurve"){
            WORLD[LAST_OBJECT_SELECTED]->removeSegment();
        }
    }
}

Object * BasicGLPane::getObject()
{
    return WORLD[LAST_OBJECT_SELECTED];
}

void BasicGLPane::setMod(int tp)
{
    int i;

    MODIFIER_TYPE = tp;

    for(i = 0; i < (int) WORLD.size(); i++){
        WORLD[i]->setModifier(tp);
    }
}

void BasicGLPane::update()
{
    displayScene();
}