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
    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);

    void delete_child(EMFrame* frame);

    DECLARE_EVENT_TABLE()
};
