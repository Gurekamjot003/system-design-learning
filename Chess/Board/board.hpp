#pragma once
#include "../Piece/piece_factory.hpp"

class Board {
    vector<vector<Piece*>> grid; // 8x8 grid of pieces
    
public:
    Board() {
        grid.resize(8, vector<Piece*>(8, nullptr)); // Initialize an 8x8 board with nullptr
        initialize_board(); // Set up the initial board state
    }

    ~Board() {
        for (auto& row : grid) {
            for (auto& piece : row) {
                delete piece; // Clean up dynamically allocated pieces
            }
        }
    }

    void place_piece(Position pos, Piece* piece) {
        if (pos.is_valid()) {
            grid[pos.get_row()][pos.get_col()] = piece;
        } else {
            throw invalid_argument("Invalid position");
        }
    }

    void remove_piece(Position pos) {
        if (pos.is_valid()) {
            grid[pos.get_row()][pos.get_col()] = nullptr; // Set the position to nullptr
        } else {
            throw invalid_argument("Invalid position");
        }
    }

    Piece* get_piece(Position pos) const {
        if (pos.is_valid()) {
            return grid[pos.get_row()][pos.get_col()];
        } else {
            throw invalid_argument("Invalid position");
        }
    }

    void initialize_board() {
        // Initialize pawns
        for (int col = 0; col < 8; ++col) {
            place_piece(Position(6, col), PieceFactory::create_piece(Color::WHITE, PieceType::PAWN));
            place_piece(Position(1, col), PieceFactory::create_piece(Color::BLACK, PieceType::PAWN));
        }

        // Initialize rooks
        place_piece(Position(7, 0), PieceFactory::create_piece(Color::WHITE, PieceType::ROOK));
        place_piece(Position(7, 7), PieceFactory::create_piece(Color::WHITE, PieceType::ROOK));
        place_piece(Position(0, 0), PieceFactory::create_piece(Color::BLACK, PieceType::ROOK));
        place_piece(Position(0, 7), PieceFactory::create_piece(Color::BLACK, PieceType::ROOK));

        // Initialize knights
        place_piece(Position(7, 1), PieceFactory::create_piece(Color::WHITE, PieceType::KNIGHT));
        place_piece(Position(7, 6), PieceFactory::create_piece(Color::WHITE, PieceType::KNIGHT));
        place_piece(Position(0, 1), PieceFactory::create_piece(Color::BLACK, PieceType::KNIGHT));
        place_piece(Position(0, 6), PieceFactory::create_piece(Color::BLACK, PieceType::KNIGHT));

        // Initialize bishops
        place_piece(Position(7, 2), PieceFactory::create_piece(Color::WHITE, PieceType::BISHOP));
        place_piece(Position(7, 5), PieceFactory::create_piece(Color::WHITE, PieceType::BISHOP));
        place_piece(Position(0, 2), PieceFactory::create_piece(Color::BLACK, PieceType::BISHOP));
        place_piece(Position(0, 5), PieceFactory::create_piece(Color::BLACK, PieceType::BISHOP));

        // Initialize queens
        place_piece(Position(7, 3), PieceFactory::create_piece(Color::WHITE, PieceType::QUEEN));
        place_piece(Position(0, 3), PieceFactory::create_piece(Color::BLACK, PieceType::QUEEN));

        // Initialize kings
        place_piece(Position(7, 4), PieceFactory::create_piece(Color::WHITE, PieceType::KING));
        place_piece(Position(0, 4), PieceFactory::create_piece(Color::BLACK, PieceType::KING));
    }

    bool is_occupied(Position pos) const {
        if (pos.is_valid()) {
            return grid[pos.get_row()][pos.get_col()] != nullptr;
        } else {
            throw invalid_argument("Invalid position");
        }
    }

    bool is_occupied_by_same_color(Position pos, Color color) const {
        if (pos.is_valid()) {
            Piece* piece = grid[pos.get_row()][pos.get_col()];
            return piece != nullptr && piece->get_color() == color;
        } else {
            throw invalid_argument("Invalid position");
        }
    }

    void move_piece(Position from, Position to) {
        if (!from.is_valid() || !to.is_valid()) {
            throw invalid_argument("Invalid position");
        }
        
        Piece* piece = get_piece(from);
        if (piece == nullptr) {
            throw runtime_error("No piece at the source position");
        }

        Piece* captured_piece = get_piece(to);
        remove_piece(from);
        place_piece(to, piece);

        if(captured_piece) delete captured_piece;
        
        piece->mark_as_moved(); // Mark the piece as moved
    }

    Position find_king(Color color) const {

        vector<Position> positions = get_all_pieces_of_color(color);
        for (const Position& pos : positions) {
            Piece* piece = get_piece(pos);
            if (piece->get_type() == PieceType::KING) {
                return pos;
            }
        }
       
        return Position(-1, -1 ); // King not found
    }

