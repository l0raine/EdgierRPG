#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <Theme.h>
#include <functional>

#include "EditorTilesheetView.h"
#include "Dialog.h"

class MessageBase;

//Editor is the map editor for the game.
//This class stores its own self-contained window to act as the render target for the editor.
//And so it's FRDGUI instance is separated from the rest of the game.
class Editor
{
    public:
        /** Default destructor */
        virtual ~Editor();
        void open();
        void load();
        void close();
        void update();
        static std::shared_ptr<Editor> getInstance();
        void handleMessage(std::unique_ptr<MessageBase> &message);
        void drawMapOverlay(sf::RenderTarget &target); //Draw things like the placement grid over the main window
        void setSelectedTile(const std::vector<sf::Vector2u> &tileTexturePos); //Sets the selected placement tiles
    protected:

    private:
        /** Default constructor */
        Editor();
        static std::shared_ptr<Editor> instance;

        //GUI elements
        std::shared_ptr<frd::Menu> mainMenu;

        enum PlacementState //What tile type is currently being placed?
        {
            StateSpecialTile, StateAnimatedTile, StateNormalTile, StateEyeDropper
        };

        //Editor core variables
        sf::RenderWindow window;
        frd::Theme theme;
        sf::VertexArray mapPlacementGrid;
        unsigned int currentlySelectedLayer;
        std::shared_ptr<frd::EditorTilesheetView> tileSelect;
        std::vector<sf::Vector2u> selectedTilePositions;
        unsigned int placementRotation;
        bool gridEnabled;
        bool layerViewEnabled;
        sf::RenderTexture specialTileTexture;
        sf::Sprite placementPreviewSprite;
        PlacementState currentPlacementState;


        //Current map related variables
        unsigned int tileSize;
        sf::Vector2i mapSizePixels;
        unsigned int layerCount;
        unsigned int previewRotation;
        bool defaultRotation;
        unsigned int switchInterval;

        //Editor core functions
        void updatePlacementPreview(); //Update the placement preview that appears when dragging
        void updatePlacementGrid(); //Update the size and position of the red placement grid over the main window
        void placeSelected(unsigned int layer, unsigned int tileOffset); //Places the selected sprite selection on the map at given position
        void removeTile(unsigned int layer, unsigned int tileOffset); //Removes tile from loaded map
        void updateMap(); //Called if the map is changed, updates things like selection grid size and other things
        void updateSpecialTileView(); //Re-render the special tiles
        void eyeDropper(); //Eye-dropper or whatever it's called.

        //Editor map functions
        void selectLayer(unsigned int newLayerID);
        void saveMap();
        void saveMapAs();
        void loadMap();
        void resetMap();
        bool isGridEnabled();

        //Direct modification
        void clearLayer();
        void clearLayerByIndex(unsigned int layerIndex);

        //Fill the selected layer with a selected tile type
        void fillLayer();
        void createAnimatedTile();

        //Rotate the selected tile clockwise
        void rotateSelectionClockwise();

        //Toggle the visibility of special tiles, i.e Block, Warp, Lua Triggers, etc
        void toggleSpecialTilesVisible();

        //Toggles red placeable grids
        void togglePlacementGrid();

        //Create a special tile
        void createSpecialTile();
        std::vector<std::string> specialTileArgs;
        unsigned int specialTileType;

        void paintTile();
        void placeEntity();
        void replaceTileType();
        void setAggressiveMusic();
        void setPassiveMusic();

        //Toggles visibility of tiles on the selected layer
        void toggleLayerView();
};

#endif // EDITOR_H
