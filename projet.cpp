// g++ projet.cpp -Wall -framework ApplicationServices

#include <ApplicationServices/ApplicationServices.h>
#include <stdlib.h>

#include <iostream>
#include <string>
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
  system("clear");
  cout << "Bienvenue dans le programme d'autoclicker" << endl;
  cout << endl;
}

class Task {
 public:
  int posx;
  int posy;
  int nbClick;
  int sleep_time;
  bool right_click;
  string name;

  Task(int x, int y, int n, int sleep, bool right, string name)
      : posx(x),
        posy(y),
        nbClick(n),
        sleep_time(sleep),
        right_click(right),
        name(name) {}

  void displayTask() {
    cout << name << endl;
    cout << "------------------------------------------------------------------"
         << endl;
    cout << "| posx " << posx << " | posy " << posy << " | nbClick " << nbClick
         << " | sleep_time " << sleep_time << " | right_click " << right_click
         << " |" << endl;
    cout << "------------------------------------------------------------------"
         << endl;
    cout << endl;
  }

  void executeTask() { click(posx, posy, nbClick, sleep_time, right_click); }
};

class TaskList {
 public:
  vector<Task> tasks;

  TaskList() {}

  void addTask(Task task) { tasks.push_back(task); }

  void displayTasks() {
    if (tasks.size() == 0) {
      system("clear");
      cout << "Aucune tache" << endl;
      cout << endl;
      return;
    } else {
      system("clear");
      for (int i = 0; i < tasks.size(); i++) {
        tasks[i].displayTask();
      }
    }
  }

  void executeTasks() {
    for (int i = 0; i < tasks.size(); i++) {
      tasks[i].executeTask();
    }
  }

  void deleteTask(int index) { tasks.erase(tasks.begin() + index); }

  void deleteAllTasks() {
    tasks.clear();
    cout << "Toutes les taches ont ete supprimees" << endl;
    cout << endl;
  }

  void editTask(int index, Task task) { tasks[index + 1] = task; }
};

int main() {
  welcom();

  TaskList taskList;

  int choice = 0;
  int x, y, n, sleep_time;
  bool right_click;
  string name;

  while (choice != 7) {
    cout << "1. Ajouter une tache" << endl;
    cout << "2. Afficher les taches" << endl;
    cout << "3. Supprimer une tache" << endl;
    cout << "4. Supprimer toutes les taches" << endl;
    cout << "5. Modifier une tache" << endl;
    cout << "6. Executer les taches" << endl;
    cout << "7. Quitter" << endl;
    cout << endl;
    cout << "Votre choix : ";
    cin >> choice;
    cout << endl;

    switch (choice) {
      case 1:
        cout << "Nom de la tache : ";
        cin >> name;
        cout << "Position x : ";
        cin >> x;
        cout << "Position y : ";
        cin >> y;
        cout << "Nombre de click : ";
        cin >> n;
        cout << "Temps de pause entre chaque click : ";
        cin >> sleep_time;
        cout << "Click droit ? (0/1) : ";
        cin >> right_click;
        cout << endl;
        system("clear");
        taskList.addTask(Task(x, y, n, sleep_time, right_click, name));
        cout << "Tache ajoutee" << endl;
        cout << endl;
        break;

      case 2:
        taskList.displayTasks();
        break;

      case 3:
        int index;
        cout << "Index de la tache a supprimer : ";
        cin >> index;
        cout << endl;
        taskList.deleteTask(index);
        system("clear");
        break;

      case 4:
        taskList.deleteAllTasks();
        system("clear");
        break;

      case 5:
        int index2;
        cout << "Index de la tache a modifier : ";
        cin >> index2;
        cout << "Position x : ";
        cin >> x;
        cout << "Position y : ";
        cin >> y;
        cout << "Nombre de click : ";
        cin >> n;
        cout << "Temps de pause entre chaque click : ";
        cin >> sleep_time;
        cout << "Click droit ? (0/1) : ";
        cin >> right_click;
        taskList.editTask(index2, Task(x, y, n, sleep_time, right_click, name));
        system("clear");
        break;

      case 6:
        system("clear");
        cout << "Execution des taches" << endl;
        cout << endl;
        taskList.executeTasks();
        cout << endl;
        cout << "Fin de l'execution des taches" << endl;
        cout << endl;
        break;

      case 7:
        system("clear");
        cout << "Au revoir" << endl;
        break;

      default:
        cout << "Erreur, veuillez choisir un nombre entre 1 et 7" << endl;
        cout << endl;
        break;
    }
  }

  return 0;
}
