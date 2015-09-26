#include "Game.h"

#include"read_write.h"

int main()
{
	freopen ("data/inf/load.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
	Game *game = new Game ();
	if (game->init (true)) {
		while (game->running) {
			CNTRL ("run");
			game->update ();
			game->render ();
		}
		game->del ();
	}
	sf::Vector2f;
    return 0;
}