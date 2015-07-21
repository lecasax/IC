/*

*/
#ifndef CUSTOM_PANEL_H
#define CUSTOM_PANEL_H

#include <wx/statline.h>
#include <wx/string.h>
#include <wx/tglbtn.h>
#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <iostream>

class Transform : public wxScrolledWindow
{

public:

    Transform(wxWindow* parent);
    Transform(wxWindow* parent, wxWindowID id);
    ~Transform();

    void setTranslationLabel(float x, float y, float z);
    void setRotationLabel(float x, float y, float z);
    void setScaleLabel(float x, float y, float z);
    void setCursorLabel(float x, float y, float z);
    void setItemLabel(std::string str);

protected:

    wxBoxSizer *principal;

    //Linhas estaticas
    wxStaticLine *staticLineTansform;
    wxStaticLine *staticLineCursor;
    wxStaticLine *staticLineItem;

    //Botao para esconder o painel
    wxToggleButton *toggleButtonTransform;
    wxToggleButton *toggleButton3dCursor;
    wxToggleButton *toggleButtonItem;

    //Botoes para a Translacao
    wxButton *buttonTranslateX;
    wxButton *buttonTranslateY;
    wxButton *buttonTranslateZ;

    //Botoes para a Rotacao
    wxButton *buttonRotateX;
    wxButton *buttonRotateY;
    wxButton *buttonRotateZ;

    //Botoes para a escala
    wxButton *buttonScaleX;
    wxButton *buttonScaleY;
    wxButton *buttonScaleZ;

    //Botoes para o cursor
    wxButton *buttonCursorX;
    wxButton *buttonCursorY;
    wxButton *buttonCursorZ;

    // textos para os grupos de tranformacoes
    wxStaticText* transformStaticText;
    wxStaticText* translateStaticText;
    wxStaticText* rotateStaticText;
    wxStaticText* scaletaticText;
    wxStaticText* controlPointStaticText;
    wxStaticText* cursor3dStaticText;
    wxStaticText* pointCursor3dStaticText;
    wxStaticText* itemStaticText;
    wxTextCtrl * itemTextCtrl;

    // painel pai dos botoes
    wxPanel * panelTransform;
    wxPanel * panel3dCursor;
    wxPanel * panelItem;

    virtual void OnButtonClickTransform( wxCommandEvent& event );
    virtual void OnButtonClick3dCursor( wxCommandEvent& event );
    virtual void OnButtonItem( wxCommandEvent& event );

    void paintEventObjectMode(wxPaintEvent & evt);
    void paintEventEditMode(wxPaintEvent & evt);
    void renderObjectMode(wxDC& dc);
    void renderEditMode(wxDC& dc);
    void doLayoutObjectMode();
    void doLayoutHideItems();
    void doLayoutEditMode();

};

#endif  /* CUSTOM_PANEL_H */
