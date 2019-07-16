#include "OthelloAI.hpp"
#include <iostream>
#include "OthelloGameState.hpp"

namespace shiqih1
{
	class JustAI : public OthelloAI
	{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
	private:
		int eval_state(const OthelloGameState& state, bool is_white_turn);
		int path_searching(const OthelloGameState &state, bool is_white_turn, int depth);


	};
}