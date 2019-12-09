/* CLI2 Library
 * Author: James Wu
 * Email : jameswu62@yahoo.co.nz
 */

#include <stdio.h>
#include <stdlib.h>
#include "cli2.h"

/* comment this out for static construction example */
#define CLI2_DYNAMIC_CREATION_EXAMPLE

void cmd_help(char *cmd, void *arg0, void *arg1);   /* command help callback */
void cmd_cmd1(char *cmd, void *arg0, void *arg1);   /* command1 callback */
void cmd_cmd2(char *cmd, void *arg0, void *arg1);   /* command2 callback */
void cmd_cmd3(char *cmd, void *arg0, void *arg1);   /* command3 callback */
void cmd_error(Cli_Handler handle);                 /* command error callback */


#ifndef CLI2_DYNAMIC_CREATION_EXAMPLE

Cli_Obj cli_obj;                // make cli object 
Cli_Data cli_data[10];          // reverse memory for up to 10 cli

#endif



int main(char *argv[], int argc){

#ifdef CLI2_DYNAMIC_CREATION_EXAMPLE

    printf("Showing dynamic creation example.\n");

    /* Create a cli object that can support up to 10 CLI */
    Cli_Handler cli_handler = Cli_Create_Object(10, cmd_error);

#else

    printf("Showing static construction example.\n");

    /* Construct a cli object */
    Cli_Handler cli_handler;
    cli_handler = Cli_Construct(&cli_obj, 
        cli_data, 
        sizeof(cli_data)/sizeof(cli_data[0]),
        cmd_error);

#endif

    /* Assemble command and function */
    Cli_Data cli_cmd_help;
    Cli_Data cli_cmd1;
    Cli_Data cli_cmd2;
    Cli_Data cli_cmd3;

    Cli_Data_init(&cli_cmd_help);
    Cli_Data_init(&cli_cmd1);
    Cli_Data_init(&cli_cmd2);
    Cli_Data_init(&cli_cmd3);

    int arg_help = 100;
    int arg1 = 1;
    int arg2 = 2;
    int arg3 = 3;

    cli_cmd_help.cmd = "help";
    cli_cmd_help.cb = cmd_help;
    cli_cmd_help.arg0 = &arg_help;

    cli_cmd1.cmd = "cmd1";
    cli_cmd1.cb = cmd_cmd1;
    cli_cmd1.arg0 = &arg1;

    cli_cmd2.cmd = "cmd2";
    cli_cmd2.cb = cmd_cmd2;
    cli_cmd2.arg0 = &arg2;

    cli_cmd3.cmd = "cmd3";
    cli_cmd3.cb = cmd_cmd3;
    cli_cmd3.arg0 = &arg3;

    /* Add command data to cli object */
    Cli_Add(cli_handler, &cli_cmd_help);
    Cli_Add(cli_handler, &cli_cmd1);
    Cli_Add(cli_handler, &cli_cmd2);
    Cli_Add(cli_handler, &cli_cmd3);

    char buffer[256];           /* tmp buffer for input string */
    printf("cmd:>");            /* command prompt */
    fgets(buffer, 256, stdin);  /* get user input */

    Cli_Scan(cli_handler, buffer);  /* process user input */


#ifdef CLI2_DYNAMIC_CREATION_EXAMPLE

    /* free memory */
    Cli_Free_Object(cli_handler);

#endif

    return 0;
}

void cmd_help(char *cmd, void *arg0, void *arg1){
    int *data = (int *)arg0;
    printf("Hello, this a help command, arg0=%d\n", *data);
}

void cmd_cmd1(char *cmd, void *arg0, void *arg1){
    int *data = (int *)arg0;
    printf("Hello, this a cmd1, arg0=%d\n", *data);
}

void cmd_cmd2(char *cmd, void *arg0, void *arg1){
    int *data = (int *)arg0;
    printf("Hello, this a cmd2, arg0=%d\n", *data);
}

void cmd_cmd3(char *cmd, void *arg0, void *arg1){
    int *data = (int *)arg0;
    printf("Hello, this a cmd3, arg0=%d\n", *data);
}

void cmd_error(Cli_Handler handle){
    printf("Command error\n");
    printf("try:\n");
    for(int i = 0; i < handle->index; i++){
        printf("%s\n", handle->cmd_list[i].cmd);
    }
}