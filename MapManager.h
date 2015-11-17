#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Map;

class MapManager
{
    public:
        virtual ~MapManager();

        static std::shared_ptr<MapManager> getInstance();

        Map* getCurrentMap();
        void setCurrentMap(Map* cMap);
        Map* loadMap(const std::string &filepath);
        bool isMapLoaded(std::unique_ptr<Map> mapToCheck);

    protected:
    private:
        //Instance of manager
        static std::shared_ptr<MapManager> instance;

        //Private constructor for singletons
        MapManager();

        std::vector<std::unique_ptr<Map>> loadedMaps;
        Map* currentlyDisplayedMap;


};

#endif // MAPMANAGER_H
