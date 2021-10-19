#include "MyScrollPanel.h"
#include <iostream>
#include <wx/wx.h>



MyScrollPanel::MyScrollPanel(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
    {
        // the sizer will take care of determining the needed scroll size
        // (if you don't use sizers you will need to manually set the viewport size)
        //wxGridBagSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_gbs=new wxGridBagSizer();
        this->SetSizer(m_gbs);
        this->SetMinClientSize(wxSize(400,150));

        // add a series of widgets
        //for (int w=1; w<=120; w++)
        //{
          //  wxButton* b = new wxButton(this, wxID_ANY, wxString::Format(wxT("Button %i"), w));
           // sizer->Add(b, 0, wxALL, 3);
        //}

        //this->SetSizer(sizer);

        // this part makes the scrollbars show up
        //this->FitInside(); // ask the sizer about the needed size
        this->SetScrollRate(5, 5);
    }
