#include <vector>
#include <wx/wx.h>
#include <wx/webview.h>

class ViewFrame: public wxFrame
{
private:
    wxWebView *viewer;

    DECLARE_EVENT_TABLE()

public:
    ViewFrame(const wxString& title);

    void OnClose(wxCommandEvent& evt);
};

class MainApp: public wxApp
{
private:
    DECLARE_EVENT_TABLE()

public:
    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);
    void NewFrame(const wxString& title);
};
