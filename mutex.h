#ifndef _MUTEX_HELPER_H_
#define _MUTEX_HELPER_H_

#if defined(_MSC_VER)
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN  // We only need minimal includes
# endif

# include <windows.h>
  typedef CRITICAL_SECTION MutexType;

#elif defined(__GNUC__)
# include <pthread.h>
  typedef pthread_mutex_t MutexType;
#endif

#include <assert.h>

namespace Helper {

class Mutex {
	
public:
	// Create a Mutex that is not held by anybody.  This constructor is
	// typically used for Mutexes allocated on the heap or the stack.
	// See below for a recommendation for constructing global Mutex
	// objects.
	inline Mutex();

	// Destructor
	inline ~Mutex();

	inline void Lock();    // Block if needed until free then acquire exclusively
	inline void Unlock();  // Release a lock acquired via Lock()

private:
	MutexType mutex_;

	// Catch the error of writing Mutex when intending MutexLock.
	Mutex(Mutex* /*ignored*/) {}
	// Disallow "evil" constructors
	Mutex(const Mutex&);
	void operator=(const Mutex&);
};

// Now the implementation of Mutex for various systems
#if defined(_MSC_VER)

Mutex::Mutex()             { InitializeCriticalSection(&mutex_); }
Mutex::~Mutex()            { DeleteCriticalSection(&mutex_); }
void Mutex::Lock()         { EnterCriticalSection(&mutex_); }
void Mutex::Unlock()       { LeaveCriticalSection(&mutex_); }

#elif defined(__GNUC__)

#define SAFE_PTHREAD(fncall)  do {   /* run fncall if is_safe_ is true */  \
  if ( fncall(&mutex_) != 0) abort();                           \
} while (0)

Mutex::Mutex()            
{
  SetIsSafe();
  if (pthread_mutex_init(&mutex_, NULL) != 0) abort();
}
Mutex::~Mutex()            { SAFE_PTHREAD(pthread_mutex_destroy); }
void Mutex::Lock()         { SAFE_PTHREAD(pthread_mutex_lock); }
void Mutex::Unlock()       { SAFE_PTHREAD(pthread_mutex_unlock); }

#endif

// --------------------------------------------------------------------------
// Some helper classes

// MutexLock(mu) acquires mu when constructed and releases it when destroyed.
class MutexLock {
public:
	explicit MutexLock(Mutex *mu) : mu_(mu) { mu_->Lock(); }
	~MutexLock() { mu_->Unlock(); }
private:
	Mutex * const mu_;
	// Disallow "evil" constructors
	MutexLock(const MutexLock&);
	void operator=(const MutexLock&);
};

} // end namespace Helper



#endif  /* #define GOOGLE_MUTEX_H__ */
