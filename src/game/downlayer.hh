/*!
 * \file  game/downlayer.hh
 *
 * @brief Déclaration de \c game::DownLayer .
 */

 /*!
 *  \class   DownLayer
 *
 *  @brief   Cette classe représente le layer le plus près du sol.
 *           Ce layer (couche) contiendra essentiellement les bonus
 *           (PowerUp) du jeu.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-29-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_DOWNLAYER_HH_
# define GAME_DOWNLAYER_HH_
# include <vector>
# include <tinyxml.h>

# include "game/fwd.hh"
# include "game/updownlayer.hh"


namespace game
{
  class GameElement;

  class DownLayer : public UpDownLayer
  {
  public:
    /*!
     *  \fn         DownLayer()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    explicit DownLayer(const Rect&);

    /*!
     *  \fn         DownLayer(const DownLayer&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    explicit DownLayer(const DownLayer&);

    /*!
     *  \fn         ~DownLayer()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~DownLayer();

    /*!
     *  \fn         DownLayer& operator=(const DownLayer&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    DownLayer& operator=(const DownLayer&);

    /*!
     *  \fn         virtual void render()
     *
     *  @brief      Cette fonction est chargée d'afficher le layer.
     */
    virtual void render();

	/*!
     *  \fn         static DownLayer& loadFromXml(TiXmlElement* node)
     *
     *  @brief      Cette fonction s'occupe de charger le layer en fonction
	 *              d'un Noeud XML qui lui est passé en paramètre.
     */
    static DownLayer* loadFromXml(TiXmlElement*, Map*);
  };
};


#endif /* !GAME_DOWNLAYER_HH_ */
