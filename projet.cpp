// g++ projet.cpp -Wall -framework ApplicationServices
#include <ApplicationServices/ApplicationServices.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

void click(int x, int y, int n, int sleep_time, bool right_click) {
  CGEventRef click1_down;
  CGEventRef click1_up;

  if (right_click) {
    click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonRight);

    click1_up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                        CGPointMake(x, y), kCGMouseButtonRight);
  } else {
    click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown, CGPointMake(x, y), kCGMouseButtonLeft);

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

void welcom(void) {
  int name;

  system("clear");
  cout << "Bienvenue dans le programme d'autoclicker" << endl;
  cout << endl;
  cout << "-----------------------------------------" << endl;
}

class Task {
 public:
  int posx;
  int posy;
  int nbClick;
  int sleep_time;
  bool right_click;

  Task(int x, int y, int n, int sleep, bool right)
      : posx(x), posy(y), nbClick(n), sleep_time(sleep), right_click(right) {}

  void displayTask() {
    cout << "-----------------------------------------" << endl;
    cout << "| " << posx << " " << posy << " " << nbClick << " " << sleep_time
         << " " << right_click << "|" << endl;
    cout << "-----------------------------------------" << endl;
  }
};

int main() {
  // click(30, 30, 2, 1, false);
  welcom();

  int x, y, n, sleep_time;
  bool right_click;
  char c;

  vector<Task> tasks;

  while (true) {
    cout << "Voulez-vous ajouter une tâche ? (y/n)" << endl;
    cin >> c;

    if (c == 'y') {
      cout << "Entrez la position x : ";
      cin >> x;
      cout << "Entrez la position y : ";
      cin >> y;
      cout << "Entrez le nombre de clics : ";
      cin >> n;
      cout << "Entrez le temps de pause entre chaque clic : ";
      cin >> sleep_time;
      cout << "Voulez-vous faire un clic droit ? (y/n)" << endl;
      cin >> c;
      if (c == 'y') {
        right_click = true;
      } else {
        right_click = false;
      }

      Task task(x, y, n, sleep_time, right_click);
      tasks.push_back(task);
    } else {
      break;
    }
  }

  tasks[0].displayTask();

  return 0;
}
