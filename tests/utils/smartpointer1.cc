#include <iostream>
#include <vector>
#include "utils/smartpointer.hh"

using namespace utils;

struct Dummy
{
  Dummy() :
  foo_ (0)
  {
    foo_ = new int(42);
  }

  ~Dummy()
  {
    delete foo_;
  }

  int* foo_;
};

int main()
{
  SmartPointer<int> sp1;
  std::cout << !!sp1 << std::endl;

  SmartPointer<int> sp2 = SmartPointer<int>(new int(42), DP_ALWAYS);
  SmartPointer<int> sp2b = SmartPointer<int>(new int(51));
  std::cout << !!sp2 << std::endl;

  SmartPointer<int> sp3 = SmartPointer<int>(sp2);
  std::cout << (sp3 == sp2) << std::endl;
  std::cout << (sp3 != sp2) << std::endl;

  {
    SmartPointer<int> sp3 = SmartPointer<int>(sp2);
    {
      SmartPointer<int> sp4 = SmartPointer<int>(sp2);
      SmartPointer<int> sp5 = SmartPointer<int>(sp4);
      {
	SmartPointer<int> sp6 = SmartPointer<int>(sp2);
      }
      SmartPointer<int> sp7 = SmartPointer<int>(sp5);
    }
  }

  {
    SmartPointer<unsigned> sp3 = sp2;
    sp3.reset();
  }

  {
    SmartPointer<int> sp = SmartPointer<int>(new int(42), DP_ENDOFLEVEL);
    sp.endoflevel(); // sans cette ligne, une fuite mémoire se produit!
  }

  std::cout << "valeur du smart pointer: " << *sp3 << std::endl;

  {
    typedef SmartPointer<Dummy> pt_t;
    typedef std::vector<pt_t> spvec_t;

    spvec_t vec;
    for (int i=0; i < 42; i++)
      {
        vec.push_back(pt_t(new Dummy));
      }
    vec.clear();
  }

  N() << "fin du programme" << std::endl;
}
