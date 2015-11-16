#include "EditorTilesheetView.h"

#include "MapManager.h"
#include "Map.h"

namespace frd
{
EditorTilesheetView::EditorTilesheetView()
{
    //ctor
}

EditorTilesheetView::~EditorTilesheetView()
{
    //dtor
}

void EditorTilesheetView::setPosition(const sf::Vector2f& newPosition)
{
    WidgetBase::setPosition(newPosition);
    spritesheet.setPosition(newPosition);
}

void EditorTilesheetView::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    updateRedGrid();
    target.draw(spritesheet, states);
    target.draw(redSelectionGrid, states);
}

void EditorTilesheetView::setTexture(sf::Texture* texture)
{
    spritesheet.setTexture(*texture);
}

void EditorTilesheetView::updateRedGrid()
{
    unsigned int halfTileSize = MapManager::getInstance()->getCurrentMap()->getTileSize()/2;
    const sf::Vector2u &mapSize = spritesheet.getTexture()->getSize();
    redSelectionGrid = sf::VertexArray(sf::Lines, (mapSize.y/halfTileSize)+ 1 + (mapSize.x/halfTileSize) + 1);
    unsigned int cVertex = 0;

    //Generate horizontal lines
    for(unsigned int y = 0; y < mapSize.y/halfTileSize; y+=2)
    {
        redSelectionGrid[cVertex].position = sf::Vector2f(getPosition().x, y*halfTileSize + getPosition().y);
        redSelectionGrid[cVertex+1].position = sf::Vector2f(mapSize.x + getPosition().x - halfTileSize*2, y*halfTileSize + getPosition().y);
        redSelectionGrid[cVertex].color = sf::Color::Red;
        redSelectionGrid[cVertex+1].color = sf::Color::Red;
        cVertex+=2;
    }

    //Generate vertical lines
    for(unsigned int x = 0; x < mapSize.x/halfTileSize; x+=2)
    {
        redSelectionGrid[cVertex].position = sf::Vector2f(x*halfTileSize + getPosition().x, getPosition().y);
        redSelectionGrid[cVertex+1].position = sf::Vector2f(x*halfTileSize + getPosition().x , mapSize.y + getPosition().y - halfTileSize*2);

        redSelectionGrid[cVertex].color = sf::Color::Red;
        redSelectionGrid[cVertex+1].color = sf::Color::Red;
        cVertex+=2;
    }
}

bool EditorTilesheetView::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::MouseButtonPressed && spritesheet.getTexture() != nullptr)
    {

    }
}

}
