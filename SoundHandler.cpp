#include "SoundHandler.h"
#include "Globals.h"

SoundHandler::SoundHandler()
{
    soundCount = 0;
    lastUpdateTime = 0;
    errorValue = "error";
    globalMusicVolume = 100.f;
    globalSoundVolume = 100.f;
    inactiveSoundTimeout = 100000;
}

SoundHandler::~SoundHandler()
{

}

void SoundHandler::update()
{
    if(updateClock.getElapsedTime().asMilliseconds() > 2)
    {
        //NOTE FOR DEVELOPERS - Please do not touch the volume fading section without consulting me (Fred) first
        //As there's a few delicate bits which will fail if tinkered with
        //It won't be a visible fail, but will cause the sound system to become unstable over time.

        for(auto iter = activeFades.begin(); iter != activeFades.end();)
        {
            //Uh oh... this looks kind of complicated - Better explain it...
            //If the sound type is a music and the sound IS active
            if(iter->second.sound->isActive == true && iter->second.sound->type == soundType::music)
            {
                if(iter->second.targetVolume < iter->second.sound->music->getVolume())
                {
                    iter->second.sound->music->setVolume(iter->second.sound->music->getVolume()-2.F);
                }
                else if(iter->second.targetVolume > iter->second.sound->music->getVolume())
                {
                    iter->second.sound->music->setVolume(iter->second.sound->music->getVolume()+2.F);
                }
                //Check to see if fade has finished
                float difference = iter->second.targetVolume-iter->second.sound->music->getVolume();
                if(difference > -3 && difference < 3)
                {
                    iter->second.sound->music->setVolume(iter->second.targetVolume);
                    iter = activeFades.erase(iter);
                }
                else
                {
                    iter++;
                }
            } //If the sound type is sound and the sound IS active
            else if(iter->second.sound->isActive == true && iter->second.sound->type == soundType::sound)
            {
                //If target volume is smaller than current volume, reduce volume by one
                if(iter->second.targetVolume < iter->second.sound->sound->getVolume())
                {
                    iter->second.sound->sound->setVolume(iter->second.sound->sound->getVolume()-2.F);
                }//Else If target volume is larger than current volume, increase volume by one
                else if(iter->second.targetVolume > iter->second.sound->sound->getVolume())
                {
                    iter->second.sound->sound->setVolume(iter->second.sound->sound->getVolume()+2.F);
                }

                //Check to see if fade has finished
                float difference = iter->second.targetVolume-iter->second.sound->sound->getVolume();
                if(difference > -3 && difference < 3)
                {
                    iter->second.sound->sound->setVolume(iter->second.targetVolume);
                    iter = activeFades.erase(iter);
                }
                else
                {
                    iter++;
                }

            } //Else, sound may of been destroyed or something, so delete the fade
            else
            {
                iter = activeFades.erase(iter);
            }
        }

        //Check playlists
        for(auto iter = activePlaylists.begin(); iter != activePlaylists.end();)
        {
            bool ic = true;
            auto &cPlaylistIter = playlists[*iter];
            auto &loadedSoundIter = loadedSounds[cPlaylistIter.currentlyPlaying];
            if(loadedSoundIter.type == soundType::sound)
            {
                if(loadedSoundIter.sound != nullptr)
                {
                    if(loadedSoundIter.sound->getStatus() != sf::Sound::Status::Playing)
                    {
                        //It's not playing, so it must have stopped. Play the next one if necessary
                        auto currentSoundIter = std::find(cPlaylistIter.filenames.begin(), cPlaylistIter.filenames.end(), cPlaylistIter.currentlyPlaying);
                        if(currentSoundIter == cPlaylistIter.filenames.end())
                        {
                            //Internal error?!?
                            std::cerr << "\nSOUND HANDLER ERROR" << std::endl;
                        }
                        else
                        {
                            //End of playlist met
                            if(cPlaylistIter.shouldLoop && cPlaylistIter.filenames.size() > 0)
                            {
                                currentSoundIter++;
                                if(currentSoundIter == cPlaylistIter.filenames.end())
                                {
                                    //Restart playlist as it is looping
                                    int idToPlay = 0;
                                    if(cPlaylistIter.playRandomly)
                                        idToPlay = rand() % cPlaylistIter.filenames.size() + 0;

                                    cPlaylistIter.currentlyPlaying = cPlaylistIter.filenames[idToPlay];
                                }
                                else
                                {
                                    if(cPlaylistIter.playRandomly)
                                        cPlaylistIter.currentlyPlaying = cPlaylistIter.filenames[rand() % cPlaylistIter.filenames.size() + 0];
                                    else
                                        cPlaylistIter.currentlyPlaying = *currentSoundIter;
                                }
                                play(cPlaylistIter.currentlyPlaying);
                            }
                            else
                            {
                                iter = activePlaylists.erase(iter); //Remove from active playlists
                                ic = false;
                            }
                        }
                    }
                }
                else
                {
                    //Invalid currently playing so load it again
                    play(cPlaylistIter.currentlyPlaying);
                }
            }
            else if(loadedSoundIter.type == soundType::music)
            {
                if(loadedSoundIter.music != nullptr)
                {
                    if(loadedSoundIter.music->getStatus() != sf::Music::Status::Playing)
                    {
                        //It's not playing, so it must have stopped. Play the next one if necessary
                        auto currentSoundIter = std::find(cPlaylistIter.filenames.begin(), cPlaylistIter.filenames.end(), cPlaylistIter.currentlyPlaying);
                        if(currentSoundIter == cPlaylistIter.filenames.end())
                        {
                            //Internal error?!?
                            std::cout << "\nSOUND HANDLER ERROR!?!?!?";
                        }
                        else
                        {
                            //End of playlist met
                            if(cPlaylistIter.shouldLoop && cPlaylistIter.filenames.size() > 0)
                            {
                                currentSoundIter++;
                                if(currentSoundIter == cPlaylistIter.filenames.end())
                                {
                                    //Restart playlist as it is looping
                                    int idToPlay = 0;
                                    if(cPlaylistIter.playRandomly)
                                        idToPlay = rand() % cPlaylistIter.filenames.size() + 0;

                                    cPlaylistIter.currentlyPlaying = cPlaylistIter.filenames[idToPlay];
                                }
                                else
                                {
                                    if(cPlaylistIter.playRandomly)
                                        cPlaylistIter.currentlyPlaying = cPlaylistIter.filenames[rand() % cPlaylistIter.filenames.size() + 0];
                                    else
                                        cPlaylistIter.currentlyPlaying = *currentSoundIter;
                                }
                                play(cPlaylistIter.currentlyPlaying);
                            }
                            else
                            {
                                iter = activePlaylists.erase(iter); //Remove from active playlists
                                ic = false;
                            }
                        }
                    }
                }
                else
                {
                    //Invalid currently playing so load it again
                    play(cPlaylistIter.currentlyPlaying);
                }
            }
            if(ic)
            {
                iter++;
            }
        }

        updateClock.restart();
    }
}

