#include <vector>
#include <wx/wx.h>
#include <wx/webview.h>

class EMFrame: public wxFrame
{
private:
    wxWebView *viewer;

public:
    EMFrame(const wxString& title);

    void OnClose(wxCommandEvent& evt);
};

class EMApp: public wxApp
{
private:
    std::vector<EMFrame *> frames;

public:
    DECLARE_EVENT_TABLE()

    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);

    void close_child(EMFrame* frame);
};
