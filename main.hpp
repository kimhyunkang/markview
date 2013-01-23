#include <wx/wx.h>
#include "em_frame.hpp"

class EMApp: public wxApp
{
private:
    EMFrame *frame;

public:
    DECLARE_EVENT_TABLE()

    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);
};
