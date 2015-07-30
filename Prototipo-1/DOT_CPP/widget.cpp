#include "widget.h"
#include <boost/tokenizer.hpp>
#include <string>
#include <sstream>
#include <wx/string.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>


//struct timeval  tv1, tv2;

#define ID_DELETE_OBJECT   2001
#define ID_DUPLICATE_OBJECT  2002
#define ID_NEW 2003
#define ID_INTERPOLATE_NURBS 2004

BEGIN_EVENT_TABLE(WidgetFrame, wxFrame)

EVT_MOTION(WidgetFrame::mouseMoved)
EVT_LEFT_DOWN(WidgetFrame::mouseDown)
EVT_RIGHT_DOWN(WidgetFrame::rightClick)
EVT_KEY_DOWN(WidgetFrame::keyPressed)
EVT_MENU(ID_NEW,   WidgetFrame::OnNew)
EVT_MENU(wxID_EXIT,  WidgetFrame::OnExit)
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
    //gettimeofday(&tv1, NULL);
    countItemTree = 1;
    m_mgr.SetManagedWindow(this);
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    opengl = new BasicGLPane( this, args);
    opengl->SetFocus ();


    //sem isso os eventos de teclado nao funcionam

    customPanel =  new Transform(this, wxID_ANY);
    //wxTextCtrl* text2 = new wxTextCtrl(this, -1, _("Pane 2 - sample text"),
    //wxDefaultPosition, wxSize(200,150),wxNO_BORDER | wxTE_MULTILINE);

    //wxTextCtrl* text3 = new wxTextCtrl(this, -1, _("Main content window"),
    //wxDefaultPosition, wxSize(200,150), wxNO_BORDER | wxTE_MULTILINE);

    wxTextCtrl* text4 = new wxTextCtrl(this, -1, _("Pane 4 - sample text"),
    wxDefaultPosition, wxSize(200,150),wxNO_BORDER | wxTE_MULTILINE);

    m_treeCtrl = new CustomTreeCtrl(this);
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

    // Edição das Curvas está em m_panel4
    m_panel4 = this->createEditBarCurve();
    m_mgr.AddPane( m_panel4, info);

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
    m_treeCtrl->Connect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( WidgetFrame::OnTreeItemRightClick ), NULL, this );
}

WidgetFrame::~WidgetFrame()
{
    cout << "Desrufasdfas dfaosidjf" << endl;
    //eventos d arvore de objetos
    m_treeCtrl->Disconnect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( WidgetFrame::OnTreeItemRightClick ), NULL, this );


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


    m_button74->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::addPtControle ), NULL, this );
	m_button75->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::rmvPtControle ), NULL, this );
	m_button17->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::decNo ), NULL, this );
	m_button16->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::incNo ), NULL, this );
	m_button9->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modOrdem ), NULL, this );
	m_button91->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPtCurva ), NULL, this );
	m_button92->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPeso ), NULL, this );

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

    menuFile->Append(ID_NEW, "&New\tCtrl-N",
                     "Restart the application");

    menuFile->Append(wxID_EXIT);

    menubar->Append( menuFile, wxT("&File") );

    menubar->Append( menuAdd, wxT("&Add") );



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

void WidgetFrame::OnNew(wxCommandEvent& event)
{
    m_treeCtrl->DeleteChildren(root);
    countItemTree = 1;
    opengl->newScene();
}

void WidgetFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void WidgetFrame::itemCurveBezierMenuSelection( wxCommandEvent& event )
{
    std::string s(opengl->createCurve(0,countItemTree));
    std::ostringstream ss;
    ss << countItemTree;
    wxString str(s + std::string(" ") + ss.str());
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    m_treeCtrl->ExpandAll ();
    countItemTree++;
    cout << "Clicando na curva de Bezier..." << endl;
}

void WidgetFrame::itemCurveSplineMenuSelection( wxCommandEvent& event )
{
    std::string s(opengl->createCurve(1,countItemTree));
    std::ostringstream ss;
    ss << countItemTree;
    wxString str(s + std::string(" ") + ss.str());
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    m_treeCtrl->ExpandAll ();
    countItemTree++;
    cout << "Clicando na curva de BSpline..." << endl;
}

