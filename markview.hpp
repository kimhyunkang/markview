#include <vector>
#include <wx/wx.h>
#include <wx/webview.h>

class ViewFrame: public wxFrame
{
private:
    wxWebView *viewer;
    bool frozen;

    DECLARE_EVENT_TABLE()

public:
    ViewFrame(const wxString& title);

    void OnNavigating(wxWebViewEvent& evt);
    void OnClose(wxCommandEvent& evt);
};

class MainApp: public wxApp
{
private:
    DECLARE_EVENT_TABLE()

public:
    virtual bool OnInit();

    void OnOpen(wxCommandEvent& evt);
    void OnQuit(wxCommandEvent& evt);
    void OpenFile();
    void NewFrame(const wxString& filepath);
};

void openBrowser(const wxString& url);
