#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_grid                                                   */
/*                                                                            */
/* Purpose: Create a new grid object.                                         */
/*                                                                            */
/* Returns: A pointer to the new grid object.                                 */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory for the grid object.                            */
/******************************************************************************/
DT_GRID *dt_create_grid(int square_width,
                        int square_height,
                        int num_tiles_x,
                        int num_tiles_y)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_GRID *temp_grid;
  int row;
  int col;

  /****************************************************************************/
  /* Allocate memory for the temporary grid object.                           */
  /****************************************************************************/
  temp_grid = dt_malloc(sizeof(DT_GRID));

  /****************************************************************************/
  /* Allocate the necessary memory for the grid itself.                       */
  /****************************************************************************/
  temp_grid->map_grid = (DT_GRID_ELEMENT ***)
                            dt_malloc(sizeof(DT_GRID_ELEMENT **) * num_tiles_y);
  for (row = 0; row < num_tiles_y; row++)
  {
    temp_grid->map_grid[row] = (DT_GRID_ELEMENT **)
                             dt_malloc(sizeof(DT_GRID_ELEMENT *) * num_tiles_x);
    for (col = 0; col < num_tiles_x; col++)
    {
      temp_grid->map_grid[row][col] = dt_create_grid_element();
    }
  }

  /****************************************************************************/
  /* Set the grid parameters.                                                 */
  /****************************************************************************/
  temp_grid->square_width = square_width;
  temp_grid->square_height = square_height;
  temp_grid->num_tiles_x = num_tiles_x;
  temp_grid->num_tiles_y = num_tiles_y;

  return(temp_grid);
}

/******************************************************************************/
/* Function: dt_destroy_grid                                                  */
/*                                                                            */
/* Purpose: Free the memory allocated for a new grid object.                  */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     grid - The grid to be freed.                            */
/*                                                                            */
/* Operation: Release the memory used in the underlying grid and then that    */
/*            used in the placeholder object itself.                          */
/******************************************************************************/
void dt_destroy_grid(DT_GRID *grid)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ii;

  /****************************************************************************/
  /* Free up each row and column of the map grid.                             */
  /****************************************************************************/
  for (ii = 0; ii < grid->num_tiles_x; ii++)
  {
    dt_free(grid->map_grid[ii]);
  }
  dt_free(grid->map_grid);

  /****************************************************************************/
  /* Free the grid object itself.                                             */
  /****************************************************************************/
  dt_free(grid);
}

/******************************************************************************/
/* Function: dt_create_grid_element                                           */
/*                                                                            */
/* Purpose: Allocate memory for a grid element.                               */
/*                                                                            */
/* Returns: A pointer to the allocated memory.                                */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory for the grid element.                           */
/*            Set the tile and unit pointers to NULL.                         */
/******************************************************************************/
DT_GRID_ELEMENT *dt_create_grid_element()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_GRID_ELEMENT *temp_grid_element;

  /****************************************************************************/
  /* Allocate memory for the grid element.                                    */
  /****************************************************************************/
  temp_grid_element = (DT_GRID_ELEMENT *) dt_malloc(sizeof(DT_GRID_ELEMENT));

  /****************************************************************************/
  /* Set the unit and tile pointers to NULL so that they can be tested.       */
  /****************************************************************************/
  temp_grid_element->unit = NULL;
  temp_grid_element->tile = NULL;

  return(temp_grid_element);
}

/******************************************************************************/
/* Function: dt_destroy_grid_element                                          */
/*                                                                            */
/* Purpose: Free the memory for a grid element.                               */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     grid_element -                                          */
/*                                                                            */
/* Operation: Free the grid element.                                          */
/******************************************************************************/
void dt_destroy_grid_element(DT_GRID_ELEMENT *grid_element)
{
  /****************************************************************************/
  /* Free the memory allocate for the grid element.                           */
  /****************************************************************************/
  dt_free(grid_element);

  return;
}

