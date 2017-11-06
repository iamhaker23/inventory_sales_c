
#ifndef DURATION_H
#define DURATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DurationStruct Duration;

Duration* duration_new(int hours, int minutes, int seconds);

void duration_free(Duration *d);

void duration_print(const Duration *d);

void duration_normalise(Duration *d);

int duration_getHours(const Duration *d);

int duration_getMinutes(const Duration *d);

int duration_getSeconds(const Duration *d);

Duration* duration_add(const Duration *d1, const Duration *d2);

int duration_compare(const Duration *d1, const Duration *d2);

int duration_ascending(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif /* DURATION_H */
