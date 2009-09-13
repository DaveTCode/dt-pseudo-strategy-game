#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_screen                                                 */
/*                                                                            */
/* Purpose: Create a new screen object.                                       */
/*                                                                            */
/* Returns: A pointer to the screen object created.                           */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory using dt_malloc. Do not preset values.          */
/******************************************************************************/
DT_SCREEN *dt_create_screen()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_SCREEN *temp_screen;

  /****************************************************************************/
  /* Allocate memory for the screen object.                                   */
  /****************************************************************************/
  temp_screen = (DT_SCREEN *) dt_malloc(sizeof(DT_SCREEN));

  /****************************************************************************/
  /* Set up the viewport to be a null surface.                                */
  /****************************************************************************/
  temp_screen->viewport = NULL;

  /****************************************************************************/
  /* Set default parameter values.                                            */
  /****************************************************************************/
  temp_screen->pixel_start_x = 0;
  temp_screen->pixel_start_y = 0;
  temp_screen->start_x = 0;
  temp_screen->start_y = 0;

  return(temp_screen);
}

/******************************************************************************/
/* Function: dt_destroy_screen                                                */
/*                                                                            */
/* Purpose: Free the memory allocated to a screen object.                     */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     screen - The object to be freed.                        */
/*                                                                            */
/* Operation: Free memory.                                                    */
/******************************************************************************/
void dt_destroy_screen(DT_SCREEN *screen)
{
  /****************************************************************************/
  /* If the screen has a viewport attached then free it.                      */
  /****************************************************************************/
  if (NULL != screen->viewport)
  {
    SDL_FreeSurface(screen->viewport);
  }

  dt_free(screen);

  return;
}

/******************************************************************************/
/* Function: dt_init_window_system                                            */
/*                                                                            */
/* Purpose: Set up the SDL screen object.                                     */
/*                                                                            */
/* Returns: DT_INIT_OK if all proceeded without problems.                     */
/*          DT_INIT_SDL_FAIL if the Video subsystem could not be started.     */
/*          DT_INIT_SCREEN_FAIL if the screen could not be init'd.            */
/*                                                                            */
/* Parameters: IN     screen - The screen object containing resolution info.  */
/*             OUT    sdl_screen - This will contain a pointer to the new     */
/*                                 SDL_Surface created for the screen.        */
/*                                                                            */
/* Operation: Initialise the SDL video subsystem and then set the video mode  */
/*            for that screen using the resolution parameters inputted.       */
/******************************************************************************/
int dt_init_window_system(DT_SCREEN *screen)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_code = DT_INIT_OK;
  int result;

  /****************************************************************************/
  /* Initialise SDL video subsystem.                                          */
  /****************************************************************************/
  result = SDL_Init(SDL_INIT_VIDEO);
  if (-1 == result)
  {
    ret_code = DT_INIT_SDL_FAIL;
    goto EXIT_LABEL;
  }

  /****************************************************************************/
  /* Set the screen parameters.                                               */
  /****************************************************************************/
  screen->bpp = DT_BPP;
  screen->start_x = 0;
  screen->start_y = 0;
  screen->height = DT_SCREEN_HEIGHT;
  screen->width = DT_SCREEN_WIDTH;

  /****************************************************************************/
  /* Set up the screen to use hardware rendering and a double frame buffer.   */
  /****************************************************************************/
  screen->viewport = (SDL_Surface *) SDL_SetVideoMode(DT_SCREEN_WIDTH,
                                                      DT_SCREEN_HEIGHT,
                                                      DT_BPP,
                                                      DT_SDL_SCREEN_FLAGS);
  if (NULL == screen->viewport)
  {
    SDL_Quit();
    ret_code = DT_INIT_SCREEN_FAIL;
    goto EXIT_LABEL;
  }

EXIT_LABEL:

  return(ret_code);
}

