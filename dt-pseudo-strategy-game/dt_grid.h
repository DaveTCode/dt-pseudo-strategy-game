#define DT_COORD_IN_WINDOW 0
#define DT_COORD_OUT_WINDOW 1

#define DT_COORD_ON_GRID 0
#define DT_COORD_OFF_GRID 1

#define DT_MAP_FILE_LOADED 0
#define DT_MAP_FILE_NO_INFO_LINE 1
#define DT_MAP_FILE_NOT_FOUND 2

#define DT_MAX_MAP_LINE_LEN 5000

/******************************************************************************/
/* DT_GRID_ELEMENT:                                                           */
/*                                                                            */
/* Each point on a grid is a grid element data structure. It has the          */
/* following fields.                                                          */
/*                                                                            */
/* unit - A single unit pointer referring to the unit at that grid position.  */
/* tile - A background tile referring to the background at that position.     */
/******************************************************************************/
typedef struct dt_grid_element
{
  struct dt_unit *unit;
  struct dt_background_tile *tile;
  bool traversable;
} DT_GRID_ELEMENT;

/******************************************************************************/
/* DT_GRID:                                                                   */
/*                                                                            */
/* A DT_GRID object refers to the underlying grid structure that tiles are    */
/* placed on. This object contains information about the size of those tiles. */
/*                                                                            */
/* map_grid - A two dimensional array which contains an element for each      */
/*            point on the grid. It is used to store information about what   */
/*            is at each location.                                            */
/* square_width - The width of a single tile in the grid.                     */
/* square_height - The height of a single tile in the grid.                   */
/* num_tiles_x - The number of tiles in the x direction on the grid.          */
/* num_tiles_y - The number of tiles in the y direction on the grid.          */
/******************************************************************************/
typedef struct dt_grid
{
  struct dt_grid_element ***map_grid;
  int square_width;
  int square_height;
  int num_tiles_x;
  int num_tiles_y;
} DT_GRID;
