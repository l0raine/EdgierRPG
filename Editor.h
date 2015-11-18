#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <Theme.h>
#include <functional>

#include "EditorTilesheetView.h"

class MessageBase;

//Editor is the map editor for the game.
//This class stores its own self-contained window to act as the render target for the editor.
//And so it's FRDGUI instance is separated from the rest of the game.
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
        std::shared_ptr<frd::EditorTilesheetView> tileSelect;
        sf::IntRect selectedTileRect;
        bool gridEnabled;

        //Editor core functions
        void updatePlacementGrid(); //Update the size and position of the red placement grid over the main window
        void setSelectedTile(sf::IntRect tileTexturePos); //Sets the selected placement tile

        //Editor map functions
        //Editor settings change
        void selectLayer(unsigned int newLayerID);
        bool isGridEnabled();

        //Direct modification
        void clearLayer();
        void fillLayer();
        void createAnimatedTile();
        void rotateSelectionClockwise();
        void toggleSpecialTilesVisible();

        //Toggles red placeable grids
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
