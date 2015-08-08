#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "render.h"
#include <map>

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
    void setGlobalRotation( float x, float y, float z);

    //events display
    void displayScene();

    //metodos para conversar com objetos externos..
    vector<float > getCursorPosition();
    void setCursorPosition(int x, int y, int z);

    std::string createBezierSurface(int symbolicIndex, int u, int v, int ru, int rv);
    std::string createSplineSurface (int symbolicIndex, int u, int v, int ru, int rv, int degree);
    std::string createNurbsSurface(int symbolicIndex, int u, int v, int ru, int rv, int degree);
    void selectObject(int idexObject);
    void deleteObject(int idexObject);
    int getIndexLastObjectSelected();


    //Isso na e legal....
    vector <float > getPositionLastObjectSelected();
    vector <float > getRotationLastObjectSelected();
    vector <float > getScaleLastObjectSelected();
    std::string getTipoLastObjectSelected();
    void newScene();


    // Para Edição das Curvas
    std::string createCurve(int tp, long symbolicIndex);
    void setNodeCurve(int idNode,double inc);
    void setOrdCurve(int ord);
    void setQuantCurv(int quant);
    void setPesoCurv(float val);
    void addPtC();
    void rmvPtC();
    void setMod(int tp);
    vector <std::string > ctrZ();
    vector <std::string > ctrY();
    void addNewState();
    vector < Object *> createTempPointer(vector < Object *> WORLD);
    vector < int > createTempVector( vector <int > oldVector);


    Object * getObject();
    std::string duplicateObject(int oldIndex, int newIndex);
    void update();
    std::string InterpolateNurbs( int indexCurve1, int indexCurve2, int symbolicIndex);

protected:

    int POINTER_BACKUP;
    vector < vector < Object * > > BACKUP;
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
    int LAST_EVENT;
    std::vector<int > LIST_INDEX_OBJECT;
    std::vector< vector<int > > LIST_INDEX_OBJECT_STATES;

     // events mouse e teclado
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

    //macro for table of the events
    DECLARE_EVENT_TABLE()
};

