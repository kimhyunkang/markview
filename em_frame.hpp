#include <wx/wx.h>
#include <wx/webview.h>

class EMFrame: public wxFrame
{
public:
    EMFrame(const wxString& title);

private:
    wxWebView *viewer;
};
