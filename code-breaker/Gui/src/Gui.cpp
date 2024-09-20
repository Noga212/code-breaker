#include "Gui.h"

#define GRID_SIZE 8
#define FEEDBACK_COLOMNS 4
#define NUM_OF_GUESSES 10

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
    m_games.push_back(Game());
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
    grid->CreateGrid(NUM_OF_GUESSES, GRID_SIZE);  // 10 guesses, 4 pegs + 1 for feedback

    grid->SetColLabelValue(0, "Color 1");
    grid->SetColLabelValue(1, "Color 2");
    grid->SetColLabelValue(2, "Color 3");
    grid->SetColLabelValue(3, "Color 4");

    for (int i = FEEDBACK_COLOMNS; i < grid->GetNumberCols(); ++i)
    {
        grid->SetColLabelValue(i, "");
        grid->SetColSize(i, 30);
    }

    for (int row = 0; row < grid->GetNumberRows(); ++row) 
    {
        for (int col = 0; col < grid->GetNumberCols(); ++col) 
        {
            grid->SetCellBackgroundColour(row, col, wxColour(200, 200, 200));
        }
    }

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
}

void MyFrame::OnExit(wxCommandEvent& event) 
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) 
{
    wxMessageBox("The computer has generated a code, you need to guess it! \n guess a combination and you will get hints : \n white for a color that exists in the code but not in the right place, and black for a color that is in its right place.\nUse the hints as you prograss to solve the code with the least amount of guesses you can!",
        "About Mastermind", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnColorButton(wxCommandEvent& event)
{

    if (currentGuess.size() < m_games[m_games.size() - 1].getCode().size()) {
        wxButton* clickedButton = dynamic_cast<wxButton*>(event.GetEventObject());
        if (clickedButton == redButton) 
        {
            currentGuess.push_back(red);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 0, 0));
        } 
        else if (clickedButton == greenButton) 
        {
            currentGuess.push_back(green);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(0, 255, 0));

        } 
        else if (clickedButton == blueButton) 
        {
            currentGuess.push_back(blue);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(0, 0, 255));

        } 
        else if (clickedButton == yellowButton) 
        {
            currentGuess.push_back(yellow);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 255, 0));

        }
        else if (clickedButton == purpleButton)
        {
            currentGuess.push_back(purple);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(128, 0, 128));

        }
        else if (clickedButton == orangeButton)
        {
            currentGuess.push_back(orange);
            grid->SetCellBackgroundColour(currentGuessRow, currentGuess.size() - 1, wxColour(255, 165, 0));

        }
        grid->ForceRefresh();
    }
}

void MyFrame::OnSubmit(wxCommandEvent& event) 
{
    unsigned int numOfColors = m_games[m_games.size() - 1].getCode().size();
    Guess guessToSubmit(currentGuess);
    if (currentGuessRow < NUM_OF_GUESSES)
    {
        if (currentGuess.size() == numOfColors)
        {
            guessToSubmit.calculateHint(m_games[m_games.size() - 1].getCode());
            unsigned int blackHint = guessToSubmit.getBlack();
            unsigned int whiteHint = guessToSubmit.getWhite();

            for (unsigned int i = 0; i < blackHint; ++i)
            {
                grid->SetCellBackgroundColour(currentGuessRow, i + numOfColors, wxColour(0,0,0));
            }
            for (unsigned int i = 0; i < whiteHint; ++i)
            {
                grid->SetCellBackgroundColour(currentGuessRow, i + blackHint + numOfColors, wxColour(255, 255, 255));
            }
            grid->ForceRefresh();

            currentGuessRow++;
            currentGuess.clear();

            if (guessToSubmit.getBlack() == numOfColors)
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
    // Generate a new secret code
    m_games.push_back(Game());

    // Clear the grid
    for (int row = 0; row < grid->GetNumberRows(); ++row) {
        for (int col = 0; col < grid->GetNumberCols(); ++col) 
        {
            grid->SetCellValue(row, col, "");
            grid->SetCellBackgroundColour(row, col, wxColour(200, 200, 200)); // Reset the background color
        }
    }

    // Reset the guess row and the current guess
    currentGuessRow = 0;
    currentGuess.clear();

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
