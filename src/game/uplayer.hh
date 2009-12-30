/*!
 * \file  game/uplayer.hh
 *
 * @brief D�claration de \c game::UpLayer.
 */

 /*!
 *  \class   UpLayer
 *
 *  @brief   Cette classe d�finit un layer (couche) de niveau sup�rieur. L'essentiel
 *           du contenu de ce layer sera des \c game::Block .
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
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
     *  @brief      Constructeur par d�faut de la classe.
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
     *  @brief      Destructeur par d�faut de la classe.
     */
    ~UpLayer ();

    /*!
     *  \fn         UpLayer& operator=(const UpLayer&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
     *              par copie de la classe.
     */
    UpLayer& operator=(const UpLayer&);

    /*!
     *  \fn         virtual void render()
     *
     *  @brief      Cette fonction est charg�e du rendu de la couche haute. (Essentiellement
     *              des \c game::Block .
     */
    virtual void render();

    /*!
     *  \fn         static UpLayer& loadFromXml()
     *
     *  @brief      Cette fonction statique est charg�e de remplir le layer par les �l�ments
     *              contenus dans un fichier XML. (src/data/maps/ *.xml)
     */
    static UpLayer* loadFromXml(TiXmlElement*, Map*);
  };
};


#endif
