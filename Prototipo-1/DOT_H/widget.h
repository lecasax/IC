#include <wx/wx.h>
#include <wx/menu.h>
#include <vector>
#include <string>
#include "manager.h"

class WidgetFrame : public wxFrame 
{

public:


	WidgetFrame (const wxString &title);
	
	wxToolBar *  createToolBar();
	wxMenuBar *  createMenuBar();
	void setBasicPlane(BasicGLPane *glPane);

	/*funcao para receber um evento de menu acessar metodos publicos de BasciPlane*/
	void acessBasicPlaneEvents(wxCommandEvent&  event);

private:
	
	/*objeto para acessar as funcoes publicas de BasicPlane */
	BasicGLPane *glPane;

};
