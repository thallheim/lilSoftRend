#pragma once
/*
 ██████╗ █████╗ ██╗     ██╗     ██████╗  █████╗  ██████╗██╗  ██╗███████╗
██╔════╝██╔══██╗██║     ██║     ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝
██║     ███████║██║     ██║     ██████╔╝███████║██║     █████╔╝ ███████╗
██║     ██╔══██║██║     ██║     ██╔══██╗██╔══██║██║     ██╔═██╗ ╚════██║
╚██████╗██║  ██║███████╗███████╗██████╔╝██║  ██║╚██████╗██║  ██╗███████║
 ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝
 */

#include <GLFW/glfw3.h>
#include <print>

using std::print;
using std::println;

static void glfwInitErrorCallback(int error, const char* msg)
{
  println("ERR: Couldn't initialise GLFW:");
  println("  -> Code: {}\n  ->  Msg: {}", error, msg);
}

static void glfwCreateWindowErrorCallback(int error, const char* msg)
{
  println("ERR: Couldn't create window:");
  println("  -> Code: {}\n  ->  Msg: {}", error, msg);
}

static void keyReportCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  println("PRESSED:\n\tKey: {}\n\tScancode: {}\n\tAction: {}\n\tMods: {}\n- - - - - - - -",
             key, scancode, action, mods);
}

static void mouseReportCallback(GLFWwindow* window, int button, int action, int mods)
{
  // print("M_PRESSED:\n\tButton: {}\n\tScancode: {}\n\tAction: {}\n\tMods: {}\n- - - - - - - -",
  //       button, action, mods);
}
