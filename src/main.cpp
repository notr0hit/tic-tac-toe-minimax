#include <array>
#include <iostream>
#include <string>

class Game {
  // player, computer, grid[3][3]
  std::array<std::array<char, 5>, 5> board{{{' ', '|', ' ', '|', ' '},
                                            {'-', '+', '-', '+', '-'},
                                            {' ', '|', ' ', '|', ' '},
                                            {'-', '+', '-', '+', '-'},
                                            {' ', '|', ' ', '|', ' '}}};
  char symbol = 'X';

public:
  void Print() {
    std::cout << "\n";
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        std::cout << board[i][j];
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  void Play() {
    this->Print();
    while (true) {
      std::cout << "Enter a Symbol (X or O, X goes first): ";
      std::cin >> symbol;
      if (symbol == 'X' or symbol == 'O') {
        break;
      }
    }

    if (symbol == 'X') {
      while (true) {
        Player('X');
        Verdict("player");

        std::cout << "Computer is playing...\n";
        Computer('O');
        Verdict("computer");
      }
    } else {
      while (true) {
        Computer('X');
        Verdict("computer");

        std::cout << "Computer is playing...\n";
        Player('O');
        Verdict("player");
      }
    }
  }

  void Player(char sym) {
    while (true) {
      int response;
      std::cout << "Enter an empty cell (1 - 9) : ";
      std::cin >> response;

      int r = 2 * ((response - 1) / 3), c = 2 * ((response - 1) % 3);
      if (response >= 1 and response <= 9 and board[r][c] == ' ') {
        // std::cerr << r << " " << c << "\n";
        board[r][c] = sym;
        break;
      }
    }
  }

  void Computer(bool sym) {}

  std::string Check() {
    std::string res = "lose";
    // check each row;
    for (int r = 0; r < 5; r += 2) {
      if (board[r][0] == board[r][2] and board[r][0] == board[r][4]) {
        if (board[r][0] == 'X' or board[r][0] == 'O')
          res = "win";
      }
    }

    // check each column
    for (int c = 0; c < 5; c += 2) {
      if (board[0][c] == board[2][c] and board[0][c] == board[4][c]) {
        if (board[0][c] == 'X' or board[0][c] == 'O')
          res = "win";
      }
    }

    // check each diagonal
    if (board[0][0] == board[2][2] and board[0][0] == board[4][4] ||
        board[0][4] == board[2][2] and board[0][4] == board[4][0]) {
      if (board[2][2] == 'X' or board[2][2] == 'O')
        res = "win";
    }

    // Check Tie
    int count = 0;
    for (int r = 0; r < 5; r += 2)
      for (int c = 0; c < 5; c += 2)
        count += (board[r][c] != ' ');

    if (count == 9) {
      res = "tie";
    }

    return res;
  }

  void Verdict(std::string who) {

    this->Print();

    std::string res = Check();

    if (who == "player") {
      if (res == "win") {
        std::cout << "Congratulations, You Won!\n";
        exit(0);
      }
    }

    if (who == "computer") {
      if (res == "win") {
        std::cout << "You lost, Better luck next time!\n";
        exit(0);
      }
    }

    if (res == "tie") {
      std::cout << "Game tied!\n";
      exit(0);
    }
  }
};

int main(int argc, char *argv[]) {
  Game game;
  game.Play();
}