    vector<Position> get_all_pieces_of_color(Color color) const {
        vector<Position> positions;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Piece* piece = grid[row][col];
                if (piece != nullptr && piece->get_color() == color) {
                    positions.push_back(Position(row, col));
                }
            }
        }
        return positions;
    }

    void display() const {
        cout << "    a    b    c    d    e    f    g    h" << endl;
        cout<<"  -----------------------------------------"<<endl;
        for (int r = 0; r < 8; ++r) {
            cout << 8 - r << " | ";
            for (int c = 0; c < 8; ++c) {
                Piece* piece = grid[r][c];
                if (piece) {
                    string color = piece->get_color() == Color::WHITE? "W": "B";
                    cout << color+piece->get_symbol() << " | ";
                } else {
                    cout << "   | ";
                }
            }
            cout <<" "<< 8 - r << " ";
            cout << endl;
            cout<<"  -----------------------------------------"<<endl;
        
        }
        cout << "    a    b    c    d    e    f    g    h" << endl;
        
        
    }
};

vector<Position> King::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    int r = pos.get_row();
    int c = pos.get_col();

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        Position new_pos(r + dr[i], c + dc[i]);
        if (new_pos.is_valid()) {
            if (!board->is_occupied(new_pos) || !board->is_occupied_by_same_color(new_pos, get_color())) {
                moves.push_back(new_pos);
            }
        }
    }
    return moves;
}

vector<Position> Queen::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    // Queen moves like a Rook and a Bishop
    // Rook moves (horizontal and vertical)
    int dr_rook[] = {-1, 1, 0, 0};
    int dc_rook[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int step = 1; step < 8; ++step) {
            Position new_pos(pos.get_row() + dr_rook[i] * step, pos.get_col() + dc_rook[i] * step);
            if (new_pos.is_valid()) {
                if (!board->is_occupied(new_pos)) {
                    moves.push_back(new_pos);
                } else {
                    if (!board->is_occupied_by_same_color(new_pos, get_color())) {
                        moves.push_back(new_pos);
                    }
                    break; // Blocked by a piece
                }
            } else {
                break; // Out of bounds
            }
        }
    }

    // Bishop moves (diagonals)
    int dr_bishop[] = {-1, -1, 1, 1};
    int dc_bishop[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int step = 1; step < 8; ++step) {
            Position new_pos(pos.get_row() + dr_bishop[i] * step, pos.get_col() + dc_bishop[i] * step);
            if (new_pos.is_valid()) {
                if (!board->is_occupied(new_pos)) {
                    moves.push_back(new_pos);
                } else {
                    if (!board->is_occupied_by_same_color(new_pos, get_color())) {
                        moves.push_back(new_pos);
                    }
                    break; // Blocked by a piece
                }
            } else {
                break; // Out of bounds
            }
        }
    }
    return moves;
}

vector<Position> Pawn::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    int r = pos.get_row();
    int c = pos.get_col();
    Color piece_color = get_color();

    int direction = (piece_color == Color::WHITE) ? -1 : 1; // White moves up, Black moves down

    // One step forward
    Position one_step(r + direction, c);
    if (one_step.is_valid() && !board->is_occupied(one_step)) {
        moves.push_back(one_step);

        // Two steps forward (only on initial position)
        if (!has_moved_once()) {
            Position two_steps(r + 2 * direction, c);
            if (two_steps.is_valid() && !board->is_occupied(two_steps)) {
                moves.push_back(two_steps);
            }
        }
    }

    // Captures
    int capture_cols[] = {c - 1, c + 1};
    for (int col_offset : capture_cols) {
        Position capture_pos(r + direction, col_offset);
        if (capture_pos.is_valid() && board->is_occupied(capture_pos) && !board->is_occupied_by_same_color(capture_pos, piece_color)) {
            moves.push_back(capture_pos);
        }
    }
    return moves;
}

vector<Position> Rook::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int step = 1; step < 8; ++step) {
            Position new_pos(pos.get_row() + dr[i] * step, pos.get_col() + dc[i] *step);
            if (new_pos.is_valid()) {
                if (!board->is_occupied(new_pos)) {
                    moves.push_back(new_pos);
                } else {
                    if (!board->is_occupied_by_same_color(new_pos, get_color())) {
                        moves.push_back(new_pos);
                    }
                    break; // Blocked by a piece
                }
            } else {
                break; // Out of bounds
            }
        }
    }
    return moves;
}

vector<Position> Bishop::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    int dr[] = {-1, -1, 1, 1}; // Up-Left, Up-Right, Down-Left, Down-Right
    int dc[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int step = 1; step < 8; ++step) {
            Position new_pos(pos.get_row() + dr[i] * step, pos.get_col() + dc[i] * step);
            if (new_pos.is_valid()) {
                if (!board->is_occupied(new_pos)) {
                    moves.push_back(new_pos);
                } else {
                    if (!board->is_occupied_by_same_color(new_pos, get_color())) {
                        moves.push_back(new_pos);
                    }
                    break; // Blocked by a piece
                }
            } else {
                break; // Out of bounds
            }
        }
    }
    return moves;
}

vector<Position> Knight::get_possible_moves(Position pos, Board* board) {
    vector<Position> moves;
    int r = pos.get_row();
    int c = pos.get_col();

    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1
    };

    for (int i = 0; i < 8; ++i) {
        Position new_pos(r + dr[i], c + dc[i]);
        if (new_pos.is_valid()) {
            if (!board->is_occupied(new_pos) || !board->is_occupied_by_same_color(new_pos, get_color())) {
                moves.push_back(new_pos);
            }
        }
    }
    return moves;
}