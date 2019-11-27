/* CLI2 Library
 * Author: James Wu
 * Email : jameswu62@yahoo.co.nz
 */

#ifndef _CLI2_H
#define _CLI2_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

/* Function callback for using the CLI2 library.
 * @param char*     - parser return char pointer, for use for the next command search 
 * @param void*     - pointer to user arg0
 * @param void*     - pointer to user arg1
 */
typedef void(*cli_cb)(char*, void*, void*);


/* CLI2 library command and function callback struct
 * This struct store all the informationn regarding
 * one command and function callback
 */
typedef struct {
    const char* cmd;// pointer to commmand
    cli_cb cb;      // command callback function
    void *arg0;     // argument 0 for the callback function, this can be removed to save memory
    void *arg1;     // argument 1 for the callback function, this can be removed to save memory
}Cli_Data;

/* CLI2 object
 * This structure store all the information of one CLI2 Object
 */
typedef struct CLI_OBJ Cli_Obj;


/* CLI2 handler
 * This will be the entry point for using a cli object
 */
typedef Cli_Obj *Cli_Handler;

/* CLI2 library default function callback when there is no command match
 * @param Cli_Handler handle   - pointer to the cli handle
 */
typedef void(*cli_error_cb)(Cli_Handler handle);

struct CLI_OBJ{
    Cli_Data *cmd_list;         // pointer to the list memory location of all the command data
    uint_least8_t index;        // index of the current empty data location in the command data list
    uint_least8_t max_size;     // maximum allow cli command size
    cli_error_cb error_cb;      // call when there is no command match
};

/* CLI2 return code
 */
typedef enum {
    CLI_OK,             // thing is as expected
    CLI_FAILED,         // something bad happend
    CLI_MEMORY_ERROR    // not enough memory allocated for the data
}Cli_ReturnCode;



/* CLI2 Data initializer. Initialize the Cli_Data to default values
 * @param Cli_Data *cli_data    - pointer to the cli data
 */
void Cli_Data_init(Cli_Data *cli_data);

/* CLI2 object construction. Construct a CLI2 object
 * @param Cli_Obj *cli_obj      - pointer CLI2 object
 * @param Cli_Data *cli_data    - pointer to CLI2 data, this is the memory location 
 *                                that store all the cli data
 * @param int max_size          - The maximum commands that is allowed for the CLI 
 *                              - Object, this is size of the Cli_Data array
 * @param cli_default_cb cb     - callback when there is no command match found
 */
Cli_Handler Cli_Construct(Cli_Obj *cli_obj, 
    Cli_Data *cli_data, 
    uint_least8_t max_size, 
    cli_error_cb cb);

/* Add command data to the CLI2 object
 * @param Cli_Handler handle    - cli object handler
 * @param Cli_Data *cli_data    - pointer to the commmand data
 * @return CliReturnCode        - CLI_FAILED = no more empty space in cli2 object
 *                                CLI_OK = addition success
 */                               
Cli_ReturnCode Cli_Add(Cli_Handler handle, Cli_Data *cli_data);

void Cli_Scan(Cli_Handler handle, char *input_str);

/* Print all the information out for debugging
 * @param Cli_Handler handle    - Cli Object handle
 */
void Cli_print(Cli_Handler handle);

#ifdef	__cplusplus
}
#endif

#endif