#include "Editor.h"

#include "GUI/GUIManager.h"
#include "MessageBase.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include "MapManager.h"
#include "EditorTilesheetView.h"
#include "Map.h"
#include "StaticTile.h"
#include "SpecialTileContainer.h"
#include "AnimatedTile.h"

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
    placementRotation = 0;
    layerViewEnabled = false;
    specialTilesVisible = false;
    selectedTilePositions = {{blankTilePosition.x,blankTilePosition.y}};
    placingAnimatedTile = false;
    defaultRotation = true;

    //Setup menu to store the main page of the editor
    mainMenu = frd::Maker::make(frd::Menu());
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
        window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2 - windowSize.x - 10, sf::VideoMode::getDesktopMode().height/4));
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
        {
            updateMap();
        break;
        }
        default:
            break;
    }

    if(!window.isOpen()) //Don't process events if editor is closed
        return;

    const sf::Vector2u &topLeft = selectedTilePositions[0];
    const sf::Vector2u &bottomRight = selectedTilePositions.back();
    const sf::Vector2u &rectangleSize = sf::Vector2u(bottomRight.x-topLeft.x + tileSize, bottomRight.y-topLeft.y + tileSize);

    //Process events which should only be processed if the editor is open
    switch(message->getMessageType())
    {
        case MessageBase::mouseMoveEvent:
        {
            //Update tile placement preview
            MouseEvent *event = dynamic_cast<MouseEvent*>(message.get());
            placementPreviewSprite.setPosition(MapManager::getInstance()->getCurrentMap()->getTile(0, HelperClass::getTileIDFromPosition(sf::Vector2f(event->getMousePosition().x, event->getMousePosition().y)))->getPosition()); //Set the position to draw at

            if(placementPreviewSprite.getRotation() > 0)
            {
                placementPreviewSprite.move(rectangleSize.x/2, rectangleSize.y/2);
            }
            if(!defaultRotation && placementPreviewSprite.getRotation() == 0)
                placementPreviewSprite.move(rectangleSize.x/2, rectangleSize.y/2);
            break;
        }
        case MessageBase::mouseDragEvent:
        {
            //Place tiles/remove tiles if dragging
            MouseEvent *event = dynamic_cast<MouseEvent*>(message.get());
            if(event->getType() == sf::Mouse::Left) //If left click, place tile
                placeSelected(currentlySelectedLayer, event->getClickedTileID());
            else if(event->getType() == sf::Mouse::Right) //If right click, remove tile
                removeTile(currentlySelectedLayer, event->getClickedTileID());
            break;
        }
        case MessageBase::mouseEvent:
        {
            //Place tiles/remove tiles if click event
            MouseEvent *event = dynamic_cast<MouseEvent*>(message.get());
            if(event->getType() == sf::Mouse::Left) //If left click, place tile
                placeSelected(currentlySelectedLayer, event->getClickedTileID());
            else if(event->getType() == sf::Mouse::Right) //If right click, remove tile
                removeTile(currentlySelectedLayer, event->getClickedTileID());
            break;
        }
    default:
        break;
    }
}

void Editor::drawMapOverlay(sf::RenderTarget& target)
{
    if(!window.isOpen()) //Don't draw if the editor is closed
        return;

    if(isGridEnabled()) //Draw the red placement grid over the main window
        target.draw(mapPlacementGrid);

    target.draw(placementPreviewSprite);

    if(specialTilesVisible)
        target.draw(sf::Sprite(specialTileTexture.getTexture()));
}

