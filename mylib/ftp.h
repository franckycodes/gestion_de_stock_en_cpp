#pragma once
#include <wx/wx.h>
#include <wx/stream.h>
#include <wx/protocol/ftp.h>
void testFtp();

void sendMail(std::string emailSubject="about", std::string messageContent="Hello world", std::string messageSender="", std::string targetMail="franckywebdesign@gmail.com");
