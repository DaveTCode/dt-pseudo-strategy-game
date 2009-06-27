#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_entity_graphic                                         */
/*                                                                            */
/* Purpose: Create a new graphic object with a given sprite.                  */
/*                                                                            */
/* Returns: A pointer to the new object.                                      */
/*                                                                            */
/* Parameters: IN     filename - The filename of the new sprite.              */
/*                                                                            */
/* Operation: This function is dependent on the particular implementation of  */
/*            the graphics object that uses sprites.                          */
/*            Allocate memory required for the object and then set the sprite */
/*            to the contents of the filename.                                */
/******************************************************************************/
int dt_create_entity_graphic(char *filename, DT_ENTITY_GRAPHIC **entity_graphic)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_code;

  /****************************************************************************/
  /* Allocate the memory for the graphic object.                              */
  /****************************************************************************/
  (*entity_graphic) = (DT_ENTITY_GRAPHIC *) dt_malloc(sizeof(DT_ENTITY_GRAPHIC));

  /****************************************************************************/
  /* Load the sprite pointed to by the filename into the entity graphic       */
  /* object.                                                                  */
  /****************************************************************************/
  ret_code = dt_load_sprite_from_file(&((*entity_graphic)->sprite), filename);

  /****************************************************************************/
  /* Set the reference count to 0 as no entities yet reference this graphic.  */
  /****************************************************************************/
  (*entity_graphic)->ref_count = 0;

  return(ret_code);
}

/******************************************************************************/
/* Function: dt_destroy_entity_graphic                                        */
/*                                                                            */
/* Purpose: Free the memory allocated for a unit graphic module.              */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     unit_graphic - The unit graphic object to be freed.     */
/*                                                                            */
/* Operation: This function is reliant on the particular sprite implementation*/
/*            of the unit graphic object. It frees the sprite (if one exists) */
/*            and the frees the object itself.                                */
/******************************************************************************/
void dt_destroy_entity_graphic(DT_ENTITY_GRAPHIC *entity_graphic)
{
  /****************************************************************************/
  /* If a bitmap was loaded for this sprite then free the surface.            */
  /****************************************************************************/
  if (NULL != entity_graphic->sprite)
  {
    SDL_FreeSurface(entity_graphic->sprite);
  }

  /****************************************************************************/
  /* Free the object itself.                                                  */
  /****************************************************************************/
  free(entity_graphic);
}

/******************************************************************************/
/* Function: dt_load_sprite_from_file                                         */
/*                                                                            */
/* Purpose: Loads a bitmap into an sdl surface from a filename.               */
/*                                                                            */
/* Returns: DT_LOAD_SPRITE_OK if all proceeds with no errors.                 */
/*          DT_LOAD_SPRITE_NOT_LOADED if sprite could not be loaded.          */
/*          DT_LOAD_SPRITE_NOT_CONVERTED if sprite could not be converted to  */
/*          display format.                                                   */
/*                                                                            */
/* Parameters: IN     graphic - The surface into which the sprite is to be    */
/*                              loaded.                                       */
/*             IN     filename - The filename containing the sprite.          */
/*                                                                            */
/* Operation: Load the bitmap into a temporary surface object.                */
/*            Convert it to display format and place into the graphic.        */
/*            Free the temporary surface.                                     */
/******************************************************************************/
int dt_load_sprite_from_file(SDL_Surface **graphic,
                             char *filename)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_code = DT_LOAD_SPRITE_OK;
  SDL_Surface *loaded_surface;
  SDL_Surface *optimised_surface;

  /****************************************************************************/
  /* Attempt to load the sprite from the filename given.                      */
  /****************************************************************************/
  loaded_surface = (SDL_Surface *) IMG_Load(filename);
  if (NULL == loaded_surface)
  {
    ret_code = DT_LOAD_SPRITE_NOT_LOADED;
    goto EXIT_LABEL;
  }

  /****************************************************************************/
  /* Set the sprite to be in the same format as the display.                  */
  /****************************************************************************/
  optimised_surface = SDL_DisplayFormat(loaded_surface);
  if (NULL == optimised_surface)
  {
    ret_code = DT_LOAD_SPRITE_NOT_CONVERTED;
    goto EXIT_LABEL;
  }

  /****************************************************************************/
  /* Free the temporary surface before returning the object.                  */
  /****************************************************************************/
  SDL_FreeSurface(loaded_surface);

  /****************************************************************************/
  /* Return the optimised image.                                              */
  /****************************************************************************/
  *graphic = optimised_surface;

EXIT_LABEL:

  return(ret_code);
}