bool SoundHandler::loadSound(const std::string &filepath, bool shouldActivate)
{
    cullSounds();
    std::string newfilepath = soundPath + filepath;
    std::cout<<"load sound path: "<<newfilepath<<std::endl;
    if(keyExists(filepath))
        return true; //Don't want to load the same sound twice...

    if(!(soundCount < 256)) //REMEMBER, SFML has an internal sound limit of 256, exceeding this would be bad, very bad indeed!
        return false; //Too many sounds

    loadedSounds[newfilepath] = soundContainer();
    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time
    cSound.type = soundType::sound;
    cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();
    cSound.isActive = false;

    if(shouldActivate) //The game wants the sound NOW, so lets also load it into memory.
    {
        cSound.sound = std::unique_ptr<sf::Sound>(new sf::Sound());
        cSound.isActive = true;
        if(!cSound.buffer.loadFromFile(newfilepath))
        {
            eraseKey(newfilepath);
            return false; //Failed to load
        }
        cSound.sound->setBuffer(cSound.buffer);
        soundCount++;
    }
    //Else no point in wasting memory if the sound isn't needed immediately so return true
    return true;
}

bool SoundHandler::loadMusic(const std::string &filepath, bool shouldActivate)
{
    cullSounds();
    std::string newfilepath = soundPath + filepath;
    if(keyExists(newfilepath))
        return true; //Don't want to load the same sound twice...

    if(!(soundCount < 256)) //REMEMBER, SFML has an internal sound limit of 256, exceeding this would be bad, very bad indeed!
        return false; //Too many sounds

    loadedSounds[newfilepath] = soundContainer();
    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time
    cSound.type = soundType::music;
    cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();
    cSound.isActive = false;
    if(shouldActivate)
    {
        cSound.music = std::unique_ptr<sf::Music>(new sf::Music());
        cSound.isActive = true;
        if(!cSound.music->openFromFile(newfilepath))
        {
            eraseKey(newfilepath);
            return false; //Failed to load
        }
        soundCount++;
    }
    return true;
}

