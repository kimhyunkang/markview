#include <iostream>
#include "markview.hpp"
#include "renderer.hpp"

BEGIN_EVENT_TABLE(ViewFrame, wxFrame)
    EVT_MENU(wxID_CLOSE, ViewFrame::OnClose)
END_EVENT_TABLE()

ViewFrame::ViewFrame(const wxString& filepath)
    : wxFrame(NULL, wxID_ANY, filepath, wxDefaultPosition, wxSize(250, 150))
{
    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();

    filemenu->Append(wxID_OPEN, "Open\tCtrl-O");
    filemenu->Append(wxID_CLOSE, "Close Window\tCtrl-W");
    filemenu->Append(wxID_EXIT, "Quit\tCtrl-Q");
    menubar->Append(filemenu, "File");

    SetMenuBar(menubar);

    MarkdownRenderer renderer;

    viewer = wxWebView::New(this, wxID_ANY);
    if(!renderer.render(filepath.GetData())) {
        std::cout << renderer.getErrMsg() << std::endl;
        return;
    }
    viewer->SetPage(renderer.getData(), filepath);

    Centre();

    Show(true);
}

void ViewFrame::OnClose(wxCommandEvent& evt)
{
    this->Destroy();
}
