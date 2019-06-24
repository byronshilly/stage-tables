#include <stdio.h> 
#include <stdint.h> 
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
stage_2(stage_table_context_t* context)
{
    printf("Stage 2\n");
    return STAGE_EXEC_SUCCESS;  
}

stage_execution_status_e  
stage_3(stage_table_context_t* context)
{
    printf("Stage 3\n");
    return STAGE_EXEC_SUCCESS;  
}
