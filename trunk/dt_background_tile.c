#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_background_tile                                        */
/*                                                                            */
/* Purpose: Create memory for a background tile.                              */
/*                                                                            */
/* Returns: A pointer to the new memory.                                      */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Safely allocate memory using dt_malloc function.                */
/******************************************************************************/
DT_BACKGROUND_TILE *dt_create_background_tile()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_BACKGROUND_TILE *temp_tile;

  /****************************************************************************/
  /* Allocate memory for the background tile.                                 */
  /****************************************************************************/
  temp_tile = (DT_BACKGROUND_TILE *) dt_malloc(sizeof(DT_BACKGROUND_TILE));

  /****************************************************************************/
  /* Set the underlying graphic object to NULL so that we test if one exists. */
  /****************************************************************************/
  temp_tile->graphic = NULL;

  /****************************************************************************/
  /* Set the tile parameters to initial values.                               */
  /****************************************************************************/
  temp_tile->elevation = 0;
  temp_tile->water_depth = 0;
  temp_tile->label = NULL;
  temp_tile->terrain_type = DT_GROUND_TYPE_PLAIN;

  return(temp_tile);
}

/******************************************************************************/
/* Function: dt_destroy_background_tile                                       */
/*                                                                            */
/* Purpose: Free the memory associated with a background tile object.         */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     tile - The tile to be freed.                            */
/*                                                                            */
/* Operation: If there is an entity graphic object referred to by this tile   */
/*            check whether this is the last item that refers to it. If so    */
/*            then destroy the graphic and if not then reduce its ref count.  */
/*            Finally free the tile object itself.                            */
/******************************************************************************/
void dt_destroy_background_tile(DT_BACKGROUND_TILE *tile)
{
  /****************************************************************************/
  /* Lower the reference count on the graphic associated with the tile.       */
  /****************************************************************************/
  if (NULL != tile->graphic)
  {
    /**************************************************************************/
    /* If the reference count is 1 then this is the last object pointing to   */
    /* the graphic so we release the memory associated with it.               */
    /**************************************************************************/
    if (1 == tile->graphic->ref_count)
    {
      dt_destroy_entity_graphic(tile->graphic);
    }
    else
    {
      (tile->graphic->ref_count)--;
    }
  }

  /****************************************************************************/
  /* Free the tile object itself.                                             */
  /****************************************************************************/
  dt_free(tile);

  return;
}

/******************************************************************************/
/* Function: dt_assign_entity_graphic_to_background_tile                      */
/*                                                                            */
/* Purpose: Safely assign a graphic to a background tile.                     */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     graphic - The graphic to be assigned.                   */
/*             IN     tile - The tile for which the graphic will be assigned. */
/*                                                                            */
/* Operation: Assign graphic. Increment reference count on the graphic.       */
/******************************************************************************/
void dt_assign_entity_graphic_to_background_tile(DT_ENTITY_GRAPHIC *graphic,
                                                DT_BACKGROUND_TILE *tile)
{
  /****************************************************************************/
  /* Assign the graphic to the tile.                                          */
  /****************************************************************************/
  tile->graphic = graphic;

  /****************************************************************************/
  /* Increment the reference count on the graphic.                            */
  /****************************************************************************/
  graphic->ref_count++;

  return;
}
