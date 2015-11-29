#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "FRDGUI.h"
#include "Utils/Globals.h"


class GUIManager
{
    public:
        virtual ~GUIManager();//Destructor

        static std::shared_ptr<GUIManager> getInstance();

        std::shared_ptr<frd::FRDGUI> getFRDGUIHandle();
        std::shared_ptr<frd::FRDGUI> getEditorFRDGUIHandle();
    protected:
    private:
        static std::shared_ptr<GUIManager> instance;//Single instance of GUIManager

        GUIManager(sf::Vector2i &windowSize, const std::string &fontFilePath, const sf::Color &defaultFontColour, unsigned int defaultFontSize);//Private constructor for Singleton
        std::shared_ptr<frd::FRDGUI> gameGui;
        std::shared_ptr<frd::FRDGUI> editorGui;

        std::vector<frd::Menu> menuList;
};

#endif // GUIMANAGER_H
