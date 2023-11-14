// g++ fin.cpp -std=c++11
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// une class joueur
class Joueur {
 public:
  string nom;
  int couponEchange;

  void creerJoueur() {
    cout << "Entrez le nom du joueur" << endl;
    cin >> nom;
    cout << "Entrez le nombre de coupon d'échange" << endl;
    cin >> couponEchange;
    cout << "Le joueur " << nom << " a été créé avec " << couponEchange
         << " coupons d'échange" << endl;
  }
};

class Tuile {
 public:
  vector<vector<int>> tuile;

  void creerTuile() {
    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
      tuile.push_back(vector<int>());
      for (int j = 0; j < 6; j++) {
        tuile[i].push_back(rand() % 2);
      }
    }
  }

  // fonction qui retourne une tuile par un axe de symétrie
  void mirorTuile() { reverse(tuile.begin(), tuile.end()); }

  // fonction qui tourne une tuile de 90°
  void rotateTuile() {
    // Transposer la matrice
    for (size_t i = 0; i < tuile.size(); ++i) {
      for (size_t j = i + 1; j < tuile[i].size(); ++j) {
        swap(tuile[i][j], tuile[j][i]);
      }
    }

    // Inverser l'ordre des colonnes
    for (size_t i = 0; i < tuile.size(); ++i) {
      reverse(tuile[i].begin(), tuile[i].end());
    }
  }

  void afficherTuile() {
    for (int i = 0; i < tuile.size(); i++) {
      for (int j = 0; j < tuile[0].size(); j++) {
        if (tuile[i][j] == 1) {
          cout << "X ";
        } else {
          cout << "  ";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

class Board {
 public:
  vector<vector<int>> cases;

  void initBoard() {
    for (int i = 0; i < 20; i++) {
      cases.push_back(vector<int>());
      for (int j = 0; j < 20; j++) {
        cases[i].push_back(0);
      }
    }
  }

  void printBord() {
    cout << endl;
    for (int i = 0; i < cases.size(); i++) {
      for (int j = 0; j < cases[0].size(); j++) {
        cout << cases[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  Board Gameboard;

  Gameboard.initBoard();
  Gameboard.printBord();

  return 0;
}