void Editor::clearLayer()
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(currentlySelectedLayer);

    //Iterate through each tile on this layer and remove it
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
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
    //Place the selection to the map

    //Get the map
    Map *cMap = MapManager::getInstance()->getCurrentMap();

    //Calculate some information about the selected tiles for placement.
    //Here we are calculating a rectangle from the first and last selected tiles and then finding which selected tile goes where in the rectangle
    //Then converting this rectangle position into actual tile positions and placing
    const sf::Vector2u &topLeft = selectedTilePositions[0];
    const sf::Vector2u &bottomRight = selectedTilePositions.back();
    const sf::Vector2u &rectangleSize = sf::Vector2u(bottomRight.x-topLeft.x + tileSize, bottomRight.y-topLeft.y + tileSize);

    //Place each tile in relation to the rectangle
    for(unsigned int x = 0; x < rectangleSize.x/tileSize; x++)
    {
        for(unsigned int y = 0; y < rectangleSize.y/tileSize; y++)
        {
            //Don't place tile outside of map
            unsigned int offsetAmount = tileOffset+(x)+(y*cMap->getMapSizeTiles().x);
            if(offsetAmount < cMap->getTileCount(currentlySelectedLayer))
            {
                TileBase *tile = cMap->getTile(currentlySelectedLayer, offsetAmount);
                tile->setTextureRect(sf::IntRect(topLeft.x + x*tileSize, topLeft.y + y*tileSize, tileSize, tileSize));
                tile->setRotation(placementRotation);
            }
        }
    }
}

void Editor::removeTile(unsigned int layer, unsigned int tileOffset)
{
    MapManager::getInstance()->getCurrentMap()->removeTile(layer, tileOffset);
}

void Editor::createAnimatedTile()
{
    placingAnimatedTile = true;
}

void Editor::rotateSelectionClockwise()
{
    //Rotate the placed tile
    placementRotation++;
    previewRotation++;

    if(placementRotation > 3)
    {
        placementRotation = 0;
    }

    if(previewRotation > 3)
    {
        std::cout<<"prev rot > 3 \n";
        previewRotation = 0;
        defaultRotation = false;
    }

    std::cout<< previewRotation<<std::endl;

    placementPreviewSprite.setOrigin(placementPreviewSprite.getTextureRect().width/2, placementPreviewSprite.getTextureRect().height/2);

    placementPreviewSprite.setRotation(previewRotation * 90);
}

void Editor::toggleSpecialTilesVisible()
{
    specialTilesVisible = !specialTilesVisible;
    specialTileTexture.clear(sf::Color::Transparent);
    if(specialTilesVisible) //If visible, generate a visual render texture from all of the tile types
    {
        //Collect some information that we'll need for generation
        SpecialTileContainer *specialTileContainer = SpecialTileContainer::getInstance().get();
        const unsigned int specialTileCount = specialTileContainer->getSpecialTileCount();

        //Setup the text that will be used for the label and some generic values
        sf::Text tileLabel;
        tileLabel.setFont(ResourceManager::getInstance()->getDefaultFont());
        tileLabel.setCharacterSize(tileSize/2);
        tileLabel.setStyle(sf::Text::Bold);

        //For each special tile, generate its tile
        for(unsigned int a = 0; a < specialTileCount; a++)
        {
            //Choose the correct label for the tile
            const SpecialTileContainer::SpecialTile &cTile = specialTileContainer->getSpecialTile(a);

            //Set text properties
            tileLabel.setString(cTile.getTileVisualID());
            tileLabel.setColor(cTile.getTileVisualColour());

            //Centre
            auto tilePos = HelperClass::getPositionFromTileID(cTile.position, *MapManager::getInstance()->getCurrentMap());
            auto textRect = tileLabel.getLocalBounds();
            tileLabel.setPosition(static_cast<int>(tilePos.x+tileSize/2 - (textRect.left + textRect.width/2.0f)), static_cast<int>(tilePos.y+tileSize/2 - (textRect.top  + textRect.height/2.0f)));

            specialTileTexture.draw(tileLabel);
        }
        specialTileTexture.display();
    }
}

void Editor::togglePlacementGrid()
{
    if(isGridEnabled())
        gridEnabled = false;
    else
        gridEnabled = true;
}

void Editor::createSpecialTile()
{
    //Create a tile selection menu and assign binds
    if(specialTileCreationMenu)
        specialTileCreationMenu->clear();
    else
    {
        std::cout << "\nCreated container!";
        specialTileCreationMenu = frd::Maker::make(frd::Container());
        specialTileCreationMenu->setSize({200, 200});
        specialTileCreationMenu->setPosition({400, 400});
        specialTileCreationMenu->setAllocation(Allocation::vertical);
        specialTileCreationMenu->setColor(sf::Color::Red);
        mainMenu->addWidget(specialTileCreationMenu);
    }


    specialTileCreationMenu->setVisible(true);
}

void Editor::paintTile()
{

}

void Editor::placeEntity()
{

}

