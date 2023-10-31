// g++ projet.cpp -Wall -framework ApplicationServices
#include <ApplicationServices/ApplicationServices.h>

#include <iostream>
using namespace std;

// Coordonées du click
int X = 422;
int Y = 192;

int main() {
  // Create MouseDown event
  CGEventRef click1_down = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseDown, CGPointMake(X, Y), kCGMouseButtonRight);

  // Create MouseUp event
  CGEventRef click1_up = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseUp, CGPointMake(X, Y), kCGMouseButtonRight);

  // Click 10 times
  for (int i = 0; i < 3; i++) {
    // Mouse down
    CGEventPost(kCGHIDEventTap, click1_down);
    cout << "Click" << endl;
    sleep(0.1);

    // Mouse up
    CGEventPost(kCGHIDEventTap, click1_up);
    cout << "Release" << endl;
    sleep(1);
  }

  return 0;
}
