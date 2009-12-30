#ifndef PORTABLE_HH_

/*
 * lstat n'existe pas sous Windows.
 * On utilisera donc stat à la place.
 */
# ifdef WIN32
#  define lstat stat
# endif /* !WIN32 */


/*
 * stracasecmp se nomme _stricmp
 * lorsque l'on utilise Visual C++.
 */
#ifdef MSVS8
# define strcasecmp _stricmp
#endif

#endif /* PORTABLE_HH_ */
