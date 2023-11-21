// clang++ test.cpp -std=c++11
#include <algorithm>
#include <iostream>
#include <map>
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
  vector<vector<int>> board;
  int size = 20;

  Board(vector<Player> players) {
    if (players.size() > 4) {
      size = 30;
    }

    for (int i = 0; i < size; i++) {
      board.push_back(vector<int>());
      for (int j = 0; j < size; j++) {
        board[i].push_back(100);
      }
    }

    // on place les tuiles de départ des joueurs aléatoirement
    srand(time(NULL));
    vector<pair<int, int>> positions;  // Stocke les positions déjà utilisées

    for (int i = 0; i < players.size(); i++) {
      int x, y;
      do {
        x = rand() % size;
        y = rand() % size;
      } while (find(positions.begin(), positions.end(), make_pair(x, y)) !=
               positions.end());

      board[x][y] = stoi(players[i].getColor("int"));
      positions.push_back(make_pair(x, y));
    }
  }

  void printBoard() {
    cout << endl;
    // affichage des numéros de colonnes
    cout << "   ";
    for (int col = 0; col < board[0].size(); col++) {
      if (col < 10) {
        cout << col << " ";
      } else {
        cout << col;
      }
    }
    cout << endl;

    // affichage des numéros de lignes et des board
    for (int i = 0; i < board.size(); i++) {
      if (i < 10) {
        cout << i << "  ";
      } else {
        cout << i << " ";
      }
      for (int j = 0; j < board[0].size(); j++) {
        static const map<int, string> symboles = {
            {0, "⬛️"}, {1, "⬜️"}, {2, "🟩"}, {3, "🟦"}, {4, "🟨"},
            {5, "🟧"}, {6, "🟥"}, {7, "🟫"}, {8, "🟪"}, {100, "🔳"},
        };

        // Assurez-vous de remplacer 'valeur' par le bon élément de votre
        // tableau 'board'
        int valeur = board[i][j];
        auto it = symboles.find(valeur);
        if (it != symboles.end()) {
          std::cout << it->second;
        } else {
          std::cout << "❌";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

class Tuile {
 public:
  vector<vector<int>> tuile;

 public:
  struct Tiles {
    int id;
    string playerName;
    vector<vector<int>> tile;
  };

  vector<Tiles> createTileList() {
    vector<Tiles> tileList;
    srand(time(0));

    for (int tot = 0; tot < 96; tot++) {
      int size = rand() % 6 + 2;
      vector<vector<int>> tileMatrix(size, vector<int>(size, 0));

      // Point de départ
      int startX = rand() % size;
      int startY = rand() % size;

      // Nombre de déplacements aléatoires
      int numMoves = rand() % (2 * size) + (3 * size);

      // Déplacements possibles : haut, bas, droite, gauche
      int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

      int currentX = startX;
      int currentY = startY;

      for (int move = 0; move < numMoves; move++) {
        // Choisir une direction aléatoire
        int randomDirection = rand() % 4;
        int newX = currentX + directions[randomDirection][0];
        int newY = currentY + directions[randomDirection][1];

        // Vérifier si la nouvelle position est valide
        if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
          tileMatrix[newX][newY] = 1;
          currentX = newX;
          currentY = newY;
        }
      }

      // on suprimme les lignes et colonnes vides
      for (int i = 0; i < tileMatrix.size(); i++) {
        if (tileMatrix[i] == vector<int>(size, 0)) {
          tileMatrix.erase(tileMatrix.begin() + i);
          i--;
        }
      }
      for (int i = 0; i < tileMatrix[0].size(); i++) {
        bool empty = true;
        for (int j = 0; j < tileMatrix.size(); j++) {
          if (tileMatrix[j][i] != 0) {
            empty = false;
            break;
          }
        }
        if (empty) {
          for (int j = 0; j < tileMatrix.size(); j++) {
            tileMatrix[j].erase(tileMatrix[j].begin() + i);
          }
          i--;
        }
      }

      // on ajoute la tuile à la liste
      Tiles tile;
      tile.id = tot;
      tile.tile = tileMatrix;
      tile.playerName = "";
      tileList.push_back(tile);
    }

    return tileList;
  }

  void printTilesListDebug(vector<Tiles> tileList) {
    for (int i = 0; i < tileList.size(); i++) {
      cout << "Tuile " << tileList[i].id + 1 << " de " << tileList[i].playerName
           << endl;
      for (int j = 0; j < tileList[i].tile.size(); j++) {
        for (int k = 0; k < tileList[i].tile[0].size(); k++) {
          if (tileList[i].tile[j][k] == 1) {
            cout << "🟩";
          } else {
            cout << "⬜️";
          }
        }
        cout << endl;
      }
      cout << endl;
    }
  }

  void flipTuile() { reverse(tuile.begin(), tuile.end()); }

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
          cout << "";
        } else {
          cout << " ";
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
};

int main() {
  system("clear");
  vector<Player> players = createPlayers();

  Board board(players);
  board.printBoard();

  cout << "do you want to play with the default tiles ? (y/n) : ";
  char answer;
  cin >> answer;
  while (answer != 'y' && answer != 'n') {
    cout << "do you want to play with the default tiles ? (y/n) : ";
    cin >> answer;
  }
  if (answer == 'y') {
    // affiche allTiles
    for (int i = 0; i < 15; i++) {
      cout << "Tuile " << allTiles[i].id + 1 << " de " << allTiles[i].playerName
           << endl;
      for (int j = 0; j < allTiles[i].tile.size(); j++) {
        for (int k = 0; k < allTiles[i].tile[0].size(); k++) {
          if (allTiles[i].tile[j][k] == 1) {
            cout << "🟩";
          } else {
            cout << "⬜️";
          }
        }
        cout << endl;
      }
      cout << endl;
    }
  } else {
    Tuile tuile;
    vector<Tuile::Tiles> tileList = tuile.createTileList();
    tuile.printTilesListDebug(tileList);
  }

  return 0;
}
