#include "markview.hpp"

BEGIN_EVENT_TABLE(ViewFrame, wxFrame)
    EVT_MENU(wxID_CLOSE, ViewFrame::OnClose)
END_EVENT_TABLE()

ViewFrame::ViewFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
    Centre();

    viewer = wxWebView::New(this,
                            wxID_ANY,
                            "file:///Users/kimhyunkang/project/markview/temp.html");

    // This menu bar only appears when there are no open windows
    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();

    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    filemenu->Append(wxID_CLOSE, "Close\tCtrl-W");
    menubar->Append(filemenu, "File");

    SetMenuBar(menubar);

    Show(true);
}

void ViewFrame::OnClose(wxCommandEvent& evt)
{
    this->Destroy();
}
