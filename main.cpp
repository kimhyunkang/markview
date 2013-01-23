#include "markview.hpp"

IMPLEMENT_APP(MainApp)

BEGIN_EVENT_TABLE(MainApp, wxApp)
    EVT_MENU(wxID_EXIT, MainApp::OnQuit)
END_EVENT_TABLE()

bool MainApp::OnInit()
{
#ifdef __WXMAC__
    // Mac users expect programs not to be terminated when main window closes
    wxApp::SetExitOnFrameDelete(false);

    // This menu bar only appears when there are no open windows
    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();

    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    menubar->Append(filemenu, "File");

    wxMenuBar::MacSetCommonMenuBar(menubar);
#endif // __WXMAC__

    NewFrame("Empty File");

    return true;
}

void MainApp::NewFrame(const wxString& title)
{
    ViewFrame *frame = new ViewFrame("ViewFrame");
}

void MainApp::OnQuit(wxCommandEvent& evt)
{
    ExitMainLoop();
}
