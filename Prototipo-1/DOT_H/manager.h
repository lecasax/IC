
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "render.h"

using namespace std;

class BasicGLPane : public wxGLCanvas
{

private:
	wxFrame* frame;
    wxGLContext*	m_context;

public:

	//construtor e destrutors
	BasicGLPane(wxFrame* parent, int* args);
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

	void setNodeCurve(int idNode,double inc);
	void setOrdCurve(int ord);
	void setQuantCurv(int quant);
	void setPesoCurv(float val);

	//events menubar
	void OnQuit(wxCommandEvent& event);

	//events display
	void displayScene();


	// Atributos para a FRAME
    /* Componentes de Edição de Curva */
	wxPanel* m_panel4;
	wxButton* m_button74;
	wxButton* m_button75;
	wxButton* m_button76;
	wxStaticText* m_staticText6;
	//wxCheckListBox* m_checkList2;
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


	void loadInfo();

	void addPtControle( wxMouseEvent& event );
	void rmvPtControle( wxMouseEvent& event );
	void move( wxMouseEvent& event );
	void key( wxKeyEvent& event ) { event.Skip(); }

 	//macro for table of the events
	DECLARE_EVENT_TABLE()
};

