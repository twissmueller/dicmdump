#include "MainFrame.hpp"

#include <FileFormatWxListCtrl.hpp>
#include <DcmtkBuilder.hpp>
#include <DicomLibException.hpp>

enum
{
	ID_File_Open = 1,
    ID_File_Quit = 2,
    ID_Help_About = 3,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_File_Open, MainFrame::OnFileOpen)
    EVT_MENU(ID_File_Quit, MainFrame::OnFileQuit)
    EVT_MENU(ID_Help_About, MainFrame::OnHelpAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{	
	// Create the menus
    wxMenu *menuFile = new wxMenu;
	wxMenu *menuHelp = new wxMenu;

    menuFile->Append( ID_File_Open, "&Open..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_File_Quit, "E&xit" );

	menuHelp -> Append( ID_Help_About, "&About...");

	// Create the menubar
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );

    SetMenuBar( menuBar );

	// Create the statusbar
    CreateStatusBar();
    SetStatusText( "Welcome to DicmDump!" );

	// Create the dump view
	fileFormatView = new FileFormatWxListCtrl(this);
}

void MainFrame::OnFileOpen(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* openDlg = new wxFileDialog(this, "Open a DICOM file", "", "", "",
											 wxOPEN, wxDefaultPosition);

	if (openDlg->ShowModal() == wxID_OK)
	{
		try
		{
			DcmtkBuilder dbuilder;
			dbuilder.setFilename(openDlg->GetPath().c_str());
			fileFormatView -> setData(dbuilder.getFileFormat());
			SetStatusText( "Please wait!" );
			fileFormatView -> createView();
			SetStatusText( "Finished!" );
		}
		catch (DicomLibException& e)
		{
			wxMessageBox(e.what().c_str(), "Exception error!", wxOK | wxICON_INFORMATION, this);
		}
		catch (...)
		{
			throw;
		}
	}

	openDlg -> Destroy();
}

void MainFrame::OnFileQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MainFrame::OnHelpAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("DicmDump by Tobias Wissmueller",
        "About DicmDump", wxOK | wxICON_INFORMATION, this);
}

