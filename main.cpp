#include "main.hpp"

IMPLEMENT_APP(EMApp)

BEGIN_EVENT_TABLE(EMApp, wxApp)
    EVT_MENU(wxID_EXIT, EMApp::OnQuit)
END_EVENT_TABLE()

bool EMApp::OnInit()
{

#ifdef __WXMAC__
    // Mac users expect programs not to be terminated when main window closes
    wxApp::SetExitOnFrameDelete(false);
#endif

    EMFrame* frame = new EMFrame("EditMarked");
    frames.push_back(frame);

    return true;
}

void EMApp::OnQuit(wxCommandEvent& evt)
{
    exit(0);
}
