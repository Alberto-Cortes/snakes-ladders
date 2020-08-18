#include <iostream>
#include <vector>
#include <algorithm>
#include "jugador.h"
#include "casillaBonus.h"
#include "dado.h"

using namespace std;

// Customizable aspects of the game, default values are from last hw.
// Using global variables to avoid using them on each method as parameter.
int tiles = 30;
int snakes = 3;
int ladders = 3;
int penalty = -3;
int reward = 3;
int players = 2;
int maxTurns = 40;
int playerQuant = 2;
char gameType = 'M'; // M for manual, A for auto.

class MyGame
{
public:
    int nextTurn(int turn, Jugador player, Dado dicey, vector <Casillas> board){
        // calcula avance del Jugador
        int current = player.getPosition();
        int roll = dicey.GetValorDado();

        int after_roll = current + roll;
        int bonus_type = board[after_roll].getBonus();
        int bonus_val = 0;
        if (bonus_type == 1){
            bonus_val = penalty;
        } else if (bonus_type == 2){
            bonus_val = reward;
        }
        int after_bonus = after_roll + bonus_val;

        string bonus_char;
        if (bonus_type == 0) {
            bonus_char = "N";
        } else if (bonus_type == 1) {
            bonus_char = "S";
        } else if (bonus_type == 2) {
            bonus_char = "L";
        }

        cout << turn << " " << current << " " << roll << " " << bonus_char << " " << after_bonus << endl;
        return after_bonus;
    }
    void start()
    {
        vector <int> used;
        vector <Casillas> board;
        string input = "C";
        bool cont;
        int turn = 0;
        int currentBonus = 0;
        Dado dicey;
        Jugador player1(1, 1);
        Jugador player2(2, 1);
        int movement, firstBonus, secondBonus, playerInTurn;

        cout << "Please enter the following Customizable attributes for your game.\n";
        cout << "\nNumber of tiles: ";
        cin >> tiles;
        cout << "Number of snakes: ";
        cin >> snakes;
        cout << "Number of ladders: ";
        cin >> ladders;
        cout << "Penalty per snake: ";
        cin >> penalty;
        cout << "Reward per ladder: ";
        cin >> reward;
        cout << "Number of players: ";
        cin >> playerQuant;
        cout << "Game type: ";
        cin >> gameType;
        cout << "Max turns: ";
        cin >> maxTurns;

        int totalBonusTiles = snakes + ladders;

        // Generating the board of the game.
        for (int i = 0; i < tiles; i++){
            Casillas cas(0);
            board.push_back(cas);
        }
        // Process to randomize location of stairs and snakes.
        for (int j = 0; j < totalBonusTiles; j++){
            int minBonusTile = reward+1;
            int maxBonusTile = tiles+penalty-1;
            int pos = (rand() % maxBonusTile) + minBonusTile;
            while (find(used.begin(), used.end(), pos) != used.end())
                // Checking if not repeating the special tile.
                pos = (rand() % maxBonusTile) + minBonusTile;
            used.push_back(pos);

            // Determine if there will be less snakes or ladders to use that order.
            if (snakes < ladders){
                firstBonus = 2;
                secondBonus = 1;
            } else {
                firstBonus = 1;
                secondBonus = 2;
            }
            if (currentBonus % 2 == 0){
                CasillaBonus temp = CasillaBonus(firstBonus);
                board[pos] = temp;
            } else if (currentBonus % 2){
                CasillaBonus temp = CasillaBonus(secondBonus);
                board[pos] = temp;
            }
            currentBonus++;
        }
        // Generating a vector of players;
        vector <Jugador> players;
        for (int k = 0; k < playerQuant; k++){
            Jugador temp_player(k, 1);
            players.push_back(temp_player);
        }
        if (gameType == 'M'){
            cout << "\nPress C to continue next turn, or E to end the game: " << endl;
        }
        while (input != "E"){
            if (gameType == 'M'){
                cin >> input;
            } else {
                input = 'C';
            }
            if (input == "C"){
                playerInTurn = turn % playerQuant;
                movement = nextTurn(turn, players[playerInTurn], dicey, board);
                if (movement < tiles){
                    players[playerInTurn].setPosition(movement);
                } else {
                    cout << "Player " << playerInTurn << " has won!\n" << endl;
                    break;
                }
                if (turn < maxTurns){
                    turn++;
                } else {
                    cout << "Turn limit reached! No one wins.\n";
                    break;
                }
            } else if (input == "E"){
                cout << "Thank you for playing!" << endl;
            } else {
                cout << "Invalid option, please press C to continue next turn or E to end the game" << endl;
            }
        }
    }
};

int main(){
    MyGame g;
    g.start();
    return 0;
}