bool SoundHandler::play(const std::string &filepath)
{
    std::string newfilepath = soundPath + filepath;
    if(!keyExists(newfilepath))
        return false; //No such sound
    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time

    //If the sound isn't active, then activate it
    if(!cSound.isActive)
    {
        if(!activateSound(newfilepath))
        {   std::cout<<"Point 3: \n";
            return false; //If the sound couldn't be activated, return false
        }
    }

    if(cSound.type == soundType::music && cSound.music != nullptr)
    {
        cSound.music->setVolume(globalMusicVolume);
        cSound.music->play();
    }
    else if(cSound.type == soundType::sound && cSound.sound != nullptr)
    {
        cSound.sound->setVolume(globalMusicVolume);
        cSound.sound->play();
    }

    cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();

    return true; //Play successful
}

void SoundHandler::pause(const std::string &filepath)
{
    std::string newfilepath = soundPath + filepath;
    if(!keyExists(newfilepath))
        return; //No such sound

    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time
    if(activateSound(newfilepath))
    {
        if(cSound.type == soundType::sound && cSound.sound != nullptr)
        {
            cSound.sound->pause();
        }
        else if(cSound.type == soundType::music && cSound.music != nullptr)
        {
            cSound.music->pause();
        }
    }
}

void SoundHandler::resume(const std::string &filepath)
{
    std::string newfilepath = soundPath + filepath;
    if(!keyExists(newfilepath))
        return; //No such sound
    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time
    if(activateSound(newfilepath))
    {
        if(cSound.type == soundType::sound && cSound.sound != nullptr)
        {
            if(cSound.sound->getStatus() == sf::Sound::Paused || cSound.sound->getStatus() == sf::Sound::Stopped)
                cSound.sound->play();
        }
        else if(cSound.type == soundType::music && cSound.music != nullptr)
        {
            if(cSound.music->getStatus() == sf::Music::Paused || cSound.music->getStatus() == sf::Music::Stopped)
                cSound.music->play();
        }
        cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();
    }
}

void SoundHandler::setVolume(const std::string &filepath, float vol)
{
    std::string newfilepath = soundPath + filepath;
    if(!keyExists(newfilepath))
        return; //No such sound
    auto &cSound = loadedSounds[newfilepath]; //Take reference so we don't have to implicitly search loadedSounds every time
    if(activateSound(newfilepath))
    {
        if(cSound.type == soundType::sound && cSound.sound != nullptr)
        {
            cSound.sound->setVolume(vol);
        }
        else if(cSound.type == soundType::music && cSound.music != nullptr)
        {
            cSound.music->setVolume(vol);
        }
    }
}

