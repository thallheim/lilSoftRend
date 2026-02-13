#include "../include/input.hpp"
#include "../include/enums.hpp"
#include "../include/types.hpp"
#include "../include/lilSoftRend.hpp"
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
  r.CreateWindow(r.display, &DefaultRootWindow(r.display),
                 BaseColour::Black, BaseColour::Red, "Test", "_test_");

  r.CreateWindow(r.display, &DefaultRootWindow(r.display),
                 BaseColour::Black, BaseColour::Red, "Hey", "Woo");

  // Select MapNotify events
  // TODO: XSelectinput() wrapper
  XSelectInput(r.display, r.GetWindowByName("Test"), StructureNotifyMask);
  XSelectInput(r.display, r.GetWindowByName("Hey"), StructureNotifyMask); // ok

  // Map window
  XMapWindow(r.display, r.GetWindowByName("Test"));
  XMapWindow(r.display, r.GetWindowByName("Hey")); // ?


  // Create graphics ctx
  // TODO: XCreateGC() wrapper
  r.NewGC("Test", r.GetWindowByName("Test"));
  r.NewGC("hey", r.GetWindowByName("Hey")); // ?

  // Set colours
  // TODO: XSetForeground() wrapper
  XSetForeground(r.display, r.gcs[r._contextIDs.at("Test")],
                 NamedColour.at(ColourToString.at(BaseColour::White)));
  XSetForeground(r.display, r.gcs[r._contextIDs.at("Hey")],
                 NamedColour.at(ColourToString.at(BaseColour::White)));

  // Wait for the MapNotify event
  for(;;) {
    XEvent e;
    XNextEvent(r.display, &e);
    if (e.type == MapNotify)
      break;
  }

  // Draw the line
  // XDrawLine(r.display, win, gc, 10, 60, 180, 20);
  // XDrawLine(r.display, win2, r.contexts[0], 10, 60, 180, 20);
  XDrawLine(r.display, r.GetWindowByName("Test"),
            r.gcs[r._contextIDs.at("Test")], 10, 60, 180, 20);

  // Send the "DrawLine" request to the server
  XFlush(r.display);

  // Wait
  pause();

  return 0;
}
