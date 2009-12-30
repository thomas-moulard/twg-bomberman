#ifndef GAME_IA_BEHAVIOR_HH_
# define GAME_IA_BEHAVIOR_HH_
# include "game/iaplayer.hh"
# include "game/battlescene.hh"

namespace game
{
  class IAPlayer;

  namespace ia
  {
    class Behavior
    {
    public:
      Behavior(game::IAPlayer&);
      Behavior(const Behavior&);

      virtual ~Behavior();

      Behavior& operator=(const Behavior&);

      virtual void play(game::BattleScene&) = 0;

    protected:
      game::IAPlayer& player_;
    };

  }; // End of namespace ia
}; // End of namespace game

#endif /* !GAME::IA_BEHAVIOR_HH_ */
