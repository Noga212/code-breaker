#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <string>
#include "Game.h"

class MyFrame : public wxFrame 
{
public:
    MyFrame();

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
    void OnColorButton(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void ResetGame();
    void OnWin();

    wxGrid* grid; // Grid for displaying guesses

    wxButton *redButton; // Button for Red color
    wxButton *greenButton; // Button for Green color
    wxButton *blueButton; // Button for Blue color
    wxButton *yellowButton; // Button for Yellow color
    wxButton *purpleButton; // Button for Purple color
    wxButton *orangeButton; // Button for Orange color

    wxButton* submitButton; // Button to submit guess
    wxButton* undoButton;
    
    std::vector<Game> m_games;
    std::vector<std::string> secretCode; // The secret code
    std::vector<colors> currentGuess; // Store the user's current guess
    int currentGuessRow; // Tracks the current guess row
};