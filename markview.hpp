#include <vector>
#include <wx/wx.h>
#include <wx/webview.h>

class ViewFrame: public wxFrame
{
private:
    wxWebView *viewer;

public:
    ViewFrame(const wxString& title);

    void OnClose(wxCommandEvent& evt);
};

class MainApp: public wxApp
{
private:
    std::vector<ViewFrame *> frames;

public:
    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);

    void delete_child(ViewFrame* frame);

    DECLARE_EVENT_TABLE()
};
