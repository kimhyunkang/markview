#include "main.hpp"
#include "em_frame.hpp"

IMPLEMENT_APP(EMApp)

bool EMApp::OnInit()
{
    EMFrame *frame = new EMFrame(wxT("EditMarked"));
    frame->Show(true);

    return true;
}
