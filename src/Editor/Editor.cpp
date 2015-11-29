#include "Editor.h"

#include "GUI/GUIManager.h"
#include "Messaging/MessageBase.h"
#include "Messaging/MessageHandler.h"
#include "Events/EventTypes.h"
#include "Map/MapManager.h"
#include "EditorTilesheetView.h"
#include "Map/Map.h"
#include "Map/StaticTile.h"
#include "Map/SpecialTileContainer.h"
#include "Map/AnimatedTile.h"
#include "Resources/ResourceManager.h"

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
    selectedTilePositions = {{blankTilePosition.x,blankTilePosition.y}};
    currentPlacementState = PlacementState::StateNormalTile;
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

    //Eye-dropper button
    auto eyeDropperButton = frd::Maker::make(frd::Button());
    eyeDropperButton->setLabel("Eye dropper");
    eyeDropperButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::eyeDropper, this));
    theme.applyTheme(eyeDropperButton);

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
    editButtonsContainer->addWidget(eyeDropperButton);

    //Add container to main menu
    mainMenu->addWidget(editButtonsContainer);


    //Now setup the layer selection buttons
    auto layerSelectContainer = frd::Maker::make(frd::Container());
    layerSelectContainer->setAllocation(Allocation::horizontal);
    layerSelectContainer->setSize({500, 50});
    layerSelectContainer->setPosition({0,600 - layerSelectContainer->getSize().y});

    std::shared_ptr<frd::Button> cLayerButton[mapLayerCount];
    for(unsigned int a = 0; a < mapLayerCount; a++)
    {
        cLayerButton[a] = frd::Maker::make(frd::Button());
    }

    for(unsigned int a = 0; a < mapLayerCount; a++)
    {
        theme.applyTheme(cLayerButton[a]);
        cLayerButton[a]->setLabel("Layer " + std::to_string(a));
        cLayerButton[a]->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::selectLayer, this, a));
/*      cLayerButton[a]->bindFunction(EventTypes::LeftClick_Up, std::bind([=]()
        {
            for(unsigned int i=0;i<mapLayerCount; i++)
            {
                cLayerButton[i]->setColor(sf::Color(0, 102, 0));
            }
            cLayerButton[a]->setColor(sf::Color::Red);
        }));*/
        cLayerButton[currentlySelectedLayer]->setColor(sf::Color::Red);
        layerSelectContainer->addWidget(cLayerButton[a]);
    }

    mainMenu->addWidget(layerSelectContainer);

    //Setup the save, load buttons container
    auto editorUtilitiesContainer = frd::Maker::make(frd::Container());
    editorUtilitiesContainer->setAllocation(Allocation::horizontal);
    editorUtilitiesContainer->setSize({500,500});
    editorUtilitiesContainer->allowAutomaticResizing(false);

    //Save button
    auto saveButton = frd::Maker::make(frd::Button());
    theme.applyTheme(saveButton);
    saveButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::saveMap, this));
    saveButton->setLabel("Save");

    //Save As button
    auto saveAsButton = frd::Maker::make(frd::Button());
    theme.applyTheme(saveAsButton);
    saveAsButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::saveMapAs, this));
    saveAsButton->setLabel("Save As");

    //Load button
    auto loadButton = frd::Maker::make(frd::Button());
    theme.applyTheme(loadButton);
    loadButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::loadMap, this));
    loadButton->setLabel("Load");

    //Reset button
    auto resetButton = frd::Maker::make(frd::Button());
    theme.applyTheme(resetButton);
    resetButton->bindFunction(EventTypes::LeftClick_Up, std::bind(&Editor::resetMap, this));
    resetButton->setLabel("Reset");

    editorUtilitiesContainer->addWidget(saveButton);
    editorUtilitiesContainer->addWidget(saveAsButton);
    editorUtilitiesContainer->addWidget(loadButton);
    editorUtilitiesContainer->addWidget(resetButton);

    mainMenu->addWidget(editorUtilitiesContainer);

    //Now add the tile selection window
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

    if(currentPlacementState == PlacementState::StateSpecialTile)
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

