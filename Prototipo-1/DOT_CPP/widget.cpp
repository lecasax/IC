#include "widget.h"
#include <wx/string.h>
#include <string>

using namespace std;

/* variavel para controlar o id dos componentes do menu*/
static int idEvent = 1;

WidgetFrame::WidgetFrame(const wxString &title)
            :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{

    m_mgr.SetManagedWindow(this);
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    opengl = new BasicGLPane( this, args);
    //glPane->SetFocus ();


    //sem isso os eventos de teclado nao funcionam


    m_treeCtrl = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxTR_DEFAULT_STYLE|wxTR_ROW_LINES );
    wxTreeItemId root = m_treeCtrl->AddRoot(wxString("Objects"), -1, -1,NULL);
    m_treeCtrl->AppendItem (root, wxString ("Filho-1"), -1, -1, NULL);
    m_treeCtrl->AppendItem (root, wxString ("Filho-2"), -1, -1, NULL);
    m_treeCtrl->AppendItem (root, wxString ("Filho-3"), -1, -1, NULL);

    //isso serve para passar as info para o panel
    wxAuiPaneInfo info = wxAuiPaneInfo ();
    info.CloseButton (false);
    info.Left();
    m_mgr.AddPane(m_treeCtrl, info);
    info.Right();
    // Edição das Curvas está em m_panel4
    opengl->m_panel4 = this->createEditBarCurve();
    m_mgr.AddPane( opengl->m_panel4, info);
    info.Bottom();
   // m_mgr.AddPane(text4, info);
    info.Center();
    m_mgr.AddPane(opengl, info);

    m_menubar1 = new wxMenuBar( 0 );
    m_menu1 = new wxMenu();
    m_menu11 = new wxMenu();

    wxMenuItem* m_menu11Item = new wxMenuItem( m_menu1, wxID_ANY, wxT("MyMenu"), wxEmptyString, wxITEM_NORMAL, m_menu11 );
    m_menu1->Append( m_menu11Item );

    m_menubar1->Append( m_menu1, wxT("MyMenu") );

    m_menu2 = new wxMenu();
    m_menubar1->Append( m_menu2, wxT("MyMenu") );

    m_menu3 = new wxMenu();
    m_menubar1->Append( m_menu3, wxT("MyMenu") );

    m_mgr.Update();

    this->SetMenuBar( m_menubar1 );

    SetMenuBar(createMenuBar());
    createToolBar();

    this->Centre();
    //Connect(wxID_ANY , wxEVT_COMMAND_MENU_SELECTED,
    //wxCommandEventHandler(WidgetFrame::acessBasicPlaneEvents));//command for class BasicGLPane
}

