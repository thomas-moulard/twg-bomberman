/**
 * \file game/bomb.hh
 * \brief Déclaration de Game::Bomb.
 */
#ifndef GAME_BOMB_HH_
# define GAME_BOMB_HH_
# include <vector>

# include "game/fwd.hh"
# include "game/gameelement.hh"
# include "game/player.hh"
# include "utils/timemanager.hh"

namespace game
{
  class Bomb : public GameElement
  {
  public:
    typedef std::vector<graphic::ImageElement*> explosions_t;
    enum BombState
      {
        BOMB_IDLE,
        BOMB_EXPLODE,
        BOMB_HAS_EXPLODED
      };

    enum BombAnimation
      {
        BOMB_ANIMATION_HORIZONTAL       = 1,
        BOMB_ANIMATION_VERTICAL         = 2,

        BOMB_ANIMATION_TOP              = 4,
        BOMB_ANIMATION_RIGHT            = 5,
        BOMB_ANIMATION_BOTTOM           = 6,
        BOMB_ANIMATION_LEFT             = 3
      };

    Bomb(game::Player* owner, const char* filename);
    Bomb(const Bomb&);

    ~Bomb();

    Bomb& operator=(const Bomb&);

    virtual void makeExplode();

    virtual void handleStates(game::BattleScene&);
    virtual void handleStateIdle(game::BattleScene&);
    virtual void handleStateExplode(game::BattleScene&);
    virtual void handleStateHasExploded(game::BattleScene&);

    virtual void render();

    virtual bool isTouched(int, int, int = 0, int = 0);
    virtual bool isWalkable(int, int, int = 0, int = 0) const;
    virtual bool isDestructible(int, int, int = 0, int = 0) const;
    virtual void onTouch(game::BattleScene&, game::Player& pl);
    virtual unsigned getExplodeDelay();
    virtual unsigned getExplosionLength();

    static Bomb* loadFromXml(TiXmlElement*, Map*);

    template <typename Derived>
    static Bomb* create(game::Player* pl)
    {
      return new Derived(pl);
    }

    BombState getState() const
    {
      return state_;
    }

  protected:
    game::Bomb* collideWithBomb(game::BattleScene&, int, int, int, int) const;
    void triggerBomb(game::BattleScene&, int, int, int, int);
    bool collideWithBlock(game::BattleScene&, int, int, int, int) const;
    void addExplosions(int, int, game::BattleScene&);
    void addExplosions(game::BattleScene&);
    void addExplosion(unsigned, unsigned, unsigned);

    BombState state_;
    utils::TimeManager timer_;

    explosions_t explosion_;

    /*!
     * Indique le possesseur de cette bombe,
     * si owner_ est à 0, alors la bombe
     * n'appartient à personne.
     */
    game::Player* owner_;

    /*!
     * Indique la puissance de la bombe.
     */
    unsigned fire_;

    /*!
     * Force la mise a feu.
     */
    bool forceExplosion_;
  };
};


#endif /* !GAME_BOMB_HH_ */
