/*!
 * \file  utils/resourcemanager.hh
 *
 * @brief Déclaration de \c utils::ResourceManager .
 */

 /*!
 *  \class   ResourceManager
 *
 *  @brief   Cette classe est chargée de gérer les ressources sonores
 *           et graphiques du jeu.
 *           Cette classe est gérée par un couplage du motif de conception
 *           "poids-mouche" (flyweight pattern), et de pointeurs intelligents
 *           (SmartPointers). Les ressources ne seront donc jamais dupliquées
 *           en mémoire, et elles seront automatiquement desalloués dès
 *           qu'elles ne seront plus référencées (plus précisément une
 *           police de desallocation est passée en paramètre pour
 *           controler les desallocations de manière plus fine).
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
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
     *           de comparer deux chaines de caractères ( \c string ).
     *           Elle est utilisée pour gérer l'unicité des éléments
     *           du \c ResourceManager .
     *  @author  Thomas Moulard <thomas.moulard@gmail.com>
     *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
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
     *  @brief   Ce typedef permet de créer l'alias \c SpSurface_t
     *           (comprendre Smartpointer vers \c GraphicManager::Surface ).
     */
    typedef utils::SmartPointer<graphic::GraphicManager::Surface> SpSurface_t;

    /*!
     *  \typedef utils::SmartPointer<sound::Sound*> SpSound_t
     *
     *  @brief   Ce typedef permet de créer l'alias \c SpSound_t
     *           (comprendre Smartpointer vers \c Sound ).
     */
    typedef utils::SmartPointer<sound::Sound> SpSound_t;

    typedef graphic::GraphicManager::Surface Surface;
    typedef graphic::GraphicManager::Color Color;

    /*!
     *  \fn         ResourceManager()
     *
     *  @brief      Constructeur par défaut de la classe.
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
     *  @brief      Destructeur par défaut de la classe.
     */
    ~ResourceManager();

    /*!
     *  \fn         ResourceManager& operator=(const ResourceManager&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
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
     *  @brief      Cette fonction permet de récupérer des données
     *              graphiques contenues dans le \c ResourceManager. Un
     *              SmartPointer est renvoyé à cet effet et doit pouvoir
     *              être enregistré par la classe appelante.
     *  @param[in]  filename
     *              Chemin d'accès (\c const \c char*) au fichier de
     *              la ressource demandée.
     *  @param[in]  desallocationPolicy
     *              Comprendre "politique de desallocation". Ce paramètre
     *              énuméré permet de spécifier finement dans quelle
     *              circonstance pourra être détruite la ressource.
     *              \li \c utils::SmartPointer::SmartPointer::DP_ALWAYS : La ressource sera
     *              desallouée dès qu'aucune référence ne lui sera faite.
     *              \li \c utils::SmartPointer::SmartPointer::DP_ENDOFLEVEL : La ressource
     *              sera desallouée coute que coute à la fin du niveau en
     *              cours.
     *              \li \c utils::SmartPointer::DP_ENDOFGAME : La ressource
     *              sera détruite quoi qu'il arrive à la fin du jeu.
     *  @return     Renvoie un \cSpVisualElement_t \c \& faisant référence
     *              à la ressource demandée.
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
     *  @brief      Cette fonction permet de récupérer des données
     *              sonores contenues dans le \c ResourceManager. Un
     *              SmartPointer est renvoyé à cet effet et doit pouvoir
     *              être enregistré par la classe appelante.
     *  @param[in]  filename
     *              Chemin d'accès (\c const \c char*) au fichier de
     *              la ressource demandée.
     *  @param[in]  desallocationPolicy
     *              Comprendre "politique de desallocation". Ce paramètre
     *              énuméré permet de spécifier finement dans quelle
     *              circonstance pourra être détruite la ressource.
     *              \li \c utils::SmartPointer::DP_ALWAYS : La ressource sera
     *              desallouée dès qu'aucune référence ne lui sera faite.
     *              \li \c utils::SmartPointer::DP_ENDOFLEVEL : La ressource
     *              sera desallouée coute que coute à la fin du niveau en
     *              cours.
     *              \li \c utils::SmartPointer::DP_ENDOFGAME : La ressource
     *              sera détruite quoi qu'il arrive à la fin du jeu.
     *  @return     Renvoie un \c SpSound_t \c \& faisant référence
     *              à la ressource demandée.
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
     *              que la fin du niveau en cours est arrivée. Les
     *              ressources ayant la politique de desallocation
     *              définie comme \c utils::SmartPointer::DP_ENDOFLEVEL
     *              seront donc desallouées.
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
     *              que la fin du programme est arrivée. Les
     *              ressources ayant la politique de desallocation
     *              définie comme \c utils::SmartPointer::DP_ENDOFGAME
     *              seront donc desallouées.
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
     *  @brief      Cette \c map contient les éléments de type graphique
                    ( \c graphic::VisualElement ) du \c ResourceManager.
     *  @sa         graphic::VisualElement
     */
    std::map<const char*, SpSurface_t, s_ltstr> hashVisualElements_;

    /*!
     *  \property   std::map<const char*, SpSound_t, s_ltstr> hashSounds_
     *
     *  @brief      Cette \c map contient les éléments de type sonore
                    ( \c sound::Sound ) du \c ResourceManager.
     *  @sa         sound::Sound
     */
    std::map<const char*, SpSound_t, s_ltstr> hashSounds_;

    static ResourceManager* instance_;
  };
};

#endif
