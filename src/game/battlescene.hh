#ifndef GAME_BATTLESCENE_HH_
# define GAME_BATTLESCENE_HH_
# include <vector>

# include "game/map.hh"
# include "game/scene.hh"
# include "utils/timemanager.hh"

namespace graphic
{
  class TextElement;
}; // End of namespace graphic

namespace game
{
  class Player;
  class Map;

  class BattleScene : public Scene
  {
  public:
    typedef std::vector<Player*> players_t;

    BattleScene(const char* filename);
    BattleScene(const BattleScene&);

    ~BattleScene();

    BattleScene& operator=(const BattleScene&);

    static const unsigned MAX_PLAYERS = 4;

    virtual int play();

    void outOfTime();

    void addPlayer(Player*);

    Map* getCurrentMap()
    {
      return map_;
    }

    players_t& get_players()
    {
      return players_;
    }

    unsigned getDefaultBattleLength() const;
    unsigned outOfTimeDelay() const;
  private:
    players_t players_;
    bool isPaused_;
    graphic::TextElement* pauseText_;
    Map* map_;
    bool outoftime_;
    utils::TimeManager timer_;
    bool skipCount_;

    /*!
     * Compte le nombre de joueurs encore vivant.
     */
    unsigned nbPlayerAlive() const;

    void render();
    void handle();
    void playersPlay();

    void showCount();
    void switchPause();
  };
}; // End of namespace game


#endif /* !GAME_BATTLESCENE_HH_ */

