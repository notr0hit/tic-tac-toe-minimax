#include <algorithm>
#include <array>
#include <iostream>
#include <string>

struct Move {
  int r, c, score;
};

class Game {
  // player, computer, grid[3][3]
  char player = 'X';
  char bot = 'O';

public:
  void Print(std::array<std::array<char, 5>, 5> board) {
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

    std::array<std::array<char, 5>, 5> board{{{' ', '|', ' ', '|', ' '},
                                              {'-', '+', '-', '+', '-'},
                                              {' ', '|', ' ', '|', ' '},
                                              {'-', '+', '-', '+', '-'},
                                              {' ', '|', ' ', '|', ' '}}};
    Print(board);
    char symbol = 'X';
    while (true) {
      std::cout << "Enter a Symbol (X or O, X goes first): ";
      std::cin >> symbol;
      if (symbol == 'X' or symbol == 'O') {
        break;
      }
    }

    if (symbol == 'X') {
      player = 'X', bot = 'O';
      while (true) {
        Player(board);
        Verdict(board, "player");

        std::cout << "Computer is playing...\n";
        Computer(board);
        Verdict(board, "computer");
      }
    } else {
      player = 'O', bot = 'X';
      while (true) {
        std::cout << "Computer is playing...\n";
        Computer(board);
        Verdict(board, "computer");

        Player(board);
        Verdict(board, "player");
      }
    }
  }

  void Player(std::array<std::array<char, 5>, 5> &board) {
    while (true) {
      int response;
      std::cout << "Enter an empty cell (1 - 9) : ";
      std::cin >> response;

      int r = 2 * ((response - 1) / 3), c = 2 * ((response - 1) % 3);
      if (response >= 1 and response <= 9 and board[r][c] == ' ') {
        // std::cerr << r << " " << c << "\n";
        board[r][c] = player;
        break;
      }
    }
  }

  void Computer(std::array<std::array<char, 5>, 5> &board) {

    Move best;
    best.score = -10;
    for (int r = 0; r < 5; r += 2) {
      for (int c = 0; c < 5; c += 2) {
        if (board[r][c] == ' ') {
          board[r][c] = bot;
          int score = MiniMax(board, "player", 0);
          board[r][c] = ' ';

          if (best.score < score) {
            best.score = score;
            best.r = r;
            best.c = c;
          }
        }
      }
    }

    board[best.r][best.c] = bot;
  }

  int MiniMax(std::array<std::array<char, 5>, 5> board, std::string who,
              int depth) {

    int res = Check(board);

    if (res == 1 or res == -1 or res == 0)
      return res;

    if (who == "computer") {
      int max_score = -10;
      for (int r = 0; r < 5; r += 2) {
        for (int c = 0; c < 5; c += 2) {
          if (board[r][c] == ' ') {
            board[r][c] = bot;
            int score = MiniMax(board, "player", depth + 1);
            max_score = std::max(max_score, score);
            board[r][c] = ' ';
          }
        }
      }
      return max_score;

    } else if (who == "player") {
      int min_score = 10;
      for (int r = 0; r < 5; r += 2) {
        for (int c = 0; c < 5; c += 2) {
          if (board[r][c] == ' ') {
            board[r][c] = player;
            int score = MiniMax(board, "computer", depth + 1);
            min_score = std::min(min_score, score);
            board[r][c] = ' ';
          }
        }
      }
      return min_score;
    }

    return 0;
  }

  int Check(std::array<std::array<char, 5>, 5> board) {
    // check each row;
    for (int r = 0; r < 5; r += 2) {
      if (board[r][0] == board[r][2] and board[r][0] == board[r][4]) {
        if (board[r][0] == player) {
          return -1;
        }
        if (board[r][0] == bot) {
          return 1;
        }
      }
    }

    // check each column
    for (int c = 0; c < 5; c += 2) {
      if (board[0][c] == board[2][c] and board[0][c] == board[4][c]) {
        if (board[0][c] == player) {
          return -1;
        }
        if (board[0][c] == bot) {
          return 1;
        }
      }
    }

    // check each diagonal
    if ((board[0][0] == board[2][2] and board[2][2] == board[4][4]) ||
        (board[0][4] == board[2][2] and board[2][2] == board[4][0])) {
      if (board[2][2] == player) {
        return -1;
      }
      if (board[2][2] == bot) {
        return 1;
      }
    }

    // Check Tie
    int count = 0;
    for (int r = 0; r < 5; r += 2)
      for (int c = 0; c < 5; c += 2)
        count += (board[r][c] != ' ');

    if (count == 9) {
      return 0;
    }

    return 100;
  }

  void Verdict(std::array<std::array<char, 5>, 5> board, std::string who) {

    Print(board);

    int res = Check(board);

    if (res == 1) {
      if (who == "player") {
        std::cout << "Congratulations, You Won!\n";
        exit(0);
      }
      if (who == "computer") {
        std::cout << "You lost, Better luck next time!\n";
        exit(0);
      }
    }

    if (res == 0) {
      std::cout << "Game tied!\n";
      exit(0);
    }
  }
};

int main(int argc, char *argv[]) {
  Game game;
  game.Play();
}
