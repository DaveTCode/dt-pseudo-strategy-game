/******************************************************************************/
/* GLOBAL - master_unit_list:                                                 */
/*                                                                            */
/* A master list of all units allocated in game. This has global scope so     */
/* that error handling routines can cleanup on code failure.                  */
/******************************************************************************/
struct dt_unsorted_list *master_unit_list;

/******************************************************************************/
/* GLOBAL - master_file_list:                                                 */
/*                                                                            */
/* A master list of all files that have been opened during normal operation   */
/* of the program. Used for cleanup on code failure and for detecting code    */
/* errors.                                                                    */
/******************************************************************************/
struct dt_unsorted_list *master_file_list;
