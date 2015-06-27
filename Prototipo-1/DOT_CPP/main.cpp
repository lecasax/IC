#include "main.h"
#include "widget.h"


IMPLEMENT_APP(MyApp)
 
 
bool MyApp::OnInit()
{

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    WidgetFrame *frame = new  WidgetFrame(wxT("3D-STUDIO-FORMS"));
 
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
 
    BasicGLPane *glPane = new BasicGLPane( (wxFrame*) frame, args);

    /*sem isso os eventos de teclado nao funcionam*/
    glPane->SetFocus ();
    
    /* passa o glPane para a frame, a frame pode trasmitir os eventos para BasicGLPane*/
    frame->setBasicPlane(glPane);

    sizer->Add(glPane, 1, wxEXPAND);
 
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    
    frame->Show();
    return true;
} 
 