WidgetFrame::~WidgetFrame()
{
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

wxMenuBar * WidgetFrame::createMenuBar()
{
    /*variaveis auxliares*/
    int k = 0;
    int sizeMenuBar = 2;

    /* menubar e menu*/
    string vecMenu[]    = {"Save",  "Save as", "Projetcion 2D", "Projetcion 3D "};
    string vecMenuBar[] = {"File",  "Projetcion"};

    /*vector para adicionar os menus no menubar*/
    vector <wxMenu * > arrayMenu;
    wxMenuBar *menubar = new wxMenuBar;


    //create a  complete menu
    for (int i = 0; i < 2; i++) {

        wxMenu *m = new wxMenu;

        for (int j = 0; j < 2; j++) {

            /*conversao de string para o formato da wxWidget*/
            wxString mystring(vecMenu[k++].c_str(), wxConvUTF8);
            m->Append(idEvent++, mystring);
        }

        arrayMenu.push_back(m);
    }

    /*adiciona os menus no menubar*/
    for (int i = 0; i < sizeMenuBar; i++ ){


        /*conversao de string para o formato da wxWidget*/
        wxString mystring(vecMenuBar[i].c_str(), wxConvUTF8);
        menubar->Append(arrayMenu[i], mystring);
    }


    return menubar;

}

wxToolBar * WidgetFrame::createToolBar()
{
    vector <string > arrayStringNames;
    //string s1 = ("ICONS/pencil.png");
    //string s2 = ("ICONS/exit.png");


    wxImage::AddHandler( new wxPNGHandler );

    wxBitmap curve(wxT("ICONS/pencil.png"), wxBITMAP_TYPE_PNG);
    wxBitmap exit(wxT("ICONS/exit.png"), wxBITMAP_TYPE_PNG);
    wxBitmap surface(wxT("ICONS/surface.png"), wxBITMAP_TYPE_PNG);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(idEvent++, curve, wxT("Curve Bezier"));
    toolbar->AddTool(idEvent++, surface, wxT("Surface Bezier"));
    toolbar->AddTool(idEvent++, exit, wxT("I will...."));
    toolbar->Realize();

    return toolbar;

}

wxPanel * WidgetFrame::createEditBarCurve()
{
	//wxGridBagSizer* gbSizer1;
	//gbSizer1 = new wxGridBagSizer( 0, 0 );
	//gbSizer1->SetFlexibleDirection( wxBOTH );
	//gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	//wxBoxSizer* bSizer2;
	//bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	opengl->m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	opengl->m_button74 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Adicionar Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( opengl->m_button74, 0, wxALL, 5 );
	
	opengl->m_button75 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Remover Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( opengl->m_button75, 0, wxALL, 5 );
	
	opengl->m_button76 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Mover"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( opengl->m_button76, 0, wxALL, 5 );
	
	opengl->m_staticText6 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Lista de Nós"), wxDefaultPosition, wxDefaultSize, 0 );
	opengl->m_staticText6->Wrap( -1 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	wxArrayString m_checkList2Choices;
	opengl->m_checkList2 = new wxListBox( opengl->m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, NULL, 0 );
	opengl->m_checkList2 ->SetMinSize( wxSize( 100,180 ) );

	bSizer10->Add( opengl->m_checkList2, 0, wxALL, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	opengl->m_button16 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Incrementar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( opengl->m_button16, 0, wxALL, 5 );
	
	opengl->m_button17 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Decrementar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( opengl->m_button17, 0, wxALL, 5 );
	
	//opengl->m_staticText52 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Valor do Incremento"), wxDefaultPosition, wxDefaultSize, 0 );
	//opengl->m_staticText52->Wrap( -1 );
	//bSizer14->Add( opengl->m_staticText52, 0, wxALL, 5 );
	
	//opengl->m_textCtrl4 = new wxTextCtrl( opengl->m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	//bSizer14->Add( opengl->m_textCtrl4, 0, wxALL, 5 );
	
	bSizer10->Add( bSizer14, 1, wxEXPAND, 5 );
	
	
	opengl->m_staticText8 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Ordem da Curva"), wxDefaultPosition, wxDefaultSize, 0 );
	opengl->m_staticText8->Wrap( -1 );
	bSizer8->Add( opengl->m_staticText8, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );
	
	opengl->m_textCtrl3 = new wxTextCtrl( opengl->m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( opengl->m_textCtrl3, 0, wxALL, 5 );
	
	opengl->m_button9 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( opengl->m_button9, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer61, 0, wxEXPAND, 5 );
	
	opengl->m_staticText51 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Quantidade de Pontos da Curva"), wxDefaultPosition, wxDefaultSize, 0 );
	opengl->m_staticText51->Wrap( -1 );
	bSizer8->Add( opengl->m_staticText51, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxHORIZONTAL );
	
	opengl->m_textCtrl31 = new wxTextCtrl( opengl->m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( opengl->m_textCtrl31, 0, wxALL, 5 );
	
	opengl->m_button91 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( opengl->m_button91, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer611, 0, wxEXPAND, 5 );
	
	opengl->m_staticText5 = new wxStaticText( opengl->m_panel4, wxID_ANY, wxT("Peso do Ponto de Controle"), wxDefaultPosition, wxDefaultSize, 0 );
	opengl->m_staticText5->Wrap( -1 );
	bSizer8->Add( opengl->m_staticText5, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer612;
	bSizer612 = new wxBoxSizer( wxHORIZONTAL );
	
	opengl->m_textCtrl32 = new wxTextCtrl( opengl->m_panel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer612->Add( opengl->m_textCtrl32, 0, wxALL, 5 );
	
	opengl->m_button92 = new wxButton( opengl->m_panel4, wxID_ANY, wxT("Modificar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer612->Add( opengl->m_button92, 0, wxALL, 5 );

	bSizer8->Add( bSizer612, 0, wxEXPAND, 5 );



	// Lista de Nos por Ultimo
	bSizer8->Add( opengl->m_staticText6, 0, wxALL, 5 );
	bSizer8->Add( bSizer10, 1, wxEXPAND, 5 );

	opengl->m_panel4->SetSizer( bSizer8 );
	opengl->m_panel4->Layout();
	bSizer8->Fit( opengl->m_panel4 );

	opengl->m_button74->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BasicGLPane::addPtControle ), NULL, this );
	opengl->m_button75->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BasicGLPane::rmvPtControle ), NULL, this );
	opengl->m_button76->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BasicGLPane::move ), NULL, this );
	opengl->m_checkList2->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::getNoSelect ), NULL, this );
	opengl->m_button17->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::decNo ), NULL, this );
	opengl->m_button16->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::incNo ), NULL, this );
	opengl->m_button9->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modOrdem ), NULL, this );
	opengl->m_button91->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPtCurva ), NULL, this );
	opengl->m_button92->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( WidgetFrame::modPeso ), NULL, this );
	opengl->m_textCtrl3->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );
	opengl->m_textCtrl31->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );
	opengl->m_textCtrl32->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( BasicGLPane::key ), NULL, this );

	return opengl->m_panel4;
}

void WidgetFrame::getNoSelect( wxMouseEvent& event )
{    

	//opengl->displayScene();
    event.Skip(); 
}

void WidgetFrame::decNo( wxMouseEvent& event )
{
	int id = opengl->m_checkList2->GetSelection();
	opengl->setNodeCurve(id,-0.80);	
   	event.Skip(); 
}

void WidgetFrame::incNo( wxMouseEvent& event )
{ 	

    int id = opengl->m_checkList2->GetSelection();
    opengl->setNodeCurve(id,0.80);
    event.Skip(); 
}

void WidgetFrame::modOrdem( wxMouseEvent& event )
{ 	
	wxString str = opengl->m_textCtrl3->GetValue();
	int num =  wxAtoi(str);
	opengl->setOrdCurve(num);
    event.Skip(); 
}

void WidgetFrame::modPtCurva( wxMouseEvent& event )
{ 
	wxString str = opengl->m_textCtrl31->GetValue();
	int num =  wxAtoi(str);
	opengl->setQuantCurv(num);
    event.Skip();  
}

void WidgetFrame::modPeso( wxMouseEvent& event )
{ 
	wxString str = opengl->m_textCtrl32->GetValue();
	double num;
	if(!str.ToDouble(&num)){ /* error! */ }	
	opengl->setPesoCurv( (float) num);
    event.Skip(); 
}