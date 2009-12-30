/*!
 * \file  sound/soundmanager.cc
 *
 * @brief Implémentation de \c sound::SoundManager .
 */

#include <cassert>

#include "sound/soundmanager.hh"
#include "utils/gettext.hh"

namespace sound
{
  SoundManager::SoundManager()
  {
      //Initialisation de SDL_MIXER
      soundFrequence = 22050;
      soundMode = 2;
      soundTailleEchantillon = 1024;
      if( Mix_OpenAudio(soundFrequence, MIX_DEFAULT_FORMAT, soundMode, soundTailleEchantillon ) == -1)
      {
        ERROR() << "Impossible d'initialiser le module sonore." << std::endl;
        exit(42);
      }
  }

  SoundManager::SoundManager(const SoundManager&)
  {
      assert(0);
  }

  SoundManager::~SoundManager()
  {
      //Fermeture de SDL_MIXER
      Mix_CloseAudio();
  }

  SoundManager& SoundManager::operator=(const SoundManager&)
  {
  	return *this; //FIXME
  }
};
