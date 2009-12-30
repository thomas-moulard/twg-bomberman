/*!
 * \file  game/gameelement.hh
 *
 * @brief Déclaration de \c game::GameElement .
 */

 /*!
 *  \class   GameElement
 *
 *  @brief   La classe \c GameElement n'est pas totalement documentée.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-29-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_GAMEELEMENT_HH_
# define GAME_GAMEELEMENT_HH_
# include <tinyxml.h>

# include "game/fwd.hh"
# include "graphic/imageelement.hh"
# include "utils/resourcemanager.hh"
# include "utils/smartpointer.hh"

namespace game
{
  class BattleScene;
  class Player;

  class GameElement
  {
  public:
    /*!
     *  \fn         GameElement()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    GameElement(const char* filename, unsigned frameSizeX, unsigned frameSizeY);
    /*!
     *  \fn         GameElement(const GameElement&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    GameElement(const GameElement&);

    /*!
     *  \fn         virtual ~GameElement()
     *
     *  @brief      Destructeur par défaut spécialisé de la classe.
     */
    virtual ~GameElement();

    /*!
     *  \fn         GameElement& operator=(const GameElement&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    GameElement& operator=(const GameElement&);

    /*!
     *  \fn         static GameElement& loadFromXml(TiXmlElement* node)
     *
     *  @brief      Cette fonction statique s'occupe de charger le GameElement
     *              avec des données contenues dans un noeud XML passé en paramètre.
     *  @param[in]  node
     *              Le noeud XML à partir duquel les ressources devront être
     *              récupérées.
     */
    static GameElement* loadFromXml(TiXmlElement*, Map*);

    /*!
     *  \fn         virtual void render() = 0
     *
     *  @brief      Fonction chargée du rendu du \c GameElement.
     */
    virtual void render() = 0;

    virtual bool isWalkable(int x, int y, int w = 0, int h = 0) const = 0;

    virtual bool isDestructible(int x, int y, int w = 0, int h = 0) const = 0;

    int getX() const
    {
      return sprite_.getX();
    }

    int getY() const
    {
      return sprite_.getY();
    }

    int getWidth() const
    {
      return sprite_.getWidth();
    }

    int getHeight() const
    {
      return sprite_.getWidth();
    }

    graphic::ImageElement& getSprite()
    {
      return sprite_;
    }

    virtual void onTouch(game::BattleScene& bs, game::Player& pl) = 0;

    /*!
     * Détermine si le rectangle donné touche l'élément.
     */
    virtual bool isTouched(int x, int y, int w = 0, int h = 0)
    {
      return collide(x, y, w, h);
    }

    /*!
     * Determine si l'élément et un rectangle donnée sont superposés.
     */
    bool collide(int x, int y, int w = 0, int h = 0) const
    {
      return collide(x, y, w, h, getX(), getY(), getWidth(), getHeight());
    }

    static bool collide(int x,
                        int y,
                        int w,
                        int h,
                        int x2,
                        int y2,
                        int w2,
                        int h2)
    {
      int xmax, ymax, xmin_e, xmax_e, ymin_e, ymax_e;

      xmax = x + w;
      ymax = y + h;

      xmin_e = x2;
      ymin_e = y2;
      xmax_e = xmin_e + w2;
      ymax_e = ymin_e + h2;

      if ((xmax > xmin_e && x < xmax_e) &&
          (ymax > ymin_e && y < ymax_e))
        return true;
      return false;
    }

  protected:
    GameElement();
    /*!
     *  \property   core::ResourceManager::SpImageElement_t sprite_
     *
     *  @brief      Cet attribut est chargé de lier le \c GameElement à un \c VisualElement .
     *  @sa         graphic::ImageElement
     */
    graphic::ImageElement sprite_;
  };
};

#endif
