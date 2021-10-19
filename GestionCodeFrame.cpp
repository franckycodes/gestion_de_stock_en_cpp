#include "GestionCodeFrame.h"
#include "MyAppMain.h"
#include <string>
#include <vector>
#include "Db.h"
#include "conversiontools.h"
#include "strtools.h"

#include "translateplugins.h"
#include "MyScrollPanel.h"
#include "Projects.h"
#include "ArticlesStock.h"
using namespace std;

enum
{

    ID_Hello=1
};

wxBEGIN_EVENT_TABLE(GestionCodeFrame, wxFrame)
    EVT_MENU(ID_Hello, GestionCodeFrame::OnHello)
    EVT_MENU(wxID_EXIT, GestionCodeFrame::OnExit)
    EVT_MENU(wxID_ABOUT,GestionCodeFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyAppMain);

GestionCodeFrame::GestionCodeFrame(const wxString& title, const wxPoint& pos, const wxSize& size):
 wxFrame(NULL, wxID_ANY, title, pos, size)
    {

    this->SetTitle("Gestion de Stock");
    m_gbs=new wxGridBagSizer();

    // m_projectNameLbl=new wxStaticText(this, wxID_ANY, "Le nom de votre logiciel");
    // m_projectNameTxt=new wxTextCtrl(this, wxID_ANY, "");
    // m_languageUsedLbl=new wxStaticText(this, wxID_ANY, "Langage utilise: exemple C++");
    // m_languageUsedTxt=new wxTextCtrl(this, wxID_ANY, "");
    m_saveBt=new wxButton(this, wxID_ANY, "enregistrer");
    m_resultLbl=new wxStaticText(this, wxID_ANY, "");

    //gestion stock forms 
    m_referenceNumberTxt=new wxTextCtrl(this, wxID_ANY, "");
    m_articleNameTxt=new wxTextCtrl(this, wxID_ANY, "");
    m_articlePriceTxt=new wxTextCtrl(this, wxID_ANY, "");
    m_totalStockTxt=new wxTextCtrl(this, wxID_ANY, "");
    m_descriptionTxt=new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    //labels
    m_referenceNumberLbl=new wxStaticText(this, wxID_ANY, "Numéro de référence");
    m_articleNameLbl=new wxStaticText(this, wxID_ANY, "Nom de l'article");
    m_articlePriceLbl=new wxStaticText(this, wxID_ANY, "Prix de l'article");
    m_totalStockLbl=new wxStaticText(this, wxID_ANY, "Total en stock");
    m_descriptionLbl=new wxStaticText(this, wxID_ANY, "Description de l'article");

    //positioning
 
    m_gbs->Add(m_referenceNumberLbl, wxGBPosition(10,20));
    m_gbs->Add(m_referenceNumberTxt, wxGBPosition(11,20));
    m_gbs->Add(m_articleNameLbl, wxGBPosition(12,20));
    m_gbs->Add(m_articleNameTxt, wxGBPosition(13, 20));
    //description 
    m_gbs->Add(m_descriptionLbl, wxGBPosition(14,20));
    m_gbs->Add(m_descriptionTxt, wxGBPosition(15, 20));

    m_gbs->Add(m_articlePriceLbl, wxGBPosition(16,20));
    m_gbs->Add(m_articlePriceTxt, wxGBPosition(17, 20));
    m_gbs->Add(m_totalStockLbl, wxGBPosition(18,20));
    m_gbs->Add(m_totalStockTxt, wxGBPosition(19, 20));

    m_gbs->Add(m_saveBt, wxGBPosition(20, 20));
    m_gbs->Add(m_resultLbl, wxGBPosition(21,20));

    m_projectsListPanel=new MyScrollPanel(this, wxID_ANY);
    m_gbs->Add(m_projectsListPanel, wxGBPosition(22,20));

    //populate projects
        Db *projectsDb=new Db("articles.rov");

        vector<string> projects=projectsDb->getAllRows();
        wxGridBagSizer *panelSizer=new wxGridBagSizer();
        m_projectsListPanel->SetSizer(panelSizer);
        //Refresh();

        for(int i(1),c(projects.size()+1);i<=c;i++)
        {
            try{
                string myline(projects[i]);
                if(i>1 && myline.find("rov")>0){
                    ArticlesStock *mycode=new ArticlesStock(i);
                    wxButton *titleCode=new wxButton(m_projectsListPanel, wxID_ANY, mycode->getAll("article name"));
                    wxStaticText *languageCode=new wxStaticText(m_projectsListPanel, wxID_ANY, mycode->getAll("article price")+"Ar");
                    panelSizer->Add(titleCode, wxGBPosition(i,0));
                    panelSizer->Add(languageCode, wxGBPosition(i,1));
                }
            }catch(std::exception e)
            {

            }
        }

    //projectsList->SetMinClientSize(wxSize(450,100));
    //m_gbs->Remove(m_gbs->GetSize()-1);

    //events
    m_saveBt->Bind(wxEVT_BUTTON, this->OnAddProject, this);

    this->SetSizer(m_gbs);
}


GestionCodeFrame::~GestionCodeFrame()
{
    Destroy();

}

void GestionCodeFrame::OnHello(wxCommandEvent& event)
{


}

void GestionCodeFrame::OnAbout(wxCommandEvent& event)
{


}
void GestionCodeFrame::OnExit(wxCommandEvent& event)
{

   Close();
}
void GestionCodeFrame::OnAddProject(wxCommandEvent& event)
{

    // string articleName(m_projectNameTxt->GetValue().ToStdString());
    // string projectLanguage(m_languageUsedTxt->GetValue().ToStdString());
    //     wxStaticText *m_referenceNumberLbl;
    // wxStaticText *m_articleNameLbl;
    // wxStaticText *m_articlePriceLbl;
    // wxStaticText *m_totalStockLbl;
    string articleReference(m_referenceNumberTxt->GetValue().ToStdString());
    string articleName(m_articleNameTxt->GetValue().ToStdString());
    string articlePrice(m_articlePriceTxt->GetValue().ToStdString());
    string articleTotal(m_totalStockTxt->GetValue().ToStdString());
    string description(m_descriptionTxt->GetValue().ToStdString());

    if(articleName.size()>0 && articleReference.size()>0 && 
    articlePrice.size()>0 
    && articleTotal.size()>0
    && description.size()>0
    )
    {
        Db *saveDb=new Db("articles.rov");
        int id=saveDb->getTotalRows()+1;
        string dataLine(toStr(id)+"_rov_"+articleReference+"_rov_"+articleName+"_rov_"+description+"_rov_"+articlePrice+"_rov_"+articleTotal+"_rov_");

        saveDb->addData(dataLine);

        m_resultLbl->SetLabel("Article enregistre, nom article: "+articleName);
 
        GestionCodeFrame *app=new GestionCodeFrame("Gestion de stock", wxDefaultPosition,wxSize(800,600));
        app->Show();
        Close();

    }else{
         m_resultLbl->SetLabel("Veuillez bien verifier que tous les champs ne sont pas vides");

    }

}

