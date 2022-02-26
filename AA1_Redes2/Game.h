#include <vector>
#include "Maze.h"
#include "Player.h"
#include "Constants.h"


class Game
{

public:
	Maze* maze;
	std::vector<Player*> players;

	Game();

	void Update();
	void Draw();
};