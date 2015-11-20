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
        bool specialTilesVisible;
        sf::RenderTexture specialTileTexture;
        bool placingAnimatedTile;
        sf::Sprite placementPreviewSprite;

        //Current map related variables
        unsigned int tileSize;
        sf::Vector2i mapSizePixels;
        unsigned int layerCount;
        unsigned int previewRotation;
        bool defaultRotation;

        //Editor core functions
        void updatePlacementPreview();
        void updatePlacementGrid(); //Update the size and position of the red placement grid over the main window
        void placeSelected(unsigned int layer, unsigned int tileOffset); //Places the selected sprite selection on the map at given position
        void removeTile(unsigned int layer, unsigned int tileOffset); //Removes tile from loaded map
        void updateMap(); //Called if the map is changed, updates things like selection grid size and other things

        //Editor map functions
        //Editor settings change
        void selectLayer(unsigned int newLayerID);
        bool isGridEnabled();
        std::shared_ptr<frd::Container> specialTileCreationMenu;

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
