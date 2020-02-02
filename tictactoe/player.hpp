#ifndef _TICTACTOE_PLAYER_HPP_
#define _TICTACTOE_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace TICTACTOE
{

class Player
{
public:
    uint8_t maxPlayer;
    uint8_t minPlayer;
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
    int minimax(const GameState &state, uint8_t player, int depth);
    int evaluation_board(const GameState &state);
    const int rows_columns_diagonals[10][4] = {
    // rows in a 4x4 board
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15},
    // columns in a 4x4 board
        {0,4,8,12},
        {1,5,9,13},
        {2,6,10,14},
        {3,7,11,15},
    // diagonals in a 4x4 board
        {0,5,10,15},
        {3,6,9,12}
    };

    const int weights[5][5] = {
    {      0,   -10,  -100, -1000, -10000 },
    {     10,     0,     0,     0, 0      },
    {    100,     0,     0,     0, 0      },
    {   1000,     0,     0,     0, 0      },
    {  10000,     0,     0,     0, 0      }
    };
};

/*namespace TICTACTOE*/ }

#endif
