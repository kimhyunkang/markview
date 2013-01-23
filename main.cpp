#include "editmarked.hpp"

IMPLEMENT_APP(EMApp)

BEGIN_EVENT_TABLE(EMApp, wxApp)
    EVT_MENU(wxID_CLOSE, EMFrame::OnClose)
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

void EMApp::delete_child(EMFrame* frame)
{
    std::vector<EMFrame *>::iterator it = frames.begin();
    for( ; it != frames.end(); ++it) {
        if(*it == frame) {
            frames.erase(it);
            break;
        }
    }
}
