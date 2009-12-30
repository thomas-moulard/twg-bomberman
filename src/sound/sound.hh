/*!
 * \file  sound/sound.hh
 *
 * @brief DÃ©claration de \c sound::Sound .
 */

/*!
 *  \class   Sound
 *
 *  @brief   Cette classe est un conteneur de son. Elle est principalement
 *           utilisÃ©e dans \c core::ResourceManager .
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  AurÃ©lien VallÃ©e <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-29-2006
 *  @bug     none
 *  @warning none
 */

#ifndef SOUND_HH
# define SOUND_HH
# include <string>
# include <SDL/SDL_mixer.h>

namespace sound
{
  class Sound
  {
  public:
    enum SoundType
      {
        SOUNDTYPE_MUSIC = 0,
        SOUNDTYPE_SOUND
      };

    /*!
     *  \fn         Sound()
     *
     *  @brief      Constructeur par dÃ©faut de la classe.
     */
    Sound(const char* filename);

    /*!
     *  \fn         Sound(const Sound&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    Sound(const Sound&);

    /*!
     *  \fn         ~Sound()
     *
     *  @brief      Destructeur par dÃ©faut de la classe.
     */
    virtual ~Sound();

    /*!
     *  \fn         Sound& operator=(const Sound&)
     *
     *  @brief      Surcharge de l'opÃ©rateur = (assignation)/
     *              Cet opÃ©rateur est Ã©quivalent au constructeur
     *              par copie de la classe.
     */
    Sound& operator=(const Sound&);

    /*!
     *  \fn         void play()
     *
     *  @brief      Lance la lecture d'un son
     */
    /*PS : setType est la fonction qui permet de choisir entre effet sonore ou
      musique, elle doit être apellée après le constructeur avant la première
      lecture du son */

    void setType(SoundType type); /** Choix entre effet sonore ou musique **/
    void play();              /** Lecture du son                          **/
    void stop();              /** Arrete la lecture d'une musique         **/
    void pause();             /** Met en pause une musique                **/
    void resume();            /** Reprends la musique après pause         **/

  private:
    std::string filename_;
    Mix_Music* music_;        /** Type de donnée Musique                  **/
    Mix_Chunk* sound_;        /** Type de donnée effet sonore             **/
    bool isLoaded_;           /** Indique si le fichier est chargé ou pas **/
    SoundType soundType_;     /** Type de fichier sonore **/
  };
};

#endif /* !SOUND_HH */
