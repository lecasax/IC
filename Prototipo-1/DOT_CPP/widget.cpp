#include "widget.h"
#include <wx/string.h>
#include <string>



BEGIN_EVENT_TABLE(WidgetFrame, wxFrame)


EVT_MOTION(WidgetFrame::mouseMoved)
EVT_LEFT_DOWN(WidgetFrame::mouseDown)
EVT_RIGHT_DOWN(WidgetFrame::rightClick)
EVT_KEY_DOWN(WidgetFrame::keyPressed)
/*EVT_LEFT_UP(BasicGLPane::mouseReleased)
EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
EVT_SIZE(BasicGLPane::resized)
EVT_KEY_UP(BasicGLPane::keyReleased)
EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
EVT_MIDDLE_DCLICK(BasicGLPane::mouseMiddleDclick)
EVT_MIDDLE_DOWN(BasicGLPane::mouseMiddleDown)
EVT_MIDDLE_UP(BasicGLPane::mouseMiddleUp)
EVT_PAINT(WidgetFrame::render)
*/
END_EVENT_TABLE()

using namespace std;

/* variavel para controlar o id dos componentes do menu*/

WidgetFrame::WidgetFrame(const wxString &title)
            :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))

{

    m_mgr.SetManagedWindow(this);
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    opengl = new BasicGLPane( this, args);
    //glPane->SetFocus ();


    //sem isso os eventos de teclado nao funcionam

    customPanel =  new Transform(this, wxID_ANY);
    //wxTextCtrl* text2 = new wxTextCtrl(this, -1, _("Pane 2 - sample text"),
    //wxDefaultPosition, wxSize(200,150),wxNO_BORDER | wxTE_MULTILINE);

    //wxTextCtrl* text3 = new wxTextCtrl(this, -1, _("Main content window"),
    //wxDefaultPosition, wxSize(200,150), wxNO_BORDER | wxTE_MULTILINE);

    wxTextCtrl* text4 = new wxTextCtrl(this, -1, _("Pane 4 - sample text"),
    wxDefaultPosition, wxSize(200,150),wxNO_BORDER | wxTE_MULTILINE);

    m_treeCtrl = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxTR_DEFAULT_STYLE|wxTR_ROW_LINES );
    root = m_treeCtrl->AddRoot(wxString("Objects"), -1, -1,NULL);
    //m_treeCtrl->AppendItem (root, wxString ("Filho-1"), -1, -1, NULL);
    //m_treeCtrl->AppendItem (root, wxString ("Filho-2"), -1, -1, NULL);
    //m_treeCtrl->AppendItem (root, wxString ("Filho-3"), -1, -1, NULL);

    //isso serve para passar as info para o panel
    wxAuiPaneInfo info = wxAuiPaneInfo ();
    info.CloseButton (false);
    info.Left();
    m_mgr.AddPane(m_treeCtrl, info);
    info.Right();
    m_mgr.AddPane(customPanel, info);
    //m_mgr.AddPane(text2, info);
    info.Bottom();
    m_mgr.AddPane(text4, info);
    info.Center();
    m_mgr.AddPane(opengl, info);

    m_mgr.GetPane(customPanel).Hide();
    //m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BORDER_COLOUR, *wxBLACK);
    //m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, *wxGREEN);
    //m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 15);
    m_mgr.Update();


    //SetMenuBar(createMenuBar());
    createMenuBar();
    this->SetMenuBar( menubar );
    createToolBar();

    this->Centre();
    //Connect(wxID_ANY , wxEVT_COMMAND_MENU_SELECTED,
    //wxCommandEventHandler(WidgetFrame::acessBasicPlaneEvents));//command for class BasicGLPane
    //this->Connect(-1, wxEVT_LEFT_DOWN , wxCommandEventHandler(WidgetFrame::OnClick));
}

WidgetFrame::~WidgetFrame()
{
    /*Eventos dos submenus */
    this->Disconnect( itemCurveBezier->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveBezierMenuSelection ) );

    this->Disconnect( itemCurveSpline->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveSplineMenuSelection ) );

    this->Disconnect( itemCurveNurbs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveNurbsMenuSelection ) );

    this->Disconnect( itemSurfaceBezier->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceBezierMenuSelection ) );

    this->Disconnect( itemSurfaceSpline->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceSplineMenuSelection ) );

    this->Disconnect( itemSurfaceNurbs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceNurbsMenuSelection ) );

    m_mgr.UnInit();
}

/*void WidgetFrame::setBasicPlane(BasicGLPane *glPane)

{   //set pointer glPane
    this->glPane = glPane;
}
*/
void WidgetFrame::acessBasicPlaneEvents(wxCommandEvent&  event)

{

    int id =  event. GetId ();
    opengl->optionsActions(id);
}

void WidgetFrame::createMenuBar()

