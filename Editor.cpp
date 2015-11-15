#include "Editor.h"

Editor::Editor()
{
    //Setup UI
    frd::FRDGUI *gui = GUIManager::getInstance()->getEditorFRDGUIHandle().get();
    theme.load("myTheme.txt");

    //Setup menu to store the main page of the editor
    auto mainMenu = frd::Maker::make(frd::Menu());
    gui->addMenu(mainMenu);

    //Setup the left-hand buttons to manipulate the map
    auto editButtonsContainer = frd::Maker::make(frd::Container());
    editButtonsContainer->setSize({100, 100});

    auto clearLayerButton = frd::Maker::make(frd::Button());
    clearLayerButton->setLabel("Clear layer");
    clearLayerButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::clearLayer, this));
    theme.applyTheme(clearLayerButton);

    editButtonsContainer->addWidget(clearLayerButton);
    mainMenu->addWidget(editButtonsContainer);
}

Editor::~Editor()
{
    //dtor
}

void Editor::open()
{
    //Create an editor window if it's not already open
    if(!window.isOpen())
    {
        window.create(sf::VideoMode(windowSize.x, windowSize.y), "Editor Window", sf::Style::Close);
        window.setFramerateLimit(60);
        window.setKeyRepeatEnabled(false);
    }
}

void Editor::close()
{
    //Close the editor window
    window.close();
}

void Editor::update()
{
    if(window.isOpen()) //Only if the editor is open will we update. Effectively our window loop
    {
        //Poll for events
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F1)
                    close();
            }
            GUIManager::getInstance()->getEditorFRDGUIHandle()->handleEvent(event);
        }

        GUIManager::getInstance()->getEditorFRDGUIHandle()->update();

        window.clear(sf::Color::Black);
        window.draw(*GUIManager::getInstance()->getEditorFRDGUIHandle().get());
        window.display();
    }
}

void Editor::handleMessage(std::unique_ptr<MessageBase>& message)
{
    switch(message->getMessageType())
    {
    case MessageBase::keyEvent: //Check to see if we should open the editor
        {
            KeyEvent *event = dynamic_cast<KeyEvent*>(message.get());
            if(event->isKeyPress() && event->getKey() == sf::Keyboard::F1) //If it's the key to open the editor
            {
                open();
            }
            break;
        }
    default:
        break;
    }
}


void Editor::clearLayer()
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();
    //Change tiles on layer 0 to another type
    unsigned int tileCount = tempMap->getTileCount(0); //Get the number of tiles on this layer
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        TileBase *tile = tempMap->getTile(0, tileID); //Get a pointer to the current tile
        tile->setTextureRect(sf::IntRect(96, 0, 32, 32)); //Set a new texture
    }
}

void Editor::fillLayer()
{

}

void Editor::createAnimatedTile()
{

}

void Editor::rotateSelectionClockwise()
{

}

void Editor::toggleSpecialTilesVisible()
{

}

void Editor::togglePlacementGrid()
{

}

void Editor::createSpecialTile()
{

}

void Editor::paintTile()
{

}

void Editor::placeEntity()
{

}

void Editor::replaceTileType()
{

}

void Editor::setAggressiveMusic()
{

}

void Editor::setPassiveMusic()
{

}

void Editor::toggleLayerView()
{

}



