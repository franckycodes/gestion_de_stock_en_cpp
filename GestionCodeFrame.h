#pragma once
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include "MyScrollPanel.h"
class GestionCodeFrame: public wxFrame
{
public:
    GestionCodeFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~GestionCodeFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnAddProject(wxCommandEvent& event);

    wxGridBagSizer *m_gbs;
   
    //gestion stock forms
    wxTextCtrl *m_referenceNumberTxt;
    wxTextCtrl *m_articleNameTxt;
    wxTextCtrl *m_articlePriceTxt;
    wxTextCtrl *m_totalStockTxt;
    wxTextCtrl *m_descriptionTxt;

    //labels
    wxStaticText *m_referenceNumberLbl;
    wxStaticText *m_articleNameLbl;
    wxStaticText *m_articlePriceLbl;
    wxStaticText *m_totalStockLbl;
    wxStaticText *m_descriptionLbl;

    wxButton *m_saveBt;
    wxStaticText *m_resultLbl;
    MyScrollPanel *m_projectsListPanel;
    wxDECLARE_EVENT_TABLE();
};