void Editor::replaceTileType() //Use first and last selection from EditorTilesheetView
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(currentlySelectedLayer);

    //Iterate through each tile on this layer and remove it
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        TileBase *tile = tempMap->getTile(currentlySelectedLayer, tileID);
        if(tile->getTextureRect().left == static_cast<int>(selectedTilePositions.front().x) && tile->getTextureRect().top == static_cast<int>(selectedTilePositions.front().y)) //If tile matches first selection, replace with second selection
            tile->setTextureRect(sf::IntRect(selectedTilePositions.back().x, selectedTilePositions.back().y, tileSize, tileSize));
    }
}

void Editor::setAggressiveMusic()
{

}

void Editor::setPassiveMusic()
{

}

void Editor::toggleLayerView()
{
    layerViewEnabled = !layerViewEnabled;
    if(layerViewEnabled)
    {
        MapManager::getInstance()->getCurrentMap()->setLayerDrawRange(currentlySelectedLayer, currentlySelectedLayer+1);
    }
    else
    {
        MapManager::getInstance()->getCurrentMap()->setLayerDrawRange(0, MapManager::getInstance()->getCurrentMap()->getLayerCount());
    }
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
    //Update selection
    selectedTilePositions = tileTexturePos;
    if(selectedTilePositions.size() > 1) //If multiple tiles selected
    {
        //If rectangle points are upside down (x or y), then flip them
        sf::Vector2u &first = selectedTilePositions.front();
        sf::Vector2u &last = selectedTilePositions.back();
        if(first.x > last.x)
        {
            auto buffer = first.x;
            first.x = last.x;
            last.x = buffer;
        }
        if(first.y > last.y)
        {
            auto buffer = first.y;
            first.y = last.y;
            last.y = buffer;
        }
    }

    //Update placement preview
    placingAnimatedTile = false;
    updatePlacementPreview();
}

bool Editor::isGridEnabled()
{
    return gridEnabled;
}

void Editor::updateMap()
{
    //Generate placement helper grid if the map changes. Tile size *COULD* vary in the future.
    updatePlacementGrid();

    //Resize special tile render texture
    mapSizePixels = MapManager::getInstance()->getCurrentMap()->getMapSizePixels();
    specialTileTexture.create(mapSizePixels.x, mapSizePixels.y);
    tileSize = MapManager::getInstance()->getCurrentMap()->getTileSize();
    layerCount = MapManager::getInstance()->getCurrentMap()->getLayerCount();

    //Update some map-specific data
    if(layerViewEnabled)
        toggleLayerView();

    if(specialTilesVisible)
        toggleSpecialTilesVisible();
}

void Editor::updatePlacementPreview()
{
    //Get int rect of the window
    sf::IntRect windowRect(sf::Vector2i(0,0), windowSize);
    Map *cMap = MapManager::getInstance()->getCurrentMap();

    unsigned int previewTileID = HelperClass::getTileIDFromPosition(sf::Vector2f(sf::Mouse::getPosition(*gameWindow).x, sf::Mouse::getPosition(*gameWindow).y));

    TileBase *cTile = cMap->getTile(0, previewTileID); //Doesnt matter which layer, since we aren't placing the tile

    //Get texture to draw
    const sf::Vector2u &topLeft = selectedTilePositions[0];
    const sf::Vector2u &bottomRight = selectedTilePositions.back();
    const sf::Vector2u &rectangleSize = sf::Vector2u(bottomRight.x-topLeft.x + tileSize, bottomRight.y-topLeft.y + tileSize);

    sf::Texture* tilePreviewTexture = ResourceManager::getInstance()->getLoadedTexture("tilesheets/tiles.png"); //Load the texture from memory
    placementPreviewSprite.setTexture(*tilePreviewTexture); //Generate sprite to draw
    placementPreviewSprite.setTextureRect(sf::IntRect(topLeft.x, topLeft.y, rectangleSize.x, rectangleSize.y));
    placementPreviewSprite.setOrigin(0,0);
    placementPreviewSprite.setRotation(placementRotation * 90);
    placementPreviewSprite.setColor(sf::Color(placementPreviewSprite.getColor().r, placementPreviewSprite.getColor().g, placementPreviewSprite.getColor().b, 180));
}
