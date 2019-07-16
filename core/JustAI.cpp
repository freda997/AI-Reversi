#include <ics46/factory/DynamicFactory.hpp>
#include "JustAI.hpp"
#include <iostream>
#include "OthelloGameState.hpp"
	
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, shiqih1::JustAI, "**|EUREKA|**(Required)");

std::pair<int, int> shiqih1::JustAI::chooseMove(const OthelloGameState& state)
{
	int winner = 0;
	std::pair<int, int> result;
	bool is_white_turn = state.isWhiteTurn();
	int width = state.board().width();
	int height = state.board().height();
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (state.isValidMove(w, h)) {
				if (path_searching(state, is_white_turn, 3) > winner) result = std::make_pair(w, h);
			}
		}
	}
	return result;

}	

int shiqih1::JustAI::path_searching(const OthelloGameState &state, bool is_white_turn, int depth)
{
	int result;
	if (state.isWhiteTurn() == is_white_turn) result = -10000;
	else result = 10000;
	if (depth == 0 || state.isGameOver()) return eval_state(state,is_white_turn);
	else {
		int width = state.board().width();
		int height = state.board().height();
		
        std::cout<<"setup complete"<<std::endl;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				if (state.isValidMove(w, h)) {
					OthelloGameState* new_state = state.clone();
					*new_state.makeMove(w, h);
                    std::cout<<"sss"<<std::endl;
					int temp = path_searching(new_state, is_white_turn, depth);
					if (state.isWhiteTurn() == is_white_turn) {
						if (temp > result) result = temp;
					}
					else {
						if (temp < result) result = temp;
					}
				}
			}
		}
	}
	return result;
}

int shiqih1::JustAI::eval_state(const OthelloGameState& state,bool is_white_turn)
{
	if (is_white_turn) return state.whiteScore() - state.blackScore();
	else return state.blackScore() - state.whiteScore();
}
