#include "Dialog.h"

Dialog::Dialog(const std::string &windowTitle)
: dialogGUI(sf::Vector2i(400,200), fontPath + "arial.ttf", sf::Color::White, 7)
{
    load(windowTitle);
}

void Dialog::load(const std::string &tempDialogTitle)
{
    //Setup UI
    if(!dialogTheme.load(themePath + "dialogTheme.txt"))
        std::cout<<themePath + "dialogTheme.txt"<<std::endl;
    dialogTitle = tempDialogTitle; //Set the title of the dialog box
    dialogWindowSize = sf::Vector2i(400, 200);

    //Setup the menu to store everything
    menu = frd::Maker::make(frd::Menu());

    //Initialize the main container variables
    mainContainer = frd::Maker::make(frd::Container());

    mainContainer->setSize({dialogWindowSize.x - 20, dialogWindowSize.y - 100 }); //Create the workable area
    mainContainer->setPosition({50, dialogWindowSize.y/2 - 50}); //Set workable area's position to top left of the dialog box
    mainContainer->setAllocation(Allocation::vertical); //Set its allocation to vertical

    confirmationButtons = frd::Maker::make(frd::Container()); //Create the container for confirmation buttons i.e okay and cancel
    confirmationButtons->setSize({dialogWindowSize.x - 20, dialogWindowSize.y/6 }); //Set the container's size to right under the mainContainer's area
    confirmationButtons->setPosition({50, 140}); //Set its position to under the mainContainer's area
    confirmationButtons->setAllocation(Allocation::horizontal); //Set allocation to horizontal
    confirmationButtons->setSpacing({100,5}); // Set the spacing between the buttons to 5 on and X and Y axis
    confirmationButtons->allowAutomaticResizing(false); //Disable automatic resizing

    menu->addWidget(confirmationButtons); //Add the confirmation buttons to the menu

    menu->addWidget(mainContainer); //Add the main container to the menu

    //Initialize confirmation button count to 0
    confirmationButtonCount = 0;

    //Initialize the entry ID to 0 to keep track of the added entries
    entryID = 0;

    //Main working area with borders
    borders = sf::RectangleShape(sf::Vector2f(dialogWindowSize.x - 20.f, dialogWindowSize.y - 30.f));
    borders.setPosition(10,20);
    borders.setFillColor(sf::Color(0, 102, 0, 60));

    //Setup the title label
    auto titleLabel = frd::Maker::make(frd::Button());
    titleLabel->setLabel(dialogTitle);
    titleLabel->setBezelEnabled(false);
    titleLabel->setEnabled(false);
    titleLabel->setColor(sf::Color::Transparent);
    titleLabel->setCharacterSize(13);
    titleLabel->setSize({20, 10});
    titleLabel->setPosition({dialogWindowSize.x/2 - titleLabel->getSize().x/2, 5});

    //Add widgets to the menu
    menu->addWidget(titleLabel);

    dialogGUI.addMenu(menu);
}


Dialog::~Dialog()
{
    //dtor
}

void Dialog::open()
{
    if(!dialogWindow.isOpen())
    {
        //Create the window
        dialogWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - dialogWindowSize.x - 10, sf::VideoMode::getDesktopMode().height/4));
        dialogWindow.create(sf::VideoMode(dialogWindowSize.x, dialogWindowSize.y), dialogTitle, sf::Style::None);
    }
}

void Dialog::close()
{
    dialogWindow.close();
}

void Dialog::update()
{
    //Open the window if not open
    open();

    //Update the window
    while(dialogWindow.isOpen()) //Only if the dialog box is open
    {
        //Poll for events
        sf::Event event;
        while(dialogWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                close();
            }

            dialogGUI.handleEvent(event);
        }

        dialogGUI.update();

        dialogWindow.clear(sf::Color::Red); //Clear the window with a red colour
        dialogWindow.draw(borders); //Draw the borders of the dialog box
        dialogWindow.draw(dialogGUI); //Draw the FRDGUI instance of this dialog box
        dialogWindow.display(); //Display the dialog box
    }

}

