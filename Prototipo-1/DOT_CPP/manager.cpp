#include <GL/glut.h>
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
 
static float obsP[] =  { -50, 100, 250, 0, 0, 0, 0, 1, 0 };
vector <Object *> world;
vector<int > obj_selected;
int last_object_selected = 0;

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
    float  t[] = {0.0, 0.0, 1.0};
    float  t2[] = {2.0, 0.0, 0.0};
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

    world.push_back(grid);
    world.push_back(cube);
    world.push_back(cube2);
    world.push_back(cube3);

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
 
}


void BasicGLPane::mouseMiddleDclick(wxMouseEvent &event)

{

}
void BasicGLPane::mouseMoved(wxMouseEvent& event )
{

        //displayScene(); 

}

int getMinDepth(vector<int > obj_selected, vector <Object *> world)

{
    int index = 0;
    if (obj_selected.size() > 0){
        float min = world[0]->getDepth();
        for(int i = 0; i < obj_selected.size(); i++){
            if( world[obj_selected[i]]->getDepth() >=  min ){

                min = world[obj_selected[i]]->getDepth();
                index = obj_selected[i];
            }
        }
        return index;
    } else {
        return 0;
    }
}

void BasicGLPane::mouseDown(wxMouseEvent& event) 
{
    //simulando a criacao de objetos
    vector <float > pointWorld = Render::worldPoint(event.GetX(), event.GetY());
    cout << "X: " << pointWorld[0] << "Y: " << pointWorld[1] << "Z: " << pointWorld[2] << endl;
    //world[1].translateObject(pointWorld);
    vector <float > proj;
    proj.push_back(45.0); proj.push_back((float)getWidth()/(float)getHeight()); 
    proj.push_back(0.1); proj.push_back(400);
    
    obj_selected = Render::render(world,  proj,  event.GetX(), event.GetY());
    int obj_sel = getMinDepth(obj_selected, world) ;
    
    //modificando o estado do objeto selecionado
    last_object_selected = obj_sel;
    if(obj_sel){

        world[obj_sel]->setSelected(true);
    }
    cout << "Ultimo objeto selecionado: " << last_object_selected << endl;
    displayScene();
}


void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) 
{
    cout << "mouseWheelMoved" << endl;
    cout << "X: " << event.GetX() << "Y: "<< event.GetY();
    displayScene();
}


void BasicGLPane::mouseReleased(wxMouseEvent& event) 
{
    cout << "mouseReleased" << endl;
}


void BasicGLPane::rightClick(wxMouseEvent& event) 
{

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
            //modo edicao....
            cout << "Evento de tab..." <<  endl;
        }
        
        if (uc == WXK_SPACE){
            cout << "Evendo do espaco...." << endl;
        }

        if (uc ==  a){
            cout << "Evento de A..." <<  endl;
        }
    }

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
    Render::renderObjects(world);
   
    glFlush();
    SwapBuffers();

}