void SoundHandler::cullSounds()
{
    if(soundCount == 0)
        return; //No sounds to cull

    if(soundCount > 250) //Be a little ruthless about things if there's this many sounds loaded
    {
        for(auto iter = loadedSounds.begin(); iter != loadedSounds.end(); iter++)
        {
            if(iter->second.isActive == true && iter->second.type == soundType::sound)
            {
                if(iter->second.sound->getStatus() != sf::Sound::Status::Playing) //Not playing so remove it
                {
                    if(iter->second.sound != nullptr)
                        iter->second.sound.reset();
                    iter->second.isActive = false;
                    soundCount--;
                }
            }
            else if(iter->second.isActive == true && iter->second.type == soundType::music)
            {
                if(iter->second.music->getStatus() != sf::Music::Status::Playing) //Not playing so remove it
                {
                    if(iter->second.music != nullptr)
                        iter->second.music.reset();
                    iter->second.isActive = false;
                    soundCount--;
                }
            }
        }
    }
    else //We're not running out of space, so we can be a little more liberal about things
    {
        for(auto iter = loadedSounds.begin(); iter != loadedSounds.end(); iter++)
        {

            if(iter->second.isActive == true && iter->second.type == soundType::sound)
            {
                if(iter->second.sound->getStatus() != sf::Sound::Status::Playing && iter->second.lastPlayTime + inactiveSoundTimeout < static_cast<unsigned int>(timeL.getElapsedTime().asMicroseconds())) //Not playing so remove it and hasn't been played in a while so remove it
                {
                    if(iter->second.sound != nullptr)
                        iter->second.sound.reset();
                    iter->second.isActive = false;
                    soundCount--;
                }
            }
            else if(iter->second.isActive == true && iter->second.type == soundType::music)
            {
                if(iter->second.music->getStatus() != sf::Music::Status::Playing && iter->second.lastPlayTime + inactiveSoundTimeout < static_cast<unsigned int>(timeL.getElapsedTime().asMilliseconds())) //Not playing so remove it
                {
                    if(iter->second.music != nullptr)
                        iter->second.music.reset();
                    iter->second.isActive = false;
                    soundCount--;
                }
            }
        }
    }
}

bool SoundHandler::fadeToVolume(const std::string &filepath, float vol)
{
    std::string newfilepath = soundPath + filepath;
    if(!keyExists(newfilepath))
        return false; //No such sound
    activeFades[newfilepath] = fadeInfo(); //Reset existing fades/create a new one
    auto &fadeRef = activeFades[newfilepath];
    fadeRef.sound = &loadedSounds[newfilepath];
    fadeRef.targetVolume = vol;
    return true;
}

bool SoundHandler::fadeIn(const std::string &filepath)
{
    std::string newfilepath = soundPath + filepath;
    if(keyExists(newfilepath))
    {
        if(loadedSounds[newfilepath].type == soundType::music)
            return fadeToVolume(newfilepath, globalMusicVolume);
        else if(loadedSounds[newfilepath].type == soundType::sound)
            return fadeToVolume(newfilepath, globalSoundVolume);
    }
    return false;
}

bool SoundHandler::fadeOut(const std::string &filepath)
{
    std::string newfilepath = soundPath + filepath;
    return fadeToVolume(newfilepath, 0);
}

bool SoundHandler::keyExists(const std::string &filepath)
{
    //Check if the given key exists
    if(loadedSounds.count(filepath) > 0)
        return true;

    return false;
}

void SoundHandler::eraseKey(const std::string &filepath)
{
    auto iter = loadedSounds.find(filepath);
    if(iter != loadedSounds.end())
    {
        if(iter->second.music != nullptr)
            iter->second.music.reset();
        if(iter->second.sound != nullptr)
            iter->second.sound.reset();
        loadedSounds.erase(iter);
        soundCount--;
    }
}

bool SoundHandler::activateSound(const std::string &filepath)
{
    if(!keyExists(filepath))
        return false; //Sound doesn't exist - Can't be reloaded.

    auto &cSound = loadedSounds[filepath];

    if(cSound.isActive == true)
        return true; //Already loaded. Nothing more to be done.

    if(cSound.type == soundType::music)
    {
        if(!(soundCount < 256)) //Don't want to exceed the limit...
            return false; //Too many sounds

        cSound.music = std::unique_ptr<sf::Music>(new sf::Music());
        cSound.isActive = true;
        cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();
        if(!cSound.music->openFromFile(filepath))
        {
            eraseKey(filepath);
            return false; //Failed to load so may as well erase it.
        }
        soundCount++;
        return true;
    }
    else if(cSound.type == soundType::sound)
    {
        if(!(soundCount < 256)) //Don't want to exceed the limit...
            return false; //Too many sounds

        cSound.sound = std::unique_ptr<sf::Sound>(new sf::Sound());
        cSound.isActive = true;
        cSound.lastPlayTime = timeL.getElapsedTime().asMilliseconds();
        if(!cSound.buffer.loadFromFile(filepath))
        {
            eraseKey(filepath);
            return false; //Failed to load so may as well erase it
        }
        cSound.sound->setBuffer(cSound.buffer);
        soundCount++;
        return true;
    }
    return false; //Uhh... this should be impossible - But lets return false to be on the safe side...
}

