#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Tiles {
  int id;
  string playerName;
  vector<vector<int>> tile;
};

class Player {
 public:
  string name;
  int couponEchange;
  int colorInt;

  Player(vector<string> availableColors) {
    name = choseName();
    couponEchange = 1;
    colorInt = choseColor(availableColors);
  }

  vector<int> choseStartingPosition() {
    vector<int> position;
    int pos;
    cout << "row number :";
    cin >> pos;
    position.push_back(pos);
    cout << "column number :";
    cin >> pos;
    position.push_back(pos);
    return position;
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
    cin >> colorInt;
    while (colorInt < 1 || colorInt > availableColors.size() ||
           availableColors[colorInt - 1] == "❌") {
      cout << "❌ Color already taken or out of bounds ❌" << endl;
      for (int i = 0; i < availableColors.size(); i++) {
        cout << i + 1 << " : " << availableColors[i] << endl;
      }
      cout << "Enter the player's color : ";
      cin >> colorInt;
    }
    colorInt--;
    return colorInt;
  }
};

class Game {
 public:
  vector<Player> players;
  vector<Tiles> tiles;
  vector<vector<int>> board;

  Game() {
    int nbPlayers;
    vector<string> colors = {"⬛️", "⬜️", "🟩", "🟦", "🟨",
                             "🟧", "🟥", "🟫", "🟪"};

    cout << endl;
    cout << "Enter the number of players : (2-9) : ";
    cin >> nbPlayers;
    while (nbPlayers < 2 || nbPlayers > 9) {
      system("clear");
      cout << "❌ Invalid number of players ❌" << endl;
      cout << "Enter the number of players : (2-9) : ";
      cin >> nbPlayers;
    }
    for (int i = 0; i < nbPlayers; i++) {
      players.push_back(Player(colors));
      colors[players[i].colorInt] = "❌";
    }

    // initialisation du plateau en fonction du nombre de joueurs
    initBoard(players);

    char choice;
    cout << endl;
    cout << "you wanna play with the old or new tiles (o/n) ? : " << endl;
    cin >> choice;
    while (choice != 'o' && choice != 'n') {
      cout << "❌ Invalid choice ❌" << endl;
      cout << "you wanna play with the old or new tiles (o/n) ? : " << endl;
      cin >> choice;
    }
    if (choice == 'o') {
      initTilesFromPDF();
    } else {
      initTilesFromNowere();
    }
  }

  void initBoard(vector<Player> players) {
    for (int i = 0; i < players.size(); i++) {
      cout << endl;
      cout << "Enter " << players[i].name << "'s starting position" << endl;
      vector<int> pos = players[i].choseStartingPosition();
    }
  }

  void initTilesFromPDF() {
    tiles = {
        {1, "", {{1, 0, 0}, {1, 1, 1}}},
        {2, "", {{0, 1, 0}, {0, 1, 0}, {1, 1, 1}}},
        {3, "", {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}},
        {4, "", {{0, 0, 1}, {1, 1, 1}, {1, 0, 0}}},
        {5, "", {{0, 1, 0}, {1, 1, 1}}},
        {6, "", {{1, 1}, {1, 1}}},
        {7, "", {{1, 0, 1}, {1, 1, 1}}},
        {8, "", {{1, 1, 1}}},
        {9, "", {{0, 1}, {1, 1}, {1, 0}}},
        {10, "", {{1, 0}, {1, 1}}},
        {11, "", {{0, 0, 1}, {0, 1, 1}, {1, 1, 0}}},
        {12, "", {{1, 1}}},
        {13, "", {{0, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 1}}},
        {14, "", {{1, 1, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}}},
        {15,
         "",
         {{0, 0, 0, 1, 0},
          {0, 0, 0, 1, 0},
          {0, 0, 0, 1, 1},
          {0, 1, 1, 1, 0},
          {1, 1, 0, 0, 0}}},
    };
  }

  void initTilesFromNowere() {
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

    tiles = tileList;
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
            {5, "🟧"}, {6, "🟥"}, {7, "🟫"}, {8, "🟪"}, {100, "🔳"}};

        int valeur = board[i][j];
        auto it = symboles.find(valeur);
        if (it != symboles.end()) {
          cout << it->second;
        } else {
          cout << "❌";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  system("clear");
  Game game;
  game.printBoard();
}
