#include "customDialog.h"
CustomDialog::CustomDialog(wxWindow* parent,
        wxWindowID id,
        const wxString& title)
    : wxDialog(parent, id, title,
            wxDefaultPosition, wxSize(300, 280))    {

  // Setup the Panel and Widgets.
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(150, 150, 150));

    cancelButton = new wxButton(panel, wxID_ANY, "Cancel");
    okButton = new wxButton(panel, wxID_ANY, "Ok");

    controlPointTextCtrlU = new wxTextCtrl(panel, wxID_ANY);
    controlPointTextCtrlV = new wxTextCtrl(panel, wxID_ANY);
    resolutionTextCtrlU  = new wxTextCtrl(panel, wxID_ANY);
    resolutionTextCtrlV  = new wxTextCtrl(panel, wxID_ANY);
    degree = new wxTextCtrl(panel, wxID_ANY);

    wxFont font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD, false);

    // Put the widgets in a sizer.
    wxBoxSizer *sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer7 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *st1 = new wxStaticText(panel, wxID_ANY, "Control Point U: " );
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY, "Control Point V: " );
    wxStaticText *st3 = new wxStaticText(panel, wxID_ANY, "Resolution U:     " );
    wxStaticText *st4 = new wxStaticText(panel, wxID_ANY, "Resolution V:     " );
    wxStaticText *st5 = new wxStaticText(panel, wxID_ANY, "degree:             " );

    st1->SetFont(font);
    st2->SetFont(font);
    st3->SetFont(font);
    st4->SetFont(font);
    st5->SetFont(font);

    sizer2->Add(st1, 0, wxALL, 5);
    sizer2->Add(controlPointTextCtrlU, 0,wxALL, 5);

    sizer3->Add(st2, 0, wxALL, 5);
    sizer3->Add(controlPointTextCtrlV, 0,wxALL, 5);


    sizer4->Add(st3, 0, wxALL, 5);
    sizer4->Add(resolutionTextCtrlU, 0,wxALL, 5);

    sizer5->Add(st4, 0, wxALL, 5);
    sizer5->Add(resolutionTextCtrlV, 0,wxALL, 5);

    sizer6->Add(st5, 0, wxALL, 5);
    sizer6->Add(degree, 0,wxALL, 5);

    sizer7->Add(okButton, 0, wxALL , 0);
    sizer7->Add(cancelButton, 0, wxALL | 0);

    sizer1->Add(sizer2, 0, wxALL, 5);
    sizer1->Add(sizer3, 0, wxALL, 5);
    sizer1->Add(sizer4, 0, wxALL, 5);
    sizer1->Add(sizer5, 0, wxALL, 5);
    sizer1->Add(sizer6, 0, wxALL, 5);
    sizer1->Add(sizer7, 0, wxALL | wxALIGN_RIGHT | wxALIGN_BOTTOM, 0);
    panel->SetSizer(sizer1);

    okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog::OnButtonClickOk ), NULL, this );
    cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog::OnButtonClickCancel ), NULL, this );
    this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CustomDialog::OnClose ), NULL, this );
    Center();
}

CustomDialog::~CustomDialog() {
    okButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog::OnButtonClickOk ), NULL, this );
    cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CustomDialog::OnButtonClickCancel ), NULL, this );
   this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CustomDialog::OnClose ), NULL, this );

}

void CustomDialog::OnButtonClickOk( wxCommandEvent& event)
{
    EndModal(wxID_OK);
    Destroy();
}
void CustomDialog::OnButtonClickCancel( wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
    Destroy();
}


void CustomDialog::OnClose( wxCloseEvent& event )
{
     Destroy();
}

std::string CustomDialog::getControlPointU()
{

    return controlPointTextCtrlU->GetValue().ToStdString();
}

std::string CustomDialog::getControlPointV()
{

    return controlPointTextCtrlV->GetValue().ToStdString();
}

std::string CustomDialog::getResolutionU()
{

    return resolutionTextCtrlU->GetValue().ToStdString();
}

std::string CustomDialog::getResolutionV()
{
    return resolutionTextCtrlV->GetValue().ToStdString();
}

std::string CustomDialog::getDegree()
{
    return degree->GetValue().ToStdString();
}