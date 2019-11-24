#include <stdio.h>
#include "cli2.h"

void cmd_help(char *cmd, void *arg0, void *arg1);

Cli_Obj cli_obj;                // make cli object 
Cli_Data cli_data[10];          // reverse memory for all the cli data

int main(char *argv[], int argc){

    Cli_Handler cli_handler;
    cli_handler = Cli_Construct(&cli_obj, cli_data, 10);

    Cli_Data cmd1;
    Cli_Data_init(&cmd1);
    cmd1.cmd = "cmd1";
    cmd1.cb = cmd_help;

    Cli_Add(cli_handler, &cmd1);

    Cli_print(cli_handler);




    return 0;
}

void cmd_help(char *cmd, void *arg0, void *arg1){
    printf("Hello, this a help command1\n");
}