void Editor::clearLayerByIndex(unsigned int layerIndex)
{
    Map *tempMap = MapManager::getInstance()->getCurrentMap();

    //Get the number of tiles on the selected layer
    unsigned int tileCount = tempMap->getTileCount(layerIndex);

    //Iterate through each tile on this layer and remove it
    for(unsigned int tileID = 0; tileID < tileCount; tileID++) //Loop through each loaded tile
    {
        tempMap->removeTile(layerIndex, tileID);
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

    if(currentPlacementState == PlacementState::StateSpecialTile) //Placing special tile
    {
        cMap->specialTileContainer.registerSpecialTile(specialTileType, tileOffset, specialTileArgs);
        updateSpecialTileView();
    }
    else if(currentPlacementState == PlacementState::StateEyeDropper) //If picking tile
    {
        //Get clicked tile
        TileBase *cTile = cMap->getTile(layer, tileOffset);

        //Change placement state depending on tile type
        if(cTile->isAnimated())
            currentPlacementState = PlacementState::StateAnimatedTile;
        else
            currentPlacementState = PlacementState::StateNormalTile;

        //Set selected bounds to the clicked tiles
        if(cTile->isAnimated()) //Multiple frames, grab them all
        {
            selectedTilePositions.clear();
            AnimatedTile *animTile = dynamic_cast<AnimatedTile*>(cTile);
            switchInterval = animTile->getSwitchInterval();
            placementRotation = animTile->getRotation();
            for(unsigned int a = 0; a < animTile->getFrameCount(); a++)
            {
                selectedTilePositions.emplace_back(animTile->getFrame(a).left, animTile->getFrame(a).top);
            }
        }
        else //Only one frame, grab it
        {
            selectedTilePositions = {sf::Vector2u(cTile->getTextureRect().left, cTile->getTextureRect().top)};
            placementRotation = cTile->getRotation();
        }

        //Make sure that placement preview has updated
        updatePlacementPreview();
    }
    else if(currentPlacementState == PlacementState::StateAnimatedTile) //Placing animated tile
    {
        Map* cMap = MapManager::getInstance()->getCurrentMap();
        cMap->setTileAnimated(currentlySelectedLayer, tileOffset); //Ensure that the current frame is an animated tile

        AnimatedTile* animTile = dynamic_cast<AnimatedTile*>(cMap->getTile(currentlySelectedLayer, tileOffset));

        //Set the switch interval and rotation
        animTile->setSwitchInterval(switchInterval);
        animTile->setRotation(placementRotation);

        //Adding the frames to the animated tile
        for(auto &cFrame : selectedTilePositions)
        {
            animTile->addFrame(sf::IntRect(cFrame.x, cFrame.y, tileSize, tileSize));
        }
    }
    else //Placing normal tile
    {
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
                    //Clear old tile info
                    cMap->removeTile(currentlySelectedLayer, offsetAmount);

                    //Get tile
                    TileBase *tile = cMap->getTile(currentlySelectedLayer, offsetAmount);

                    //Set new tile info
                    tile->setTextureRect(sf::IntRect(topLeft.x + x*tileSize, topLeft.y + y*tileSize, tileSize, tileSize));
                    tile->setRotation(placementRotation);
                }
            }
        }
    }
}

void Editor::removeTile(unsigned int layer, unsigned int tileOffset)
{
    if(currentPlacementState != PlacementState::StateSpecialTile) //If special tiles are toggled off, remove normal tiles
        MapManager::getInstance()->getCurrentMap()->removeTile(layer, tileOffset);
    else //if special tiles are toggled on (visible), remove special tiles
    {
        MapManager::getInstance()->getCurrentMap()->specialTileContainer.removeSpecialTile(tileOffset);
        updateSpecialTileView();
    }
}
void Editor::saveMap()
{
    const std::string& mapName = MapManager::getInstance()->getCurrentMap()->getMapFilepath(); //Get the map name of the currently loaded map without the filepath

    if(mapName != "") //if the map name isnt blank
    {
        std::cout<<"Save Map, map name: "<<mapName<<std::endl;
        MapManager::getInstance()->getCurrentMap()->save(mapName); //save the current map to the its path
    }
    std::cout<<"Map saved at :"<<mapPath + mapName<<std::endl;
}