void SoundHandler::createPlaylist(const std::string& playlistName, bool shouldLoop, bool shuffle)
{
    playlists[playlistName] = playList();
    auto &cPlaylist = playlists[playlistName];
    cPlaylist.playRandomly = shuffle;
    cPlaylist.shouldLoop = shouldLoop;
}

void SoundHandler::addToPlaylist(const std::string& playlistName, const std::string& soundFilepath, soundType type)
{
    std::string newfilepath = soundPath + soundFilepath;
    //Check if the given playlist exists
    if(!(playlists.count(playlistName) > 0))
    {
        std::cerr << "\nAttempt to add sound to an invalid playlist was detected." << std::endl;
        std::cerr << "Playlist name: " << playlistName << ", Sound filepath: " << newfilepath << std::endl;
        return; //No such playlist - Return
    }

    playlists[playlistName].filenames.push_back(newfilepath);
    if(type == soundType::sound) //All of the sounds in the playlist don't need to be loaded immediately... so set load immediately to false
        loadSound(newfilepath, false);
    else
        loadMusic(newfilepath, false);
}

void SoundHandler::destroyPlaylist(const std::string& playlistName)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistName);
    if(iter != playlists.end())
    {
        //Deactivate all songs in the playlist
        for(unsigned int a = 0; a < playlists[playlistName].filenames.size(); a++)
        {
            if(loadedSounds[playlists[playlistName].filenames[a]].type == soundType::sound)
            {
                if(loadedSounds[playlists[playlistName].filenames[a]].isActive == true && loadedSounds[playlists[playlistName].filenames[a]].sound != nullptr)
                {
                    loadedSounds[playlists[playlistName].filenames[a]].sound.reset();
                    loadedSounds[playlists[playlistName].filenames[a]].isActive = false;
                    soundCount--;
                }
            }
            else
            {
                if(loadedSounds[playlists[playlistName].filenames[a]].isActive == true && loadedSounds[playlists[playlistName].filenames[a]].music != nullptr)
                {
                    loadedSounds[playlists[playlistName].filenames[a]].music.reset();
                    loadedSounds[playlists[playlistName].filenames[a]].isActive = false;
                    soundCount--;
                }
            }
        }
        //Erase the playlist from the map
        playlists.erase(iter);
    }
}

void SoundHandler::clearPlaylist(const std::string& playlistName)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistName);
    if(iter != playlists.end())
    {
        bool shuffle = playlists[playlistName].playRandomly;
        bool loop = playlists[playlistName].shouldLoop;
        //Shortcuts are fun!
        destroyPlaylist(playlistName);
        createPlaylist(playlistName, loop, shuffle);
    }
}

void SoundHandler::setPlaylistProperty(const std::string& playlistName, playlistProperty propertyType, bool tf)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistName);
    if(iter == playlists.end())
        return;

    if(propertyType == playlistProperty::shouldLoop)
    {
        playlists[playlistName].shouldLoop = tf;
    }
    else if(propertyType == playlistProperty::shouldRandom)
    {
        playlists[playlistName].playRandomly = tf;
    }
}

void SoundHandler::removeFromPlaylist(const std::string& playlistName, const std::string& soundFilepath)
{
    std::string newfilepath = soundPath + soundFilepath;
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistName);
    if(iter == playlists.end())
        return;

    //Remove the sound from the playlist
    auto soundPos = std::find(playlists[playlistName].filenames.begin(), playlists[playlistName].filenames.end(), newfilepath);
    if(soundPos != playlists[playlistName].filenames.end())
        playlists[playlistName].filenames.erase(soundPos);

    //Deactivate the sound
    auto nPos = loadedSounds.find(newfilepath);
    if(nPos != loadedSounds.end())
    {
        if(nPos->second.type == soundType::music)
        {
            nPos->second.music.reset();
            soundCount--;
            nPos->second.isActive = false;
        }
        else if(nPos->second.type == soundType::sound)
        {
            nPos->second.sound.reset();
            soundCount--;
            nPos->second.isActive = false;
        }
    }
}

const std::string &SoundHandler::getPlayingFromPlaylist(const std::string& playlistName)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistName);
    if(iter == playlists.end())
        return errorValue;

    return iter->second.currentlyPlaying;
}


