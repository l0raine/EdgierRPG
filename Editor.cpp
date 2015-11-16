#include "Editor.h"

#include "GUI/GUIManager.h"
#include "MessageBase.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include "MapManager.h"
#include "EditorTilesheetView.h"
#include "Map.h"

Editor::Editor()
{
    //Setup UI
    frd::FRDGUI *gui = GUIManager::getInstance()->getEditorFRDGUIHandle().get();
    theme.load(themePath + "myTheme.txt");

    //Initialise some core editor variables
    currentlySelectedLayer = 0;

    //Setup menu to store the main page of the editor
    auto mainMenu = frd::Maker::make(frd::Menu());
    gui->addMenu(mainMenu);

    //Setup the left-hand buttons to manipulate the map
    auto editButtonsContainer = frd::Maker::make(frd::Container());
    editButtonsContainer->setSize({160, 530});
    editButtonsContainer->setAllocation(Allocation::vertical);
    editButtonsContainer->setSpacing(sf::Vector2f(0,10));
    editButtonsContainer->setPosition({620,45});

    //ClearLayer Button
    auto clearLayerButton = frd::Maker::make(frd::Button());
    clearLayerButton->setLabel("Clear layer");
    clearLayerButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::clearLayer, this));
    theme.applyTheme(clearLayerButton);

    //FillLayer Button
    auto fillLayerButton = frd::Maker::make(frd::Button());
    fillLayerButton->setLabel("Fill Layer");
    fillLayerButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::fillLayer, this));
    theme.applyTheme(fillLayerButton);

    //Create Animated Tile Button
    auto createAnimatedTileButton = frd::Maker::make(frd::Button());
    createAnimatedTileButton->setLabel("Create Animated Tile");
    createAnimatedTileButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::createAnimatedTile, this));
    theme.applyTheme(createAnimatedTileButton);

    //Toggle Special Tiles Visible Button
    auto toggleSpecialTilesVisibleButton = frd::Maker::make(frd::Button());
    toggleSpecialTilesVisibleButton->setLabel("Toggle Special Tiles Visible");
    toggleSpecialTilesVisibleButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::toggleSpecialTilesVisible, this));
    theme.applyTheme(toggleSpecialTilesVisibleButton);

    //Rotate Clockwise Button
    auto rotateClockwiseButton = frd::Maker::make(frd::Button());
    rotateClockwiseButton->setLabel("Rotate Clockwise");
    rotateClockwiseButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::rotateSelectionClockwise, this));
    theme.applyTheme(rotateClockwiseButton);

    //Toggle Placement Grid Button
    auto togglePlacementGridButton = frd::Maker::make(frd::Button());
    togglePlacementGridButton->setLabel("Toggle Placement Grid");
    togglePlacementGridButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::togglePlacementGrid, this));
    theme.applyTheme(togglePlacementGridButton);

    //Create Special Tile Button
    auto createSpecialTileButton = frd::Maker::make(frd::Button());
    createSpecialTileButton->setLabel("Create Special Tile");
    createSpecialTileButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::createSpecialTile, this));
    theme.applyTheme(createSpecialTileButton);

    //Paint Tile Button
    auto paintTileButton = frd::Maker::make(frd::Button());
    paintTileButton->setLabel("Paint Tile");
    paintTileButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::paintTile, this));
    theme.applyTheme(paintTileButton);

    //Place Entity Button
    auto placeEntityButton = frd::Maker::make(frd::Button());
    placeEntityButton->setLabel("Place Entity");
    placeEntityButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::placeEntity, this));
    theme.applyTheme(placeEntityButton);

    //Replace Tile Type Button
    auto replaceTileTypeButton = frd::Maker::make(frd::Button());
    replaceTileTypeButton->setLabel("Replace Tile Type");
    replaceTileTypeButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::replaceTileType, this));
    theme.applyTheme(replaceTileTypeButton);

    //Set Aggressive Music Button
    auto setAggressiveMusicButton = frd::Maker::make(frd::Button());
    setAggressiveMusicButton->setLabel("Set Aggressive Music");
    setAggressiveMusicButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::setAggressiveMusic, this));
    theme.applyTheme(setAggressiveMusicButton);

    //Set Passive Music Button
    auto setPassiveMusicButton = frd::Maker::make(frd::Button());
    setPassiveMusicButton->setLabel("Set Passive Music");
    setPassiveMusicButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::setPassiveMusic, this));
    theme.applyTheme(setPassiveMusicButton);

    //Toggle Layer View Button
    auto toggleLayerViewButton = frd::Maker::make(frd::Button());
    toggleLayerViewButton->setLabel("Toggle Layer View");
    toggleLayerViewButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::toggleLayerView, this));
    theme.applyTheme(toggleLayerViewButton);

    //Add buttons to the editing buttons container
    editButtonsContainer->addWidget(clearLayerButton);
    editButtonsContainer->addWidget(fillLayerButton);
    editButtonsContainer->addWidget(createAnimatedTileButton);
    editButtonsContainer->addWidget(rotateClockwiseButton);
    editButtonsContainer->addWidget(toggleSpecialTilesVisibleButton);
    editButtonsContainer->addWidget(togglePlacementGridButton);
    editButtonsContainer->addWidget(createSpecialTileButton);
    editButtonsContainer->addWidget(paintTileButton);
    editButtonsContainer->addWidget(placeEntityButton);
    editButtonsContainer->addWidget(replaceTileTypeButton);
    editButtonsContainer->addWidget(setAggressiveMusicButton);
    editButtonsContainer->addWidget(setPassiveMusicButton);
    editButtonsContainer->addWidget(toggleLayerViewButton);

    //Add container to main menu
    mainMenu->addWidget(editButtonsContainer);


    //Now setup the layer selection buttons
    auto layerSelectContainer = frd::Maker::make(frd::Container());
    layerSelectContainer->setAllocation(Allocation::horizontal);
    layerSelectContainer->setSize({500, 50});
    for(unsigned int a = 0; a < mapLayerCount; a++)
    {
        auto cLayerButton = frd::Maker::make(frd::Button());
        theme.applyTheme(cLayerButton);
        cLayerButton->setLabel("Layer " + std::to_string(a));
        cLayerButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::selectLayer, this, a));
        layerSelectContainer->addWidget(cLayerButton);
    }
    mainMenu->addWidget(layerSelectContainer);




    //Now add the tile selection window
    auto tileSelect = std::shared_ptr<frd::EditorTilesheetView>(new frd::EditorTilesheetView());
    tileSelect->setTexture(ResourceManager::getInstance()->loadTexture("tilesheets/tiles.png"));
    tileSelect->setPosition({10, 60});
    mainMenu->addWidget(tileSelect);

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
        window.setPosition({50, 50});
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

        window.clear(sf::Color::White);
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
    case MessageBase::mapChangeEvent:
            //Generate placement helper grid if the map changes. Tile size *COULD* vary in the future.
            updatePlacementGrid();
        break;
    default:
        break;
    }
}

