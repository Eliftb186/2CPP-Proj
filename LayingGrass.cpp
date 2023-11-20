// clang++ LayingGrass.cpp -std=c++11
#include <algorithm>
#include <iostream>
#include <vector>

#include "tiles.cpp"
using namespace std;

// une class joueur
class Player {
 public:
  string name;
  int couponEchange;

  void createPlayer() {
    cout << "Enter the player's name : ";
    cin >> name;
    cout << "Enter the number of exchange coupons : ";
    cin >> couponEchange;
    cout << "Player " << name << " has been created with " << couponEchange
         << " exchange coupons" << endl;
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

  // fonction qui retourne une tuile
  void flipTuile() { reverse(tuile.begin(), tuile.end()); }

  // fonction qui tourne la tuile
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

  // liste des carrés de couleurs
  // ⬛️ ⬜️ 🟩 🟦 🟨 🟧 🟥 🟫 🟪 | 🔳 | ❌

  /**
   * @brief print the board
   */
  void printBord() {
    cout << "   ";
    for (int col = 0; col < cases[0].size(); col++) {
      if (col < 10) {
        cout << col << " ";
      } else {
        cout << col;
      }
    }
    cout << endl;

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

/**
 * @brief this class is used to manage the tiles
 *
 * @param id the id of the tile
 * @param tile the tile matrix
 * @param playerName the name of the player who place the tile
 *
 * @return vector<Tiles> the list of tiles
 */
class LayingGrass {
 public:
  struct Tiles {
    int id;
    vector<vector<int>> tile;
    string playerName;
  };

  /**
   * @brief Create a Tile List object
   *
   * @return vector<Tiles>
   */
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
      int numMoves = rand() % (2 * size) + (2 * size);

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

      Tiles tile;
      tile.id = tot;
      tile.tile = tileMatrix;
      tileList.push_back(tile);
    }

    return tileList;
  }

  /**
   * @brief print the tile list
   *
   * @param tileList the list of tiles
   */
  void printTileList(vector<Tiles> tileList) {
    for (int i = 0; i < tileList.size(); i++) {
      cout << "Tuile " << tileList[i].id + 1 << endl;
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
};

/**
 * @brief Create a Players object
 *
 * @return vector<Player>
 */
vector<Player> createPlayers() {
  int nbJoueurs;
  cout << "Enter the number of players (between 2 and 9)" << endl;
  cin >> nbJoueurs;
  while (nbJoueurs < 2 || nbJoueurs > 9) {
    cout << "Invalid number of players. Please enter a number between 2 and 9"
         << endl;
    cin >> nbJoueurs;
  }
  vector<Player> players;
  for (int i = 0; i < nbJoueurs; i++) {
    Player player;
    player.createPlayer();
    players.push_back(player);
  }
  return players;
}

int main() {
  int boardSize = 20;

  system("clear");

  // vector<Player> players = createPlayers();

  // Board board(9);
  // board.printBord();

  LayingGrass layingGrass;
  vector<LayingGrass::Tiles> tileList = layingGrass.createTileList();
  layingGrass.printTileList(tileList);

  return 0;
}
