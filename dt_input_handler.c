#include "dt_include.h"

/******************************************************************************/
/* Function: dt_handle_mouse_click                                            */
/*                                                                            */
/* Purpose: Handle a mouse click by the user.                                 */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/* Parameters: IN     grid - The grid object we are going to search.          */
/*             IN     screen - The screen object on which the click is        */
/*                             registered.                                    */
/*             IN     event - The event object which contains the button      */
/*                            click.                                          */
/*                                                                            */
/* Operation: Convert the mouse coordinates on the screen into grid           */
/*            coordinates.                                                    */
/*            Retrieve any unit which is placed at the grid coordinates.      */
/******************************************************************************/
int dt_handle_mouse_click(DT_GRID *grid, DT_SCREEN *screen, SDL_Event *event)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT *unit;
  int x_pos;
  int y_pos;
  int grid_x;
  int grid_y;
  int ret_val;

  /****************************************************************************/
  /* Retrieve the position of the mouse when the button was pressed.          */
  /****************************************************************************/
  x_pos = event->button.x;
  y_pos = event->button.y;

  /****************************************************************************/
  /* Convert the button press coordinates into grid coordinates.              */
  /****************************************************************************/
  ret_val = dt_convert_screen_to_grid_pos(grid,
                                          screen,
                                          x_pos,
                                          y_pos,
                                          &grid_x,
                                          &grid_y);
  if (ret_val == DT_COORD_ON_GRID)
  {
    /**************************************************************************/
    /* Retrieve a unit from a grid position.                                  */
    /**************************************************************************/
    unit = dt_retrieve_unit_from_grid(grid, grid_x, grid_y);
  }

  return(0);
}

/******************************************************************************/
/* Function:                                                                  */
/*                                                                            */
/* Purpose:                                                                   */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/* Operation:                                                                 */
/******************************************************************************/
int dt_handle_key_press(DT_GRID *grid, DT_SCREEN *screen, SDL_Event *event)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  bool redraw_screen = false;
  int ret_val;

  /****************************************************************************/
  /* Deal with input based on what key was pressed.                           */
  /****************************************************************************/
  switch(event->key.keysym.sym)
  {
    case SDLK_LEFT:
      if (screen->start_x > 0)
      {
        (screen->start_x)--;

        redraw_screen = true;
      }

      break;

    case SDLK_RIGHT:
      if (screen->start_x <
                      grid->num_tiles_x  - (screen->width / grid->square_width))
      {
        (screen->start_x)++;

        redraw_screen = true;
      }

      break;

    case SDLK_UP:
      if (screen->start_y > 0)
      {
        (screen->start_y)--;

        redraw_screen = true;
      }

      break;

    case SDLK_DOWN:
      if (screen->start_y <
                    grid->num_tiles_y  - (screen->height / grid->square_height))
      {
        (screen->start_y)++;

        redraw_screen = true;
      }

      break;
  }

  /****************************************************************************/
  /* If the screen needs redrawing then do so now.                            */
  /****************************************************************************/
  if (redraw_screen)
  {
    ret_val = dt_redraw_screen(grid, screen);
  }

  return(0);
}
