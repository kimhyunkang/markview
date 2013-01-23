#include "em_frame.hpp"
#include <wx/webview.h>

EMFrame::EMFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
    Centre();

    viewer = wxWebView::New(this,
                            wxID_ANY,
                            "file:///Users/kimhyunkang/project/editmarked/temp.html");
}
