#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <xcb/xcb.h>
#include <X11/Xlib.h>
#define NUM_NAMES 500
/*
  NOTE: For concision, we're going to be cheesy and use arrays where real code
  would use points and memory allocation.s
*/
#ifndef __GNUC__
char* strdup(const char* s) {
  int n = strlen(s) + 1;

  char *dup = malloc(n);

  if(dup)
    strcpy(dup, s);

  return dup;
}
#endif

/*
  return interval of time (uses time.h)
*/
double
get_time (void) {
  struct timeval timev;
  gettimeofday(&timev, NULL);
  return (double)timev.tv_sec + (((double)timev.tv_usec) / 1000000);
}


/*
  Request all atoms at once.
*/


int
main () {
  /* setup names for tests */
  double start, XlibTime, XlibGoodTime, XCBBadTime, XCBGoodTime;

  /* test XCB */
  xcb_connection_t *connection = xcb_connect (NULL, NULL);
  start = get_time ();

  XCBGoodTime = get_time () - start;
  xcb_disconnect(connection);

  /* report times */
  printf ("Start time    : %f\n", start);
  printf ("Good xcb time : %f\n", XCBGoodTime);

  return 0;
}
