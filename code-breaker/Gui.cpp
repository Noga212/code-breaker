#include "Gui.h"

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

enum {
    ID_Submit = 100,
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Mastermind Game"),
    currentGuessRow(0) {

    wxMenu* menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Mastermind version 0.1");

    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    // Setup grid
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(10, 4); // 10 guesses, 4 pegs
    grid->SetColLabelValue(0, "Peg 1");
    grid->SetColLabelValue(1, "Peg 2");
    grid->SetColLabelValue(2, "Peg 3");
    grid->SetColLabelValue(3, "Peg 4");

    // Input box for guesses
    input = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    // Submit button
    submitButton = new wxButton(this, ID_Submit, "Submit");
    Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this, ID_Submit);

    // Layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    sizer->Add(input, 0, wxEXPAND | wxALL, 5);
    sizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizer);

    // TODO integration : remove hardcoded
    secretCode = { "R", "G", "B", "Y" }; // Red, Green, Blue, Yellow
    colors = { wxColour(255, 0, 0), wxColour(0, 255, 0), wxColour(0, 0, 255), wxColour(255, 255, 0) };
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a computer game version of the Mastermind game",
        "About Mastermind", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnSubmit(wxCommandEvent& event) 
{
    if (currentGuessRow < 10) 
    {
        wxString guess = input->GetValue();
        if (guess.length() == 4) 
        {
            if (ensureChars(guess))
            {
                // Store the guess in the grid
                for (int i = 0; i < 4; ++i) {
                    
                    grid->SetCellValue(currentGuessRow, i, guess.SubString(i, i));
                    // TODO : add the logic of guess
                }
                currentGuessRow++;
                input->Clear();
                // TODO: Implement feedback logic (e.g., number of correct pegs)
            }
            else
            {
                wxMessageBox("Please enter combinations of those 4 characters (R, G, B, Y).",
                    "Input Error", wxOK | wxICON_ERROR);
            }
        }
        else 
        {
            wxMessageBox("Please enter exactly 4 characters (R, G, B, Y).",
                "Input Error", wxOK | wxICON_ERROR);
        }
    }
    else 
    {
        wxMessageBox("Maximum number of guesses reached.", "Game Over", wxOK | wxICON_INFORMATION);
    }
}

int MyFrame::ensureChars(wxString guess)
{
    for (int i = 0; i < guess.size(); ++i)
    {
        if ((guess.GetChar(i) != 'R') && (guess.GetChar(i) != 'G') && (guess.GetChar(i) != 'B') && (guess.GetChar(i) != 'Y'))
        {
            return false;
        }
    }
    return true;
}
