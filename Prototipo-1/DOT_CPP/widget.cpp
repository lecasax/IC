#include "widget.h"
#include <wx/string.h>
#include <string>

using namespace std;

/* variavel para controlar o id dos componentes do menu*/
static int idEvent = 1;

WidgetFrame::WidgetFrame(const wxString &title)
			:wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))

{
	
	wxMenuBar *menubar = createMenuBar();
	createToolBar();
	


 	Connect(wxID_ANY , wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(WidgetFrame::acessBasicPlaneEvents));//command for class BasicGLPane


	SetMenuBar(menubar);

	Centre();
}

void WidgetFrame::setBasicPlane(BasicGLPane *glPane)

{	/*set pointer glPane*/
	this->glPane = glPane;
}

void WidgetFrame::acessBasicPlaneEvents(wxCommandEvent&  event)

{

    int id =  event. GetId (); 
    glPane->optionsActions(id);
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

