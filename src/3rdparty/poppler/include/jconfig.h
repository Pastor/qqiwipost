#define HAVE_PROTOTYPES
#define HAVE_UNSIGNED_CHAR
#define HAVE_UNSIGNED_SHORT
#define HAVE_STDDEF_H
#define HAVE_STDLIB_H

#define JPEG_STDIO_IN_HEADERS

#if defined(_WIN32)
    #if defined(libjpeg_EXPORTS)
        #define JPEG_EXPORT __declspec(dllexport)
    #else
        #define JPEG_EXPORT __declspec(dllimport)
    #endif
#else
    #define JPEG_EXPORT 
#endif

#ifdef _WIN32
# include <windows.h>
/* Define "boolean" as unsigned char, not int, per Windows custom */
# if !defined __RPCNDR_H__ || defined __MINGW32__    /* don't conflict if rpcndr.h already read */
#  ifndef boolean     /* don't conflict if rpcndr.h already read */
    typedef unsigned char boolean;
#  endif /* boolean */
# endif /* __RPCNDR_H__ */
# define HAVE_BOOLEAN     /* prevent jmorecfg.h from redefining it */
#endif /* _WIN32 */

#define GLOBAL(type) JPEG_EXPORT type
#define EXTERN(type) JPEG_EXPORT type
