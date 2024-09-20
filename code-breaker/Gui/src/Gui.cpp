#include "Gui.h"

class MyApp : public wxApp 
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

enum 
{
    ID_Submit = 100,
    ID_ButtonRed,
    ID_ButtonGreen,
    ID_ButtonBlue,
    ID_ButtonYellow,
    ID_ButtonPurple,
    ID_ButtonOrange,
    ID_ButtonUndo,

};

bool MyApp::OnInit() 
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    frame->SetSize(frame->GetEffectiveMinSize());
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Code Breaker"),
    currentGuessRow(0) 
{

    // Create a wxStaticText for the "Code Breaker" title/logo
    wxStaticText* logoText = new wxStaticText(this, wxID_ANY, "Code Breaker");

    // Create a font object to style the text (bigger size, bold)
    wxFont logoFont(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    logoText->SetFont(logoFont);

    // Set the foreground color to make it stand out (optional)
    logoText->SetForegroundColour(wxColour(0, 102, 204));  // A blue color

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
    grid->SetColSize(4, 170); //TODO: hardcoded - change by using a dedicated function

    // Color buttons
    redButton = new wxButton(this, ID_ButtonRed, "Red");
    greenButton = new wxButton(this, ID_ButtonGreen, "Green");
    blueButton = new wxButton(this, ID_ButtonBlue, "Blue");
    yellowButton = new wxButton(this, ID_ButtonYellow, "Yellow");
    purpleButton = new wxButton(this, ID_ButtonPurple, "Purple");
    orangeButton = new wxButton(this, ID_ButtonOrange, "Orange");
    undoButton = new wxButton(this, ID_ButtonUndo, "Undo");


    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonRed);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonGreen);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonBlue);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonYellow);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonPurple);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorButton, this, ID_ButtonOrange);
    Bind(wxEVT_BUTTON, &MyFrame::OnUndo, this, ID_ButtonUndo);

    // Submit button
    submitButton = new wxButton(this, ID_Submit, "Submit");
    Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this, ID_Submit);

    // Layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(logoText, 0, wxALIGN_CENTER | wxALL, 10);  // Center and add padding
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);


    wxBoxSizer* colorButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    colorButtonSizer->Add(redButton, 0, wxEXPAND | wxALL, 5);
    colorButtonSizer->Add(greenButton, 0, wxEXPAND | wxALL, 5);
    colorButtonSizer->Add(blueButton, 0, wxEXPAND | wxALL, 5);
    colorButtonSizer->Add(yellowButton, 0, wxEXPAND | wxALL, 5);
    colorButtonSizer->Add(purpleButton, 0, wxEXPAND | wxALL, 5);
    colorButtonSizer->Add(orangeButton, 0, wxEXPAND | wxALL, 5);

    redButton->SetBackgroundColour(wxColour(255, 0, 0));
    greenButton->SetBackgroundColour(wxColour(0, 255, 0));
    blueButton->SetBackgroundColour(wxColour(0, 0, 255));
    yellowButton->SetBackgroundColour(wxColour(255, 255, 0));
    purpleButton->SetBackgroundColour(wxColour(128, 0, 128));
    orangeButton->SetBackgroundColour(wxColour(255, 165, 0));



    sizer->Add(colorButtonSizer, 0, wxALIGN_CENTER | wxALL, 5);
    sizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 5);
    sizer->Add(undoButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizer);

    secretCode = { "Red", "Green", "Blue", "Yellow" }; // Red, Green, Blue, Yellow
}

void MyFrame::OnExit(wxCommandEvent& event) 
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) 
{
    wxMessageBox("This is a computer game version of the Mastermind game",
        "About Mastermind", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnColorButton(wxCommandEvent& event)
{

    if (currentGuess.size() < 4) {
        wxButton* clickedButton = dynamic_cast<wxButton*>(event.GetEventObject());
        if (clickedButton == redButton) 
        {
            currentGuess.push_back("Red");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 0, 0));
        } 
        else if (clickedButton == greenButton) 
        {
            currentGuess.push_back("Green");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(0, 255, 0));

        } 
        else if (clickedButton == blueButton) 
        {
            currentGuess.push_back("Blue");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(0, 0, 255));

        } 
        else if (clickedButton == yellowButton) 
        {
            currentGuess.push_back("Yellow");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 255, 0));

        }
        else if (clickedButton == purpleButton)
        {
            currentGuess.push_back("Purple");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(128, 0, 128));

        }
        else if (clickedButton == orangeButton)
        {
            currentGuess.push_back("Orange");
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 165, 0));

        }
        grid->SetCellValue(currentGuessRow, currentGuess.size() - 1, currentGuess.back());
    }
}