void WidgetFrame::itemCurveNurbsMenuSelection( wxCommandEvent& event )
{

    std::string s(opengl->createCurve(2,countItemTree));
    std::ostringstream ss;
    ss << countItemTree;
    wxString str(s + std::string(" ") + ss.str());
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    m_treeCtrl->ExpandAll ();
    countItemTree++;
    cout << "Clicando na curva de BSpline..." << endl;
}

void WidgetFrame::itemSurfaceBezierMenuSelection( wxCommandEvent& event )
{
    dialog = new CustomDialog(this, wxID_ANY, wxString("Bezier Config"));
    if ( dialog->ShowModal() == wxID_OK ){
        std::string s = opengl->createBezierSurface(countItemTree,
                                                atoi(dialog->getControlPointU().c_str()),
                                                atoi(dialog->getControlPointV().c_str()),
                                                atoi(dialog->getResolutionU().c_str()),
                                                atoi(dialog->getResolutionV().c_str())
                                                );

            //std::string s(opengl->createBezierSurface(countItemTree));
        std::ostringstream ss;
        ss << countItemTree;
        wxString str(s + std::string(" ") + ss.str());
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
        cout << "Clicando na superficie Bezier..." << endl;
    }
}
void WidgetFrame::itemSurfaceSplineMenuSelection( wxCommandEvent& event )
{
    dialog = new CustomDialog(this, wxID_ANY, wxString("BSpline Config"));
    if ( dialog->ShowModal() == wxID_OK ){
        std::string s = opengl->createSplineSurface(countItemTree,
                                                atoi(dialog->getControlPointU().c_str()),
                                                atoi(dialog->getControlPointV().c_str()),
                                                atoi(dialog->getResolutionU().c_str()),
                                                atoi(dialog->getResolutionV().c_str()),
                                                atoi(dialog->getDegree().c_str())
                                                );
        std::ostringstream ss;
        ss << countItemTree;
        wxString str(s + std::string(" ") + ss.str());
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
        cout << "Clicando na superficie Spline..." << endl;
    }
}

void WidgetFrame::itemSurfaceNurbsMenuSelection( wxCommandEvent& event )
{
    dialog = new CustomDialog(this, wxID_ANY, wxString("Nurbs Config"));
    if ( dialog->ShowModal() == wxID_OK ){
        std::string s = opengl->createNurbsSurface(countItemTree,
                                                atoi(dialog->getControlPointU().c_str()),
                                                atoi(dialog->getControlPointV().c_str()),
                                                atoi(dialog->getResolutionU().c_str()),
                                                atoi(dialog->getResolutionV().c_str()),
                                                atoi(dialog->getDegree().c_str())
                                                );
        std::ostringstream ss;
        ss << countItemTree;
        wxString str(s + std::string(" ") + ss.str());
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
        cout << "Clicando na superficie Nurbs..." << endl;

    }
}

void WidgetFrame::fillCustomPanel(std::vector<float > t,  std::vector<float > r, std::vector<float > s,
                        std::string tipo  )
{

    customPanel->setTranslationLabel(t[0], t[1], t[2]);
    customPanel->setRotationLabel(r[0], r[1], r[2]);
    customPanel->setScaleLabel(s[0], s[1], s[2]);
    customPanel->setItemLabel(tipo);
}


wxToolBar * WidgetFrame::createToolBar()

{
    vector <string > arrayStringNames;
    //string s1 = ("ICONS/pencil.png");
    //string s2 = ("ICONS/exit.png");


    wxImage::AddHandler( new wxPNGHandler );

    wxBitmap trans(wxT("ICONS/translacao.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rotac(wxT("ICONS/rotacao.png"), wxBITMAP_TYPE_PNG);
    wxBitmap escal(wxT("ICONS/escala.png"), wxBITMAP_TYPE_PNG);
    wxBitmap disab(wxT("ICONS/disable.png"), wxBITMAP_TYPE_PNG);
    wxBitmap undo(wxT("ICONS/undo.png"), wxBITMAP_TYPE_PNG);
    wxBitmap redo(wxT("ICONS/redo.png"), wxBITMAP_TYPE_PNG);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(1001, wxT("Copy"), trans, wxString("Translacao"));
    toolbar->AddTool(1002,wxT("Copy"), rotac, wxString("Rotacao"));
    toolbar->AddTool(1003,wxT("Copy"), escal, wxString("Escala"));
    toolbar->AddTool(1004,wxT("Copy"), disab, wxString("Desabilitar Modificador"));
    toolbar->AddTool(1005,wxT("&Undo\tCtrl-Z"), undo, wxString("Undo"));
    toolbar->AddTool(1006,wxT("&Redo\tCtrl-Y"), redo, wxString("Redo"));
    toolbar->Realize();

    Connect(1001, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickTranslat ));
    Connect(1002, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickRotat ));
    Connect(1003, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickEscal ));
    Connect(1004, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickDesab ));
    Connect(1005, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickUndo ));
    Connect(1006, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(WidgetFrame::clickRedo ));


    return toolbar;
}