void Editor::saveMapAs()
{
    Dialog saveMapDialog("Save Map As");

    unsigned int saveMapEntryID = saveMapDialog.addEntry("Save as...");

    saveMapDialog.setOkayButton([&]()
    {
        const std::string& mapName = saveMapDialog.getEntryStringByID(saveMapEntryID); //Get the imputed map name by entry ID
        if(mapName != "") //if the map name isnt blank
        {
            std::cout<<"Save Map As, map name: "<<mapName<<std::endl;
            MapManager::getInstance()->getCurrentMap()->setMapName(mapName);
            MapManager::getInstance()->getCurrentMap()->save(mapName); //save the current map to the defined path
        }

        else
        {
            std::cout<<"Invalid map name entered! \n";
        }

        std::cout<<"Map saved at :"<<mapPath + mapName<<std::endl;
        saveMapDialog.close();//Close the dialog when done
    });

    saveMapDialog.setCancelButton([&]()
      {
         saveMapDialog.close();
      });

    saveMapDialog.update();
}

void Editor::loadMap()
{
    Dialog loadMapDialog("Load Map");

    unsigned int loadMapEntryID = loadMapDialog.addEntry("Load...");

    loadMapDialog.setOkayButton([&]()
    {
        const std::string& mapName = loadMapDialog.getEntryStringByID(loadMapEntryID);
        if(mapName != "") //If map name isn't blank
        {
            if(!MapManager::getInstance()->loadMap(mapName)) //Load the specified map
                std::cout<<"Map not found! \n";
            else
                std::cout<<"Loaded map:"<<mapPath + mapName<<std::endl;
        }
        else
        {
            std::cout<<"Invalid map name entered! \n";
        }
       loadMapDialog.close();
    });

    loadMapDialog.setCancelButton([&]()
    {
        loadMapDialog.close();
    });
    loadMapDialog.update();
}

void Editor::resetMap()
{
    //Confirm map reset

    Dialog confirmReset("Confirm Map Reset");

    confirmReset.addLabel("Are you sure you want to reset the map?");

    confirmReset.setOkayButton([&]()
    {
        //Loop through all the layers and clear them
        Map *cMap = MapManager::getInstance()->getCurrentMap();
        for(unsigned int cLayer=0; cLayer<cMap->getLayerCount(); cLayer++)
        {
            clearLayerByIndex(cLayer);
        }

        //Clear the special tile container
        //TODO: after changing storage to per map, iterate through the map and clear
        cMap->specialTileContainer.clear();

        updateSpecialTileView();
        confirmReset.close();
    });

    confirmReset.setCancelButton([&]()
    {
        confirmReset.close();
    });

    confirmReset.update();
}

void Editor::createAnimatedTile()
{
    currentPlacementState = PlacementState::StateAnimatedTile;

    //Select tiles to animate
    if(selectedTilePositions.size() > 1)
    {

        Dialog animatedTileDialog("Create Animated Tile");
        unsigned int switchIntervalEntryID = animatedTileDialog.addEntry("Frame Switch Interval");

        //Enter the switch interval and close the dialog
        auto switchFrameCallback = [&]()
        {
            switchInterval = stoul(animatedTileDialog.getEntryStringByID(switchIntervalEntryID));
            animatedTileDialog.close();
        };

        //Set the callback for the okay button
        animatedTileDialog.setOkayButton(switchFrameCallback);

        //Update the animated tile dialog box
        animatedTileDialog.update();
    }
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
        previewRotation = 0;
        defaultRotation = false;
    }

    placementPreviewSprite.setOrigin(placementPreviewSprite.getTextureRect().width/2, placementPreviewSprite.getTextureRect().height/2);

    placementPreviewSprite.setRotation(previewRotation * 90);
}

void Editor::toggleSpecialTilesVisible()
{
    //Toggle special tiles visible
    if(currentPlacementState == PlacementState::StateSpecialTile)
        currentPlacementState = PlacementState::StateNormalTile;
    else //Else ensure that we're no longer placing special tiles
    {
        currentPlacementState = PlacementState::StateSpecialTile;
        updateSpecialTileView();
    }
}