void Dialog::addList(const std::vector<std::string>& buttonLabels , std::vector<std::function<void()>> callbacks)
{
    //Create the containers
    auto buttonContainer = frd::Maker::make(frd::Container());
    buttonContainer->setAllocation(Allocation::horizontal);
    buttonContainer->setSize({400, 200});
    buttonContainer->setPosition({dialogWindowSize.x / 8.f, dialogWindowSize.y / 6.f});
    buttonContainer->setSpacing({0, 5});
    buttonContainer->allowAutomaticResizing(false);

    unsigned int currentBind = 0; //Index for assigning the bindings

    //Get all the button labels and set them up
    for(auto &cLabel : buttonLabels)
    {
        auto button = frd::Maker::make(frd::Button());
        button->setLabel(cLabel);
        dialogTheme.applyTheme(button);
        button->setColor(sf::Color::White);
        button->setSize({100, 25});
        button->getLabel().setColor(sf::Color::Blue);
        button->bindFunction(EventTypes::LeftClick_Up, callbacks[currentBind++]);

        buttonContainer->addWidget(button);
    }

    menu->addWidget(buttonContainer);
}

void Dialog::addLabel(const std::string& label)
{
    auto frdLabel = frd::Maker::make(frd::Button());
    frdLabel->setColor(sf::Color::Transparent);
    frdLabel->setBezelEnabled(false);
    frdLabel->setLabel(label);
    frdLabel->setCharacterSize(13);

    mainContainer->addWidget(frdLabel);
}

void Dialog::setOkayButton(std::function<void()> callback)
{
    //Setup the okay button
    auto okayButton = frd::Maker::make(frd::Button());
    okayButton->setLabel("Okay");
    dialogTheme.applyTheme(okayButton);
    //okayButton->setPosition({50, 150});
    okayButton->setSize({100, 25});

    okayButton->bindFunction(EventTypes::LeftClick_Up, callback);

    confirmationButtons->addWidget(okayButton);

    confirmationButtonCount++;
}

void Dialog::setCancelButton(std::function<void()> callback)
{
    //Setup the cancel button
    auto cancelButton = frd::Maker::make(frd::Button());
    cancelButton->setLabel("Cancel");
    dialogTheme.applyTheme(cancelButton);
    //cancelButton->setPosition({250, 150});
    cancelButton->setSize({100, 25});

    cancelButton->bindFunction(EventTypes::LeftClick_Up, callback);

    confirmationButtons->addWidget(cancelButton);

    confirmationButtonCount++;
}

unsigned int Dialog::addEntry(const std::string& defaultLabel)
{
    auto entryContainer = frd::Maker::make(frd::Container());
    entryContainer->setSize({200, 20});
    entryContainer->setAllocation(Allocation::horizontal);


    //Define the label for the user to know what kind of data they are inputting
    auto entryLabel = frd::Maker::make(frd::Button());
    entryLabel->setColor(sf::Color::Transparent);
    entryLabel->setBezelEnabled(false);
    entryLabel->setLabel(defaultLabel);
    entryLabel->setCharacterSize(13);

    //Define the input system
    auto entry = frd::Maker::make(frd::Entry());
    entry->getLabel().setColor(sf::Color::Black);
    entry->setCursorColor(sf::Color::Black);
    entry->setCursorEnabled(true);
    entry->setCursorFlashInterval(sf::seconds(1));
    entry->setCharacterSize(10);
    entry->setCursorWidth(2);

    mainContainer->allowAutomaticResizing(false);

    entryContainer->addWidget(entryLabel);
    entryContainer->addWidget(entry);

    mainContainer->addWidget(entryContainer);

    entries.emplace_back(std::make_pair(++entryID, entry));
    return entryID;
}

const std::string Dialog::getEntryStringByID(unsigned int entryID)
{
    for(auto iter = entries.begin(); iter != entries.end(); iter++)
    {
        if(iter->first == entryID)
        {
            return iter->second->getString();
        }
    }
    return "1";
}

