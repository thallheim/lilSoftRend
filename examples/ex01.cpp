#include "../include/lilSoftRend.hpp"
#include "../include/input.hpp"
#include "enums.hpp"
#include "types/colour.hpp"
#include <stdexcept>
#include <unistd.h>


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60


#include <print>
#include <map>
#include <unistd.h>
#include <X11/Xlib.h>

// using namespace lsr;
using std::print;

int main()
{
  lsr::Renderer r; // Init renderer

  Window win = XCreateSimpleWindow(
      r.display, DefaultRootWindow(r.display), 0, 0, W_WIDTH, W_HEIGHT, 0,
      0x0, // border colour - hardcoded for now (along with 0 border width)
      NamedColour.at(ColourToString.at(BaseColour::Black)));

  // Create a window
  Window win2 = r.CreateWindow(r.display, &DefaultRootWindow(r.display),
                               BaseColour::Black, BaseColour::Red, "Woo");

  // Select MapNotify events
  XSelectInput(r.display, win, StructureNotifyMask);
  XSelectInput(r.display, win2, StructureNotifyMask);

  // Map window
  XMapWindow(r.display, win);
  XMapWindow(r.display, win2);

  // Create graphics ctx
  GC gc = XCreateGC(r.display, win, 0, NULL);
  GC gc2 = XCreateGC(r.display, win2, 0, NULL);

  // Tell the GC we draw using the white color
  XSetForeground(r.display, gc,
                 NamedColour.at(ColourToString.at(BaseColour::White)));
  XSetForeground(r.display, gc2,
                 NamedColour.at(ColourToString.at(BaseColour::White)));

  // Wait for the MapNotify event
  for(;;) {
    XEvent e;
    XNextEvent(r.display, &e);
    if (e.type == MapNotify)
      break;
  }

  // Draw the line
  XDrawLine(r.display, win, gc, 10, 60, 180, 20);
  XDrawLine(r.display, win2, gc2, 20, 70, 180, 20);

  // Send the "DrawLine" request to the server
  XFlush(r.display);

  // Wait
  pause();

  return 0;
}
