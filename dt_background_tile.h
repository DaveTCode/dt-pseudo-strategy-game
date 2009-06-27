/******************************************************************************/
/* Group: DT_GROUND_TYPES                                                     */
/*                                                                            */
/* A list of all possible ground types for background tiles. These are used   */
/* in the path finding algorithm. DAT - Where will the solution to expense(Ground_type, unit_type) be? */
/******************************************************************************/
#define DT_GROUND_TYPE_PLAIN    0x0000
#define DT_GROUND_TYPE_SWAMP    0x0001
#define DT_GROUND_TYPE_MOUNTAIN 0x0002
#define DT_GROUND_TYPE_RIVER    0x0003

/******************************************************************************/
/* DT_BACKGROUND_TILE:                                                        */
/*                                                                            */
/* A background tile object which is a holder for the graphic at a map point. */
/*                                                                            */
/* graphic - A graphic object that contains the sprite for this tile.         */
/*           May be shared with multiple objects.                             */
/* label - A string that is displayed when information is shown about the     */
/*         tile.                                                              */
/* ground_type - The type of ground that this tile represents.                */
/*               One of DT_GROUND_TYPES.                                      */
/* elevation - The height above sea level (this is a signed integer).         */
/* water_depth - The depth of water across the tile. Set to 0 for non-watery  */
/*               tiles.                                                       */
/******************************************************************************/
typedef struct dt_background_tile
{
  DT_ENTITY_GRAPHIC *graphic;
  char *label;
  int terrain_type;
  int elevation;
  int water_depth;
  int movement_modifier;
} DT_BACKGROUND_TILE;
