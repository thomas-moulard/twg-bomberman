/*!
 * \file  sound/soundmanager.hh
 *
 * @brief Déclaration de \c sound::SoundManager .
 */

/*!
 *  \class   SoundManager
 *
 *  @brief   Gestionnaire sonore du jeu.
 *           Cette classe est chargée de stocker tous les paramètres
 *           sonores du jeu (volume, qualité...).
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-29-2006
 *  @bug     none
 *  @warning none
 */

#ifndef SOUND_SOUNDMANAGER_HH_
# define SOUND_SOUNDMANAGER_HH_

#include <SDL/SDL_mixer.h>
#include "utils/debug.hh"
#include <iostream>

namespace sound
{
  class SoundManager
  {
  public:
    /*!
     *  \fn         SoundManager()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    SoundManager();

    /*!
     *  \fn         SoundManager(const SoundManager&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    SoundManager(const SoundManager&);

    /*!
     *  \fn         ~SoundManager()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~SoundManager();

    /*!
     *  \fn         SoundManager& operator=(const SoundManager&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    SoundManager& operator=(const SoundManager&);
  private:
    unsigned int soundFrequence;          /** Frequence du son (22050,44100) **/
    unsigned int soundMode;               /** Mode St�reo(2) ou mono(1)      **/
    unsigned int soundTailleEchantillon;  /** Taille de l'�chantillon        **/

  };
};


#endif /* !SOUND_SOUNDMANAGER_HH_ */
