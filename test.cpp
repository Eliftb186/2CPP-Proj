// clang++ LayingGrass.cpp -std=c++11
#include <algorithm>
#include <iostream>
#include <vector>

#include "tiles.cpp"
using namespace std;

class Player {
 public:
  string name;
  int couponEchange;
  int color;

  Player(vector<string> availableColors) {
    name = choseName();
    couponEchange = 1;
    color = choseColor(availableColors);
  }

  string choseName() {
    cout << "Enter the player's name : ";
    cin >> name;
    return name;
  }

  int choseColor(vector<string> availableColors) {
    for (int i = 0; i < availableColors.size(); i++) {
      cout << i + 1 << " : " << availableColors[i] << endl;
    }
    cout << "Enter the player's color : ";
    cin >> color;
    while (color < 1 || color > availableColors.size() ||
           availableColors[color - 1] == "❌") {
      for (int i = 0; i < availableColors.size(); i++) {
        cout << i + 1 << " : " << availableColors[i] << endl;
      }
      cout << "Enter the player's color : ";
      cin >> color;
    }
    color--;
    return color;
  }

  string getName() { return name; };
  int getCouponEchange() { return couponEchange; };

  string getColor(string arg = "emoji") {
    vector<string> colors = {"⬛️", "⬜️", "🟩", "🟦", "🟨",
                             "🟧", "🟥", "🟫", "🟪"};
    if (arg == "int") {
      return to_string(color);
    } else {
      return colors[color];
    }
  }
};

class Board {
 public:
  vector<vector<int>> cases;
  int size = 20;

  Board(int nbPlayers) {
    if (nbPlayers > 4) {
      size = 30;
    }

    for (int i = 0; i < size; i++) {
      cases.push_back(vector<int>());
      for (int j = 0; j < size; j++) {
        cases[i].push_back(100);
      }
    }

    // on place les tuiles de départ des joueurs aléatoirement
    srand(time(NULL));
    vector<pair<int, int>> positions;  // Stocke les positions déjà utilisées

    for (int i = 0; i < nbPlayers; i++) {
      int x, y;
      do {
        x = rand() % size;
        y = rand() % size;
      } while (find(positions.begin(), positions.end(), make_pair(x, y)) !=
               positions.end());

      cases[x][y] = i;
      positions.push_back(make_pair(x, y));
    }
  }

  void printBord() {
    cout << endl;
    // affichage des numéros de colonnes
    cout << "   ";
    for (int col = 0; col < cases[0].size(); col++) {
      if (col < 10) {
        cout << col << " ";
      } else {
        cout << col;
      }
    }
    cout << endl;
    // affichage des numéros de lignes et des cases
    for (int i = 0; i < cases.size(); i++) {
      if (i < 10) {
        cout << i << "  ";
      } else {
        cout << i << " ";
      }
      for (int j = 0; j < cases[0].size(); j++) {
        switch (cases[i][j]) {
          case 0:
            cout << "🟥";
            break;
          case 1:
            cout << "🟩";
            break;
          case 2:
            cout << "🟦";
            break;
          case 3:
            cout << "🟨";
            break;
          case 4:
            cout << "🟪";
            break;
          case 5:
            cout << "🟧";
            break;
          case 6:
            cout << "⬜️";
            break;
          case 7:
            cout << "🟫";
            break;
          case 8:
            cout << "⬛️";
            break;
          default:
            cout << "🔳";
            break;
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

vector<Player> createPlayers() {
  int nbPlayers;
  vector<string> colors = {"⬛️", "⬜️", "🟩", "🟦", "🟨",
                           "🟧", "🟥", "🟫", "🟪"};
  cout << "Enter the number of players (2-9) : ";
  cin >> nbPlayers;
  while (nbPlayers < 2 || nbPlayers > 9) {
    cout << "Enter the number of players (2-9) : ";
    cin >> nbPlayers;
  }
  vector<Player> players;
  for (int i = 0; i < nbPlayers; i++) {
    Player player(colors);
    cout << endl;
    colors[stoi(player.getColor("int"))] = "❌";
    players.push_back(player);
  }
  return players;
}

int main() {
  system("clear");
  vector<Player> players = createPlayers();

  // debug
  for (int i = 0; i < players.size(); i++) {
    cout << players[i].name << " : " << players[i].getColor("int") << endl;
  }
  return 0;
}
