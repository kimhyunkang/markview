#include <vector>
#include <wx/wx.h>
#include "em_frame.hpp"

class EMApp: public wxApp
{
private:
    std::vector<EMFrame *> frames;

public:
    DECLARE_EVENT_TABLE()

    virtual bool OnInit();

    void OnQuit(wxCommandEvent& evt);
};
