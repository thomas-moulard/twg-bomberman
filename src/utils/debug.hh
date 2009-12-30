/*!
* \file utils/debug.hh
* \brief Contient le n√©cessaire pour g√©rer le d√©bug.
*/
#ifndef UTILS_DEBUG_HH_
# define UTILS_DEBUG_HH_
# include <iostream>
# include <fstream>

# if !defined ( NDEBUG ) && !defined ( DEBUG )
#  define DEBUG() utils::Debug::get_instance()->get_flow()

#  define __PRINTERROR(x)         \
  DEBUG() << __FILE__ << ":"      \
          << __LINE__ << ":"      \
          << (x) << ":"

#  define NOTICE() __PRINTERROR(_("notice"))
#  define WARNING() __PRINTERROR(_("warning"))
#  define ERROR() __PRINTERROR(_("error"))
# else
// FIXME: il faudrait crÈer un "dummy"-flow
// afin de supprimer les sorties de debug en mode release sans perte
// de vitesse.
#  define NOTICE() std::cout
#  define WARNING() std::cout
#  define ERROR() std::cout
# endif

// Alias trËs courts ‡ utiliser pendant le dÈbug, mais ne laissez pas
// ces macro dans le code en permanence.
#  define N() NOTICE()
#  define W() WARNING()
#  define E() ERROR()

namespace utils
{
  class Debug
  {
  public:
    static Debug* get_instance()
    {
      if (!instance_)
	instance_ = new Debug();
      return instance_;
    }
    static void kill()
    {
      if (instance_)
      delete instance_;
    }

    std::ostream& get_flow()
    {
      if (debug_file)
	return fp_;
      return std::cerr;
    }
  private:
    Debug();
    Debug(const Debug&);

    ~Debug();

    Debug& operator=(const Debug&);


    static Debug* instance_;
    static const bool debug_file = false;

    std::ofstream fp_;
  };
};

#endif /* !UTILS_DEBUG_HH_ */
