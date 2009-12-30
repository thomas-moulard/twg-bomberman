#ifndef GAME_BATTLEOPTIONS_HH_
# define GAME_BATTLEOPTIONS_HH_
# include <string>
# include <vector>

# include "game/scene.hh"
# include "graphic/gui/choiceelement.hh"

namespace game
{
  class BattleOptionsScene : public Scene
  {
  public:
    typedef std::vector<graphic::gui::ChoiceElement*> vcelements_t;

    struct BattleSettings
    {
      enum gameType_t
        {
          GAME_TYPE_CLASSIC,
          GAME_TYPE_SURVIVAL
        };

      enum playerType_t
        {
          PLAYER_TYPE_HUMAN,
          PLAYER_TYPE_IA
        };
      typedef std::vector<playerType_t> playertypes_t;

      gameType_t gameType;
      std::string mapFilename;
      playertypes_t playerTypes;
    };

    BattleOptionsScene(BattleSettings&);
    BattleOptionsScene(const BattleOptionsScene&);

    ~BattleOptionsScene();

    BattleOptionsScene& operator=(const BattleOptionsScene&);

    void refreshColors();
    void changeChoice(unsigned);

    void setResults();

    void getMaps(std::vector<std::string>& v);

    virtual int play();
  private:
    BattleSettings& settings_;

    graphic::TextElement* title_;
    vcelements_t vcelements_;
    unsigned currentRow_;
    std::vector<std::string> maps_;
    bool skip_;
  };
};

#endif /* !GAME_BATTLEOPTIONS_HH_ */