void WidgetFrame::mouseDown(wxMouseEvent& event)
{
    //Verficando se o click acertou algum objeto da lista...
    //GetChildren().GetEventHandler();
    //wxWindowList* wlist = &this->GetChildren();
    //wxWindow *child;
    /*for( wxWindowList::iterator iter = wlist->begin();
           iter != wlist->end();
           ++iter )
     {
         child = *iter;
         cout <<"Name:" <<child->GetName() << endl;
     }
    */


    int num=wxTREE_HITTEST_ONITEMLABEL;
    wxTreeItemId item = m_treeCtrl->HitTest(event.GetPosition(), num);
    if (item.IsOk()){
        int idObject = getNumberBottomString( m_treeCtrl->GetItemText(item).ToStdString());
        m_treeCtrl->SelectItem(item, true);
        opengl->selectObject(idObject);
        fillCustomPanel(opengl->getPositionLastObjectSelected(),
                    opengl->getRotationLastObjectSelected(),
                    opengl->getScaleLastObjectSelected(),
                    opengl->getTipoLastObjectSelected()
                    );
        cout << "item clicked: " << m_treeCtrl->GetItemText(item).ToStdString() << endl;
    }

    vector <float > cursor = opengl->getCursorPosition();
    customPanel->setCursorLabel(cursor[0], cursor[1], cursor[2]);

    cout << "Fui chamado de fora...Mouse left down... fazer algoo..." << endl;

    //fazer aqui uma condica para verificar ao qual janela o ponto pertence.....


}

void WidgetFrame::mouseMoved(wxMouseEvent& event)
{
    fillCustomPanel(opengl->getPositionLastObjectSelected(),
                    opengl->getRotationLastObjectSelected(),
                    opengl->getScaleLastObjectSelected(),
                    opengl->getTipoLastObjectSelected()
                    );
    cout << "Fui chamado de fora..., Mouse em movimento, fui chamada de fora...." << endl;
}

void WidgetFrame::rightClick(wxMouseEvent& event)
{
    fillCustomPanel(opengl->getPositionLastObjectSelected(),
                    opengl->getRotationLastObjectSelected(),
                    opengl->getScaleLastObjectSelected(),
                    opengl->getTipoLastObjectSelected()
                    );


    cout << "Evento de botao direito na frame......chamar aqui as funcoes da opengl...." << endl;
    loadInfo();
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
            this->Update();
        }
    }else if (uc == WXK_CONTROL_Z){

        cout << "CTR-Z"<< endl;
    } else  {
        switch ( event.GetKeyCode() ){

            case WXK_NUMPAD1:
                cout << "TECLADO ... END" << endl;
                opengl->setGlobalRotation(0, -360, 0);
                //TO DO AIXS X/Y
            break;

            case WXK_NUMPAD3:
                cout << "TECLADO ... END" << endl;
                opengl->setGlobalRotation(0, 0, 90);
                //TO DO AIXS Y/Z
            break;

            case WXK_NUMPAD7:
                cout << "TECLADO ... WXK_NUMPAD7" << endl;
                opengl->setGlobalRotation(360, 0, 0);
                //TO DO AIXS X/Z
            break;

            case WXK_CONTROL_Z:
                cout << "CTR-Z"<< endl;
            break;


            case WXK_CONTROL_Y:
                cout << "CTR-Z"<< endl;
            break;

        }
    }
    cout <<"Testando eventos de teclado: " << event.GetKeyCode() << endl;
    cout << "evendo de teclado...." << endl;

	loadInfo();
}

