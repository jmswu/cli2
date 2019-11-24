#include "cli2.h"

/*  Cli2 library default call back function
 */
void cmd_default(char *cmd, void *arg0, void *arg1);
void cmd_default(char *cmd, void *arg0, void *arg1){
    // spin forever
    while(1);
}

void Cli_Data_init(Cli_Data *cli_data){
    cli_data->cb = cmd_default;     /* assing to the default callback function */
    cli_data->cmd = "cli2_default"; /* default command */
    cli_data->arg0 = NULL;          /* no argument 0 */
    cli_data->arg1 = NULL;          /* no argument 1 */
}

Cli_Handler Cli_Construct(Cli_Obj *cli_obj, Cli_Data *cli_list, int max_size){

    /* Initialize the data with NULL value */
    for(int i = 0; i < max_size; i++){
        cli_list[i].cmd = NULL;
        cli_list[i].cb = NULL;
        cli_list[i].arg0 = NULL;
        cli_list[i].arg1 = NULL;
    }

    cli_obj->max_size = max_size;   /* assign maximum allowed command size */
    cli_obj->cmd_list = cli_list;   /* assign external cli data to the list */
    cli_obj->index = 0;             /* pointing to the first empty location */
    return (Cli_Handler)cli_obj;
}

Cli_ReturnCode Cli_Add(Cli_Handler handle, Cli_Data *cli_data){
    int index = 0;
    int max_size = 0;
    index = handle->index;
    max_size = handle->max_size;
    if (index >= max_size){
        return CLI_FAILED;
    }
    handle->cmd_list[index].cmd = cli_data->cmd;
    handle->cmd_list[index].cb = cli_data->cb;
    handle->cmd_list[index].arg0 = cli_data->arg0;
    handle->cmd_list[index].arg1 = cli_data->arg1;
    index++;
    handle->index = index;
    return CLI_OK;
}

void Cli_print(Cli_Handler handle){
    printf("Printing a CLI object:\n");
    printf("Size: %d, index: %d\n", handle->max_size, handle->index);
    int counter = 0;
    for(int i = 0; i < handle->max_size; i++){
        if (handle->cmd_list[i].cb != NULL){
            printf("index: %d, cmd = %s\n", i, handle->cmd_list[i].cmd);
            counter++;
        }
    }
    printf("Free cli slot: %d, used slot: %d\n", 
        handle->max_size - counter,
        counter);
}
