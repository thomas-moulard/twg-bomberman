/*!
 * \file  sound/sound.hh
 *
 * @brief Déclaration de \c sound::Sound .
 */

/*!
 *  \class   Sound
 *
 *  @brief   Cette classe est un conteneur de son. Elle est principalement
 *           utilisée dans \c core::ResourceManager .
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
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
     *  @brief      Constructeur par défaut de la classe.
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
     *  @brief      Destructeur par défaut de la classe.
     */
    virtual ~Sound();

    /*!
     *  \fn         Sound& operator=(const Sound&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation)/
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    Sound& operator=(const Sound&);

    /*!
     *  \fn         void play()
     *
     *  @brief      Lance la lecture d'un son
     */
    /*PS : setType est la fonction qui permet de choisir entre effet sonore ou
      musique, elle doit �tre apell�e apr�s le constructeur avant la premi�re
      lecture du son */

    void setType(SoundType type); /** Choix entre effet sonore ou musique **/
    void play();              /** Lecture du son                          **/
    void stop();              /** Arrete la lecture d'une musique         **/
    void pause();             /** Met en pause une musique                **/
    void resume();            /** Reprends la musique apr�s pause         **/

  private:
    std::string filename_;
    Mix_Music* music_;        /** Type de donn�e Musique                  **/
    Mix_Chunk* sound_;        /** Type de donn�e effet sonore             **/
    bool isLoaded_;           /** Indique si le fichier est charg� ou pas **/
    SoundType soundType_;     /** Type de fichier sonore **/
  };
};

#endif /* !SOUND_HH */
