/*
 * File: GraphicHelloWorld.cpp
 * --------------------------
 * This program writes "hello, world" in white on top of a blue
 * rectangle in the graphics window.
 */

#include "cs106lib-0.3.1/CS106/graphics.h"
using namespace std;

int main() {
  initGraphics();
  setColor("BLUE");
  fillRect(50, 50, 300, 150);
  setFont("SansSerif-Bold-48");
  setColor("WHITE");
  drawString("hello, world", 60, 140);
  return 0;
}
