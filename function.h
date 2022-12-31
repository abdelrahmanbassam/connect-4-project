#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Rxml.h"




int main_menu(struct tool * game)
{
    char choice[10];
    printf( BLUE "Hello, choose the game mode..\n1) Start new game\n2) Load a game\n3) View top players\n4) Quit\n");
    scanf("%s", &choice);
    while(atoi(choice) < 1 || atoi(choice) > 4){
        printf("Plaese, Enter a valid number mode..\n");
        scanf("%s", &choice);
    }
    switch(atoi(choice))
    {
    case 1 :    start_game(game);
        break;
    case 2 :
        load(game);
        char select_menu[10];
        int moves = game->total_moves;
        game->total_moves=0; game->first->score=0; game->second->score=0;
        for(int i=0; i<moves; i++){
            sprintf(select_menu, "%d", game->select_cols[i]);
            make_move(game, select_menu);
        }
        if(game->mode == 1)
            mode_1player(game);
        else
            mode_2players(game);
        break;
    case 3 :    MENU_HIGHSCORE(game);
        break;
    case 4 :    return 0;
        break;
    }
}

int select_mode()
{
    char mode[10];
    printf("What's the mode you want..\n1) 1 player mode (vs cpu)\n2) 2 players mode\n");
    scanf("%s", &mode);
    while(atoi(mode) != 1 && atoi(mode) != 2){
        printf("Please, Enter a vaild number to choose the mode..\n");
         scanf("%s", &mode);
    }
    return atoi(mode);
}


void start_game(struct tool * game)
{
    game->mode = select_mode();
    if(game->mode == 1)
        mode_1player(game);
    else
        mode_2players(game);
}

void mode_2players(struct tool *game)
{
    game->gameTime = time(NULL);
    char select_menu[10];

    scan_game(*game);
     while(game->total_moves < (game->rows*game->cols))
    {
        scanf("%s", select_menu);
        inGame_menu(game, select_menu);
        scan_game(*game);
    }
    GameOver(game);
}

void scan_game(struct tool game)
{
    if(game.total_moves%2 == 0)
        printf(CYAN "%s PLAYER TURN\n", game.first->name);
    else
        printf(RED "%s PLAYER TURN\n", game.second->name);

    printf(MAGENTA "Time = %d:%d ,Number of Moves = %d\n", (time(NULL)-game.gameTime)/60, (time(NULL)-game.gameTime)%60, game.total_moves);
    printf(CYAN "SCORE OF %s PLAYER = %d,  " RED "SCORE OF %s PLAYER = %d\n" RESET, game.first->name, game.first->score, game.second->name, game.second->score);

    for(int i=0; i<game.cols; i++)
        printf("  %d ", i+1);
    printf("\n");
    for(int i=0; i<game.rows; i++)
    {
        for(int j=0; j<game.cols; j++)                             //remmeber -> player.color (any player can choose the color he wants)
        {
            printf(GREEN "|");
            if(game.board[i][j] == 'X') printf(CYAN " %c ", game.board[i][j]);
            else printf(RED " %c ", game.board[i][j]);
        }
        printf(GREEN "|\n");
        for(int k=0; k<game.cols; k++)
            printf("----");
        printf("-\n" RESET);
    }
}

void creat_game(struct tool *game, player * first, player * second)
{
    game->first = first, game->second = second;
    strcpy(first->name, "FIRST"), strcpy(second->name, "SECOND");
    first->symbol = 'X', second->symbol = 'O';
    system("color 00");
    first->score = 0, second->score = 0;
    game->total_moves =0, game->level=0;

    for(int i=0; i<game->rows; i++)
        for(int j=0; j<game->cols; j++)
            game->board[i][j] = ' ';
    for(int i=0; i<game->cols; i++)
            game->available_cols[i] = game->rows;
    for(int i=0; i<(game->rows*game->cols); i++)
    {
        game->select_cols[i] = 0;
        for(int j=0; j<2; j++)
            game->undo_moves[i][j] = 0;
    }
}

