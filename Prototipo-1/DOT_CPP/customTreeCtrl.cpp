#include "customTreeCtrl.h"

CustomTreeCtrl::CustomTreeCtrl(wxWindow* parent):wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition,
                                wxSize(200, 200), wxTR_DEFAULT_STYLE|wxTR_ROW_LINES|wxTR_MULTIPLE)
{
    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CustomTreeCtrl::OnLeftButtonClick ) );
}
CustomTreeCtrl::~CustomTreeCtrl()
{
    this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CustomTreeCtrl::OnLeftButtonClick ) );
}

void CustomTreeCtrl::OnLeftButtonClick( wxMouseEvent& event )
{
    GetParent()->GetEventHandler()->ProcessEvent(event);
}