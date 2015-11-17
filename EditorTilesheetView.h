#ifndef EDITORTILESHEETVIEW_H
#define EDITORTILESHEETVIEW_H

#include <WidgetBase.h>
#include <functional>

namespace frd
{
class EditorTilesheetView : public WidgetBase
{
    public:
        /** Default constructor */
        EditorTilesheetView(std::function<void(sf::IntRect)> tileSelectFunc);
        /** Default destructor */
        virtual ~EditorTilesheetView();
        virtual void setPosition(const sf::Vector2f& newPosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

        void setTexture(sf::Texture *texture);
        void processEvent(const sf::Event &event);
        virtual bool handleEvent(const sf::Event& event);
        virtual const sf::Vector2u getSize();
    protected:
    private:
        void updateRedGrid();

        sf::Sprite spritesheet;
        sf::VertexArray redSelectionGrid;
        std::function<void(sf::IntRect)> tileSelectFunction;
};

}
#endif // EDITORTILESHEETVIEW_H
