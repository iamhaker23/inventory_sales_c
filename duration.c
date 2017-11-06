
#include <stdio.h>
#include <stdlib.h>

#include "duration.h"

typedef struct DurationStruct
{
    int hours, minutes, seconds;
}
Duration;

int duration_totalSeconds(const Duration *d)
{
    return d->seconds + 60*(d->minutes + 60*d->hours);
}

void duration_print(const Duration *d)
{
    printf("%02d:%02d:%02d", d->hours, d->minutes, d->seconds);
}

Duration* duration_new(int hours, int minutes, int seconds)
{
   Duration *d = (Duration*)malloc(sizeof(Duration));
   
   // TODO: check malloc successful
   
   d->hours   = hours;
   d->minutes = minutes;
   d->seconds = seconds;
   
   duration_normalise(d);
   
   return d;    
}

void duration_free(Duration *d)
{
    free(d);
}

Duration* duration_add(const Duration *d1, const Duration *d2)
{
    return duration_new(d1->hours   + d2->hours, 
                        d1->minutes + d2->minutes,
                        d1->seconds + d2->seconds);
}

int duration_compare(const Duration *d1, const Duration *d2)
{
    return duration_totalSeconds(d1) - duration_totalSeconds(d2);
}

void duration_normalise(Duration *d)
{
    d->seconds = duration_totalSeconds(d);
    d->minutes = d->seconds/60;
    d->seconds = d->seconds%60;
    d->hours   = d->minutes/60;
    d->minutes = d->minutes%60;
}

int duration_getHours(const Duration *d)
{
    return d->hours;
}

int duration_getMinutes(const Duration *d)
{
    return d->minutes;
}

int duration_getSeconds(const Duration *d)
{
   return d->seconds;    
}

int duration_ascending(const void *a, const void *b)
{
   return duration_compare(*(Duration**)a, *(Duration**)b);    
}