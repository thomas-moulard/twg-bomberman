/*!
 * \file  sound/sound.cc
 *
 * @brief Implémentation de \c sound::Sound .
 */

#include "sound/sound.hh"
#include <string>
#include <cassert>

namespace sound
{
  Sound::Sound(const char* filename) :
    filename_ (filename),
    music_ (0),
    isLoaded_(false),
    soundType_ (SOUNDTYPE_SOUND)
  {
    //FIXME: soundType_ devrait etre determine a partir
    // de l'extension ou du type MIME.
  }

  Sound::Sound(const Sound& s) :
    filename_ (s.filename_),
    music_ (s.music_),
    isLoaded_(s.isLoaded_),
    soundType_ (s.soundType_)
  {
    assert(0);
  }

  Sound::~Sound()
  {
    switch(soundType_)
      {
      case 1: //Effet sonore
        Mix_FreeChunk(sound_);
        break;

      case 2: //Musique
        Mix_FreeMusic(music_);
        break;

      default: //Choix inconnu
        break;
      }
  }

  Sound& Sound::operator=(const Sound&)
  {
    return *this; //FIXME
  }

  void Sound::setType(SoundType type)
  {
    soundType_ = type;
  }

  void Sound::play()
  {
    /** CHARGEMENT **/
    if(isLoaded_ == false)
      {
        switch(soundType_)
          {
          case 1: //Effet sonore
            sound_ = Mix_LoadWAV(filename_.c_str());
            isLoaded_ = true;
            break;

          case 2: //Musique
            music_ = Mix_LoadMUS(filename_.c_str());
            isLoaded_ = true;
            break;

          default: //Choix inconnu
            isLoaded_ = false;
            break;
          }
      }

    /** LECTURE **/
    if(isLoaded_ == true)
      {
        switch(soundType_)
          {
          case 1: //Effet sonore
            Mix_PlayChannel( -1, sound_, 0 );
            break;

          case 2: //Musique
            if( Mix_PlayingMusic() == 0 )
              Mix_PlayMusic(music_, -1 );
            break;

          default: //Choix inconnu
            break;
          }
      }

  }

  void Sound::stop()
  {
    if(Mix_PlayingMusic() && isLoaded_)
      {
        Mix_HaltMusic();
      }
  }

  void Sound::pause()
  {
    if(Mix_PlayingMusic() == 1 && isLoaded_)
      {
        Mix_PauseMusic();
      }
  }

  void Sound::resume()
  {
    if(Mix_PausedMusic() && isLoaded_)
      {
        Mix_ResumeMusic();
      }
  }
};
