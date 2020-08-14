#ifndef __CONSTANT_4__
#define __CONSTANT_4__

// turn on 1 in these!
// #define TEST_ZOMBIE_WAIT
// #define TEST_ZOMBIE_WAITPID
// #define TEST_ZOMBIE_SIGNAL
#define TEST_ZOMBIE_SIGACTION

#if (defined TEST_ZOMBIE_WAIT) \
	|| (defined TEST_ZOMBIE_WAITPID) \
	|| (defined TEST_ZOMBIE_SIGNAL) \
	|| (defined TEST_ZOMBIE_SIGACTION) \

#define TEST_ZOMBIE
#endif

#endif