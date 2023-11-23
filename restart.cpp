#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <vector>
using namespace std;

struct Tiles {
  int id;
  int playerName;
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
    cout << "row number : ";
    cin >> pos;
    position.push_back(pos);
    cout << "column number : ";
    cin >> pos;
    position.push_back(pos);
    return position;
  }

  string choseName() {
    cout << "Enter the player's name : ";
    cin >> name;
    if (name == "patate") {
      name = "🥔";
    }
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

    cout << endl;
    char choice;
    cout << "you wanna play with the old or new tiles (o/n) ? : ";
    cin >> choice;
    while (choice != 'o' && choice != 'n') {
      cout << "❌ Invalid choice ❌" << endl;
      cout << "you wanna play with the old or new tiles (o/n) ? : " << endl;
      cin >> choice;
    }
    if (choice == 'o') {
      tiles = initTilesStandard();
    } else {
      initTilesFromNowere();
    }
    initBoard(players);
  }

  void initBoard(vector<Player> players) {
    if (players.size() <= 4) {
      board = vector<vector<int>>(20, vector<int>(20, 100));
    } else {
      board = vector<vector<int>>(30, vector<int>(30, 100));
    }
    for (int i = 0; i < players.size(); i++) {
      system("clear");
      printBoard();
      cout << endl;
      cout << "Enter " << players[i].name << "'s starting position" << endl;
      vector<int> pos = players[i].choseStartingPosition();
      board[pos[0]][pos[1]] = players[i].colorInt;
    }
  }

  vector<Tiles> initTilesStandard() {
    vector<Tiles> tiles_ = {
        {1, 0, {{1, 0, 0}, {1, 1, 1}}},
        {2, 0, {{0, 1, 0}, {0, 1, 0}, {1, 1, 1}}},
        {3, 0, {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}},
        {4, 0, {{0, 0, 1}, {1, 1, 1}, {1, 0, 0}}},
        {5, 0, {{0, 1, 0}, {1, 1, 1}}},
        {6, 0, {{1, 1}, {1, 1}}},
        {7, 0, {{1, 0, 1}, {1, 1, 1}}},
        {8, 0, {{1, 1, 1}}},
        {9, 0, {{0, 1}, {1, 1}, {1, 0}}},
        {10, 0, {{1, 0}, {1, 1}}},
        {11, 0, {{0, 0, 1}, {0, 1, 1}, {1, 1, 0}}},
        {12, 0, {{1, 1}}},
        {13, 0, {{0, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 1}}},
        {14, 0, {{1, 1, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}}},
        {15,
         0,
         {{0, 0, 0, 1, 0},
          {0, 0, 0, 1, 0},
          {0, 0, 0, 1, 1},
          {0, 1, 1, 1, 0},
          {1, 1, 0, 0, 0}}},
    };

    return tiles_;
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
      tile.playerName = 0;
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

  void printTile(Tiles tile) {
    cout << endl;
    for (int i = 0; i < tile.tile.size(); i++) {
      for (int j = 0; j < tile.tile[0].size(); j++) {
        if (tile.tile[i][j] == 1) {
          cout << "🔳";
        } else {
          cout << "  ";
        }
      }
      cout << endl;
    }
    cout << endl;
  }

  void placeTile(Player player) {
    cout << endl;
    cout << "Enter the tile's position : " << endl;
    vector<int> position = player.choseStartingPosition();
    while (!canPlaceTile(tiles[0], position)) {
      cout << "❌ Invalid position ❌" << endl;
      cout << "Enter the tile's position : " << endl;
      position = player.choseStartingPosition();
    }
    for (int i = 0; i < tiles[0].tile.size(); i++) {
      for (int j = 0; j < tiles[0].tile[0].size(); j++) {
        if (tiles[0].tile[i][j] == 1) {
          board[position[0] + i][position[1] + j] = player.colorInt;
        }
      }
    }
    tiles[0].playerName = player.colorInt;
    tiles.erase(tiles.begin());
  }

  void exchangeTile() {
    // on affiche les 5 prochaines tuiles
    cout << endl;
    cout << "Your next tiles : (1 - 5)" << endl;
    for (int i = 0; i < 5; i++) {
      printTile(tiles[i]);
    }
    // on demande quelle tuile on veut échanger
    cout << endl;
    cout << "Enter the tile's id you wanna exchange : ";
    int id;
    cin >> id;
    while (id < 1 || id > 5) {
      cout << "❌ Invalid id ❌" << endl;
      cout << "Enter the tile's id you wanna exchange : ";
      cin >> id;
    }
    // on swap la tuile avec la première
    Tiles temp = tiles[0];
    tiles[0] = tiles[id - 1];
    tiles[id - 1] = temp;
  }

  void printCurrentTile() {
    cout << "Your tile : " << endl;
    printTile(tiles[0]);
  }

  bool canPlaceTile(Tiles tile, vector<int> position) {
    // on ne peux pas superposer les tuiles
    for (int i = 0; i < tile.tile.size(); i++) {
      for (int j = 0; j < tile.tile[0].size(); j++) {
        if (tile.tile[i][j] == 1) {
          if (board[position[0] + i][position[1] + j] != 100) {
            cout << "can't superpose tiles" << endl;
            return false;
          }
        }
      }
    }
    // on ne peux pas placer une tuile en dehors du board
    if (position[0] < 0 || position[0] >= board.size() || position[1] < 0 ||
        position[1] >= board[0].size()) {
      cout << "out of bounds" << endl;
      return false;
    }
    // on ne peux pas la placer si elle n'est pas connectée à une autre tuile
    bool connected = false;
    for (int i = 0; i < tile.tile.size(); i++) {
      for (int j = 0; j < tile.tile[0].size(); j++) {
        if (tile.tile[i][j] == 1) {
          if (board[position[0] + i - 1][position[1] + j] != 100 ||
              board[position[0] + i + 1][position[1] + j] != 100 ||
              board[position[0] + i][position[1] + j - 1] != 100 ||
              board[position[0] + i][position[1] + j + 1] != 100) {
            connected = true;
          }
        }
      }
    }
    if (!connected) {
      cout << "not connected" << endl;
      return false;
    }
    return true;
  }

  Tiles flipTile(Tiles tile) {
    Tiles flippedTile = tile;
    reverse(flippedTile.tile.begin(), flippedTile.tile.end());
    return flippedTile;
  }

  Tiles rotateTile(Tiles tile) {
    Tiles rotatedTile = tile;
    vector<vector<int>> newTile(tile.tile[0].size(),
                                vector<int>(tile.tile.size(), 0));
    for (int i = 0; i < tile.tile.size(); i++) {
      for (int j = 0; j < tile.tile[0].size(); j++) {
        newTile[j][tile.tile.size() - 1 - i] = tile.tile[i][j];
      }
    }
    rotatedTile.tile = newTile;
    return rotatedTile;
  }

  void play() {
    bool end = false;
    int currentPlayerIndex = 0;

    while (!end) {
      system("clear");
      printBoard();
      cout << endl;
      cout << players[currentPlayerIndex].name << " : " << endl;
      printCurrentTile();
      cout << endl;

      int choice;
      do {
        system("clear");
        printBoard();
        printCurrentTile();
        cout << "1 : place a tile" << endl;
        cout << "2 : exchange a tile" << endl;
        cout << "3 : rotate tile" << endl;
        cout << "4 : flip tile" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        while (choice < 1 || choice > 4) {
          cout << "❌ Invalid choice ❌" << endl;
          cout << "Enter your choice : ";
          cin >> choice;
        }

        if (choice == 1) {
          placeTile(players[currentPlayerIndex]);
          currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        } else if (choice == 2) {
          system("clear");
          printBoard();
          exchangeTile();
          system("clear");
          printBoard();
          printCurrentTile();
          placeTile(players[currentPlayerIndex]);
          currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        } else if (choice == 3) {
          int rotateChoice;
          do {
            system("clear");
            printBoard();
            tiles[0] = rotateTile(tiles[0]);
            printTile(tiles[0]);
            system("clear");
            printBoard();
            printCurrentTile();
            cout << "Rotate again? (1: Yes, 0: No) : ";
            cin >> rotateChoice;
          } while (rotateChoice == 1);
          system("clear");
          printBoard();
          printCurrentTile();
          placeTile(players[currentPlayerIndex]);
          currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        } else if (choice == 4) {
          int flipChoice;
          do {
            system("clear");
            printBoard();
            tiles[0] = flipTile(tiles[0]);
            system("clear");
            printBoard();
            printCurrentTile();
            cout << "Flip again? (1: Yes, 0: No) : ";
            cin >> flipChoice;
          } while (flipChoice == 1);
          system("clear");
          printBoard();
          printCurrentTile();
          placeTile(players[currentPlayerIndex]);
          currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
      } while (choice != 1);
    }
  }
};

int main() {
  system("clear");
  Game game;
  game.play();
}
