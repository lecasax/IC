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
#include "customTreeCtrl.h"
#include "customDialog.h"

class WidgetFrame : public wxFrame
{

public:


    WidgetFrame (const wxString &title);
    ~WidgetFrame();


protected:

    CustomDialog *dialog;
    CustomTreeCtrl* m_treeCtrl;
    wxTreeItemId root;
    wxTreeItemId lastItemSelected;
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
    void OnExit(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnPopupClickDeleteObject(wxCommandEvent &event);
    void OnPopupClickDuplicateObject(wxCommandEvent &event);
    void OnPopupClickInterpolateNurbsObject(wxCommandEvent &event);


    //Eventos do subMenu
    virtual void itemCurveBezierMenuSelection( wxCommandEvent& event );
    virtual void itemCurveSplineMenuSelection( wxCommandEvent& event );
    virtual void itemCurveNurbsMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceBezierMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceSplineMenuSelection( wxCommandEvent& event );
    virtual void itemSurfaceNurbsMenuSelection( wxCommandEvent& event );
    virtual void OnTreeItemRightClick(wxTreeEvent& event);
    //virtual void OnPopupClick(wxCommandEvent &evt);


    DECLARE_EVENT_TABLE();

    //--------------------------------------------//
    // Componentes para edição da Curva
	wxPanel* m_panel4;
	wxButton* m_button74;
	wxButton* m_button75;
	wxButton* m_button76;
	wxStaticText* m_staticText6;
	wxListBox* m_checkList2;
	wxButton* m_button16;
	wxButton* m_button17;
	wxStaticText* m_staticText8;
	wxTextCtrl* m_textCtrl3;
	wxButton* m_button9;
	wxStaticText* m_staticText51;
	wxTextCtrl* m_textCtrl31;
	wxButton* m_button91;
	wxStaticText* m_staticText5;
	wxTextCtrl* m_textCtrl32;
	wxButton* m_button92;
	wxStaticText* m_staticText52;
	wxTextCtrl* m_textCtrl4;

	// Funções para Edição da Curva
	wxPanel * createEditBarCurve();

	// Eventos da Curva
	void decNo( wxMouseEvent& event );
	void incNo( wxMouseEvent& event );
	void modOrdem( wxMouseEvent& event );
	void modPtCurva( wxMouseEvent& event );
	void modPeso( wxMouseEvent& event );
	void loadInfo();

    void addPtControle( wxMouseEvent& event );
    void rmvPtControle( wxMouseEvent& event );

    void clickTranslat(wxCommandEvent& event);
    void clickRotat(wxCommandEvent& event);
    void clickEscal(wxCommandEvent& event);
    void clickDesab(wxCommandEvent& event);

    void clickUndo(wxCommandEvent& event);
    void clickRedo(wxCommandEvent& event);

    wxToolBar *  createToolBar();
    void  createMenuBar();
    //void setBasicPlane(BasicGLPane *glPane);

    /*funcao para receber um evento de menu acessar metodos publicos de BasciPlane*/
    void acessBasicPlaneEvents(wxCommandEvent&  event);
    int getNumberBottomString(std::string str);
    void fillCustomPanel(std::vector<float > t,  std::vector<float > r, std::vector<float >,
                        std::string tipo  );
    std::string getFirstNameItem(std::string str);
    std::vector <int  >  getListNameObjectSelected(std::string name);
    int lengthObjecteSelected();



private:

    /*objeto para acessar as funcoes publicas de BasicPlane */
    BasicGLPane *opengl;
    wxAuiManager m_mgr;
    long countItemTree;




};