void Editor::updateSpecialTileView()
{
    specialTileTexture.clear(sf::Color::Transparent);
    if(currentPlacementState == PlacementState::StateSpecialTile) //If visible, generate a visual render texture from all of the tile types
    {
        //Collect some information that we'll need for generation
        SpecialTileContainer *specialTileContainer = &MapManager::getInstance()->getCurrentMap()->specialTileContainer;
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
    //Ensure that special tiles are visible
    currentPlacementState = PlacementState::StateSpecialTile;

    //Create a tile selection menu and assign binds
    Dialog dialog("Create Special Tile"); //Loads the dialog box in the constructor

    dialog.setCancelButton([&]()
     {
        dialog.close();
     });

    auto blockSpecialTile = [&]()
    {
        //Set selection to block tile
        currentPlacementState = PlacementState::StateSpecialTile;
        specialTileType = 0;
        specialTileArgs.clear();
        dialog.close();
    };

    auto warpSpecialTile = [&]()
    {
        //Set selection to warp tile
        currentPlacementState = PlacementState::StateSpecialTile;
        specialTileType = 1;
        specialTileArgs.clear();

        Dialog setWarpLocationBox("Set warp location"); //Bring up a dialog box asking for the tilePos

        //Define the entries to be placed in the dialog box
        unsigned int xCoordID = setWarpLocationBox.addEntry("X coordinate: ");
        unsigned int yCoordID = setWarpLocationBox.addEntry("Y coordinate: ");
        unsigned int mapNameID = setWarpLocationBox.addEntry("Map: ");

        unsigned int currentTileSize = MapManager::getInstance()->getCurrentMap()->getTileSize();

        //Define the function for accepting warp arguments
        auto setWarpArgs = [&]()
         {
             //Get the data in the entries by passing in the entryID
            const std::string& xCoord = setWarpLocationBox.getEntryStringByID(xCoordID);
            const std::string& yCoord = setWarpLocationBox.getEntryStringByID(yCoordID);
            const std::string& mapName = setWarpLocationBox.getEntryStringByID(mapNameID);

            if(xCoord != "" && yCoord !="" && mapName !="") // If the entries aren't just empty fields
            {
                if(!mapName.empty())
                {
                    specialTileArgs.emplace_back(mapName);
                    specialTileArgs.emplace_back(std::to_string(HelperClass::getTileIDFromPosition(sf::Vector2f(stoul(xCoord) * currentTileSize, stoul(yCoord) * currentTileSize))));
                }
                else
                    specialTileArgs.emplace_back(std::to_string(HelperClass::getTileIDFromPosition(sf::Vector2f(stoul(xCoord) * currentTileSize, stoul(yCoord) * currentTileSize), *MapManager::getInstance()->getCurrentMap())));
            }
            setWarpLocationBox.close();
         };

        //Set the okay button
        setWarpLocationBox.setOkayButton(setWarpArgs);
        setWarpLocationBox.setCancelButton([&]()
       {
          setWarpLocationBox.close();
       });

        setWarpLocationBox.update();

        dialog.close();
    };

    auto luaTrigger = [&]()
    {
        //Print a lua trigger
        std::cout<<"Set selection to Lua trigger. \n";
        currentPlacementState = PlacementState::StateSpecialTile;
        specialTileType = 2;
        dialog.close();
    };

    dialog.addList({"Block", "Warp", "Lua Trigger"}, {blockSpecialTile, warpSpecialTile, luaTrigger});

    dialog.update(); //While the dialog box is open, update it i.e listen for events, update buttons, take inputs, etc
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
    //Reset rotational values
    defaultRotation = true;
    placementRotation = 0;
    previewRotation = 0;

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
    currentPlacementState = PlacementState::StateNormalTile;

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

    if(currentPlacementState == PlacementState::StateSpecialTile)
        toggleSpecialTilesVisible();
}

void Editor::updatePlacementPreview()
{
    //Get int rect of the window
    sf::IntRect windowRect(sf::Vector2i(0,0), windowSize);

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

void Editor::eyeDropper()
{
    //Change placement mode to eye-dropper
    currentPlacementState = PlacementState::StateEyeDropper;
}
