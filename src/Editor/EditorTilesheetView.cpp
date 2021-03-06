#include "EditorTilesheetView.h"

#include "Map/MapManager.h"
#include "Map/Map.h"
#include "Input/InputHandler.h"
#include "Editor.h"

namespace frd
{
EditorTilesheetView::EditorTilesheetView()
    : WidgetBase()
{
    isDragSelecting = false;
}

EditorTilesheetView::~EditorTilesheetView()
{

}

void EditorTilesheetView::setTexture(sf::Texture* texture)
{
    //Initialise
    unsigned int tileSize = MapManager::getInstance()->getCurrentMap()->getTileSize();
    WidgetBase::setTexture(texture);

    //Setup main container
    tileContainer = frd::Maker::make(frd::Container());
    tileContainer->setSpacing({4.f, 4.f});
    tileContainer->setAllocation(Allocation::vertical);
    tileContainer->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));

    //Go through each row in the tilesheet
    for(unsigned int y = 0; y < texture->getSize().y; y += tileSize)
    {
        //Setup sub-containers for each row and store
        tileRows.emplace_back(frd::Maker::make(frd::Container()));
        tileContainer->addWidget(tileRows.back());

        //Get pointer to the current row and setup the container
        frd::Container *cTileRow = tileRows.back().get();
        cTileRow->setSpacing({4.f, 4.f});
        cTileRow->setAllocation(Allocation::horizontal);
        cTileRow->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y/tileSize));

        //Add each tile in the row to the container
        for(unsigned int x = 0; x < texture->getSize().x; x += tileSize)
        {
            //Create a button for each tile
            auto button = frd::Maker::make(frd::Button());
            button->getShape().setOutlineColor(sf::Color::Red);
            tileButtons.emplace_back(button);
            cTileRow->addWidget(button);

            //Setup said button
            button->setTexture(texture);
            button->getShape().setTextureRect(sf::IntRect(x, y, tileSize, tileSize));
            button->bindFunction(EventTypes::LeftClick_Down, std::bind([&, x, y, button]()
            {
                clickedTile = sf::Vector2u(x, y), isDragSelecting = true;
                selectTile(x, y, button.get());
            }));
            button->bindFunction(EventTypes::LeftClick_Up, std::bind(&EditorTilesheetView::sendSelection, this, x, y));
            button->bindFunction(EventTypes::MouseEntry, std::bind(&EditorTilesheetView::selectTile, this, x, y, button.get()));
        }
    }
}

void EditorTilesheetView::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    tileContainer->draw(target, states);
}

void EditorTilesheetView::setPosition(const sf::Vector2f& newPosition)
{
    WidgetBase::setPosition(newPosition);
    tileContainer->setPosition(newPosition);
}

void EditorTilesheetView::update()
{
    tileContainer->update();
}

bool EditorTilesheetView::handleEvent(const sf::Event& event)
{
    return tileContainer->handleEvent(event);
}

void EditorTilesheetView::init(const sf::Font& defaultFont, unsigned int defaultCharacterSize, const sf::Color& defaultLabelColor, sf::Vector2i winSize)
{
    tileContainer->init(defaultFont, defaultCharacterSize, defaultLabelColor, winSize);
}

void EditorTilesheetView::selectTile(unsigned int x, unsigned int y, frd::Button *caller)
{
    if(isDragSelecting)
    {
        //Add the tile to the selected list
        selectedTiles.emplace_back(x, y);

        //Highlight the selected rectangle
        caller->setColor(sf::Color(220,20,60));
    }

}

void EditorTilesheetView::sendSelection(unsigned int x, unsigned int y)
{
    if(clickedTile == sf::Vector2u(x, y)) //If the user clicked the tile and did not drag, send just this tile
    {
        Editor::getInstance()->setSelectedTile({{x,y}});
    }
    else
    {
        Editor::getInstance()->setSelectedTile(selectedTiles);
    }
    resetButtonOutlines();
    selectedTiles.clear();
    isDragSelecting = false;
}

void EditorTilesheetView::resetButtonOutlines()
{
    //Reset the colour of each tile so it looks like it's no longer selected
    for(auto &cButton : tileButtons)
    {
        cButton->setColor(sf::Color::White);
    }
}
}