/******************************************************************************/
/* Function: dt_convert_grid_to_screen_pos                                    */
/*                                                                            */
/* Purpose: Change grid coordinates to screen coordinates.                    */
/*                                                                            */
/* Returns: DT_COORD_IN_WINDOW if the coordinates lie in the window.          */
/*          DT_COORD_OUT_WINDOW if the coordinates would not appear on the    */
/*          screen.                                                           */
/*                                                                            */
/* Parameters: IN     grid - The grid object on which the transform happens.  */
/*             IN     screen - The screen object with details on the size of  */
/*                             screen etc.                                    */
/*             IN     grid_x - The x coordinate in grid space.                */
/*             IN     grid_y - The y coordinate in grid space.                */
/*             OUT    screen_x - The converted screen x coordinate.           */
/*             OUT    screen_y - The converted screen y coordinate.           */
/*                                                                            */
/* Operation: Objects at point x,y in the grid take up n,m pixels on the      */
/*            screen where n = grid square width * width of object and m =    */
/*            grid square height * height of object.                          */
/*            For the purposes of this though we are converting a single pair */
/*            of coordinates and these correlate to:                          */
/*            screen_x = grid_x * grid_square_width.                          */
/*            screen_y = grid_y * grid_square_height.                         */
/*            Although these are adjusted using the start offset of the       */
/*            viewport.                                                       */
/******************************************************************************/
int dt_convert_grid_to_screen_pos(DT_GRID *grid,
                                  DT_SCREEN *screen,
                                  int grid_x,
                                  int grid_y,
                                  int *screen_x,
                                  int *screen_y)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_val = DT_COORD_IN_WINDOW;

  /****************************************************************************/
  /* Set the screen x and y coordinates as detailed above.                    */
  /****************************************************************************/
  (*screen_x) = (grid_x - screen->start_x) * grid->square_width;
  (*screen_y) = (grid_y - screen->start_y) * grid->square_height;

  /****************************************************************************/
  /* If the screen coordinates do not fit in the screen then report this to   */
  /* the calling function.                                                    */
  /****************************************************************************/
  if ((screen->width < (*screen_x)) || (0 > (*screen_x)) ||
      (screen->height < (*screen_x)) || (0 > (*screen_y)))
  {
    ret_val = DT_COORD_OUT_WINDOW;
  }

  return(ret_val);
}

/******************************************************************************/
/* Function: dt_convert_screen_to_grid_pos                                    */
/*                                                                            */
/* Purpose: Convert screen coordinates to a position on the grid.             */
/*                                                                            */
/* Returns: DT_COORD_ON_GRID if the coordinates correspond to a valid pos.    */
/*          DT_COORD_OFF_GRID if the coordinates are outside the grid.        */
/*                                                                            */
/* Parameters: IN     grid - The grid object on which the transform happens.  */
/*             IN     screen - The screen object with details on the size of  */
/*                             screen etc.                                    */
/*             IN     screen_x - The x coordinate on the screen.              */
/*             IN     screen_y - The y coordinate on the screen.              */
/*             OUT    grid_x - The converted grid x coordinate.               */
/*             OUT    grid_y - The converted grid y coordinate.               */
/*                                                                            */
/* Operation: A screen coordinate may be anywhere in the box of a grid tile.  */
/*            To convert back to a grid coordinate we perform an integer div  */
/*            of the inputted screen coordinate by the width/height of the    */
/*            grid squares.                                                   */
/*            Make sure that we adjust the grid values based on the position  */
/*            of the screen viewport.                                         */
/******************************************************************************/
int dt_convert_screen_to_grid_pos(DT_GRID *grid,
                                  DT_SCREEN *screen,
                                  int screen_x,
                                  int screen_y,
                                  int *grid_x,
                                  int *grid_y)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_val = DT_COORD_ON_GRID;

  /****************************************************************************/
  /* Convert to grid coordinates as detailed above.                           */
  /****************************************************************************/
  (*grid_x) = (int) (screen_x / grid->square_width) + screen->start_x;
  (*grid_y) = (int) (screen_y / grid->square_height) + screen->start_y;

  /****************************************************************************/
  /* Check that this lies in the grid and if not the report to calling func.  */
  /****************************************************************************/
  if ((grid->num_tiles_x < (*grid_x)) || (0 > (*grid_x)) ||
      (grid->num_tiles_y < (*grid_y)) || (0 > (*grid_y)))
  {
    ret_val = DT_COORD_OFF_GRID;
  }

  return(ret_val);
}

/******************************************************************************/
/* Function: dt_retrieve_unit_from_grid                                       */
/*                                                                            */
/* Purpose: Find a unit at a grid location.                                   */
/*                                                                            */
/* Returns: NULL if there was no unit at the position or a pointer to a unit  */
/*          if there was a unit there.                                        */
/*                                                                            */
/* Parameters: IN     grid - The grid where we search for the unit.           */
/*             IN     grid_x - The x coordinate on the grid.                  */
/*             IN     grid_y - The y coordinate on the grid.                  */
/*                                                                            */
/* Operation: Retrieve the unit from the map coordinates.                     */
/******************************************************************************/
DT_UNIT *dt_retrieve_unit_from_grid(DT_GRID *grid, int grid_x, int grid_y)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT *temp_unit;

  /****************************************************************************/
  /* Retrieve the unit from the map coordinates.                              */
  /****************************************************************************/
  temp_unit = grid->map_grid[grid_x][grid_y]->unit;

  return(temp_unit);
}
