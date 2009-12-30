/*!
 * \file  game/backgroundlayer.hh
 *
 * @brief Déclaration de \c game::BackgroundLayer .
 */

 /*!
 *  \class   BackgroundLayer
 *
 *  @brief   Cette classe représente le layer "sol".
 *           C'est donc un conteneur pour des tiles (tuiles) représentant un
 *           bloc de terrain.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-29-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_BACKGROUNDLAYER_HH_
# define GAME_BACKGROUNDLAYER_HH_
# include <vector>
# include <tinyxml.h>

# include "game/fwd.hh"
# include "game/layer.hh"

namespace graphic
{
  class VisualElement;
};

namespace game
{
  class BackgroundLayer : public Layer
  {
  public:
    /*!
     *  \fn         BackgroundLayer()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    explicit BackgroundLayer(const Rect&);

    /*!
     *  \fn         BackgroundLayer(const BackgroundLayer&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    explicit BackgroundLayer(const BackgroundLayer&);

    /*!
     *  \fn         ~BackgroundLayer()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~BackgroundLayer();

    /*!
     *  \fn         BackgroundLayer& operator=(const BackgroundLayer&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    BackgroundLayer& operator=(const BackgroundLayer&);

    /*!
     *  \fn         virtual void render()
     *
     *  @brief      Cette fonction est chargée d'afficher le layer.
     */
    virtual void render();

    /*!
     *  \fn         static BackgroundLayer& loadFromXml(TiXmlElement* node)
     *
     *  @brief      Cette fonction s'occupe de charger le layer en fonction
     *              d'un Noeud XML qui lui est passé en paramètre.
     */
    static BackgroundLayer* loadFromXml(TiXmlElement* node, Map*);

    virtual bool isWalkable(int x, int y, int w = 0, int h = 0);
    virtual bool isDestructible(int x, int y, int w = 0, int h = 0);

    virtual void handleEvents(game::BattleScene& bs);

    virtual void removeBlocks(unsigned, unsigned)
    {
    }

  private:
    typedef std::vector<graphic::VisualElement*> TileVec;

    /*!
     *  \property   std::vector<VisualElement*> tiles_
     *
     *  @brief      Cet attribut regroupe tous les éléments tiles (tuiles) de ce layer.
     *  @sa         graphic::VisualElement
     */
    TileVec tiles_;
  };
};


#endif /* !GAME_BACKGROUND_HH_ */
