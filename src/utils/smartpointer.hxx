/**
 * \file utils/smartpointer.hxx
 * \brief Implémentation de Util::SmartPointer.
 */
#ifndef UTILS_SMARTPOINTER_HXX_
# define UTILS_SMARTPOINTER_HXX_
# include <cassert>
# include <typeinfo> // Pour std::bad_cast

# include "graphic/graphicmanager.hh"
# include "utils/debug.hh"
# include "utils/gettext.hh"

namespace utils
{
  template <typename T>
  SmartPointer<T>::SmartPointer() :
    pointer_ (0),
    metainfo_ (0)
  {
    //NOTICE() << "SmartPointer<T>::SmartPointer()" << std::endl;
  }

  template <typename T>
  SmartPointer<T>::SmartPointer(T* p,
				DesallocationPolicy_t dp = DP_ALWAYS) :
    pointer_ (p),
    metainfo_ (0)
  {
    /*
    NOTICE() << "SmartPointer<T>::SmartPointer(T*, DesallocationPolicy_t)"
	     << std::endl;
    */

    metainfo_ = new Metainfo;
    assert(metainfo_);
    metainfo_->countRef_ = 1;
    metainfo_->desallocationPolicy_ = dp;
  }

  template <typename T>
  SmartPointer<T>::SmartPointer(const SmartPointer<T>& ptr) :
    pointer_ (0),
    metainfo_ (0)
  {
    /*
    NOTICE() << "SmartPointer<T>::SmartPointer(const SmartPointer<T>& ptr)"
	     << std::endl;
    */

    if (ptr.pointer_ && ptr.metainfo_)
      ++ptr.metainfo_->countRef_;
    share(ptr.pointer_, ptr.metainfo_);
  }

  template <typename T>
  template <typename U>
  SmartPointer<T>::SmartPointer(const SmartPointer<U>& ptr) :
    pointer_ (0),
    metainfo_ (0)
  {
    /*
    NOTICE() << "SmartPointer<T>::SmartPointer(const SmartPointer<U>& ptr)"
	     << std::endl;
    */

    if (ptr.pointer_ && ptr.metainfo_)
      ++ptr.metainfo_->countRef_;
    share(reinterpret_cast<T*>(ptr.pointer_), ptr.metainfo_);
  }

  template <typename T>
  SmartPointer<T>::~SmartPointer()
  {
    //NOTICE() << "SmartPointer<T>::~SmartPointer()" << std::endl;
    dispose();
  }

  template <typename T>
  template <typename U>
  SmartPointer<T>&
  SmartPointer<T>::operator=(const SmartPointer<U>& sp)
  {
    /*
    NOTICE() << "SmartPointer<T>::operator=(const SmartPointer<U>& sp)"
	     << std::endl;
    */
    if (this == &sp)
      return *this;
    pointer_ = 0;
    metainfo_ = 0;
    share(sp.pointer_, sp.metainfo_);
    assert(pointer_ == sp.pointer_ && metainfo_ == sp.metainfo_);
    ++sp.metainfo_->countRef;
    return *this;
  }

  template <typename T>
  void
  SmartPointer<T>::reset()
  {
    //NOTICE() << "SmartPointer<T>::reset()" << std::endl;
    dispose();
    pointer_ = 0;
    metainfo_ = 0;
  }

  template <typename T>
  void
  SmartPointer<T>::endoflevel()
  {
    //NOTICE() << "SmartPointer<T>::endoflevel()" << std::endl;
    if (metainfo_
	&& !metainfo_->countRef_
	&& pointer_
	&& metainfo_->desallocationPolicy_ == DP_ENDOFLEVEL)
	  {
	    NOTICE() << "pointeur " << pointer_ << " supprime (eol)"
		     << std::endl;
	    delete pointer_;
	    delete metainfo_;
	    pointer_ = 0;
	    metainfo_ = 0;
	  }
  }

  template <typename T>
  T&
  SmartPointer<T>::operator*() const
  {
    //NOTICE() << "SmartPointer<T>::operator*() const" << std::endl;
    return *this->pointer_;
  }

  template <typename T>
  T*
  SmartPointer<T>::operator->() const
  {
    //NOTICE() << "SmartPointer<T>::operator->() const" << std::endl;
    return this->pointer_;
  }

  template <typename T>
  template <typename U>
  bool
  SmartPointer<T>::operator==(const SmartPointer<U>& sp) const
  {
    /*
    NOTICE() << "SmartPointer<T>::operator==(const SmartPointer<U>& sp) const"
	     << std::endl;
    */
    return pointer_ == sp.pointer_;
  }

  template <typename T>
  template <typename U>
  bool
  SmartPointer<T>::operator!=(const SmartPointer<U>& sp) const
  {
    /*
    NOTICE() << "SmartPointer<T>::operator!=(const SmartPointer<U>& sp) const"
	     << std::endl;
    */
    return !(*this == sp);
  }

  template <typename T>
  SmartPointer<T>::operator bool() const
  {
    //NOTICE() << "SmartPointer<T>::operator bool() const" << std::endl;
    return !!pointer_;
  }

  template <typename T>
  template <typename U>
  SmartPointer<U>
  SmartPointer<T>::cast() const
  {
    //NOTICE() << "SmartPointer<T>::cast() const" << std::endl;
    U* tmp = dynamic_cast<U*>(pointer_);
    if (!tmp)
      throw std::bad_cast();
    SmartPointer<U> res = SmartPointer();
    res.share(pointer_, metainfo_);
    return res;
  }

  template <typename T>
  template <typename U>
  SmartPointer<U>
  SmartPointer<T>::unsafe_cast() const
  {
    //NOTICE() << "SmartPointer<T>::unsafe_cast() const" << std::endl;
    return SmartPointer(*this);
  }

  template <typename T>
  template <typename U>
  bool
  SmartPointer<T>::is_a(SmartPointer<U>& ptr) const
  {
    //NOTICE() << "SmartPointer<T>::is_a(SmartPointer<U>&) const" << std::endl;
    return !!dynamic_cast<T*>(ptr.pointer_);
  }

  template <typename T>
  SmartPointer<T>::SmartPointer(T* p,
				unsigned cnt,
				DesallocationPolicy_t dp)
  {
    /*
    NOTICE() << "SmartPointer<T>::SmartPointer(T*, unsigned, DesaPolicy_t)"
	     << std::endl;
    */
    pointer_ = p;
    if (pointer_)
      dispose();

    metainfo_ = new Metainfo;
    assert(metainfo_);
    metainfo_->countRef_ = cnt;
    metainfo_->desallocationPolicy_ = dp;
  }

  template <typename T>
  void
  SmartPointer<T>::dispose()
  {
    //NOTICE() << "SmartPointer<T>::dispose()" << std::endl;

    if (metainfo_)
      {
	if (metainfo_->countRef_)
	  --metainfo_->countRef_;
	else
          ERROR() << "compteur nul mais les metainfo existent" << std::endl;
	if (!metainfo_->countRef_ && pointer_ &&
	    metainfo_->desallocationPolicy_ == DP_ALWAYS)
	  {
	    //NOTICE() << "pointeur " << pointer_ << " supprime " << std::endl;
	    delete pointer_;
	    delete metainfo_;
	    pointer_ = 0;
	    metainfo_ = 0;
	  }
      }
  }

  template <typename T>
  void
  SmartPointer<T>::share(T* p, Metainfo* mi)
  {
    NOTICE() << "SmartPointer<T>::share()" << std::endl;
    dispose();
    pointer_ = p;
    metainfo_ = mi;
  }
};

#endif /* !UTILS_SMARTPOINTER_HXX_ */