int inGame_menu(struct tool *game, char select_menu[])
{
    printf(YELLOW "Enter the number of col (m for in-game menu)\n");
    if(isdigit(select_menu[0])){
        make_move(game, select_menu);
        return 0;
    }
    switch(tolower(select_menu[0]))
    {
        case 'm' :
            printf(YELLOW "Enter \nc for a countinue \nu for undo \nr for redo \ns for save \ne for quit\n");
        case 'c' :
            break;
        case 'u' :
            if(game->total_moves == 0){
                printf(YELLOW "There is no move to make undo\n");
            }else{
                undo(game);
                if(game->mode == 1)
                    undo(game);
            }
            break;
        case 'r' :
            if(game->nofUndo == 0)
                printf(YELLOW "You can't make redo\n");
            else
                redo(game);
            break;
        case 's' :
                take_current_game(*game);
                save();
            break;
        case 'e' :
            printf("Do you want to leave?\n1)Yes\n2)No\n");
            scanf("%s", select_menu);
            if(atoi(select_menu) == 1){
                printf("Do you want to save the game?\n1)Yes\n2)No\n");
                scanf("%s", select_menu);
                if(atoi(select_menu) == 1) save();
                _Exit(0);
            }
            break;
    }
}



void make_move(struct tool *game, char select_menu[])
{
    player *playerTurn;
    if(game->total_moves%2 == 0)
        playerTurn = game->first;
    else
        playerTurn = game->second;

    int nofcol = atoi(select_menu);
    if(nofcol >= 1 && nofcol <= game->cols && game->available_cols[nofcol-1] > 0){
        game->board[game->available_cols[nofcol-1]-1][nofcol-1] = playerTurn->symbol;
        game->available_cols[nofcol-1]--;
        game->select_cols[game->total_moves] = nofcol;
        game->total_moves+=1;

        playerTurn->score += count_score(game);
        for(int i=0; i<game->nofUndo; i++)
            for(int j=0; j<2; j++)
                game->undo_moves[i][j] = 0;
        game->nofUndo = 0;
    }else printf("please, Enter a vaild nof col..\n");
    return 0;
}

void undo(struct tool *game)
{
    player *other;
    if(game->total_moves%2 == 1)
        other = game->first;
    else
        other = game->second;

    other->score -= count_score(game);

    int des_row, des_col;
    des_col = game->select_cols[game->total_moves-1] - 1;
    des_row = game->available_cols[des_col] ;
    game->board[des_row][des_col] = ' ';
    game->undo_moves[game->nofUndo][0] = des_row;
    game->undo_moves[game->nofUndo][1] = des_col;
    game->select_cols[game->total_moves-1] = 0;            // -> minus values by 1 && increas nofUndo by 1
    game->available_cols[des_col]++;
    game->total_moves-=1, game->nofUndo+=1;
    return 0;
}

void redo(struct tool *game)
{
    player * playerTurn;
    if(game->total_moves%2 == 0)
        playerTurn = game->first;
    else
        playerTurn = game->second;

    int des_row, des_col;
    des_row = game->undo_moves[game->nofUndo-1][0];
    des_col = game->undo_moves[game->nofUndo-1][1];
    game->board[des_row][des_col] = playerTurn->symbol;
    game->undo_moves[game->nofUndo-1][0] = 0;
    game->undo_moves[game->nofUndo-1][1] = 0;
    game->total_moves+=1, game->nofUndo-=1;
    game->select_cols[game->total_moves-1] = des_col+1;
    game->available_cols[des_col]--;

    playerTurn->score += count_score(game);
}

