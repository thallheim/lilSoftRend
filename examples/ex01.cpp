#include "../include/input.hpp"
#include "../include/enums.hpp"
#include "../include/types.hpp"
#include "../include/lilSoftRend.hpp"
#include "types/colour.hpp"
#include <map>
#include <print>
#include <stdexcept>
#include <unistd.h>
#include <X11/Xlib.h>


#define W_WIDTH    800
#define W_HEIGHT   600
#define TARGET_FPS 60



// using namespace lsr;
using std::print;

int main()
{
  lsr::Renderer r; // Init renderer

  // Create a window
  r.NewWindow(r.display, DefaultRootWindow(r.display),
                 BaseColour::Black, BaseColour::Red, "Test", "_test_");

  r.NewWindow(r.display, DefaultRootWindow(r.display),
                 BaseColour::Black, BaseColour::Red, "Hey", "Woo");

  // Select MapNotify events
  // TODO: XSelectinput() wrapper
  XSelectInput(r.display, r.GetWindowByName("Test"), StructureNotifyMask);
  XSelectInput(r.display, r.GetWindowByName("Hey"), StructureNotifyMask);

  // Map window
  XMapWindow(r.display, r.GetWindowByName("Test"));
  XMapWindow(r.display, r.GetWindowByName("Hey"));


  // Create graphics ctx
  r.NewGC("Test", r.GetWindowByName("Test"));
  r.NewGC("hey", r.GetWindowByName("Hey"));

  // Set colours
  XSetForeground(r.display, r.GetGCByName("Test"), NamedColour.at(LSR_WHITE));
  XSetForeground(r.display, r.GetGCByName("hey"), NamedColour.at(LSR_WHITE));

  // Wait for the MapNotify event
  for(;;) {
    XEvent e;
    XNextEvent(r.display, &e);
    if (e.type == MapNotify)
      break;
  }

  // Draw
  XDrawLine(r.display, r.GetWindowByName("Test"),
            r.GetGCByName("Test"), 10, 10, 180, 40);

  XDrawLine(r.display, r.GetWindowByName("Hey"),
            r.GetGCByName("hey"), 10, 40, 180, 10);

  // Send the "DrawLine" request to the server
  XFlush(r.display);

  // Wait
  pause();

  return 0;
}
