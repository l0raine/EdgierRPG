#include "Editor.h"

#include "GUI/GUIManager.h"
#include "MessageBase.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include "MapManager.h"
#include "EditorTilesheetView.h"
#include "Map.h"
#include "StaticTile.h"

std::shared_ptr<Editor> Editor::instance;

Editor::Editor()
{

}

Editor::~Editor()
{
    //dtor
}

std::shared_ptr<Editor> Editor::getInstance()
{
    if(instance == nullptr)
    {
        instance = std::shared_ptr<Editor>(new Editor());
    }
    return instance;
}

void Editor::load()
{
    //Setup UI
    frd::FRDGUI *gui = GUIManager::getInstance()->getEditorFRDGUIHandle().get();
    theme.load(themePath + "myTheme.txt");

    //Initialise some core editor variables
    currentlySelectedLayer = 0;
    gridEnabled = true;

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

    std::shared_ptr<frd::Button> cLayerButton[5];
    for(unsigned int a = 0; a < mapLayerCount; a++)
    {
        cLayerButton[a] = frd::Maker::make(frd::Button());
    }

    for(unsigned int a = 0; a < mapLayerCount; a++)
    {
        theme.applyTheme(cLayerButton[a]);
        cLayerButton[a]->setLabel("Layer " + std::to_string(a));
        cLayerButton[a]->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::selectLayer, this, a));
        cLayerButton[a]->bindFunction(EventTypes::LeftClick_Up, std::bind([=]()
        {
            for(unsigned int i=0;i<mapLayerCount; i++)
            {
                cLayerButton[i]->setColor(sf::Color(0, 102, 0));
            }
            cLayerButton[currentlySelectedLayer]->setColor(sf::Color::Green);
            cLayerButton[a]->setColor(sf::Color::Red);
        }));
        layerSelectContainer->addWidget(cLayerButton[a]);
    }

    mainMenu->addWidget(layerSelectContainer);

    //Now add the tile selection window
  //  tileSelect = std::shared_ptr<frd::EditorTilesheetView>(new frd::EditorTilesheetView(std::bind(&Editor::setSelectedTile, this, std::placeholders::_1)));
    tileSelect = std::shared_ptr<frd::EditorTilesheetView>(new frd::EditorTilesheetView());
    tileSelect->setTexture(ResourceManager::getInstance()->loadTexture("tilesheets/tiles.png"));
    tileSelect->setPosition({10, 60});
    mainMenu->addWidget(tileSelect);
}

void Editor::open()
{
    //Create an editor window if it's not already open
    if(!window.isOpen())
    {
        window.create(sf::VideoMode(windowSize.x, windowSize.y), "Editor Window", sf::Style::Close);
        window.setFramerateLimit(60);
        window.setKeyRepeatEnabled(false);
        window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - windowSize.x - 10,
                                    sf::VideoMode::getDesktopMode().height/4));
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
    //Process events that may be processed even if the editor is closed here
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
                if(isGridEnabled())
                    updatePlacementGrid();
            break;
        default:
            break;
    }

    if(!window.isOpen()) //Don't process events if editor is closed
        return;

    //Process events which should only be processed if the editor is open
    switch(message->getMessageType())
    {
        case MessageBase::mouseEvent:
        {

        }
        case MessageBase::mouseDragEvent:
        {
            MouseEvent *event = dynamic_cast<MouseEvent*>(message.get());
            unsigned int clickedTile = event->getClickedTileID(); //Get the ID of the tile clicked
            placeSelected(currentlySelectedLayer, clickedTile);
        }
    default:
        break;
    }
}

void Editor::drawMapOverlay(sf::RenderTarget& target)
{
    if(!window.isOpen())
        return;

    if(!isGridEnabled())
        return;

    //Draw the red placement grid over the main window
    target.draw(mapPlacementGrid);
}

void Editor::clearLayer()
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(currentlySelectedLayer);

    //Iterate through each tile on this layer and remove it
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        TileBase *tile = tempMap->getTile(currentlySelectedLayer, tileID); //Get a pointer to the current tile
        tempMap->removeTile(currentlySelectedLayer, tileID);
    }
}

void Editor::fillLayer()
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(currentlySelectedLayer);

    //Iterate through each tile on this layer and set its textureRect to the selected one
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        placeSelected(currentlySelectedLayer, tileID);
    }
}

void Editor::placeSelected(unsigned int layer, unsigned int tileOffset)
{
    Map *cMap = MapManager::getInstance()->getCurrentMap();
    unsigned int tileSize = cMap->getTileSize();

    if(selectedTilePositions.size() > 1) //If multiple selections
    {
        const sf::Vector2u &topLeft = selectedTilePositions[0];
        const sf::Vector2u &bottomRight = selectedTilePositions.back();
        const sf::Vector2u &rectangleSize = sf::Vector2u(bottomRight.x-topLeft.x + 32, bottomRight.y-topLeft.y + 32);

        sf::Vector2u selectionGrid[rectangleSize.x/32][rectangleSize.y/32];
        for(unsigned int x = 0; x < rectangleSize.x/32; x++)
        {
            for(unsigned int y = 0; y < rectangleSize.y/32; y++)
            {
                for(unsigned int cTile = 0; cTile < selectedTilePositions.size(); cTile++)
                {
                    if(selectedTilePositions[cTile] == sf::Vector2u((x*32) + topLeft.x, (y*32) + topLeft.y))
                    {
                        selectionGrid[x][y] = selectedTilePositions[cTile];
                    }
                }
            }
        }

        for(unsigned int x = 0; x < rectangleSize.x/32; x++)
        {
            for(unsigned int y = 0; y < rectangleSize.y/32; y++)
            {
                TileBase *tile = cMap->getTile(currentlySelectedLayer, tileOffset+(x)+(y*cMap->getMapSizeTiles().x));
                tile->setTextureRect(sf::IntRect(selectionGrid[x][y].x, selectionGrid[x][y].y, tileSize, tileSize));
            }
        }
    }
    else //Single tile selection
    {
        TileBase *tile = MapManager::getInstance()->getCurrentMap()->getTile(currentlySelectedLayer, tileOffset); //Get said tile
        tile->setTextureRect(sf::IntRect(selectedTilePositions[0].x, selectedTilePositions[0].y, tileSize, tileSize)); //Modify the tile to the selected one
    }

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
    if(isGridEnabled())
        gridEnabled = false;
    else gridEnabled = true;
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

void Editor::setSelectedTile(const std::vector<sf::Vector2u> &tileTexturePos)
{
    selectedTilePositions = tileTexturePos;

    for(auto &c : selectedTilePositions)
    {

    }

    if(tileTexturePos.size() > 1)
    {
        //selectedTilePositions[0] -= sf::Vector2u(32,32);
    }

}

bool Editor::isGridEnabled()
{
    return gridEnabled;
}







