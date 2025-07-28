#include "core/game_factory.hpp"
#include "Board/board.hpp"

int main(){

    Game* game = nullptr;
    Board* board = nullptr;
    Dice* dice = nullptr;
    
    cout<<"Welcome to Snakes and Ladders Game!"<<endl;
    cout<<"Choose Game Type:"<<endl;
    cout<<"1. Standard Game"<<endl;
    cout<<"2. Random Game"<<endl;
    cout<<"3. Custom Game"<<endl;
    int choice;
    cin>>choice;
    
    if(choice == 1) {
        
        game = GameFactory::create_standard_game();
    }
    else if(choice == 2) {
        int board_size;
        cout<<"Enter Board Size (e.g., 10 for 10x10): ";
        cin>>board_size;
        Difficulty difficulty;
        cout<<"Choose Difficulty (0: EASY, 1: MEDIUM, 2: HARD): ";
        int diff_choice;
        cin>>diff_choice;
        if(diff_choice == 0) difficulty = Difficulty::EASY;
        else if(diff_choice == 1) difficulty = Difficulty::MEDIUM;
        else if(diff_choice == 2)difficulty = Difficulty::HARD;
        else difficulty = Difficulty::MEDIUM; // Default to EASY if invalid input
        game = GameFactory::create_random_game(board_size, difficulty);
    }
    else if(choice == 3) {
        int board_size, num_snakes, num_ladders;
        cout<<"Enter Board Size (e.g., 10 for 10x10): ";
        cin>>board_size;
        cout<<"Do you want random positions for snakes and ladders? (1: Yes, 0: No): ";
        bool random_positions; 
        cin>>random_positions;
        if(random_positions) {
            cout<<"Enter Number of Snakes: ";
            cin>>num_snakes;
            cout<<"Enter Number of Ladders: ";
            cin>>num_ladders;
            game = GameFactory::create_custom_game(board_size, num_snakes, num_ladders, random_positions);
            
        } else {
            cout<<"Enter Number of Snakes: ";
            cin>>num_snakes;
            cout<<"Enter Number of Ladders: ";
            cin>>num_ladders;
            game = GameFactory::create_custom_game(board_size, num_snakes, num_ladders, false);
            board = game->get_board();
            cout<<"Enter Snakes (start end) separated by space (e.g., 99 54): "<<endl;
            for(int i = 0; i < num_snakes; ++i) {
                int start, end;
                cin>>start>>end;
                try {
                    board->add_entity(new Snake(start, end));
                } catch (const invalid_argument& e) {
                    cout<<"Error adding snake: "<<e.what()<<endl;
                    --i; // Retry this snake
                }
            }
            cout<<"Enter Ladders (start end) separated by space (e.g., 2 38): "<<endl;
            for(int i = 0; i < num_ladders; ++i) {
                int start, end;
                cin>>start>>end;
                try {
                    board->add_entity(new Ladder(start, end));
                } catch (const invalid_argument& e) {
                    cout<<"Error adding ladder: "<<e.what()<<endl;
                    --i; // Retry this ladder
                }
            }
        }   

    }
    else {
        cout<<"Invalid choice!"<<endl;
        return 1;
    }
    
    if(!game) {
        cout<<"Failed to create game!"<<endl;
        return 1;
    }
    
    game->add_player(new Player("Gurekam"));
    game->add_player(new Player("VT"));
    game->add_observer(new ConsoleNotifier());
    game->get_board()->display();

    game->play();
}