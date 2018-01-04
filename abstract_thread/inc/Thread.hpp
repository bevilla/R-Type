#pragme once

#include	"AThread.hpp"

#if defined(__linux__)
# include	"UnixThread.hpp"
#elif defined(WIN32)
# include	"WinThread.hpp"
#endif

typedef void	*(func)(void *);

AThread		*getThread(func f);
