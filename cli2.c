#include <ctype.h>
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

Cli_Handler Cli_Construct(Cli_Obj *cli_obj, Cli_Data *cli_list, uint_least8_t max_size){

    /* Initialize the data with NULL value */
    for(uint_fast8_t i = 0; i < max_size; i++){
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
    uint_fast8_t index = 0;
    uint_fast8_t max_size = 0;
    index = handle->index;

    /* make sure the maximum command entry is not reached */
    max_size = handle->max_size;
    if (index >= max_size){
        return CLI_FAILED;
    }

    /* add data to the object */
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
    for(uint_fast8_t i = 0; i < handle->index; i++){
        if (handle->cmd_list[i].cb != NULL){
            printf("index: %d, cmd = %s\n", i, handle->cmd_list[i].cmd);
        }
    }
    printf("Free cli slot: %d, used slot: %d\n", 
        handle->max_size - handle->index,
        handle->index);
}

/* parse a pattern in the buffer
 * @param char *buff            - char* buffer, char array needs to be parsed
 * @param const char *pattern   - const char* pattern, char array of pattern
 * @return                      - new pointer after the pattern if there is a match
 *                                (-1) negative one if there is not match
 */
char* Cli_parse(char* buffer, const char* pattern);

char* Cli_parse(char* buffer, const char* pattern)
{
    char p;  // store one char in pattern
    char b;  // store one char in buffer
    
    // make sure its a valid pointer
    if(buffer == 0)
        return 0;
    
    // skip all space
    while(isspace(*buffer))
        ++buffer;
    
    while(1)
    {
        // get one char from the pattern, then set the pointer to next 
        // char in pattern. 
        p = *pattern++;

        // check if it's end of the pattern, return new buffer pointer 
        // if its the end of pattern
        if(p == 0){
            // check the next char in the buffer is space, or its end of string
            // or, may result in a fake mis-match.
            // eg buffer = "hello", pattern = "he", this will come back as positive
            if (isspace(*buffer) || (*buffer == 0))
                return buffer;
        }

        // convert to lower case for comparison, 
        b = tolower(*buffer++);

        // exit loop if the end of the buffer is reached, 
        // or the there is a mis-match in the data
        // continue to the next one if they are match, 
        // and not the end of the buffer
        if(b == 0 || b != p)
            break;
    }
    return 0;
}

void Cli_Scan(Cli_Handler handle, char *input_str){
    char *ptr;
    for(uint_fast8_t i = 0; i < handle->index; i++){
        ptr = Cli_parse(input_str, handle->cmd_list[i].cmd);;
        if (ptr){
            handle->cmd_list[i].cb(ptr, 
                handle->cmd_list[i].arg0,
                handle->cmd_list[i].arg1);
            return;
        }
    }
}