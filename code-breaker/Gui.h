#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <string>

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
    int ensureChars(wxString guess);

    wxGrid* grid; // Grid for displaying guesses
    wxTextCtrl* input; // Input for user's guess
    wxButton* submitButton; // Button to submit guess

    std::vector<std::string> secretCode; // The secret code
    std::vector<wxColor>colors; //colors for the game
    int currentGuessRow; // Tracks the current guess row
};