#ifndef GAME_IA_RANDOMBEHAVIOR_HH_
# define GAME_IA_RANDOMBEHAVIOR_HH_
# include "game/ia/behavior.hh"
# include "game/iaplayer.hh"
# include "game/battlescene.hh"

namespace game
{
  namespace ia
  {
    class RandomBehavior : public Behavior
    {
    public:
      RandomBehavior(game::IAPlayer&);
      RandomBehavior(const RandomBehavior&);

      ~RandomBehavior();

      RandomBehavior& operator=(const RandomBehavior&);

      virtual void play(game::BattleScene&);
    private:
    };

  }; // End of namespace ia
}; // End of namespace game

#endif /* !GAME::IA_RANDOMBEHAVIOR_HH_ */
