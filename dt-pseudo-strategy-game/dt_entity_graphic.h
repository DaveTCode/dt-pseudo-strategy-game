#define DT_LOAD_SPRITE_OK 0
#define DT_LOAD_SPRITE_NOT_LOADED 1
#define DT_LOAD_SPRITE_NOT_CONVERTED 2

/******************************************************************************/
/* DT_ENTITY_GRAPHIC:                                                         */
/*                                                                            */
/* A placeholder structure that is used to hold a graphic for any entity in   */
/* game. This includes (but is not limited to) units, backgrounds and weather.*/
/*                                                                            */
/* sprite - The SDL_Surface cotnaining the sprite itself.                     */
/* ref_count - The number of objects that reference this graphic. Used to     */
/*             determine when a graphic can be freed.                         */
/******************************************************************************/
typedef struct dt_entity_graphic
{
  SDL_Surface *sprite;
  int ref_count;
} DT_ENTITY_GRAPHIC;
