#include "AppDialog.h"

//(*InternalHeaders(AppDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AppDialog)
//*)

BEGIN_EVENT_TABLE(AppDialog,wxDialog)
	//(*EventTable(AppDialog)
	//*)
END_EVENT_TABLE()

AppDialog::AppDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AppDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	//*)
}

AppDialog::~AppDialog()
{
	//(*Destroy(AppDialog)
	//*)
}

