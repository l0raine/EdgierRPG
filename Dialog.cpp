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

    //Initialize container variables
    mainContainer = frd::Maker::make(frd::Container());
    mainContainer->setSize({dialogWindowSize.x - 20, dialogWindowSize.y - 100 });
    mainContainer->setPosition({10, 20});
    mainContainer->setAllocation(Allocation::vertical);
    mainContainer->setSpacing({5,5});

    confirmationButtons = frd::Maker::make(frd::Container());
    confirmationButtons->setSize({dialogWindowSize.x - 20, dialogWindowSize.y/6 });
    confirmationButtons->setPosition({50, 140});
    confirmationButtons->setAllocation(Allocation::horizontal);
    confirmationButtons->setSpacing({5,5});
    confirmationButtons->allowAutomaticResizing(false);

    menu->addWidget(confirmationButtons);

    menu->addWidget(mainContainer);

    //Initialize confirmation button count to 0
    confirmationButtonCount = 0;
    entryID = 0;

    //Main working area with borders
    borders = sf::RectangleShape(sf::Vector2f(dialogWindowSize.x - 20, dialogWindowSize.y - 30));
    borders.setPosition(10,20);
    borders.setFillColor(sf::Color(0, 102, 0));

    //Setup the title label
    auto titleLabel = frd::Maker::make(frd::Label());
    titleLabel->setLabel(dialogTitle);
    dialogTheme.applyTheme(titleLabel);
    titleLabel->setPosition({dialogWindowSize.x/3, 50});

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

        dialogWindow.clear(sf::Color::Red);
        dialogWindow.draw(borders);
        dialogWindow.draw(dialogGUI);
        dialogWindow.display();
    }

}

void Dialog::addList(const std::vector<std::string>& buttonLabels , std::vector<std::function<void()>> callbacks)
{
    //Create the containers
    auto buttonContainer = frd::Maker::make(frd::Container());
    buttonContainer->setAllocation(Allocation::horizontal);
    buttonContainer->setSize({400, 200});
    buttonContainer->setPosition({dialogWindowSize.x/8, dialogWindowSize.y/6});
    buttonContainer->setSpacing({0, 5});
    buttonContainer->allowAutomaticResizing(false);

    unsigned int currentBind = 0;

    //Get all the button labels and
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
    auto frdLabel = frd::Maker::make(frd::Label());
    frdLabel->setLabel(label);
    frdLabel->setColor(sf::Color::Black);
    frdLabel->setSize({20,20});

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

    menu->addWidget(cancelButton);

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

