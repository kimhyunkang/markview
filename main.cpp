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

    frame = new EMFrame("EditMarked");

    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();

    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    menubar->Append(filemenu, "File");

#ifdef __WXMAC__
    // set menu bar to be displayed when no frames are open
    wxMenuBar::MacSetCommonMenuBar(menubar);
#endif

    frame->SetMenuBar(menubar);
    frame->Show(true);

    return true;
}

void EMApp::OnQuit(wxCommandEvent& evt)
{
    exit(0);
}
