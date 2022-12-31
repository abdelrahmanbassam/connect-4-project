#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"

Game_info current_game;

int main()
{
    Game_info current_game;
    struct tool game;
    player first, second;
    Rxml(&game);

    creat_game(&game, &first, &second);
    main_menu(&game);
    return 0;
}
