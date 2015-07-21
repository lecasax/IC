#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/framemanager.h>
#include <wx/treectrl.h>
#include <wx/menu.h>
#include <vector>
#include <string>
#include "manager.h"
#include "customPanel.h"

class WidgetFrame : public wxFrame
{

public:


    WidgetFrame (const wxString &title);
    ~WidgetFrame();
    wxToolBar *  createToolBar();
    void  createMenuBar();
    //void setBasicPlane(BasicGLPane *glPane);

    /*funcao para receber um evento de menu acessar metodos publicos de BasciPlane*/
    void acessBasicPlaneEvents(wxCommandEvent&  event);


    // eventos na frame que pode vir dos filhos...
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


    //Eventos do subMenu
    virtual void itemCurveBezierMenuSelection( wxCommandEvent& event );
    virtual void itemCurveSplineMenuSelection( wxCommandEvent& event );
    virtual void itemCurveNurbsMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceBezierMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceSplineMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceNurbsMenuSelection( wxCommandEvent& event );

    void teste();
    DECLARE_EVENT_TABLE();

protected:

    wxTreeCtrl* m_treeCtrl;
    wxTreeItemId root;
    wxMenuBar* menubar;
    wxMenu* menuFile;
    wxMenu* menuAdd;
    wxMenu* subMenuCurve;
    wxMenu* subMenuSurface;
    wxMenu* m_menu3;
    Transform *customPanel;

    //Objetos do menu
    wxMenuItem* menuItemCurve;
    wxMenuItem* itemCurveBezier;
    wxMenuItem* itemCurveSpline ;
    wxMenuItem* itemCurveNurbs;
    wxMenuItem* menuItemSurface;
    wxMenuItem* itemSurfaceBezier;
    wxMenuItem* itemSurfaceSpline;
    wxMenuItem* itemSurfaceNurbs;


private:

    /*objeto para acessar as funcoes publicas de BasicPlane */
    BasicGLPane *opengl;
    wxAuiManager m_mgr;

};
