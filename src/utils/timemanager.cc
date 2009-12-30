#include "utils/timemanager.hh"

namespace utils
{
  TimeManager::TimeManager(unsigned delay) :
    startTime_ (SDL_GetTicks()),
    delay_ (delay),
    repeat_ (true),
    isPaused_ (false),
    timeLeftWhenPaused_ (0)
  {
  }

  TimeManager::TimeManager(const TimeManager& tm) :
    startTime_ (tm.startTime_),
    delay_ (tm.delay_),
    repeat_ (tm.repeat_),
    isPaused_ (tm.isPaused_),
    timeLeftWhenPaused_ (tm.timeLeftWhenPaused_)
  {
  }

  TimeManager::~TimeManager()
  {
  }

  TimeManager&
  TimeManager::operator=(const TimeManager& tm)
  {
    startTime_ = tm.startTime_;
    delay_ = tm.delay_;
    isPaused_ = tm.isPaused_;
    repeat_ = tm.repeat_;
    timeLeftWhenPaused_ = tm.timeLeftWhenPaused_;
    return *this;
  }

  bool
  TimeManager::is_time(bool reinit)
  {
    if (!isPaused_ && delay_ && SDL_GetTicks() - startTime_ >= delay_)
      {
	if (reinit)
	  {
	    startTime_ = SDL_GetTicks();
	    if (!repeat_)
	      delay_ = 0;
	  }
	return true;
      }
    return false;
  }

  void
  TimeManager::DelayUtilEnd(bool reinit)
  {
      Uint32 time;

      if (isPaused_ || !delay_)
	return;

      if (SDL_GetTicks() - startTime_ >= delay_)
	time = 0;
      else
	time = delay_ - (SDL_GetTicks() - startTime_);

      if (time > 0)
        delay(time);

      if (reinit)
      {
        startTime_ = SDL_GetTicks();
        if (!repeat_)
          delay_ = 0;
      }
  }

  void TimeManager::pause()
  {
    if (!delay_)
      return;

    isPaused_ = true;
    timeLeftWhenPaused_ = (startTime_ + delay_) - SDL_GetTicks();
  }

  void TimeManager::resume()
  {
    if (!delay_)
      return;

    if (!isPaused_)
      return;
    isPaused_ = false;
    startTime_ = SDL_GetTicks() - delay_ + timeLeftWhenPaused_;
    timeLeftWhenPaused_ = 0;
  }

  void TimeManager::reset(unsigned delay)
  {
    isPaused_ = false;
    repeat_ = true;
    delay_ = delay;
    startTime_ = SDL_GetTicks();
  }
};
