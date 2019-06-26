#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
#include "stage_table_definitions.h" 
#include "stage_functions.h" 

/* 
 * All the stage functions. 
 *
 * These will be used in stage_table.c 
 */

stage_execution_status_e  
stage_1(stage_table_context_t* context)
{
    printf("Stage 1\n");
    return STAGE_EXEC_SUCCESS;  
}

stage_execution_status_e
stage_1_recovery(stage_table_context_t* context) 
{
    printf("Stage 1 recovered.\n"); 
    return STAGE_EXEC_SUCCESS;
}

stage_execution_status_e  
stage_2(stage_table_context_t* context)
{
    printf("Stage 2\n");
    return STAGE_EXEC_SUCCESS;  
}

stage_execution_status_e
stage_2_recovery(stage_table_context_t* context) 
{
    printf("Stage 2 recovered.\n"); 
    return STAGE_EXEC_SUCCESS;
}

stage_execution_status_e  
stage_3(stage_table_context_t* context)
{
    printf("Stage 3\n");

    // Simulated Failure
    // Currently not working
    context->status = STAGE_FAILURE; 
    char error_message[] = "Something went wrong in stage 3"; 
    context->error_message = strdup(error_message);
    return STAGE_EXEC_FAILURE;

    return STAGE_EXEC_SUCCESS;  
}

stage_execution_status_e
stage_3_recovery(stage_table_context_t* context) 
{
    printf("Stage 3 recovered.\n"); 
    return STAGE_EXEC_SUCCESS;
}
