#ifndef APPDIALOG_H
#define APPDIALOG_H

//(*Headers(AppDialog)
#include <wx/dialog.h>
//*)

class AppDialog: public wxDialog
{
	public:

		AppDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AppDialog();

		//(*Declarations(AppDialog)
		//*)

	protected:

		//(*Identifiers(AppDialog)
		//*)

	private:

		//(*Handlers(AppDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
