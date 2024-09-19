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
    frame->SetSize(frame->GetEffectiveMinSize());
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
    grid->CreateGrid(10, 5);  // 10 guesses, 4 pegs + 1 for feedback

    grid->SetColLabelValue(0, "Color 1");
    grid->SetColLabelValue(1, "Color 2");
    grid->SetColLabelValue(2, "Color 3");
    grid->SetColLabelValue(3, "Color 4");

    grid->SetColLabelValue(4, "Feedback");  // Label for the feedback column

    grid->SetColSize(4, 170); //TODO : hardcoded - change by using a dedcated function

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
                std::vector<bool> exactMatches(4, false);  // Track exact matches
                std::vector<bool> colorMatches(4, false);  // Track color matches
                int correctPosition = 0;
                int correctColor = 0;

                // First pass: find exact matches
                for (int i = 0; i < 4; ++i)
                {
                    if (guess.SubString(i, i) == secretCode[i])
                    {
                        exactMatches[i] = true;
                        correctPosition++;
                    }
                }

                // Second pass: find color matches (ignoring exact matches)
                for (int i = 0; i < 4; ++i)
                {
                    if (!exactMatches[i])
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if (!exactMatches[j] && !colorMatches[j] && guess.SubString(i, i) == secretCode[j])
                            {
                                colorMatches[j] = true;
                                correctColor++;
                                break;
                            }
                        }
                    }
                }

                // Update the grid with the guess and the feedback
                for (int i = 0; i < 4; ++i)
                {
                    grid->SetCellValue(currentGuessRow, i, guess.SubString(i, i));
                }

                // Add feedback: how many correct positions and colors
                wxString feedback = wxString::Format("CorrPosition: %d, CorrColor: %d", correctPosition, correctColor);
                grid->SetCellValue(currentGuessRow, 4, feedback);  // Assuming the 5th column is used for feedback TODO : Change to not hardcoded                

                currentGuessRow++;
                input->Clear();

                // Check if the player won
                if (correctPosition == 4)
                {
                    wxMessageBox("Congratulations! You've guessed the code!", "You Win!", wxOK | wxICON_INFORMATION);
                    Close(true);
                }
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