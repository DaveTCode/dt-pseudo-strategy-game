/******************************************************************************/
/* GLOBAL - master_unit_list:                                                 */
/*                                                                            */
/* A master list of all units allocated in game. This has global scope so     */
/* that error handling routines can cleanup on code failure.                  */
/******************************************************************************/
struct dt_unit_list_ns *master_unit_list;
