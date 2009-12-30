/*!
 * \file  game/uplayer.hh
 *
 * @brief Déclaration de \c game::UpLayer.
 */

 /*!
 *  \class   UpLayer
 *
 *  @brief   Cette classe définit un layer (couche) de niveau supérieur. L'essentiel
 *           du contenu de ce layer sera des \c game::Block .
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_UPLAYER_HH_
# define GAME_UPLAYER_HH_
# include <vector>
# include <tinyxml.h>

# include "game/updownlayer.hh"

namespace game
{

  class GameElement;

  class UpLayer : public UpDownLayer
  {
  public:
    /*!
     *  \fn         UpLayer()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    UpLayer (const Rect& renderingZone);

    /*!
     *  \fn         UpLayer(const UpLayer&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    UpLayer (const UpLayer&);

    /*!
     *  \fn         ~UpLayer()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~UpLayer ();

    /*!
     *  \fn         UpLayer& operator=(const UpLayer&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    UpLayer& operator=(const UpLayer&);

    /*!
     *  \fn         virtual void render()
     *
     *  @brief      Cette fonction est chargée du rendu de la couche haute. (Essentiellement
     *              des \c game::Block .
     */
    virtual void render();

    /*!
     *  \fn         static UpLayer& loadFromXml()
     *
     *  @brief      Cette fonction statique est chargée de remplir le layer par les éléments
     *              contenus dans un fichier XML. (src/data/maps/ *.xml)
     */
    static UpLayer* loadFromXml(TiXmlElement*, Map*);
  };
};


#endif
