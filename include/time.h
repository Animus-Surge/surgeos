/**
 * SurgeOS libc time.h
 * Time types
 */

#ifndef SURGEOS_TIME_H
#define SURGEOS_TIME_H

#include <sys/cdefs.h>
#include <sys/types.h>

__EXTC

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
} tm;

#define CLK_TCK 100
#define CLOCKS_PER_SEC 1000000

typedef struct {
  time_t tv_sec;
  long tv_nsec;
} timespec;

typedef struct {
  timespec it_interval;
  timespec it_value;
} itimerspec;

extern int daylight;
extern long timezone;
extern char *tzname[];

char* asctime(const tm*);
char* asctime_r(const tm*, char*);
clock_t clock(void);
int clock_getres(clockid_t, timespec*);
int clock_gettime(clockid_t, timespec*);
int clock_settime(clockid_t, const timespec*);
char* ctime(const time_t*);
char* ctime_r(const time_t*, char*);
double difftime(time_t, time_t);
tm* getdate(const time_t*);
tm* gmtime(const time_t*);
tm* gmtime_r(const time_t*, tm*);
tm* localtime(const time_t*);
tm* localtime_r(const time_t*, tm*);
time_t mktime(tm*);
int nanosleep(const timespec*, timespec*);
size_t strftime(char*, size_t, const char*, const tm*);
char* strptime(const char*, const char*, tm*);
time_t time(time_t*);
int timer_create(clockid_t, const struct sigevent*, timer_t*);
int timer_delete(timer_t);
int timer_gettime(timer_t, itimerspec*);
int timer_getoverrun(timer_t);
int timer_settime(timer_t, int, const itimerspec*, itimerspec*);
void tzset(void);

__EXTC_END

#endif // SURGEOS_TIME_H

