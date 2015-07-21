#include "customPanel.h"

Transform::Transform(wxWindow* parent): wxScrolledWindow(parent, wxID_ANY)
{

    //Criando todos os componentes
    toggleButtonTransform = new wxToggleButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(13, 13), wxBU_NOTEXT);
    panelTransform = new wxPanel(  this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    this->SetBackgroundColour(wxColour(150, 150, 150));
    panelTransform->SetBackgroundColour(wxColour(150, 150, 150));
    //Cria os botoes de translacao...
    buttonTranslateX = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransX"), wxDefaultPosition, wxSize(150, 20), 0 );
    buttonTranslateY = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransY"), wxDefaultPosition, wxSize(150, 20), 0 );
    buttonTranslateZ = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransZ"), wxDefaultPosition, wxSize(150, 20), 0 );
    transformStaticText = new wxStaticText( this, wxID_ANY, wxT("Transform               "), wxDefaultPosition, wxDefaultSize, 0 );
    controlPointStaticText = new wxStaticText( panelTransform, wxID_ANY, wxT("Control Point:"), wxDefaultPosition, wxDefaultSize, 0 );
    toggleButtonTransform->Connect( wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonClickTransform ), NULL, this );
    Connect(wxEVT_PAINT, wxPaintEventHandler(Transform::paintEventEditMode));

}

Transform::Transform(wxWindow* parent, wxWindowID id): wxScrolledWindow(parent, id)