int WidgetFrame::getNumberBottomString(std::string str)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ");
    tokenizer tokens(str, sep);
    string numberItem;
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
       numberItem = *tok_iter;
    }
    return atoi(numberItem.c_str());
}
std::string WidgetFrame::getFirstNameItem(std::string str)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ");
    tokenizer tokens(str, sep);
    string strResult;
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
       strResult =  *tok_iter;
       break;
    }
    return strResult;
}
std::vector <int  >  WidgetFrame::getListNameObjectSelected(std::string name)
{
    std::vector <int > ids;
    wxArrayTreeItemIds items;
    m_treeCtrl->GetSelections(items);

    for ( unsigned i = 0; i < items.size(); i++ )
    {
        wxTreeItemId treeid = items[i];
        if (treeid.IsOk()){
            string stringItemFirstName = getFirstNameItem(m_treeCtrl->GetItemText(treeid).ToStdString());
            string stringItem = m_treeCtrl->GetItemText(treeid).ToStdString();
            if (name.compare(stringItemFirstName) == 0){
                ids.push_back(getNumberBottomString(stringItem));
            }
        }
    }
    return ids;
}
int WidgetFrame::lengthObjecteSelected()
{
    int lenght = 0;
    wxArrayTreeItemIds items;
    m_treeCtrl->GetSelections(items);

    for ( unsigned i = 0; i < items.size(); i++ )
    {
        wxTreeItemId treeid = items[i];
        if (treeid.IsOk()){
           lenght++;
        }
    }
    return lenght;
}
void WidgetFrame::OnTreeItemRightClick(wxTreeEvent& event)
{

    // Show popupmenu at position
    bool conditionMenu = false;
    std::vector <int > nurbsCurveSelection;
    wxTreeItemId item = event.GetItem();
    lastItemSelected = item;
    int idObject = getNumberBottomString( m_treeCtrl->GetItemText(item).ToStdString());
    nurbsCurveSelection = getListNameObjectSelected(std::string("Nurbs"));
    opengl->selectObject(idObject);
    wxMenu mnu;
    if (lengthObjecteSelected() == 1 && m_treeCtrl->GetItemText(item).ToStdString().compare("Objects") != 0){
        mnu.Append(ID_DELETE_OBJECT,        "Delete");
        mnu.Append(ID_DUPLICATE_OBJECT,     "Duplicate");
        mnu.Connect(ID_DELETE_OBJECT, wxEVT_MENU, wxCommandEventHandler(WidgetFrame::OnPopupClickDeleteObject), NULL, this);
        mnu.Connect(ID_DUPLICATE_OBJECT,wxEVT_MENU, wxCommandEventHandler(WidgetFrame::OnPopupClickDuplicateObject), NULL, this);
        conditionMenu = true;
    }
    if (nurbsCurveSelection.size() == 2){
        mnu.Append(ID_INTERPOLATE_NURBS,    "Interpolate Nurbs");
        mnu.Connect(ID_INTERPOLATE_NURBS,wxEVT_MENU, wxCommandEventHandler(WidgetFrame::OnPopupClickInterpolateNurbsObject), NULL, this);
        conditionMenu = true;
    }
    if (conditionMenu){
        PopupMenu(&mnu);
    }
    //PopupMenu(&mnu);
}

void WidgetFrame::OnPopupClickInterpolateNurbsObject(wxCommandEvent &event)
{
    //TO DO
    std::vector<int > indexsSelection = getListNameObjectSelected(std::string("Nurbs"));
    std::string objectName = opengl->InterpolateNurbs( indexsSelection[0], indexsSelection[1], countItemTree);
    std::ostringstream ss;
    ss << countItemTree;
    wxString str(objectName + std::string(" ") + ss.str());
    m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
    m_treeCtrl->ExpandAll ();
    countItemTree++;
}

void WidgetFrame::OnPopupClickDeleteObject(wxCommandEvent &event)
{
    std::string stringItem = m_treeCtrl->GetItemText(lastItemSelected).ToStdString();
    if (stringItem.compare(std::string("Objects")) != 0){
        int idObject = getNumberBottomString( stringItem);
        opengl->deleteObject(idObject);
        m_treeCtrl->Delete(lastItemSelected);
    }
    cout << "DELETE-1" << endl;

}

void WidgetFrame::OnPopupClickDuplicateObject(wxCommandEvent &event)
{
    std::string stringItem = m_treeCtrl->GetItemText(lastItemSelected).ToStdString();
    if (stringItem.compare(std::string("Objects")) != 0){
        int idObject = getNumberBottomString(stringItem);
        std::string s = opengl->duplicateObject(idObject, countItemTree);
        std::ostringstream ss;
        ss << countItemTree;
        wxString str(s + std::string(" ") + ss.str());
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
    }
    cout << "Duplicate-1" << endl;
}


