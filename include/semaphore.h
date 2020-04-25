/* Copyright (C) 2002-2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H    1

#include <features.h>
#include <sys/types.h>

#include <bits/wordsize.h>

#if __WORDSIZE == 64
# define __SIZEOF_SEM_T        32
#else
# define __SIZEOF_SEM_T        16
#endif


/* Value returned if `sem_open' failed.  */
#define SEM_FAILED      ((sem_t *) 0)


typedef union
{
    char __size[__SIZEOF_SEM_T];
    long int __align;
} sem_t;

__BEGIN_DECLS

/* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
   with other processes.  */
    extern int sem_init(sem_t* __sem, int __pshared, unsigned int __value)
    __THROW __nonnull((1));

/* Free resources associated with semaphore object SEM.  */
extern int sem_destroy(sem_t* __sem) __THROW __nonnull((1));

/* Open a named semaphore NAME with open flags OFLAG.  */
extern sem_t* sem_open(const char* __name, int __oflag, ...)
__THROW __nonnull((1));

/* Close descriptor for named semaphore SEM.  */
extern int sem_close(sem_t* __sem) __THROW __nonnull((1));

/* Remove named semaphore NAME.  */
extern int sem_unlink(const char* __name) __THROW __nonnull((1));

/* Wait for SEM being posted.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int sem_wait(sem_t* __sem) __nonnull((1));

#ifdef __USE_XOPEN2K
/* Similar to `sem_wait' but wait only until ABSTIME.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int sem_timedwait(sem_t* __restrict __sem,
    const struct timespec* __restrict __abstime)
    __nonnull((1, 2));
#endif

#ifdef __USE_GNU
extern int sem_clockwait(sem_t* __restrict __sem,
    clockid_t clock,
    const struct timespec* __restrict __abstime)
    __nonnull((1, 3));
#endif

/* Test whether SEM is posted.  */
extern int sem_trywait(sem_t* __sem) __THROWNL __nonnull((1));

/* Post SEM.  */
extern int sem_post(sem_t* __sem) __THROWNL __nonnull((1));

/* Get current value of SEM and store it in *SVAL.  */
extern int sem_getvalue(sem_t* __restrict __sem, int* __restrict __sval)
__THROW __nonnull((1, 2));


__END_DECLS

#endif  /* semaphore.h */