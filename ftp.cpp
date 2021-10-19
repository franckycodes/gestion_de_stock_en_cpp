#include "ftp.h"
#include <string>
#include <vector>
#include "Db.h"

#include <wx/wx.h>
#include <wx/stream.h>
#include <wx/protocol/ftp.h>
#include <wx/protocol/protocol.h>
#include "lib/wxsmtp/email.h"
#include "lib/wxsmtp/smtp.h"
#include "lib/wxsmtp/cmdprot.h"

using namespace std;

void testFtp()
{
    wxFTP ftp;
    ftp.SetUser("user here");
    ftp.SetPassword( "pwd here");

    Db errorDb("error.log");

    if (!ftp.Connect("ftpupload.net"))
    {
        errorDb.addData("cant connect to ftpupload.net");
        //return;
    }
    errorDb.addData("connected to ftpupload.net");

    ftp.ChDir("/htdocs/");
    const char *filename = "index.php";

    int filesize = ftp.GetFileSize(filename);

    if (filesize == -1)
    {
        errorDb.addData("couldnt get the file size of index.php");
    }
    wxInputStream *in = ftp.GetInputStream(filename);

    if (!in)
    {
        errorDb.addData("couldnt get the file index.php");
    }
    else
    {
        char *data = new char[filesize];

        if (!in->Read(data, filesize))
        {

            errorDb.addData("read error");
        }
        else
        {
            errorDb.addData("file data is in buffer");
            wxString mydata(data);
            errorDb.addData(mydata.ToStdString());
        }
        delete[] data;
        delete in;
    }
    ftp.Close();
}

/*
wxOutputStream *out = ftp.GetOutputStream("filename");
if ( out )
{
    out->Write(...); // your data
    delete out;
}


*/

void sendMail(std::string emailSubject, std::string messageContent, std::string messageSender,
std::string targetMail)
{
    /* Instanciate the message */
    wxEmailMessage *msg = new wxEmailMessage(emailSubject,
                                             messageContent,
                                            messageSender);

    // Add the recipients of the mail
    msg->AddTo(targetMail);


    // Instanciate the smtp client
    wxSMTP *smtp = new wxSMTP(NULL);
    smtp->SetHost("smtp.gmail.com");

    /* Initiate the sending process */
    smtp->Send(msg);
}
