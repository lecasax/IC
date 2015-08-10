/*
Julho de 2015
*/


#ifndef CUSTOM_TREE_CTRL_H
#define CUSTOM_TREE_CTRL_H
#include <wx/treectrl.h>
#include <wx/wx.h>

class CustomTreeCtrl: public wxTreeCtrl

{

public:

    CustomTreeCtrl(wxWindow* parent);
    ~CustomTreeCtrl();

protected:

    void OnLeftButtonClick( wxMouseEvent& event );
};

#endif  /* CUSTOM_TREE_CTRL_H */
