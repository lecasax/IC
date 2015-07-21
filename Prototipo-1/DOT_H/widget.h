#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/framemanager.h>
#include <wx/treectrl.h>
#include <wx/menu.h>
#include <vector>
#include <string>
#include "manager.h"

class WidgetFrame : public wxFrame
{

public:


    WidgetFrame (const wxString &title);
    ~WidgetFrame();
    wxToolBar *  createToolBar();
    wxMenuBar *  createMenuBar();

    wxPanel * createEditBarCurve();
    void getNoSelect( wxMouseEvent& event );
    void move( wxMouseEvent& event );
	void decNo( wxMouseEvent& event );
	void incNo( wxMouseEvent& event );
	void modOrdem( wxMouseEvent& event );
	void modPtCurva( wxMouseEvent& event );
	void modPeso( wxMouseEvent& event );
    //void setBasicPlane(BasicGLPane *glPane);

    /*funcao para receber um evento de menu acessar metodos publicos de BasciPlane*/
    void acessBasicPlaneEvents(wxCommandEvent&  event);

protected:

    wxTreeCtrl* m_treeCtrl;
    wxMenuBar* m_menubar1;
    wxMenu* m_menu1;
    wxMenu* m_menu11;
    wxMenu* m_menu2;
    wxMenu* m_menu3;


private:

    /*objeto para acessar as funcoes publicas de BasicPlane */
    BasicGLPane *opengl;
    wxAuiManager m_mgr;

};
