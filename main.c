#include "dt_include.h"

int main(int argc, char **argv)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_LIST_NS *active_unit_list;
  DT_GRID *map_grid;
  DT_SCREEN *screen;
  SDL_Event event;
  int result;
  bool exit_requested = FALSE;
  long next_unit_id;

  DT_ENTITY_GRAPHIC *bg_graphic1;
  DT_ENTITY_GRAPHIC *bg_graphic2;
  int ii,jj;

  /****************************************************************************/
  /* Create the screen object.                                                */
  /****************************************************************************/
  screen = dt_create_screen();

  /****************************************************************************/
  /* Create the map grid.                                                     */
  /****************************************************************************/
  map_grid = dt_create_grid(10,10,10,10);

  /****************************************************************************/
  /* Set up the master unit list.                                             */
  /****************************************************************************/
  master_unit_list = dt_create_unit_list_ns();

  /****************************************************************************/
  /* Set up the active unit list.                                             */
  /****************************************************************************/
  active_unit_list = dt_create_unit_list_ns();

  /****************************************************************************/
  /* Initialise the window and check that it worked.                          */
  /****************************************************************************/
  result = dt_init_window_system(screen);
  if (DT_INIT_OK != result)
  {
    goto EXIT_LABEL;
  }
  screen->x_tiles_per_screen = (int) (screen->width / map_grid->square_width);
  screen->y_tiles_per_screen = (int) (screen->height / map_grid->square_height);

  //Dummy set up of background.
  result = dt_create_entity_graphic("bg_sprite1.png", &bg_graphic1);
  result = dt_create_entity_graphic("bg_sprite2.png", &bg_graphic2);
  for (ii=0;ii<10;ii++)
  {
    for (jj=0;jj<10;jj++)
    {
      map_grid->map_grid[ii][jj]->tile = dt_create_background_tile();
      if ((ii % 2 == 0 && jj % 2 == 0 ) || (ii % 2 == 1 && jj % 2 == 1))
      {
        map_grid->map_grid[ii][jj]->tile->graphic = bg_graphic1;
      }
      else
      {
        map_grid->map_grid[ii][jj]->tile->graphic = bg_graphic2;
      }
    }
  }

  /****************************************************************************/
  /* Draw the screen initially.                                               */
  /****************************************************************************/
  result = dt_redraw_screen(map_grid, screen);

  /****************************************************************************/
  /* Loop scanning the event queue until the user requests exit.              */
  /****************************************************************************/
  while(!exit_requested)
  {
    SDL_WaitEvent(&event);

    switch (event.type)
    {
      /**********************************************************************/
      /* Handle a quit command.                                             */
      /**********************************************************************/
      case SDL_QUIT:
        exit_requested = TRUE;
        break;

      /**********************************************************************/
      /* Handle a key press event.                                          */
      /**********************************************************************/
      case SDL_KEYDOWN:
        dt_handle_key_press(map_grid, screen, &event);
        break;

      /**********************************************************************/
      /* Handle a mouse click present.                                      */
      /**********************************************************************/
      case SDL_MOUSEBUTTONDOWN:
        dt_handle_mouse_click(map_grid, screen, &event);
        break;

      default:
        break;
    }
  }

EXIT_LABEL:

  SDL_Quit();
  dt_destroy_unit_list(active_unit_list, false);
  dt_destroy_unit_list(master_unit_list, true);
  dt_destroy_grid(map_grid);

  return(EXIT_SUCCESS);
}

/******************************************************************************/
/* Function: dt_graceful_exit                                                 */
/*                                                                            */
/* Purpose: On error we use this function to exit freeing memory and printing */
/*          error reports.                                                    */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     err_str - A string containing details of the error that */
/*                              caused this exit.                             */
/*                                                                            */
/* Operation: Print the error details from SDL and input variables.           */
/*            Cleanup the memory from the master_unit_list.                   */
/*            Exit the program with a failure code.                           */
/******************************************************************************/
void dt_graceful_exit(char *err_str)
{
  fprintf(stderr, "The program failed with error string:\n%s", err_str);
  fprintf(stderr, "SDL error on exit was: %s\n", SDL_GetError());

  SDL_Quit();

  if (NULL != master_unit_list)
  {
    dt_destroy_unit_list(master_unit_list, true);
  }

  exit(EXIT_FAILURE);
}
