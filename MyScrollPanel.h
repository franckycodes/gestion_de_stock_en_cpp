#pragma once

#include <wx/wx.h>
#include <wx/gbsizer.h>

class MyScrollPanel: public wxScrolledWindow
{

public:
    MyScrollPanel(wxWindow* parent, wxWindowID id) ;
private:
    wxGridBagSizer *m_gbs;
};
