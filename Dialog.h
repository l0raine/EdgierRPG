#ifndef DIALOG_H
#define DIALOG_H

#include <functional>
#include <vector>
#include <string>

#include "FRDGUI.h"
#include "GUI/GUIManager.h"
#include <Theme.h>
#include <Container.h>
#include "Decoration.h"
#include "MessageBase.h"


class Dialog
{
    public:
        /** Default constructor */
        Dialog(const std::string &windowTitle);
        /** Default destructor */
        virtual ~Dialog();

        void setPosition(const sf::Vector2f& newPosition); // Set the position of the dialog box
        void update(); //Update the dialog box
        void open(); //Open the dialog box
        void load(const std::string &dialogTitle); //Load the dialog box
        void close(); //Hide the dialog box

        //GUI functions for inputting data
        void addLabel(const std::string& label); //Add descriptive labels
        void addList(const std::vector<std::string>& buttonLabels, std::vector<std::function<void()>> callbacks); //Add options to select from - these are FRDGUI buttons
        unsigned int addEntry(const std::string& entryLabel); //Add FRDGUI entries to input data

        void setOkayButton(std::function<void()>); //Set function callback for the okay button
        void setCancelButton(std::function<void()>); //Set function callback for the cancel/close button

        const std::string getEntryStringByID(unsigned int entryID); //Get an entry's inputted data by passing in its ID

    protected:
    private:
        sf::RenderWindow dialogWindow; //Instance of the dialog box window
        sf::Vector2i dialogWindowSize; //Size of the dialog box window
        std::string dialogTitle;
        frd::Theme dialogTheme; //Theme of the dialog box window


        frd::FRDGUI dialogGUI; //FRDGUI reference

        //Variables for keeping track of buttons and containers
        std::shared_ptr<frd::Menu> menu;
        sf::RectangleShape borders;
        std::shared_ptr <frd::Container> mainContainer;
        std::shared_ptr <frd::Container> confirmationButtons;

        std::vector<std::pair<unsigned int, std::shared_ptr<frd::Entry>>> entries;

        unsigned int confirmationButtonCount;
        unsigned int entryID;

        //GUI elements for the dialog box window
        std::shared_ptr <frd::Menu> mainMenu;

        //Dialog manager functions
        void updatePositions();
};


#endif // DIALOG_H
