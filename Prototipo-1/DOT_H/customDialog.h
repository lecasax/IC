#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <wx/wx.h>

class CustomDialog: public wxDialog {
public:
    CustomDialog(wxWindow* parent, wxWindowID id,
                const wxString& title);
    ~CustomDialog();
    void OnButtonClickOk( wxCommandEvent& event );
    void OnButtonClickCancel( wxCommandEvent& event );
    void OnClose( wxCloseEvent& event );


    wxButton *okButton;
    wxButton *cancelButton;
    //void onCancel(wxCommandEvent& pEvent);
    //void onOk(wxCommandEvent& pEvent);

    //std::string getName()    {
    //    return nameTextCtrl_->GetValue().ToStdString();    }

    std::string getControlPointU();

    std::string getControlPointV();

    std::string getResolutionU();

    std::string getResolutionV();

    std::string getDegree();

private:
    wxTextCtrl* controlPointTextCtrlU;
    wxTextCtrl* controlPointTextCtrlV;
    wxTextCtrl* resolutionTextCtrlU;
    wxTextCtrl* resolutionTextCtrlV;
    wxTextCtrl* degree;

};

#endif /* CUSTOMDIALOG_ */