void SoundHandler::setPlayingToPlaylist(const std::string& playlistname, const std::string& soundFilepath)
{
    std::string newfilepath = soundPath + soundFilepath;
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistname);
    if(iter == playlists.end())
        return;

    auto playlistActive = std::find(activePlaylists.begin(), activePlaylists.end(), playlistname);
    if(playlistActive != activePlaylists.end()) //If something is already playing in the playlist, deactivate it.
    {
        //Deactivate the sound
        auto nPos = loadedSounds.find(playlists[playlistname].currentlyPlaying);
        if(nPos != loadedSounds.end())
        {
            if(nPos->second.type == soundType::music)
            {
                nPos->second.music.reset();
                soundCount--;
                nPos->second.isActive = false;
            }
            else if(nPos->second.type == soundType::sound)
            {
                nPos->second.sound.reset();
                soundCount--;
                nPos->second.isActive = false;
            }
        }
        activePlaylists.erase(playlistActive);
    }

    //Add playlist to currently playing
    activePlaylists.push_back(playlistname);
    //Play the sound
    play(newfilepath);
    //Update the playlist
    playlists[playlistname].currentlyPlaying = newfilepath;
}

void SoundHandler::pausePlaylist(const std::string& playlistname)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistname);
    if(iter == playlists.end())
        return;

    auto playlistActive = std::find(activePlaylists.begin(), activePlaylists.end(), playlistname);
    if(playlistActive != activePlaylists.end()) //If the playlist is actually active
    {
        //Pause the sound
        auto nPos = loadedSounds.find(playlists[playlistname].currentlyPlaying);
        if(nPos != loadedSounds.end())
        {
            if(nPos->second.type == soundType::music && nPos->second.music != nullptr)
            {
                nPos->second.music->pause();
            }
            else if(nPos->second.type == soundType::sound && nPos->second.sound != nullptr)
            {
                nPos->second.sound->pause();
            }
        }
        //Add playlist to currently playing
        activePlaylists.push_back(playlistname);
    }
}
void SoundHandler::playPlaylist(const std::string& playlistname)
{
    //Check to see if the playlist exists
    auto iter = playlists.find(playlistname);
    if(iter == playlists.end())
        return;

    auto playlistActive = std::find(activePlaylists.begin(), activePlaylists.end(), playlistname);
    if(playlistActive == activePlaylists.end()) //If the playlist is not active, activate it first.
    {
        //Add playlist to currently playing
        activePlaylists.push_back(playlistname);
    }

            //Decide on what to play
            if(playlists[playlistname].currentlyPlaying == "null")
            {
                //If nothings playing, choose a track to play
                if(playlists[playlistname].filenames.size() != 0)
                {
                    //If there's stuff in the playlist
                    if(playlists[playlistname].playRandomly)
                    {
                        int ttp = rand() % playlists[playlistname].filenames.size() + 0;
                        playlists[playlistname].currentlyPlaying = playlists[playlistname].filenames[ttp];
                    }
                    else
                    {
                        //Else play first thing in the list
                        playlists[playlistname].currentlyPlaying = playlists[playlistname].filenames[0];
                    }
                }
                else //Nothing in the playlist, nothing to play.
                {
                    activePlaylists.pop_back();
                    return;
                }
            }
            std::cout << "\nAttempting to play: " << playlists[playlistname].currentlyPlaying;
            play(playlists[playlistname].currentlyPlaying);
}

void SoundHandler::setGlobalSoundVolume(float target)
{
    globalSoundVolume = target;
    //Iterate through each loaded sound and set the new volume
    for(auto iter = loadedSounds.begin(); iter != loadedSounds.end(); iter++)
    {
        if(iter->second.isActive)
        {
            iter->second.sound->setVolume(target);
        }
    }
}

void SoundHandler::setGlobalMusicVolume(float target)
{
    globalMusicVolume = target;
    //Iterate through each loaded sound and set the new volume
    for(auto iter = loadedSounds.begin(); iter != loadedSounds.end(); iter++)
    {
        if(iter->second.isActive)
        {
            iter->second.music->setVolume(target);
        }
    }
}

float SoundHandler::getGlobalSoundVolume()
{
    return globalSoundVolume;
}

float SoundHandler::getGlobalMusicVolume()
{
    return globalMusicVolume;
}


