/*!
 * \file  utils/resourcemanager.hh
 *
 * @brief D�claration de \c utils::ResourceManager .
 */

 /*!
 *  \class   ResourceManager
 *
 *  @brief   Cette classe est charg�e de g�rer les ressources sonores
 *           et graphiques du jeu.
 *           Cette classe est g�r�e par un couplage du motif de conception
 *           "poids-mouche" (flyweight pattern), et de pointeurs intelligents
 *           (SmartPointers). Les ressources ne seront donc jamais dupliqu�es
 *           en m�moire, et elles seront automatiquement desallou�s d�s
 *           qu'elles ne seront plus r�f�renc�es (plus pr�cis�ment une
 *           police de desallocation est pass�e en param�tre pour
 *           controler les desallocations de mani�re plus fine).
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef UTILS_RESOURCEMANAGER_HH_
# define UTILS_RESOURCEMANAGER_HH_

# include <map>
# include <cstring>

# include "graphic/graphicmanager.hh"
# include "sound/sound.hh"
# include "utils/smartpointer.hh"

namespace graphic
{
  class VisualElement;
};

namespace sound
{
  class Sound;
};

namespace utils
{
  namespace
  {
     /*!
     *  \struct  s_ltstr
     *
     *  @brief   Cette structure fonctionnelle (foncteur) permet de
     *           de comparer deux chaines de caract�res ( \c string ).
     *           Elle est utilis�e pour g�rer l'unicit� des �l�ments
     *           du \c ResourceManager .
     *  @author  Thomas Moulard <thomas.moulard@gmail.com>
     *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
     *  @version 1.0
     *  @date    07-24-2006
     *  @bug     none
     *  @warning none
     */
    struct s_ltstr
    {
      bool operator()(const char* string1, const char* string2) const
      {
        return strcmp(string1, string2) < 0;
      }
    };
  };

  class ResourceManager
  {
  public:
    /*!
     *  \typedef utils::SmartPointer<graphic::GraphicManager::Surface> SpSurface_t
     *
     *  @brief   Ce typedef permet de cr�er l'alias \c SpSurface_t
     *           (comprendre Smartpointer vers \c GraphicManager::Surface ).
     */
    typedef utils::SmartPointer<graphic::GraphicManager::Surface> SpSurface_t;

    /*!
     *  \typedef utils::SmartPointer<sound::Sound*> SpSound_t
     *
     *  @brief   Ce typedef permet de cr�er l'alias \c SpSound_t
     *           (comprendre Smartpointer vers \c Sound ).
     */
    typedef utils::SmartPointer<sound::Sound> SpSound_t;

    typedef graphic::GraphicManager::Surface Surface;
    typedef graphic::GraphicManager::Color Color;

    /*!
     *  \fn         ResourceManager()
     *
     *  @brief      Constructeur par d�faut de la classe.
     */
    ResourceManager();

    /*!
     *  \fn         ResourceManager(const ResourceManager&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    ResourceManager(const ResourceManager&);

    /*!
     *  \fn         ~ResourceManager()
     *
     *  @brief      Destructeur par d�faut de la classe.
     */
    ~ResourceManager();

    /*!
     *  \fn         ResourceManager& operator=(const ResourceManager&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
     *              par copie de la classe.
     */
    ResourceManager& operator=(const ResourceManager&);

    static ResourceManager* get_instance()
    {
    	if (!instance_)
	  instance_ = new ResourceManager();
	return instance_;
    }
    static void kill()
    {
      if (instance_)
      delete instance_;
    }

    /*!
     *  \fn         SpSurface_t& querySurface(const char* filename,
     *                utils::DesallocationPolicy_t desallocationPolicy);
     *
     *  @brief      Cette fonction permet de r�cup�rer des donn�es
     *              graphiques contenues dans le \c ResourceManager. Un
     *              SmartPointer est renvoy� � cet effet et doit pouvoir
     *              �tre enregistr� par la classe appelante.
     *  @param[in]  filename
     *              Chemin d'acc�s (\c const \c char*) au fichier de
     *              la ressource demand�e.
     *  @param[in]  desallocationPolicy
     *              Comprendre "politique de desallocation". Ce param�tre
     *              �num�r� permet de sp�cifier finement dans quelle
     *              circonstance pourra �tre d�truite la ressource.
     *              \li \c utils::SmartPointer::SmartPointer::DP_ALWAYS : La ressource sera
     *              desallou�e d�s qu'aucune r�f�rence ne lui sera faite.
     *              \li \c utils::SmartPointer::SmartPointer::DP_ENDOFLEVEL : La ressource
     *              sera desallou�e coute que coute � la fin du niveau en
     *              cours.
     *              \li \c utils::SmartPointer::DP_ENDOFGAME : La ressource
     *              sera d�truite quoi qu'il arrive � la fin du jeu.
     *  @return     Renvoie un \cSpVisualElement_t \c \& faisant r�f�rence
     *              � la ressource demand�e.
     *  @sa         utils::SmartPointer
     *  @sa         utils::SmartPointer::DP_ALWAYS
     *  @sa         utils::SmartPointer::DP_ENDOFLEVEL
     *  @sa         utils::SmartPointer::DP_ENDOFGAME
     *  @sa         graphic::VisualElement
     */
	ResourceManager::SpSurface_t&
	querySurface(const char* filename, utils::DesallocationPolicy_t dp);


    ResourceManager::SpSurface_t&
    queryText(const char* text, Color col, utils::DesallocationPolicy_t dp);


    /*!
     *  \fn         SpSound_t& querySound(const char* filename,
     *              utils::DesallocationPolicy_t    desallocationPolicy)
     *
     *  @brief      Cette fonction permet de r�cup�rer des donn�es
     *              sonores contenues dans le \c ResourceManager. Un
     *              SmartPointer est renvoy� � cet effet et doit pouvoir
     *              �tre enregistr� par la classe appelante.
     *  @param[in]  filename
     *              Chemin d'acc�s (\c const \c char*) au fichier de
     *              la ressource demand�e.
     *  @param[in]  desallocationPolicy
     *              Comprendre "politique de desallocation". Ce param�tre
     *              �num�r� permet de sp�cifier finement dans quelle
     *              circonstance pourra �tre d�truite la ressource.
     *              \li \c utils::SmartPointer::DP_ALWAYS : La ressource sera
     *              desallou�e d�s qu'aucune r�f�rence ne lui sera faite.
     *              \li \c utils::SmartPointer::DP_ENDOFLEVEL : La ressource
     *              sera desallou�e coute que coute � la fin du niveau en
     *              cours.
     *              \li \c utils::SmartPointer::DP_ENDOFGAME : La ressource
     *              sera d�truite quoi qu'il arrive � la fin du jeu.
     *  @return     Renvoie un \c SpSound_t \c \& faisant r�f�rence
     *              � la ressource demand�e.
     *  @sa         utils::SmartPointer
     *  @sa         utils::SmartPointer::DP_ALWAYS
     *  @sa         utils::SmartPointer::DP_ENDOFLEVEL
     *  @sa         utils::SmartPointer::DP_ENDOFGAME
     *  @sa         sound::Sound
     */
    SpSound_t& querySound(const char* filename,
      utils::DesallocationPolicy_t desallocationPolicy);

    /*!
     *  \fn         void endOfLevel()
     *
     *  @brief      Cette fonction permet d'indiquer au \c ResourceManager
     *              que la fin du niveau en cours est arriv�e. Les
     *              ressources ayant la politique de desallocation
     *              d�finie comme \c utils::SmartPointer::DP_ENDOFLEVEL
     *              seront donc desallou�es.
     *  @sa         utils::SmartPointer
     *  @sa         utils::SmartPointer::DP_ALWAYS
     *  @sa         utils::SmartPointer::DP_ENDOFLEVEL
     *  @sa         utils::SmartPointer::DP_ENDOFGAME
     */
    void endOfLevel();

    /*!
     *  \fn         void endOfGame()
     *
     *  @brief      Cette fonction permet d'indiquer au \c ResourceManager
     *              que la fin du programme est arriv�e. Les
     *              ressources ayant la politique de desallocation
     *              d�finie comme \c utils::SmartPointer::DP_ENDOFGAME
     *              seront donc desallou�es.
     *  @sa         utils::SmartPointer
     *  @sa         utils::SmartPointer::DP_ALWAYS
     *  @sa         utils::SmartPointer::DP_ENDOFLEVEL
     *  @sa         utils::SmartPointer::DP_ENDOFGAME
     */
    void endOfGame();

  private:
    /*!
     *  \property   std::map<const char*, SpVisualElement_t, s_ltstr> hashVisualElements_
     *
     *  @brief      Cette \c map contient les �l�ments de type graphique
                    ( \c graphic::VisualElement ) du \c ResourceManager.
     *  @sa         graphic::VisualElement
     */
    std::map<const char*, SpSurface_t, s_ltstr> hashVisualElements_;

    /*!
     *  \property   std::map<const char*, SpSound_t, s_ltstr> hashSounds_
     *
     *  @brief      Cette \c map contient les �l�ments de type sonore
                    ( \c sound::Sound ) du \c ResourceManager.
     *  @sa         sound::Sound
     */
    std::map<const char*, SpSound_t, s_ltstr> hashSounds_;

    static ResourceManager* instance_;
  };
};

#endif
