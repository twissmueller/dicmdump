#include "DicmDump.hpp"

#include "MainFrame.hpp"

bool DicmDump::OnInit()
{
    MainFrame *frame = new MainFrame( "DicmDump", wxPoint(50,50), wxSize(730,800) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 