void Editor::drawMapOverlay(sf::RenderTarget& target)
{
    if(!window.isOpen())
        return;

    //Draw the red placement grid over the main window
    target.draw(mapPlacementGrid);
}

void Editor::clearLayer()
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(currentlySelectedLayer);

    //Iterate through each tile on this layer and set its textureRect to a transparent one
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        TileBase *tile = tempMap->getTile(currentlySelectedLayer, tileID); //Get a pointer to the current tile
        tempMap->removeTile(currentlySelectedLayer, tileID);
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

void Editor::updatePlacementGrid()
{
    //Create red grid out of sf::Lines
    unsigned int halfTileSize = MapManager::getInstance()->getCurrentMap()->getTileSize()/2;
    const sf::Vector2i &mapSize = MapManager::getInstance()->getCurrentMap()->getMapSizePixels();
    mapPlacementGrid = sf::VertexArray(sf::Lines, (mapSize.y/halfTileSize)+ 1 + (mapSize.x/halfTileSize) + 1);
    unsigned int cVertex = 0;

    //Generate horizontal lines
    for(unsigned int y = 0; y < mapSize.y/halfTileSize; y+=2)
    {
        mapPlacementGrid[cVertex].position = sf::Vector2f(0, y*halfTileSize);
        mapPlacementGrid[cVertex+1].position = sf::Vector2f(mapSize.x, y*halfTileSize);
        mapPlacementGrid[cVertex].color = sf::Color::Red;
        mapPlacementGrid[cVertex+1].color = sf::Color::Red;
        cVertex+=2;
    }

    //Generate vertical lines
    for(unsigned int x = 0; x < mapSize.x/halfTileSize; x+=2)
    {
        mapPlacementGrid[cVertex].position = sf::Vector2f(x*halfTileSize, 0);
        mapPlacementGrid[cVertex+1].position = sf::Vector2f(x*halfTileSize, mapSize.y);

        mapPlacementGrid[cVertex].color = sf::Color::Red;
        mapPlacementGrid[cVertex+1].color = sf::Color::Red;
        cVertex+=2;
    }
}

void Editor::selectLayer(unsigned int newLayerID)
{
    currentlySelectedLayer = newLayerID;
}



