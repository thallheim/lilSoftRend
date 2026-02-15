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

  // Select MapNotify events
  // TODO: XSelectinput() wrapper
  XSelectInput(r.display, r.GetWindowByName("Test"), StructureNotifyMask);

  // Map window
  XMapWindow(r.display, r.GetWindowByName("Test"));

  // Create graphics ctx
  r.NewGC("Test", r.GetWindowByName("Test"));

  // Set colours
  XSetForeground(r.display, r.GetGCByName("Test"), NamedColour.at(LSR_WHITE));
  // r.SetFG(r.GetGCByName("Test"), GetColourS("Red")); // FIXME: nope

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

  // Send the "DrawLine" request to the server
  XFlush(r.display);

  // Wait
  pause();

  return 0;
}
