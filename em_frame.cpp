#include "editmarked.hpp"

EMFrame::EMFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
    Centre();

    viewer = wxWebView::New(this,
                            wxID_ANY,
                            "file:///Users/kimhyunkang/project/editmarked/temp.html");

    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();

    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    menubar->Append(filemenu, "File");

#ifdef __WXMAC__
    // set menu bar to be displayed when no frames are open
    wxMenuBar::MacSetCommonMenuBar(menubar);
#endif

    SetMenuBar(menubar);
    Show(true);
}

void EMFrame::OnClose(wxCommandEvent& evt)
{
    Close(true);
}
