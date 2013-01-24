#include "markview.hpp"
#include <wx/filedlg.h>

#ifdef __WXMAC__
#include <CoreFoundation/CFBundle.h>
#include <ApplicationServices/ApplicationServices.h>
#endif // __WXMAC__

IMPLEMENT_APP(MainApp)

BEGIN_EVENT_TABLE(MainApp, wxApp)
    EVT_MENU(wxID_OPEN, MainApp::OnOpen)
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

    filemenu->Append(wxID_OPEN, "Open\tCtrl-O");
    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    menubar->Append(filemenu, "File");

    wxMenuBar::MacSetCommonMenuBar(menubar);
#endif // __WXMAC__

    OpenFile();

    return true;
}

void MainApp::OpenFile()
{
    wxFileDialog openFileDialog(NULL, "Open new file", "", "", "Markdown files (*.md)|*.md", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if(openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString filepath = openFileDialog.GetPath();

    new ViewFrame(filepath);
}

void MainApp::OnOpen(wxCommandEvent& evt)
{
    OpenFile();
}

void MainApp::OnQuit(wxCommandEvent& evt)
{
    ExitMainLoop();
}

#ifdef __WXMAC__
void openBrowser(const wxString& url)
{
    wxCharBuffer buf = url.mb_str();

    CFURLRef ref = CFURLCreateWithBytes (
            NULL,
            (UInt8*)buf.data(),
            buf.length(),
            kCFStringEncodingASCII,
            NULL
        );
    LSOpenCFURLRef(ref, 0);
    CFRelease(ref);
}
#else
void openBrowser(const wxString& url)
{
    // do nothing
}
#endif