void MyFrame::OnSubmit(wxCommandEvent& event) 
{
    if (currentGuessRow < 10) 
    {
        if (currentGuess.size() == 4) 
        {
            std::vector<bool> exactMatches(4, false);  
            std::vector<bool> colorMatches(4, false);  
            int correctPosition = 0;
            int correctColor = 0;

            for (int i = 0; i < 4; ++i) 
            {
                if (currentGuess[i] == secretCode[i]) 
                {
                    exactMatches[i] = true;
                    correctPosition++;
                }
            }

            for (int i = 0; i < 4; ++i) 
            {
                if (!exactMatches[i]) 
                {
                    for (int j = 0; j < 4; ++j) 
                    {
                        if (!exactMatches[j] && !colorMatches[j] && currentGuess[i] == secretCode[j]) 
                        {
                            colorMatches[j] = true;
                            correctColor++;
                            break;
                        }
                    }
                }
            }

            for (int i = 0; i < 4; ++i) 
            {
                grid->SetCellValue(currentGuessRow, i, currentGuess[i]);
            }

            wxString feedback = wxString::Format("CorrPosition: %d, CorrColor: %d", correctPosition, correctColor);
            grid->SetCellValue(currentGuessRow, 4, feedback);

            currentGuessRow++;
            currentGuess.clear();

            if (correctPosition == 4)
            {
                OnWin();

                // Ask the user if they want to play again
                if (wxMessageBox("Would you like to play again?", "Play Again", wxYES_NO | wxICON_QUESTION) == wxYES) {
                    ResetGame();
                }
                else {
                    Close(true); // Exit the game if they choose 'No'
                }
            }
        } 
        else 
        {
            wxMessageBox("Please select exactly 4 colors.", "Input Error", wxOK | wxICON_ERROR);
        }
    } 
    else
    {
        wxMessageBox("Maximum number of guesses reached. Game Over.", "Game Over", wxOK | wxICON_INFORMATION);

        // Ask the user if they want to play again
        if (wxMessageBox("Would you like to play again?", "Play Again", wxYES_NO | wxICON_QUESTION) == wxYES) {
            ResetGame();
        }
        else {
            Close(true); // Exit the game if they choose 'No'
        }
    }
}

void MyFrame::OnUndo(wxCommandEvent& event)
{
    // Check if there are any colors to undo
    if (!currentGuess.empty())
    {
        // Get the last selected color's index
        int lastColorIndex = currentGuess.size() - 1;

        // Clear the last selected color from the guess
        currentGuess.pop_back();

        // Clear the grid cell corresponding to the last guess
        grid->SetCellBackgroundColour(currentGuessRow, lastColorIndex, *wxWHITE);  // Reset the background color
        grid->SetCellValue(currentGuessRow, lastColorIndex, "");  // Clear the text in the cell

        // Force grid refresh to apply changes immediately
        grid->ForceRefresh();
    }
}

void MyFrame::ResetGame()
{
    // Clear the grid
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        for (int col = 0; col < grid->GetNumberCols(); ++col) {
            grid->SetCellValue(row, col, "");
            grid->SetCellBackgroundColour(row, col, *wxWHITE); // Reset the background color
        }
    }

    // Reset the guess row and the current guess
    currentGuessRow = 0;
    currentGuess.clear();

    // Generate a new secret code
    secretCode = { "Red", "Green", "Blue", "Yellow" };  // You can randomize this if needed

    // Force grid refresh to apply changes immediately
    grid->ForceRefresh();

    // Optionally update the status text to indicate a new game has started
    SetStatusText("New game started! Make your guess.");
}

void MyFrame::OnWin()
{
    // Create a custom wxDialog for the celebration
    wxDialog* congratsDialog = new wxDialog(this, wxID_ANY, "Congratulations!", wxDefaultPosition, wxSize(400, 200));

    // Create a wxBoxSizer for dialog layout
    wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

    // Create celebratory text
    wxStaticText* congratText = new wxStaticText(congratsDialog, wxID_ANY, "Congratulations! \nYou've guessed the code!");

    // Style the text to make it bold and larger
    wxFont congratsFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    congratText->SetFont(congratsFont);

    // Change the text color to something more festive (e.g., green)
    congratText->SetForegroundColour(wxColour(0, 204, 0));  // Bright green

    // Create a button to close the dialog
    wxButton* closeButton = new wxButton(congratsDialog, wxID_OK, "Celebrate!");

    // Add items to the sizer
    dialogSizer->Add(congratText, 1, wxALIGN_CENTER, 10);  // Add text
    dialogSizer->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);  // Add button

    // Set the sizer for the dialog
    congratsDialog->SetSizer(dialogSizer);

    // Center the dialog on the screen
    congratsDialog->Centre();

    // Show the dialog modally
    congratsDialog->ShowModal();
}
