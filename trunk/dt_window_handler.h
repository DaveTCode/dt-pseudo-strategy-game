#define DT_INIT_OK 0
#define DT_INIT_SDL_FAIL 1
#define DT_INIT_SCREEN_FAIL 2

#define DT_UPDATE_SCREEN_OK 0
#define DT_FLIP_SCREEN_FAILED 1

#define DT_SCREEN_WIDTH 640
#define DT_SCREEN_HEIGHT 480
#define DT_BPP 32
#define DT_SDL_SCREEN_FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF

/******************************************************************************/
/* DT_SCREEN:                                                                 */
/*                                                                            */
/* This object holds information on the screen which will be passed to SDL    */
/* routines. It is dynamic so that the user can change resoluation etc.       */
/*                                                                            */
/* width - The width of the screen.                                           */
/* height - The height of the screen.                                         */
/* bpp - The number of bits per pixel. Should be set to 32 under normal op.   */
/* start_x - The grid x coordinate that will be the left hand side of the     */
/*           screen.                                                          */
/* start_y - The grid y coordinate that will be the top of the screen.        */
/* pixel_start_x - The pixel coordinate that will be the left of the screen.  */
/* pixel_start_y - The pixel coordinate that will be the top of the screen.   */
/* x_tiles_per_screen - The number of tiles per screen in the x direction.    */
/* y_tiles_per_screen - The number of tiles per screen in the y direction.    */
/*    The previous two variables are calculated using a grid object.          */
/******************************************************************************/
typedef struct dt_screen
{
  SDL_Surface *viewport;
  int width;
  int height;
  int bpp;
  int start_x;
  int start_y;
  int pixel_start_x;
  int pixel_start_y;
  int x_tiles_per_screen;
  int y_tiles_per_screen;
} DT_SCREEN;
