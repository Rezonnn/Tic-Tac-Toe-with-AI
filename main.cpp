#include <iostream>
#include <vector>
#include <limits>
#include <optional>

/*
 * Tic-Tac-Toe with a simple AI (minimax) in C++
 *
 * - Player: 'X'
 * - Computer: 'O'
 * - Board: 3x3
 *
 * This is a clean, self-contained console project you can put on GitHub.
 */

enum class Player {
    None,
    Human,
    Computer
};

struct Move {
    int row;
    int col;
};

class Board {
public:
    Board() {
        grid.assign(3, std::vector<Player>(3, Player::None));
    }

    void reset() {
        for (auto& row : grid) {
            std::fill(row.begin(), row.end(), Player::None);
        }
    }

    bool is_full() const {
        for (const auto& row : grid) {
            for (Player p : row) {
                if (p == Player::None) return false;
            }
        }
        return true;
    }

    bool is_empty(int r, int c) const {
        return grid[r][c] == Player::None;
    }

    bool place(int r, int c, Player p) {
        if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
        if (!is_empty(r, c)) return false;
        grid[r][c] = p;
        return true;
    }

    void unplace(int r, int c) {
        grid[r][c] = Player::None;
    }

    std::optional<Player> winner() const {
        // rows
        for (int r = 0; r < 3; ++r) {
            if (grid[r][0] != Player::None &&
                grid[r][0] == grid[r][1] &&
                grid[r][1] == grid[r][2]) {
                return grid[r][0];
            }
        }
        // cols
        for (int c = 0; c < 3; ++c) {
            if (grid[0][c] != Player::None &&
                grid[0][c] == grid[1][c] &&
                grid[1][c] == grid[2][c]) {
                return grid[0][c];
            }
        }
        // diagonals
        if (grid[0][0] != Player::None &&
            grid[0][0] == grid[1][1] &&
            grid[1][1] == grid[2][2]) {
            return grid[0][0];
        }
        if (grid[0][2] != Player::None &&
            grid[0][2] == grid[1][1] &&
            grid[1][1] == grid[2][0]) {
            return grid[0][2];
        }
        return std::nullopt;
    }

    void print() const {
        std::cout << "\n   0   1   2\n";
        for (int r = 0; r < 3; ++r) {
            std::cout << r << " ";
            for (int c = 0; c < 3; ++c) {
                char ch = symbol_at(r, c);
                std::cout << " " << ch << " ";
                if (c < 2) std::cout << "|";
            }
            std::cout << "\n";
            if (r < 2) {
                std::cout << "  ---+---+---\n";
            }
        }
        std::cout << "\n";
    }

    char symbol_at(int r, int c) const {
        Player p = grid[r][c];
        if (p == Player::Human) return 'X';
        if (p == Player::Computer) return 'O';
        return ' ';
    }

private:
    std::vector<std::vector<Player>> grid;
};

class Game {
public:
    void run() {
        std::cout << "==============================\n";
        std::cout << "   Tic-Tac-Toe (C++ with AI)\n";
        std::cout << "==============================\n\n";
        std::cout << "You are X, computer is O.\n";
        std::cout << "Enter moves as: row col\n\n";

        bool play_again = true;
        while (play_again) {
            board.reset();
            play_one_round();
            play_again = ask_play_again();
        }

        std::cout << "Thanks for playing!\n";
    }

private:
    Board board;

    void play_one_round() {
        Player current = Player::Human;

        while (true) {
            board.print();
            auto win = board.winner();
            if (win.has_value()) {
                if (win == Player::Human) {
                    std::cout << "You win! 🎉\n\n";
                } else {
                    std::cout << "Computer wins. 🤖\n\n";
                }
                break;
            }

            if (board.is_full()) {
                std::cout << "It's a draw.\n\n";
                break;
            }

            if (current == Player::Human) {
                human_turn();
                current = Player::Computer;
            } else {
                computer_turn();
                current = Player::Human;
            }
        }
    }

    void human_turn() {
        while (true) {
            std::cout << "Your move (row col): ";
            int r, c;
            if (!(std::cin >> r >> c)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter two numbers.\n";
                continue;
            }
            if (r < 0 || r >= 3 || c < 0 || c >= 3) {
                std::cout << "Row and column must be between 0 and 2.\n";
                continue;
            }
            if (!board.is_empty(r, c)) {
                std::cout << "That cell is taken, pick another one.\n";
                continue;
            }
            board.place(r, c, Player::Human);
            break;
        }
    }

    void computer_turn() {
        std::cout << "Computer is thinking...\n";
        Move best_move = find_best_move();
        board.place(best_move.row, best_move.col, Player::Computer);
    }

    int evaluate_board() {
        auto win = board.winner();
        if (win.has_value()) {
            if (win == Player::Computer) {
                return +10;
            } else if (win == Player::Human) {
                return -10;
            }
        }
        return 0;
    }

    int minimax(bool is_maximizing, int depth) {
        int score = evaluate_board();
        if (score == 10 || score == -10) {
            return score - depth * (score > 0 ? 1 : -1);
        }
        if (board.is_full()) {
            return 0;
        }

        if (is_maximizing) {
            int best = std::numeric_limits<int>::min();
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    if (board.is_empty(r, c)) {
                        board.place(r, c, Player::Computer);
                        int value = minimax(false, depth + 1);
                        board.unplace(r, c);
                        if (value > best) {
                            best = value;
                        }
                    }
                }
            }
            return best;
        } else {
            int best = std::numeric_limits<int>::max();
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    if (board.is_empty(r, c)) {
                        board.place(r, c, Player::Human);
                        int value = minimax(true, depth + 1);
                        board.unplace(r, c);
                        if (value < best) {
                            best = value;
                        }
                    }
                }
            }
            return best;
        }
    }

    Move find_best_move() {
        int best_val = std::numeric_limits<int>::min();
        Move best_move{ -1, -1 };

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board.is_empty(r, c)) {
                    board.place(r, c, Player::Computer);
                    int move_val = minimax(false, 0);
                    board.unplace(r, c);

                    if (move_val > best_val) {
                        best_val = move_val;
                        best_move = { r, c };
                    }
                }
            }
        }

        return best_move;
    }

    bool ask_play_again() {
        while (true) {
            std::cout << "Play again? (y/n): ";
            char ch;
            if (!(std::cin >> ch)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (ch == 'y' || ch == 'Y') return true;
            if (ch == 'n' || ch == 'N') return false;
            std::cout << "Please enter 'y' or 'n'.\n";
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