wxPanel * WidgetFrame::createEditBarCurve()
{
	//wxGridBagSizer* gbSizer1;
	//gbSizer1 = new wxGridBagSizer( 0, 0 );
	//gbSizer1->SetFlexibleDirection( wxBOTH );
	//gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	//wxBoxSizer* bSizer2;
	//bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_button74 = new wxButton( m_panel4, wxID_ANY, wxT("Adicionar Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_button74, 0, wxALL, 5 );

	m_button75 = new wxButton( m_panel4, wxID_ANY, wxT("Remover Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_button75, 0, wxALL, 5 );

	//m_button76 = new wxButton( m_panel4, wxID_ANY, wxT("Mover"), wxDefaultPosition, wxDefaultSize, 0 );
	//bSizer8->Add( m_button76, 0, wxALL, 5 );

	m_staticText6 = new wxStaticText( m_panel4, wxID_ANY, wxT("Lista de Nós"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	wxArrayString m_checkList2Choices;
	m_checkList2 = new wxListBox( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkList2Choices, 0 );
	m_checkList2 ->SetMinSize( wxSize( 100,180 ) );

	bSizer10->Add( m_checkList2, 0, wxALL, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_button16 = new wxButton( m_panel4, wxID_ANY, wxT("Incrementar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button16, 0, wxALL, 5 );

	m_button17 = new wxButton( m_panel4, wxID_ANY, wxT("Decrementar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_button17, 0, wxALL, 5 );

	//opengl->m_staticText52 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Valor do Incremento"), wxDefaultPosition, wxDefaultSize, 0 );
	//opengl->m_staticText52->Wrap( -1 );
	//bSizer14->Add( opengl->m_staticText52, 0, wxALL, 5 );

	//opengl->m_textCtrl4 = new wxTextCtrl( opengl->m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	//bSizer14->Add( opengl->m_textCtrl4, 0, wxALL, 5 );

	bSizer10->Add( bSizer14, 1, wxEXPAND, 5 );


	m_staticText8 = new wxStaticText( m_panel4, wxID_ANY, wxT("Ordem da Curva"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer8->Add( m_staticText8, 0, wxALL, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrl3 = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( m_textCtrl3, 0, wxALL, 5 );

	m_button9 = new wxButton( m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( m_button9, 0, wxALL, 5 );

	bSizer8->Add( bSizer61, 0, wxEXPAND, 5 );

	m_staticText51 = new wxStaticText( m_panel4, wxID_ANY, wxT("Quantidade de Pontos da Curva"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	bSizer8->Add( m_staticText51, 0, wxALL, 5 );

	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrl31 = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( m_textCtrl31, 0, wxALL, 5 );

	m_button91 = new wxButton( m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( m_button91, 0, wxALL, 5 );

	bSizer8->Add( bSizer611, 0, wxEXPAND, 5 );

	m_staticText5 = new wxStaticText(m_panel4, wxID_ANY, wxT("Peso do Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer8->Add( m_staticText5, 0, wxALL, 5 );

	wxBoxSizer* bSizer612;
	bSizer612 = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrl32 = new wxTextCtrl( m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer612->Add( m_textCtrl32, 0, wxALL, 5 );

	m_button92 = new wxButton(m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer612->Add( m_button92, 0, wxALL, 5 );

	bSizer8->Add( bSizer612, 0, wxEXPAND, 5 );

	// Lista de Nos por Ultimo
	bSizer8->Add( m_staticText6, 0, wxALL, 5 );
	bSizer8->Add( bSizer10, 1, wxEXPAND, 5 );

	m_panel4->SetSizer( bSizer8 );
	m_panel4->Layout();
	bSizer8->Fit( m_panel4 );

	m_button74->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::addPtControle ), NULL, this );
	m_button75->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::rmvPtControle ), NULL, this );
	//m_button76->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BasicGLPane::move ), NULL, this );
	//m_checkList2->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::getNoSelect ), NULL, this );
	m_button17->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::decNo ), NULL, this );
	m_button16->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::incNo ), NULL, this );
	m_button9->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modOrdem ), NULL, this );
	m_button91->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPtCurva ), NULL, this );
	m_button92->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPeso ), NULL, this );
	//m_textCtrl3->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );
	//m_textCtrl31->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );
	//m_textCtrl32->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );

	return m_panel4;
}


void WidgetFrame::decNo( wxMouseEvent& event )
{
	int id = m_checkList2->GetSelection();
	opengl->setNodeCurve(id,-0.80);
   	event.Skip();
    opengl->update();
}

void WidgetFrame::incNo( wxMouseEvent& event )
{

    int id = m_checkList2->GetSelection();
    opengl->setNodeCurve(id,0.80);
    event.Skip();
    opengl->update();
}

void WidgetFrame::modOrdem( wxMouseEvent& event )
{
	wxString str = m_textCtrl3->GetValue();
	int num =  wxAtoi(str);
	opengl->setOrdCurve(num);
    event.Skip();
    opengl->update();
}

void WidgetFrame::modPtCurva( wxMouseEvent& event )
{
	wxString str = m_textCtrl31->GetValue();
	int num =  wxAtoi(str);
	opengl->setQuantCurv(num);
    event.Skip();
    opengl->update();
}

void WidgetFrame::modPeso( wxMouseEvent& event )
{
	wxString str = m_textCtrl32->GetValue();
	double num;
	if(!str.ToDouble(&num)){ /* error! */ }
	opengl->setPesoCurv( (float) num);
    event.Skip();
    opengl->update();
}

void WidgetFrame::loadInfo()
{
   string name;
   int ordem;
   float peso;
   vector<double> nos;
   wxString val;
   int i;
   Object * world = opengl->getObject();
   // Limpa os Campos
   m_textCtrl3->Clear();
   m_textCtrl31->Clear();
   m_textCtrl32->Clear();
    m_checkList2->Clear();

   name = world->getTipo();

   // if(!render_mode){
       // Preenche os Campos
    if(name == "BSplines" || name == "Nurbs"){

        ordem = world->getOrdCurva();
        nos = world->getNo();

        val = wxString::Format(wxT("%d"), (int) ordem);

        m_textCtrl3->AppendText(val);

        for(i = 0; i < (int) nos.size(); i++){

            val = wxString::Format(wxT("%f"), (double) nos[i]);
            m_checkList2->Append(val);
        }
   }

   // Preenche os Campos
    if(name == "BSplines" || name == "Nurbs" || name == "BezierCurve"){

        ordem = world->getQuant();

        val = wxString::Format(wxT("%d"), (int) ordem);

        m_textCtrl31->AppendText(val);
   }

   // Preenche os Campos
    if(name == "Nurbs"){

        peso = world->getPesoSelec();
        peso = world->getPesoSelec();

        val = wxString::Format(wxT("%f"), (float) peso);

        if(peso != -1){
            m_textCtrl32->AppendText(val);
        }
   }
   opengl->update();
   //}
}

// EVENTOS PARA EDIÇÃO DE UMA CURVA
void WidgetFrame::addPtControle( wxMouseEvent& event )
{

	opengl->addPtC();
    event.Skip();
    opengl->update();
}

void WidgetFrame::rmvPtControle( wxMouseEvent& event )
{

	opengl->rmvPtC();
    event.Skip();
    opengl->update();
}

void WidgetFrame::clickTranslat(wxCommandEvent& event)
{

    opengl->setMod(1);
    opengl->update();
}

void WidgetFrame::clickRotat(wxCommandEvent& event)
{

    opengl->setMod(2);
    opengl->update();
}

void WidgetFrame::clickEscal(wxCommandEvent& event)
{

    opengl->setMod(3);
    opengl->update();
}

void WidgetFrame::clickDesab(wxCommandEvent& event)
{

    opengl->setMod(0);
    opengl->update();
}


void WidgetFrame::clickUndo(wxCommandEvent& event)
{
    cout << "CTR-Z" << endl;
    countItemTree = 0;
    m_treeCtrl->DeleteChildren(root);
    vector<std::string >  objetcsName = opengl->ctrZ();

    for (int i = 0; i < (int)objetcsName.size(); ++i){
        wxString str(objetcsName[i]);
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
    }
}


void WidgetFrame::clickRedo(wxCommandEvent& event)
{
    cout << "CTR-Y" << endl;
    countItemTree = 0;
    m_treeCtrl->DeleteChildren(root);
    vector<std::string >  objetcsName = opengl->ctrY();

    for (int i = 0; i < (int)objetcsName.size(); ++i){
        wxString str(objetcsName[i]);
        m_treeCtrl->AppendItem (root, str, -1, -1, NULL);
        m_treeCtrl->ExpandAll ();
        countItemTree++;
    }
}