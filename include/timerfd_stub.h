//
// Created by Saleem Hamo on 25/03/2024.
//
// timerfd_stub.h

#ifdef __APPLE__
#pragma once

#include <unistd.h>
#include <sys/time.h>


#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif

#ifndef TFD_NONBLOCK
#define TFD_NONBLOCK O_NONBLOCK
#endif

struct itimerspec {
    struct timespec it_interval; /* Timer interval */
    struct timespec it_value;    /* Initial expiration */
};

// Simulate the timerfd_create function for macOS.
static inline int timerfd_create(int clockid, int flags) {
    return -1; // Return an invalid file descriptor.
}

// Simulate the timerfd_settime function for macOS.
static inline int timerfd_settime(int fd, int flags,
                                  const struct itimerspec *new_value,
                                  struct itimerspec *old_value) {
    return 0; // Pretend success
}

// Simulate the timerfd_gettime function for macOS.
static inline int timerfd_gettime(int fd, struct itimerspec *curr_value) {
    return 0; // Pretend success
}

#endif // __APPLE__

