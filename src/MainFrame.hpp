#ifndef MainFrame_HPP
#define MainFrame_HPP

#include "wx/wx.h" 

class FileFormatWxListCtrl;

class MainFrame: public wxFrame
{
public:

    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnFileOpen(wxCommandEvent& event);
    void OnFileQuit(wxCommandEvent& event);
    void OnHelpAbout(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()

private:
	FileFormatWxListCtrl* fileFormatView;
};





#endif // MainFrame_HPP