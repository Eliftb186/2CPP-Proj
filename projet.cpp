// g++ projet.cpp -Wall -framework ApplicationServices
#include <ApplicationServices/ApplicationServices.h>

#include <iostream>
using namespace std;

// Coordonées du click
int X = 1083;
int Y = 14;

void click(int x, int y, int n, int sleep_time, bool right_click) {
  CGEventRef click1_down;  // Declare the variables outside the if-else block
  CGEventRef click1_up;

  if (right_click) {
    // Create MouseDown event
    click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonRight);

    // Create MouseUp event
    click1_up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                        CGPointMake(x, y), kCGMouseButtonRight);
  } else {
    // Create MouseDown event
    click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonLeft);

    // Create MouseUp event
    click1_up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                        CGPointMake(x, y), kCGMouseButtonLeft);
  }

  // Click n times
  for (int i = 0; i < n; i++) {
    // Mouse down
    CGEventPost(kCGHIDEventTap, click1_down);
    cout << "Click" << endl;
    sleep(0.1);

    // Mouse up
    CGEventPost(kCGHIDEventTap, click1_up);
    cout << "Release" << endl;
    sleep(sleep_time);
  }

  // Release the events
  CFRelease(click1_down);
  CFRelease(click1_up);
}

int main() {
  // Click 10 times at (1083, 14) with a sleep time of 1 second
  click(X, Y, 2, 1, false);

  return 0;
}
