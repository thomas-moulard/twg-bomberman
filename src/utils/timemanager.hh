/**
 * \file utils/timemanager.hh
 * \brief Déclaration de Utils::TimeManager.
 */
#ifndef UTILS_TIMEMANAGER_HH_
# define UTILS_TIMEMANAGER_HH_
# include <SDL/SDL.h>

# include "utils/debug.hh"

namespace utils
{
  class TimeManager
  {
  public:
    TimeManager(unsigned delay);
    TimeManager(const TimeManager&);

    ~TimeManager();

    TimeManager& operator=(const TimeManager&);

    /**
     * Indique si le temps d'attente avant la fin du chrono
     * est dépassée ou pas.
     *
     * \param reinit Réinitialisation du chrono après l'appel?
     * \return est-ce que le temps est écoulé?
     */
    bool is_time(bool reinit);
    void DelayUtilEnd(bool reinit);

    Uint32 TimeElapsed()
    {
        return SDL_GetTicks() - startTime_;
    }

    Uint32 TimeLeft()
    {
      if(!timeLeftWhenPaused_)
      {
          Uint32 time = delay_ - SDL_GetTicks() - startTime_;
          return (time > 0) ? time : 0;
      }
      return timeLeftWhenPaused_;
    }


    static void delay(Uint32 ms)
    {
      SDL_Delay(ms);
    }

    void pause();
    void resume();
    void reset(unsigned delay);

    unsigned getDelay() const
    {
      return delay_;
    }

    bool isPaused() const
    {
      return isPaused_;
    }

  private:
    unsigned startTime_;
    unsigned delay_;
    bool repeat_;
    bool isPaused_;
    unsigned timeLeftWhenPaused_;
  };
};


#endif /* !UTILS_TIMEMANAGER_HH_ */
