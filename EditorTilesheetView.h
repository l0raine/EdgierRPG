#ifndef EDITORTILESHEETVIEW_H
#define EDITORTILESHEETVIEW_H

#include <WidgetBase.h>

namespace frd
{
class EditorTilesheetView : public WidgetBase
{
    public:
        /** Default constructor */
        EditorTilesheetView();
        /** Default destructor */
        virtual ~EditorTilesheetView();
        virtual void setPosition(const sf::Vector2f& newPosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

        void setTexture(sf::Texture *texture);
    protected:
    private:
        void updateRedGrid();

        sf::Sprite spritesheet;
        sf::VertexArray redSelectionGrid;
};

}
#endif // EDITORTILESHEETVIEW_H
