#include "markview.hpp"

IMPLEMENT_APP(MainApp)

BEGIN_EVENT_TABLE(MainApp, wxApp)
    EVT_MENU(wxID_CLOSE, ViewFrame::OnClose)
    EVT_MENU(wxID_EXIT, MainApp::OnQuit)
END_EVENT_TABLE()

bool MainApp::OnInit()
{

#ifdef __WXMAC__
    // Mac users expect programs not to be terminated when main window closes
    wxApp::SetExitOnFrameDelete(false);
#endif

    ViewFrame* frame = new ViewFrame("EditMarked");
    frames.push_back(frame);

    return true;
}

void MainApp::OnQuit(wxCommandEvent& evt)
{
    exit(0);
}

void MainApp::delete_child(ViewFrame* frame)
{
    std::vector<ViewFrame *>::iterator it = frames.begin();
    for( ; it != frames.end(); ++it) {
        if(*it == frame) {
            frames.erase(it);
            break;
        }
    }
}
