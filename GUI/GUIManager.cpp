#include "GUIManager.h"
#include "FRDGUI.h"

//Define static instance once
std::shared_ptr<GUIManager> GUIManager::instance;

GUIManager::GUIManager(sf::Vector2i &windowSize, const std::string &fontFilePath, const sf::Color &defaultFontColour, unsigned int defaultFontSize)
{
    gameGui = std::shared_ptr<frd::FRDGUI>(new frd::FRDGUI(windowSize, fontFilePath, defaultFontColour, defaultFontSize));
    editorGui = std::shared_ptr<frd::FRDGUI>(new frd::FRDGUI(windowSize, fontFilePath, defaultFontColour, defaultFontSize));
}

std::shared_ptr<GUIManager> GUIManager::getInstance()
{
    if(!instance)
    {
        instance = std::shared_ptr<GUIManager>(new GUIManager(windowSize, guiFontPath, sf::Color::Yellow, 15));
    }
    return instance;
}

GUIManager::~GUIManager()
{

}

std::shared_ptr<frd::FRDGUI> GUIManager::getFRDGUIHandle()
{
    return gameGui;
}

std::shared_ptr<frd::FRDGUI> GUIManager::getEditorFRDGUIHandle()
{
    return editorGui;
}
