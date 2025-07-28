#include"core/game_factory.hpp"

int main(){
    int board_size = 5;
    Symbol empty_symbol('_');

    Game* game = GameFactory::create_game(GameType::STANDARD, board_size, empty_symbol);
    Player* player1 = new Player("Gurekam", Symbol('X'));
    Player* player2 = new Player("VT", Symbol('O'));

    game->add_player(player1);
    game->add_player(player2);
    
    game->add_observer(new ConsoleNotifier());

    game->display_board();
    game->play();
}