{
    menubar = new wxMenuBar( 0 );
    menuFile = new wxMenu();
    menuAdd = new wxMenu();
    subMenuCurve = new wxMenu();
    subMenuSurface = new wxMenu();

    //Constoi o Submenu das curvas
    menuItemCurve = new wxMenuItem( menuAdd, wxID_ANY, wxT("Curve"), wxEmptyString, wxITEM_NORMAL, subMenuCurve  );
    menuAdd->Append(  menuItemCurve );

    itemCurveBezier = new wxMenuItem( subMenuCurve, wxID_ANY, wxString( wxT("Bezier") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuCurve->Append(itemCurveBezier);

    itemCurveSpline = new wxMenuItem( subMenuCurve, wxID_ANY, wxString( wxT("Spline") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuCurve->Append(itemCurveSpline);

    itemCurveNurbs = new wxMenuItem( subMenuCurve, wxID_ANY, wxString( wxT("Nurbs") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuCurve->Append(itemCurveNurbs);


    /*Constroi o Submenu das Superficies*/
    menuItemSurface = new wxMenuItem( menuAdd, wxID_ANY, wxT("Surface"), wxEmptyString, wxITEM_NORMAL, subMenuSurface  );
    menuAdd->Append(  menuItemSurface );

    itemSurfaceBezier = new wxMenuItem(  subMenuSurface, wxID_ANY, wxString( wxT("Bezier") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuSurface->Append(itemSurfaceBezier);

    itemSurfaceSpline = new wxMenuItem(  subMenuSurface, wxID_ANY, wxString( wxT("Spline") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuSurface->Append(itemSurfaceSpline);

    itemSurfaceNurbs = new wxMenuItem(  subMenuSurface, wxID_ANY, wxString( wxT("Nurbs") ) , wxEmptyString, wxITEM_NORMAL );
    subMenuSurface->Append(itemSurfaceNurbs);

    menubar->Append( menuFile, wxT("File") );

    menubar->Append( menuAdd, wxT("Add") );



    /*Eventos dos submenus */
    this->Connect( itemCurveBezier->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveBezierMenuSelection ) );


    this->Connect( itemCurveSpline->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveSplineMenuSelection ) );



    this->Connect( itemCurveNurbs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemCurveNurbsMenuSelection ) );


    this->Connect( itemSurfaceBezier->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceBezierMenuSelection ) );


    this->Connect( itemSurfaceSpline->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceSplineMenuSelection ) );


    this->Connect( itemSurfaceNurbs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler( WidgetFrame::itemSurfaceNurbsMenuSelection ) );

    //m_menu3 = new wxMenu();
    //menubar->Append( m_menu3, wxT("Help") );

}

/*void WidgetFrame::OnClick(wxCommandEvent& event)
{
  std::cout << "Evento do bota esquerdo chegando na frame, veio la da canvas..." << std::endl;
  event.Skip();
}*/

void WidgetFrame::itemCurveBezierMenuSelection( wxCommandEvent& event )
{
    cout << "Clicando na curva de Bezier..." << endl;
}
void WidgetFrame::itemCurveSplineMenuSelection( wxCommandEvent& event )
{
    cout << "Clicando na curva Spline..." << endl;
}
void WidgetFrame::itemCurveNurbsMenuSelection( wxCommandEvent& event )
{
    cout << "Clicando na curva Nurbs..." << endl;
}
void WidgetFrame::itemSurfaceBezierMenuSelection( wxCommandEvent& event )
{
    std::string s(opengl->createBezierSurface());
    //wxTreeItemId root = m_treeCtrl->GetItemParent();
    wxString str(s);
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    cout << "Clicando na superficie Bezier..." << endl;
}
void WidgetFrame::itemSurfaceSplineMenuSelection( wxCommandEvent& event )
{
    std::string s(opengl->createSplineSurface());
    //wxTreeItemId root = m_treeCtrl->GetItemParent();
    wxString str(s);
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    cout << "Clicando na superficie Spline..." << endl;
}

void WidgetFrame::itemSurfaceNurbsMenuSelection( wxCommandEvent& event )
{
    std::string s(opengl->createNurbsSurface());
    //wxTreeItemId root = m_treeCtrl->GetItemParent();
    wxString str(s);
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    cout << "Clicando na superficie Spline..." << endl;
    //vector <float > cursor = opengl->getCursorPosition();
    //customPanel->setCursorLabel(cursor[0], cursor[1], cursor[2]);
    //cout << "Clicando na superficie Nurbs..." << endl;
    //this->Layout();

}

wxToolBar * WidgetFrame::createToolBar()

{
    vector <string > arrayStringNames;
    //string s1 = ("ICONS/pencil.png");
    //string s2 = ("ICONS/exit.png");


    wxImage::AddHandler( new wxPNGHandler );

    wxBitmap curve(wxT("ICONS/pencil.png"), wxBITMAP_TYPE_PNG);
    wxBitmap exitt(wxT("ICONS/exit.png"), wxBITMAP_TYPE_PNG);
    wxBitmap surface(wxT("ICONS/surface.png"), wxBITMAP_TYPE_PNG);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(wxID_NEW, wxT("Copy"), curve, wxString("Curve Bezier"));
    toolbar->AddTool(wxID_SAVE,wxT("Copy"), surface, wxString("Surface Bezier"));
    toolbar->AddTool(wxID_COPY,wxT("Copy"), exitt, wxString("I will...."));
    toolbar->Realize();

    return toolbar;

}

void WidgetFrame::mouseDown(wxMouseEvent& event)
{
    cout << "Fui chamado de fora...Mouse left down... fazer algoo..." << endl;
}

void WidgetFrame::mouseMoved(wxMouseEvent& event)
{

    cout << "Fui chamado de fora..., Mouse em movimento, fui chamada de fora...." << endl;
}

void WidgetFrame::rightClick(wxMouseEvent& event)
{
    cout << "Evento de botao direito na frame......chamar aqui as funcoes da opengl...." << endl;
}


void WidgetFrame::keyPressed(wxKeyEvent& event)
{

    char n = 78;
    static bool panelOption = true;
    wxChar uc = event.GetUnicodeKey();
    //cout << uc << endl;
    if (uc != WXK_NONE){
        //cout << "Aqui dentro..." << endl;
        if (uc ==  n){
            if (panelOption){
                //cout << "Evento de n..." <<  endl;
                m_mgr.GetPane(customPanel).Show();
            } else {
                m_mgr.GetPane(customPanel).Hide();
            }
            panelOption = !panelOption;
            m_mgr.Update();
        }
    }
}