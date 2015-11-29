#ifndef EDITORTILESHEETVIEW_H
#define EDITORTILESHEETVIEW_H

#include <WidgetBase.h>
#include <functional>
#include <Container.h>
#include <Maker.h>

namespace frd
{
class EditorTilesheetView : public WidgetBase
{
public:
    /** Default constructor */
    EditorTilesheetView();
    /** Default destructor */
    virtual ~EditorTilesheetView();
    void setTilesheet(sf::Texture *texture);
    virtual void setTexture(sf::Texture* texture);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
    virtual void setPosition(const sf::Vector2f& newPosition);
    virtual void update();
    virtual bool handleEvent(const sf::Event& event);
    virtual void init(const sf::Font& defaultFont, unsigned int defaultCharacterSize, const sf::Color& defaultLabelColor, sf::Vector2i winSize);
protected:
private:
    std::shared_ptr<frd::Container> tileContainer;
    std::vector<std::shared_ptr<frd::Container>> tileRows;
    std::vector<std::shared_ptr<frd::Button>> tileButtons;

    std::vector<sf::Vector2u> selectedTiles;
    bool isDragSelecting;

    //Tile selection functions
    void selectTile(unsigned int x, unsigned int y, frd::Button *caller); //Adds a tile to the selection list
    void sendSelection(unsigned int x, unsigned int y); //Sends selection list to editor and clears local selection list
    sf::Vector2u clickedTile;
    void resetButtonOutlines(); //Resets the selection visual guide


};

}
#endif // EDITORTILESHEETVIEW_H