{
    //Criando todos os componentes
    toggleButtonTransform = new wxToggleButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(13, 13), wxBU_NOTEXT);
    toggleButton3dCursor = new wxToggleButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(13, 13), wxBU_NOTEXT);
    toggleButtonItem = new wxToggleButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(13, 13), wxBU_NOTEXT);
    panelTransform = new wxPanel(  this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    panel3dCursor = new wxPanel(  this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    panelItem = new wxPanel(  this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

    this->SetBackgroundColour(wxColour(150, 150, 150));
    panelTransform->SetBackgroundColour(wxColour(150, 150, 150));
    panel3dCursor->SetBackgroundColour(wxColour(150, 150, 150));
    panelItem->SetBackgroundColour(wxColour(150, 150, 150));

    //Cria os botoes de translacao...
    buttonTranslateX = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransX"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonTranslateY = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransY"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonTranslateZ = new wxButton( panelTransform, wxID_ANY, wxT("ButtonTransZ"), wxDefaultPosition, wxSize(150, 25), 0 );

    buttonTranslateX->SetBackgroundColour(wxColour(150, 150, 150));
    //panelTransform->SetBorder(45);

    buttonRotateX = new wxButton( panelTransform, wxID_ANY, wxT("ButtonRatateX"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonRotateY = new wxButton( panelTransform, wxID_ANY, wxT("ButtonRotateY"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonRotateZ = new wxButton( panelTransform, wxID_ANY, wxT("ButtonRotateZ"), wxDefaultPosition, wxSize(150, 25), 0 );

    buttonScaleX = new wxButton( panelTransform, wxID_ANY, wxT("ButtonScaleX"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonScaleY = new wxButton( panelTransform, wxID_ANY, wxT("ButtonScaleY"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonScaleZ = new wxButton( panelTransform, wxID_ANY, wxT("ButtonScaleZ"), wxDefaultPosition, wxSize(150, 25), 0 );

    buttonCursorX = new wxButton( panel3dCursor, wxID_ANY, wxT("CursorX"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonCursorY = new wxButton( panel3dCursor, wxID_ANY, wxT("CursorY"), wxDefaultPosition, wxSize(150, 25), 0 );
    buttonCursorZ = new wxButton( panel3dCursor, wxID_ANY, wxT("CursorZ"), wxDefaultPosition, wxSize(150, 25), 0 );

    transformStaticText = new wxStaticText( this, wxID_ANY, wxT("Transform               "), wxDefaultPosition, wxDefaultSize, 0 );
    cursor3dStaticText = new wxStaticText( this, wxID_ANY, wxT("3D Cursor"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText = new wxStaticText( this, wxID_ANY, wxT("Item"), wxDefaultPosition, wxDefaultSize, 0 );
    translateStaticText = new wxStaticText( panelTransform, wxID_ANY, wxT("Translation:"), wxDefaultPosition, wxDefaultSize, 0 );
    rotateStaticText = new wxStaticText( panelTransform, wxID_ANY, wxT("Rotation:"), wxDefaultPosition, wxDefaultSize, 0 );
    scaletaticText = new wxStaticText( panelTransform, wxID_ANY, wxT("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
    pointCursor3dStaticText = new wxStaticText( panel3dCursor, wxID_ANY, wxT("Point:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemTextCtrl = new wxTextCtrl( panelItem, wxID_ANY, wxString("Surface Nurbs"), wxDefaultPosition, wxSize(150, 25), 0 );

    staticLineTansform = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize(200, 10), wxLI_HORIZONTAL );
    staticLineCursor = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize(200, 10), wxLI_HORIZONTAL );
    staticLineItem = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize(200, 10), wxLI_HORIZONTAL );

    toggleButtonTransform->Connect( wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonClickTransform ), NULL, this );
    toggleButton3dCursor->Connect( wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonClick3dCursor ), NULL, this );
    toggleButtonItem->Connect(wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonItem), NULL, this);
    doLayoutObjectMode();

}
Transform::~Transform()
{
    toggleButtonItem->Disconnect(wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonItem), NULL, this);
    toggleButtonTransform->Disconnect( wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonClickTransform ), NULL, this );
    toggleButton3dCursor->Disconnect( wxEVT_TOGGLEBUTTON, wxCommandEventHandler( Transform::OnButtonClick3dCursor ), NULL, this );

}
void Transform::doLayoutObjectMode()
{
     //Criacao dos sizers
    principal =  new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *transformSizer =  new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *cursorSizer =  new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *itemSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonTransformSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *button3dCursorSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *textItemSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *lineTransformSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lineCursor = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lineItem = new wxBoxSizer(wxHORIZONTAL);

    //faz o layout
    transformSizer->Add( toggleButtonTransform, 0, wxALL, 5 );
    transformSizer->Add( transformStaticText, 0, wxALL, 5 );

    cursorSizer->Add(toggleButton3dCursor, 0, wxALL, 5);
    cursorSizer->Add( cursor3dStaticText, 0, wxALL, 5 );

    itemSizer->Add(toggleButtonItem, 0, wxALL, 5);
    itemSizer->Add(itemStaticText, 0, wxALL, 5);

    lineTransformSizer->Add(staticLineTansform, 0, wxALL, 0 );
    lineCursor->Add(staticLineCursor, 0, wxALL, 0 );
    lineItem->Add(staticLineItem, 0, wxALL, 0 );

    //---Tudo do transform------------------------------------------------------
    buttonTransformSizer->Add(translateStaticText, 0, wxALL, 5);
    buttonTransformSizer->Add(buttonTranslateX, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonTranslateY, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonTranslateZ, 0, wxALL, -2);

    buttonTransformSizer->AddSpacer  (10);

    buttonTransformSizer->Add(rotateStaticText, 0, wxALL, 5);
    buttonTransformSizer->Add(buttonRotateX, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonRotateY, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonRotateZ, 0, wxALL, -2);

    buttonTransformSizer->AddSpacer  (10);

    buttonTransformSizer->Add(scaletaticText, 0, wxALL, 5);
    buttonTransformSizer->Add(buttonScaleX, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonScaleY, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonScaleZ, 0, wxALL, -2);

    panelTransform->SetSizer(buttonTransformSizer);
    panelTransform->Layout();
    buttonTransformSizer->Fit(panelTransform);

    //------------Cursor-------------------------------------------------------//

    button3dCursorSizer->Add(pointCursor3dStaticText, 0, wxALL, 5);
    button3dCursorSizer->Add(buttonCursorX, 0, wxALL, -2);
    button3dCursorSizer->Add(buttonCursorY, 0, wxALL, -2);
    button3dCursorSizer->Add(buttonCursorZ, 0, wxALL, -2);

    panel3dCursor->SetSizer(button3dCursorSizer);
    panel3dCursor->Layout();
    button3dCursorSizer->Fit(panel3dCursor);

    //----------Item------------------------------------------------------//

    textItemSizer->Add( itemTextCtrl, 0, wxALL, -2 );
    panelItem->SetSizer(textItemSizer);
    panelItem->Layout();
    textItemSizer->Fit(panelItem);

    principal->Add(transformSizer, 0, wxALL, 5);
    principal->Add(panelTransform, 0, wxALL, 5);
    principal->Add(lineTransformSizer, 0, wxALL, 5);
    principal->Add(cursorSizer, 0, wxALL, 5);
    principal->Add(panel3dCursor, 0, wxALL, 5);
    principal->Add(lineCursor, 0, wxALL, 5);
    principal->Add(itemSizer, 0, wxALL, 5);
    principal->Add(panelItem, 0, wxALL, 5);
    principal->Add(lineItem, 0, wxALL, 5);

    this->SetSizer(principal);
    this->Layout();
    principal->Fit(this);
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
}

void Transform::doLayoutEditMode()
{
    wxBoxSizer *principal =  new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *transformSizer =  new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonTransformSizer = new wxBoxSizer(wxVERTICAL);

    //faz o layout
    transformSizer->Add( toggleButtonTransform, 0, wxALL, 5 );
    transformSizer->Add( transformStaticText, 0, wxALL, 5 );

    transformSizer->AddSpacer  (2);

    buttonTransformSizer->Add( controlPointStaticText , 0, wxALL, 5);
    buttonTransformSizer->Add(buttonTranslateX, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonTranslateY, 0, wxALL, -2);
    buttonTransformSizer->Add(buttonTranslateZ, 0, wxALL, -2);

    panelTransform->SetSizer(buttonTransformSizer);
    panelTransform->Layout();
    buttonTransformSizer->Fit(panelTransform);

    principal->Add(transformSizer, 0, wxALL, 5);
    principal->Add(panelTransform, 0, wxALL, 5);

    this->SetSizer(principal);
    this->Layout();
    principal->Fit(this);
}

void Transform::doLayoutHideItems()
{
    wxBoxSizer *principal =  new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *transformSizer =  new wxBoxSizer(wxHORIZONTAL);
    transformSizer->Add( toggleButtonTransform, 0, wxALL, 5 );
    transformSizer->Add( transformStaticText, 0, wxALL, 5 );
    principal->Add(transformSizer, 0, wxALL, 5);
    this->SetSizer(principal);
    this->Layout();
    principal->Fit(this);
}

void Transform::OnButtonClickTransform( wxCommandEvent& event )
{
    toggleButtonTransform->GetValue() == true ?  panelTransform->Hide() : panelTransform->Show();

    /*setTranslationLabel(12, 3, 4);
    setRotationLabel(45, 39, 23);
    setScaleLabel(33, 2, 4);
    setCursorLabel(3, 4, 5);
    setItemLabel(std::string("Curve BSplines"));
    */
    principal->Layout();
    //this->Update();
}

void Transform::OnButtonClick3dCursor( wxCommandEvent& event )
{
    toggleButton3dCursor->GetValue() == true ?  panel3dCursor->Hide() : panel3dCursor->Show();
    principal->Layout();
}
void Transform::OnButtonItem( wxCommandEvent& event )
{
    toggleButtonItem->GetValue() == true ?  panelItem->Hide() : panelItem->Show();
    principal->Layout();
}

void Transform::paintEventObjectMode(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    //renderObjectMode(dc);
}
void Transform::renderObjectMode(wxDC&  dc)
{
    //
}

void Transform::paintEventEditMode(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    //renderEditMode(dc);
}

void Transform::renderEditMode(wxDC&  dc)
{
    //
}

void Transform::setTranslationLabel(float x, float y, float z)
{
    buttonTranslateX->SetLabel(wxString::Format(wxT("X: %5f"), x));
    buttonTranslateY->SetLabel(wxString::Format(wxT("Y: %5f"), y));
    buttonTranslateZ->SetLabel(wxString::Format(wxT("Z: %5f"), z));
}

void Transform::setRotationLabel(float x, float y, float z)
{
    buttonRotateX->SetLabel(wxString::Format(wxT("X: %5f"), x));
    buttonRotateY->SetLabel(wxString::Format(wxT("Y: %5f"), y));
    buttonRotateZ->SetLabel(wxString::Format(wxT("Z: %5f"), z));

}

void Transform::setScaleLabel(float x, float y, float z)
{
    buttonScaleX->SetLabel(wxString::Format(wxT("X: %5f"), x));
    buttonScaleY->SetLabel(wxString::Format(wxT("Y: %5f"), y));
    buttonScaleZ->SetLabel(wxString::Format(wxT("Z: %5f"), z));
}

void Transform::setCursorLabel(float x, float y, float z)
{
    buttonCursorX->SetLabel(wxString::Format(wxT("X: %5f"), x));
    buttonCursorY->SetLabel(wxString::Format(wxT("Y: %5f"), y));
    buttonCursorZ->SetLabel(wxString::Format(wxT("Z: %5f"), z));
}
void Transform::setItemLabel(std::string str)
{
    wxString s(str);
    itemTextCtrl->ChangeValue(str);
}
