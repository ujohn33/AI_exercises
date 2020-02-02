#include "player.hpp"
#include <cstdlib>
#include "constants.hpp"
#include <climits>
#include <algorithm>


namespace TICTACTOE
{

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int tree_depth = 2;
    maxPlayer = CELL_X ; // maximizing for this one
    minPlayer = CELL_O ; // minimizing for this one

    if (lNextStates.size() == 0) return GameState(pState, Move());
    if (lNextStates.size() == 1) {
      return lNextStates[0];  //skip the loop, one state left
    }

    int oldGain = INT_MIN;
    int index = 0;
    for (uint k = 0; k < lNextStates.size(); k++) {
        int Gain = minimax(lNextStates[k], pState.getNextPlayer(), tree_depth);
        //std::cerr << k << " check cell\n";
        if (Gain > oldGain) {
            index = k;
            oldGain = Gain;
        }
    }
    return lNextStates[index % lNextStates.size()];
}

//minmax algorithm with alphabeta pruning
int Player::minimax(const GameState &pState, uint8_t player, int depth) {

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int len = lNextStates.size();
    // here is a pseudo code I am going to implement
    //    if depth == 0 or game over in position
    //        return static evaluation of position
    if (pState.isEOG() || depth == 0) {
        return evaluation_board(pState);
        //std::cerr << evaluation_board(pState) << " here we are at depth 0\n";
    }
    int bestPossible = 0;
    //    if maximizingPlayer
    //        maxEval = -infinity
    //        for each child of position
    //            eval = minimax(child, depth - 1, alpha, beta, false)
    //            maxEval = max(maxEval, eval)
    //            alpha = max(alpha, eval)
    //            if beta <= alpha
    //              break
    //        return maxEval
    // player X -> 1
    if (player == maxPlayer) {
        int bestPossible = INT_MIN;
        for (int i = 0; i < len; ++i) {
            int eval = minimax(lNextStates[i], minPlayer, depth-1);
            //std::cerr << eval << " eval for other Player\n";
            bestPossible = std::max(eval, bestPossible);
        }
        return bestPossible;
    //    else
    //        minEval = +infinity
    //        for each child of position
    //            eval = minimax(child, depth - 1, alpha, beta, true)
    //            minEval = min(minEval, eval)
    //            beta = min(beta, eval)
    //            if beta <= alpha
    //              break
    //        return minEval
  } else if (player == minPlayer) {
        int bestPossible = INT_MAX;
        for (int i = 0; i < len; ++i) {
            int eval = minimax(lNextStates[i], maxPlayer, depth-1);
            //std::cerr << eval << " eval for first Player\n";
            bestPossible = std::min(eval, bestPossible);
        }
        return bestPossible;
    }

    return bestPossible;

}

int Player::evaluation_board(const GameState &pstate) {

    int score = 0;
    if (pstate.isEOG()) {
        if (pstate.isXWin()) {
          return INT_MAX;
        }
        else if (pstate.isOWin()) {
            return INT_MIN;
        }
        else{
          return 0;
        }
    }

    for (int i = 0; i < 10; i++)  {
        int count_max = 0;
        int count_min = 0;
        for (int j = 0; j < 4; j++)  {
            int piece = pstate.at(rows_columns_diagonals[i][j]);
            if (piece&maxPlayer){
                count_max++;
                //std::cerr << count_other << " count at number"<<rows_columns_diagonals[i][j]<<"\n";
              }
            else if (piece&minPlayer){
                count_min++;
                //std::cerr << count_active << " count at number"<<rows_columns_diagonals[i][j]<<"\n";
              }
      }
      score += weights[count_max][count_min];
    }
    return score;

}
/*namespace TICTACTOE*/ }
