#include "MyAppMain.h"

#include "GestionCodeFrame.h"
#include "initapp.h"
bool MyAppMain::OnInit()
{
    // codeManagementTables();
    stockManagementTables();
    GestionCodeFrame *app=new GestionCodeFrame("Gestion de Stock",wxDefaultPosition,wxSize(800,600));
    app->Show();

    return true;
}