int count_score(struct tool *game)
{
    player *playerTurn;
    if(game->total_moves%2 == 1)
        playerTurn = game->first;
    else
        playerTurn = game->second;

    int counter=0, score=0;
    int des_col = game->select_cols[game->total_moves-1] - 1;
    int des_row = game->available_cols[des_col];
   //horizental
    for(int i=-3; i<=3; i++)
    {
        if(des_col+i >= 0 && des_col+i < game->cols)
        while(des_col+i < 0) i++;
        if(des_col+i > game->cols-1) break;
        if(playerTurn->symbol == game->board[des_row][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
            }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //vertical
    for(int i=0; i<=3; i++)
    {
        if(des_row+i > game->rows-1) break;
        if(playerTurn->symbol == game->board[des_row + i][des_col]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //main diagonal
    for(int i=-3; i<=3; i++)
    {
        while(des_row+i < 0 || des_col+i < 0) i++;
        if(des_row+i > game->rows-1 || des_col+i > game->cols-1) break;
        if(playerTurn->symbol == game->board[des_row + i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //off diagonal
     for(int i=-3; i<=3; i++)
    {
        while(des_row-i > game->rows-1 || des_col+i < 0) i++;  //-> prop here (alhamdulellah)
        if(des_row-i > game->rows-1 || des_col+i > game->cols-1) break;
        if(playerTurn->symbol == game->board[des_row - i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;
    return score;
}

void select_level(struct tool *game)
{
    char level[10];
    printf("What's level do you want ?\n1) Easy\n2) Medium\n3) Hard\n4) Super hard\n");
    while(atoi(level) < 1 || atoi(level) > 4)
    {
        printf("Please, Enter a vaild number to choose the level..\n");
        scanf("%s", level);
    }
    game->level = atoi(level);
}


void mode_1player(struct tool *game)
{
    if(game->level == 0) select_level(game);
    game->gameTime = time(NULL);
    switch(game->level)
    {
        case 1 :    level_easy(game);
            break;
        case 2 :    level_medium(game);
            break;
        case 3 :    level_hard(game);
            break;
        case 4 :    level_supeHard(game);
            break;
    }
}
  //  char select_menu[10];*/

   /* scan_game(*game);
     while(game->total_moves < (game->rows*game->cols))
    {
        if(game->total_moves%2 == 0){
            scanf("%s", select_menu);
            inGame_menu(game, select_menu);
        }else{
            sprintf(select_menu, "%d", (rand()%game->cols +1));
            inGame_menu(game, select_menu);
        }
        scan_game(*game);
    }
    GameOver(game);*/




int level_easy(struct tool *game)
{
    srand(time(NULL));
    char select_menu[10];

    scan_game(*game);
     while(game->total_moves < (game->rows*game->cols))
    {
        if(game->total_moves%2 == 0){
            scanf("%s", select_menu);
            inGame_menu(game, select_menu);
        }else{
            sprintf(select_menu, "%d", (rand()%game->cols +1));
            inGame_menu(game, select_menu);
        }
        scan_game(*game);
    }
    GameOver(game);
}

int level_medium(struct tool *game)
{
    srand(time(NULL));
    char select_menu[10];

    scan_game(*game);
     while(game->total_moves < (game->rows*game->cols))
    {
        if(game->total_moves%2 == 0){
           /* scanf("%s", select_menu);
            inGame_menu(game, select_menu);
        }else{
            sprintf(select_menu, "%d", );
            inGame_menu(game, select_menu);
        }*/
        scan_game(*game);
    }
    GameOver(game);

}
}


int level_hard(struct tool *game)
{

}

int level_supeHard(struct tool *game)
{

}


void GameOver(struct tool * game)
{
    printf(YELLOW "GAME OVER\n");
    if(game->first->score == game->second->score){
        printf("THERE IS NO WINNER\n");
        return 0;
    }
    player *winner;
    if(game->first->score > game->second->score)
        winner = game->first;
    else
        winner = game->second;
    switch(game->mode)
    {
        case 1 :
            if(winner == game->first){
                printf("YOU ARE THE WINNER !!\nPLEASE, ENTER YOUR NAME..\n");
                scanf("%s", &winner->name);
                END_sortandstorge(winner);
                break;
            }
            printf("YOU LOSE THE GAME..\n");
            break;
        case 2 :
        printf(CYAN "%s PLAYER IS THE WINNER !!\n please Enter your name, %s PLAYER..\n" RESET, winner->name, winner->name);
        scanf("%s", &winner->name);
        END_sortandstorge(winner);
        break;
    }
}
