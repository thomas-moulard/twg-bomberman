/*!
 * \file  utils/resourcemanager.hh
 *
 * @brief Implémentation de \c utils::ResourceManager.
 */
#include <cassert>
#include "utils/resourcemanager.hh"
#include "utils/debug.hh"
#include "utils/pathmanager.hh"
#include "utils/smartpointer.hh"

namespace utils
{
  ResourceManager* ResourceManager::instance_ = 0;

  ResourceManager::ResourceManager()
  {
  }

  ResourceManager::ResourceManager(const ResourceManager&)
  {
  	assert(0);
  }

  ResourceManager::~ResourceManager()
  {
  }

  ResourceManager& ResourceManager::operator=(const ResourceManager&)
  {
  	assert(0);
  	return *this;
  }

  ResourceManager::SpSurface_t&
  ResourceManager::querySurface(const char* filename,
          utils::DesallocationPolicy_t dp)
  {
    //FIXME: implémenter le resourcemanager, ceci est juste un stub!
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    Surface* img = gm->load(filename);

    if (!img)
      {
	E() << "Impossible de charger l'image ``" << filename
	    << "''. La raison est:" << std::endl;
	E() << SDL_GetError() << std::endl;
	img = gm->load(
           utils::PathManager::getDataFilename("/img/fixme.png").c_str());
      }
    assert(img);
    return *new SpSurface_t(img, dp);
  }

  ResourceManager::SpSurface_t&
  ResourceManager::queryText(const char* text,
			     Color col,
			     utils::DesallocationPolicy_t dp)
  {
    //FIXME: implémenter le resourcemanager, ceci est juste un stub!
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    Surface* img = gm->print(text, col);

    if (!img)
      {
	E() << "Impossible de générer le texte ``" << text
	    << "''. La raison est:" << std::endl;
	E() << SDL_GetError() << std::endl;
      }
    assert(img);
    return *new SpSurface_t(img, dp);
  }

  ResourceManager::SpSound_t&
  ResourceManager::querySound(const char* filename,
                              utils::DesallocationPolicy_t dp)
  {
  	//FIXME: implémenter le resourcemanager, ceci est juste un stub!
  	sound::Sound* snd = new sound::Sound(filename);
  	return *new SpSound_t(snd, dp);
  }

  void ResourceManager::endOfLevel()
  {
  }

  void ResourceManager::endOfGame()
  {
  }
};