/******************************************************************************/
/* Function: dt_update_units_on_screen                                        */
/*                                                                            */
/* Purpose: Takes a list of units that have moved and moves them on the       */
/*          screen.                                                           */
/*                                                                            */
/* Returns: DT_UPDATE_SCREEN_OK if screen updates ok.                         */
/*          DT_FLIP_SCREEN_FAILED if the screen couldn't be flipped.          */
/*                                                                            */
/* Parameters: IN     screen - The screen object which is to be updated.      */
/*             IN     active_unit_list - An unsorted linked list of the units */
/*                                       which have moved.                    */
/*                                                                            */
/* Operation: Loop through the units in the active unit list.                 */
/*            For each unit, erase its old position and put it on its new     */
/*            position.                                                       */
/******************************************************************************/
int dt_update_units_on_screen(DT_SCREEN *screen,
                              DT_UNIT_LIST_NS *active_unit_list,
                              DT_GRID *grid)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT *curr_unit;
  SDL_Rect copy_location;
  bool ret_val;
  int ret_code = DT_UPDATE_SCREEN_OK;
  DT_GRID_ELEMENT *element;

  /****************************************************************************/
  /* Set the loop variable to the first unit in the active unit list.         */
  /****************************************************************************/
  curr_unit = (DT_UNIT *) active_unit_list->first->unit;

  /****************************************************************************/
  /* Scan through all the active units moving them to their new positions.    */
  /****************************************************************************/
  while(NULL != curr_unit)
  {
    /**************************************************************************/
    /* Convert the grid coordinates of the units old position to screen x, y  */
    /* coordinates and place the result into an SDL_Rect structure for blit.  */
    /**************************************************************************/
    dt_convert_grid_to_screen_pos(grid,
                                  screen,
                                  curr_unit->curr_pos_x,
                                  curr_unit->curr_pos_y,
                                  (int *) &(copy_location.x),
                                  (int *) &(copy_location.y));

    /**************************************************************************/
    /* Erase the old unit position with the map tile that was there before.   */
    /**************************************************************************/
    element = grid->map_grid[curr_unit->curr_pos_x][curr_unit->curr_pos_y];
    SDL_BlitSurface(element->tile->graphic->sprite,
                    NULL,
                    screen->viewport,
                    &copy_location);

    /**************************************************************************/
    /* Convert the new grid position into screen coordinates and place into a */
    /* SDL_Rect for blit.                                                     */
    /**************************************************************************/
    dt_convert_grid_to_screen_pos(grid,
                                  screen,
                                  curr_unit->new_pos_x,
                                  curr_unit->new_pos_y,
                                  (int *) &(copy_location.x),
                                  (int *) &(copy_location.y));

    /**************************************************************************/
    /* Blit the unit onto the new position.                                   */
    /**************************************************************************/
    SDL_BlitSurface(curr_unit->graphic->entity_graphic->sprite,
                    NULL,
                    screen->viewport,
                    &copy_location);

    /**************************************************************************/
    /* Set the units current position to the one it has been moved to on the  */
    /* screen.                                                                */
    /**************************************************************************/
    dt_update_unit_position(curr_unit);
  }

  /****************************************************************************/
  /* Flip the screen so that the new buffer is visible.                       */
  /****************************************************************************/
  ret_val = SDL_Flip(screen->viewport);
  if (false == ret_val)
  {
    ret_code = DT_FLIP_SCREEN_FAILED;
    goto EXIT_LABEL;
  }

EXIT_LABEL:

  return(ret_code);
}

/******************************************************************************/
/* Function: dt_redraw_screen                                                 */
/*                                                                            */
/* Purpose: Redraw the entire screen.                                         */
/*                                                                            */
/* Returns: DT_UPDATE_SCREEN_OK if screen draw succeeded.                     */
/*          DT_FLIP_SCREEN_FAILED if screen flip failed.                      */
/*                                                                            */
/* Parameters: IN     grid - The underlying grid for the screen.              */
/*             IN     screen - The screen object that is to be redrawn.       */
/*                                                                            */
/* Operation: ***ONLY USE IF ALL SCREEN NEEDS REDRAWING***                    */
/*            Redraw each tile that can be seen by the current viewport.      */
/*            Flip the screen so that the new image can be seen.              */
/******************************************************************************/
int dt_redraw_screen(DT_GRID *grid, DT_SCREEN *screen)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_code = DT_UPDATE_SCREEN_OK;
  int ret_val;
  int row;
  int col;
  SDL_Rect curr_loc;
  int start_x, end_x;
  int start_y, end_y;

  /****************************************************************************/
  /* Set the starting and finishing points of the grid loop to be such that   */
  /* if the grid is smaller than the screen we only consider those tiles      */
  /* which are valid grid tiles.                                              */
  /****************************************************************************/
  start_y = MIN(0, screen->start_y);
  end_y = MIN(screen->start_y + screen->y_tiles_per_screen, grid->num_tiles_y);
  start_x = MIN(0, screen->start_x);
  end_x = MIN(screen->start_x + screen->x_tiles_per_screen, grid->num_tiles_x);

  /****************************************************************************/
  /* Loop through all visible portions of the grid applying tiles in turn.    */
  /* Non-optimised.                                                           */
  /****************************************************************************/
  for (row = start_y; row < end_y; row++)
  {
    for (col = start_x; col < end_y; col++)
    {
      /************************************************************************/
      /* Convert the current grid coordinates to screen coordinates. This     */
      /* could be done as part of the loop variable stuff to optimise...      */
      /************************************************************************/
      ret_val = dt_convert_grid_to_screen_pos(grid,
                                              screen,
                                              col,
                                              row,
                                              (int *) &(curr_loc.x),
                                              (int *) &(curr_loc.y));

      /************************************************************************/
      /* Apply the background to the screen first.                            */
      /************************************************************************/
      if (NULL != grid->map_grid[col][row]->tile)
      {
        SDL_BlitSurface(grid->map_grid[col][row]->tile->graphic->sprite,
                        NULL,
                        screen->viewport,
                        &curr_loc);
      }

      /************************************************************************/
      /* If there is a unit at the current map square then apply that on top  */
      /* of the backgruond tile.                                              */
      /************************************************************************/
      if (NULL != grid->map_grid[col][row]->unit)
      {
        SDL_BlitSurface(grid->map_grid[col][row]->unit->graphic->
                                                         entity_graphic->sprite,
                        NULL,
                        screen->viewport,
                        &curr_loc);
      }

    }
  }

  /****************************************************************************/
  /* Flip the screen buffers so that the refreshed screen is visible.         */
  /****************************************************************************/
  ret_val = SDL_Flip(screen->viewport);
  if (ret_val == -1)
  {
    ret_code = DT_FLIP_SCREEN_FAILED;
    goto EXIT_LABEL;
  }

EXIT_LABEL:

  return(ret_code);
}
