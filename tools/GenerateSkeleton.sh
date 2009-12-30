#! /bin/sh

function usage
{
    echo "Usage: $0 <class> [<namespace>]"
    exit 1
}

if [ "$#" -lt '1' ]; then
    usage
fi
if [ "$#" -gt '2' ]; then
    usage
fi

class="$1"
UppersizeClass=`echo "$1" | tr '[A-Za-z]' '[A-ZA-Z]'`
LowersizeClass=`echo "$1" | tr '[a-zA-Z]' '[a-za-z]'`

if [ "$#" -eq '2' ]; then
    package="$2"
    UppersizePackage=`echo "$2" | tr '[a-z]' '[A-Z]'`
    LowersizePackage=`echo "$2" | tr '[A-Z]' '[a-z]'`

    echo "#ifndef ""$UppersizePackage""_""$UppersizeClass""_HH_
# define ""$UppersizePackage""_""$UppersizeClass""_HH_

namespace $package
{
   class $class
   {
     public:
       $class();
       $class(const $class&);

       ~$class();

       $class& operator=(const $class&);

     private:
   };

}; // End of namespace $package


#endif /* !""$UppersizePackage""_""$UppersizeClass""_HH_ */" > "$LowersizeClass.hh"

    echo "#include \"$LowersizePackage/$LowersizeClass.hh\"

namespace $package
{
   $class::$class()
   {
   }

   $class::$class(const $class&)
   {
   }

   $class::~$class()
   {
   }

   $class&
   $class::operator=(const $class&)
   {
      return *this;
   }

}; // End of namespace $package
" > "$LowersizeClass.cc"
else
    echo "#ifndef ""$UppersizeClass""_HH_
# define ""$UppersizeClass""_HH_

class $class
{
  public:
    $class();
    $class(const $class&);

    ~$class();

    $class& operator=(const $class&);

  private:
};

#endif /* !""$UppersizeClass""_HH_ */" > "$LowersizeClass.hh"

    echo "#include \"$LowersizeClass.hh\"

$class::$class()
{
}

$class::$class(const $class&)
{
}

$class::~$class()
{
}

$class&
$class::operator=(const $class&)
{
   return *this;
}

" > "$LowersizeClass.cc"
fi

echo "Les fichiers ont été générés avec succès."
