/**
 * \file utils/smartpointer.hh
 * \brief Déclaration de Util::SmartPointer.
 */
#ifndef UTILS_SMARTPOINTER_HH_
# define UTILS_SMARTPOINTER_HH_

/*
 * ATTENTION - SMARTPOINTERS SPECIAUX!
 * => cf. gestion de la politique de désallocation.
 */

namespace utils
{
  typedef unsigned DesallocationPolicy_t;
  static const DesallocationPolicy_t DP_ALWAYS = 0;
  static const DesallocationPolicy_t DP_ENDOFLEVEL = 1;
  static const DesallocationPolicy_t DP_ENDOFGAME = 2;

  namespace {
    class Metainfo
    {
    public:
      unsigned                countRef_;
      DesallocationPolicy_t   desallocationPolicy_;
    };
  };

  template <typename T>
  class SmartPointer
  {
  public:
    typedef T element_t;

    /** Crée un SmartPointer vide. */
    SmartPointer();

    /** Crée un SmartPointer à partir d'un pointeur. */
    SmartPointer(T*, DesallocationPolicy_t);

    /** Crée un SmartPointer à partir d'un deuxième. */
    SmartPointer(const SmartPointer<T>&);

    template <typename U>
    SmartPointer(const SmartPointer<U>&);

    /**
     * Destruction du SmartPointer (n'entraine pas la désallocation
     * de la ressource.
     */
    ~SmartPointer();

    /**
     * Copie un SmartPointer.
     */
    template <typename U>
    SmartPointer& operator=(const SmartPointer<U>&);

    /**
     * Remise à zéro du SmartPointer.
     */
    void reset();

    void endoflevel();


    T& operator*() const;

    T* operator->() const;

    template <typename U>
    bool operator==(const SmartPointer<U>&) const;

    template <typename U>
    bool operator!=(const SmartPointer<U>&) const;

    bool operator!=(const T*) const;

    /**
     * Renvoit vrai si le SmartPointer est initialisé.
     */
    operator bool() const;

    template <typename U>
    SmartPointer<U> cast() const;

    template <typename U>
    SmartPointer<U> unsafe_cast() const;

    template <typename U>
    bool is_a(SmartPointer<U>&) const;
  protected:
    template <typename U>
    friend class SmartPointer;

    SmartPointer(T*, unsigned, DesallocationPolicy_t);

    void dispose();

    void share(T*, Metainfo*);

    T*          pointer_;
    Metainfo*   metainfo_;
  };
};

# include "utils/smartpointer.hxx"
#endif /* !UTILS_SMARTPOINTER_HH_ */









