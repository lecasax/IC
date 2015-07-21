#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "render.h"

using namespace std;

class BasicGLPane : public wxGLCanvas
{
    wxGLContext*    m_context;

public:

    //construtor e destrutors
    BasicGLPane(wxWindow* parent, int* args);
    virtual ~BasicGLPane();

    //metodos do opengl
    void resized(wxSizeEvent& evt);
    int getWidth();
    int getHeight();

    //metodos auxiliares
    void getCoordenateWorldMouse(int mouseX, int mouseY, double *point);
    void optionsActions(int id);
    void quadrado(float base, float altura);
    void render(wxPaintEvent& evt);

    // events mouse
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void mouseMiddleDclick(wxMouseEvent &event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    void mouseMiddleDown(wxMouseEvent& event);
    void mouseMiddleUp(wxMouseEvent& event);

    //events menubar
    void OnQuit(wxCommandEvent& event);

    //events display
    void displayScene();

    //metodos para conversar com objetos externos..
    vector<float > getCursorPosition();
    std::string createBezierSurface();
    std::string createSplineSurface ();
    std::string createNurbsSurface();
    //macro for table of the events
    DECLARE_EVENT_TABLE()

protected:

    vector <Object *> WORLD;
    vector <float > ROTATION;
    vector <float > CURSOR_POSITION;
    vector <float > LAST_MOUSE_POSITION_DRAGG;
    bool RENDER_MODE;
    int MODIFIER_TYPE ;
    float SCALE ;
    int LAST_OBJECT_SELECTED;
    unsigned int LAST_CLICK_OBJECT;
    int START_X;
    int START_Y;
    int START_ANGLE_X;
    int START_ANGLE_Y;
    int ANGLE_X;
    int ANGLE_Y;

};

