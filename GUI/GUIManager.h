#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "FRDGUI.h"


class GUIManager
{
    public:
        GUIManager(sf::Vector2i &windowSize, const std::string &fontFilePath, const sf::Color &defaultFontColour, unsigned int defaultFontSize);
        virtual ~GUIManager();

        frd::FRDGUI* getGUIRef();
    protected:
    private:
        frd::FRDGUI *gui;

        std::vector<frd::Menu> menuList;
};

#endif // GUIMANAGER_H
