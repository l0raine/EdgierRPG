#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <Theme.h>
#include <functional>

#include "GUI/GUIManager.h"
#include "MessageBase.h"
#include "MessageHandler.h"
#include "EventTypes.h"
#include "MapManager.h"

//Editor is the map editor for the game. This class stores its own self-contained window to act as the render target for the editor. And so it's FRDGUI instance is separated from the rest of the game.
class Editor
{
    public:
        /** Default constructor */
        Editor();
        /** Default destructor */
        virtual ~Editor();
        void open();
        void close();
        void update();
        void handleMessage(std::unique_ptr<MessageBase> &message);
        void drawMapOverlay(sf::RenderTarget &target); //Draw things like the placement grid over the main window
    protected:
    private:
        sf::RenderWindow window;
        frd::Theme theme;
        sf::VertexArray mapPlacementGrid;

        //Editor core variables
        unsigned int currentlySelectedLayer;

        //Editor core functions
        void updatePlacementGrid(); //Update the size and position of the red placement grid over the main window

        //Editor map functions
        //Editor settings change
        void selectLayer(unsigned int newLayerID);

        //Direct modification
        void clearLayer();
        void fillLayer();
        void createAnimatedTile();
        void rotateSelectionClockwise();
        void toggleSpecialTilesVisible();
        void togglePlacementGrid();
        void createSpecialTile();
        void paintTile();
        void placeEntity();
        void replaceTileType();
        void setAggressiveMusic();
        void setPassiveMusic();
        void toggleLayerView();
};

#endif // EDITOR_H
