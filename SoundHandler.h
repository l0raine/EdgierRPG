#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <string>
#include <map>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <memory>

#include <SFML/Audio.hpp>

enum soundType //What type of sound is it, a music, or a sound?
{
    music, sound
};

enum playlistProperty //Playlist properties to change
{
    shouldRandom, shouldLoop
};

struct soundContainer //Contains a single sound and its information
{
    std::unique_ptr<sf::Sound> sound;
    std::unique_ptr<sf::Music> music;
    sf::SoundBuffer buffer;
    soundType type;
    bool isActive;
    unsigned int lastPlayTime;
};

struct playList //Contains a single playlist
{
    std::vector<std::string> filenames;
    bool shouldLoop;
    bool playRandomly;
    std::string currentlyPlaying = "null";
};

struct fadeInfo //Contains information of a single active fade
{
    soundContainer *sound; //Pointer to sound to modify
    float targetVolume;
};

class SoundHandler //The main sound handling class. Contains and manages ALL sounds.
{
public:
    //Class functions
    void update(); //Updates fades

    //Constructor/Deconstructor
    SoundHandler();
    virtual ~SoundHandler();

    //Generic sound handling functions
    bool loadSound(const std::string &filename, bool initImmediately); //Loads a sound, key = filename
    bool loadMusic(const std::string &filename, bool initImmediately); //Loads a music, key = filename
    bool play(const std::string &filename); //Plays sound/music in given key if it exists
    void pause(const std::string &filepath); //Pauses sound/music in given key if it exists
    void resume(const std::string &filepath); //Resumes paused sound/music in given key if it exists
    void setVolume(const std::string &filepath, float vol); //Sets the volume of the sound/music in given key if it exists. Should not be used, volumes should be managed by the global settings
    void setGlobalSoundVolume(float target); //Sets all sounds volume
    void setGlobalMusicVolume(float target);  //Sets all musics volume
    float getGlobalSoundVolume(); //Gets the global sound volume
    float getGlobalMusicVolume(); //Gets the global music volume

    //Snazzy sound handling functions :D
    bool fadeToVolume(const std::string &filepath, float vol); //Fades a volume to a set volume
    bool fadeOut(const std::string &filepath); //Fades a volume out
    bool fadeIn(const std::string &filepath); //Fades a volume in

    //Playlist functions
    void createPlaylist(const std::string& playlistName, bool shouldLoop, bool shuffle);
    void addToPlaylist(const std::string& playlistName, const std::string& soundFilepath, soundType type);
    void destroyPlaylist(const std::string& playlistName);
    void clearPlaylist(const std::string& playlistName);
    void setPlaylistProperty(const std::string& playlistName, playlistProperty propertyType, bool tf);
    void removeFromPlaylist(const std::string& playlistName, const std::string& soundFilepath);
    const std::string& getPlayingFromPlaylist(const std::string& playlistName);
    void setPlayingToPlaylist(const std::string& playlistname, const std::string& soundFilepath);
    void pausePlaylist(const std::string& playlistName);
    void playPlaylist(const std::string& playlistName);
    bool loadPlaylistFromDatabase(const std::string& databaseFilepath);

private:
    //Helper functions
    bool keyExists(const std::string &filename); //Returns true/false depending on if the given key exists
    void eraseKey(const std::string &filename); //Erase the given key and its contained music/sound
    bool activateSound(const std::string &filename); //Activates a sound, loading it into memory and changing its state
    void deactivateSound(const std::string &filename); //Deactivates a sound, sets it to inactive and deletes it
    void cullSounds(); //Iterates through active sounds and removes sounds if needed

    //Containers
    std::unordered_map<std::string, soundContainer> loadedSounds; //Contains loaded sounds and music
    std::unordered_map<std::string, playList> playlists; //Contains playlist information. The actual sounds are stored in the loadedSounds container, just referenced by this.
    std::unordered_map<std::string, fadeInfo> activeFades; //Contains all sounds which are being faded
    std::vector<std::string> activePlaylists; //Contains active playlist information (currently playing)


    //Internal sound count to ensure that active sound count does not exceed the limit
    unsigned short soundCount;

    //Internal global volume
    float globalSoundVolume;
    float globalMusicVolume;

    //Class references
    sf::Clock timeL; //Reference to the time handling class to help with culling
    sf::Clock updateClock; //Keeps track of how long ago the last update call was. Temporary as Clock is broken atm.

    float lastUpdateTime;
    std::string errorValue;
};

#endif

