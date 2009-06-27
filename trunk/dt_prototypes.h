/******************************************************************************/
/* prototypes for functions in dt_master_unit_list.c.                         */
/******************************************************************************/
void dt_increment_next_unit_id();
void dt_reset_next_unit_id();
long dt_get_next_unit_id();
void dt_init_master_unit_list();
struct dt_unit_list_ns *dt_retrieve_master_unit_list();

/******************************************************************************/
/* prototypes for functions in dt_mem_alloc_handler.c.                        */
/******************************************************************************/
void *dt_malloc(size_t);
void dt_free(void *);

/******************************************************************************/
/* prototypes for functions in dt_unit.c.                                     */
/******************************************************************************/
struct dt_unit *dt_create_unit(long *);
void dt_destroy_unit(struct dt_unit *);
void dt_update_unit_position(struct dt_unit *);
int dt_unit_comparator(struct dt_unit *, struct dt_unit *);
struct dt_unit_graphic *dt_create_unit_graphic();
void dt_destroy_unit_graphic(struct dt_unit_graphic *);

/******************************************************************************/
/* prototypes for functions in dt_unit_list.c.                                */
/******************************************************************************/
struct dt_unit_list_ns *dt_create_unit_list_ns();
void dt_destroy_unit_list(struct dt_unit_list_ns *, bool);
struct dt_unit_list_element *dt_create_list_element();
void dt_destroy_list_element(struct dt_unit_list_element *);
void dt_add_to_list_ns(struct dt_unit_list_ns *, struct dt_unit *);
int dt_remove_from_list_ns(struct dt_unit_list_ns *, long);

/******************************************************************************/
/* prototypes for functions in main.c                                         */
/******************************************************************************/
void cleanup();
void dt_graceful_exit(char *);
int main(int, char **);

/******************************************************************************/
/* prototypes for functions in dt_entity_graphic.c                            */
/******************************************************************************/
int dt_create_entity_graphic(char *, struct dt_entity_graphic **);
void dt_destroy_entity_graphic(struct dt_entity_graphic *);
int dt_load_sprite_from_file(SDL_Surface **, char *);

/******************************************************************************/
/* prototypes for functions in dt_window_handler.c                            */
/******************************************************************************/
struct dt_screen *dt_create_screen();
void dt_destroy_screen(struct dt_screen *);
int dt_init_window_system(struct dt_screen *);
int dt_update_units_on_screen(struct dt_screen *,
                              struct dt_unit_list_ns *,
                              struct dt_grid *);
int dt_redraw_screen(struct dt_grid *, struct dt_screen *);


/******************************************************************************/
/* prototypes for functions in dt_background_tile.c                           */
/******************************************************************************/
struct dt_background_tile *dt_create_background_tile();
void dt_destroy_background_tile(struct dt_background_tile *);
void dt_assign_entity_graphic_to_background_tile(struct dt_entity_graphic *,
                                                 struct dt_background_tile *);

/******************************************************************************/
/* prototypes for functions in dt_grid.c                                      */
/******************************************************************************/
struct dt_grid *dt_create_grid(int , int, int, int);
void dt_destroy_grid(struct dt_grid *);
struct dt_grid_element *dt_create_grid_element();
void dt_destroy_grid_element(struct dt_grid_element *);
int dt_convert_grid_to_screen_pos(struct dt_grid *,
                                  struct dt_screen *,
                                  int,
                                  int,
                                  int *,
                                  int *);
int dt_convert_screen_to_grid_pos(struct dt_grid *,
                                  struct dt_screen *,
                                  int,
                                  int,
                                  int *,
                                  int *);
struct dt_unit *dt_retrieve_unit_from_grid(struct dt_grid *, int, int);

/******************************************************************************/
/* prototypes for functions in dt_input_handler.c                             */
/******************************************************************************/
int dt_handle_mouse_click(struct dt_grid *, struct dt_screen *, SDL_Event *);
int dt_handle_key_press(struct dt_grid *, struct dt_screen *, SDL_Event *);
