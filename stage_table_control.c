#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
#include "stage_table_definitions.h" 
#include "stage_table_control.h" 


/* 
 * Initialize the stage table context. 
 */
void 
initialize_context(stage_table_context_t* context, stage_table_t* stage_table) 
{
    context->status         = STAGE_SUCCESS;
    context->error_message  = "N/A"; 
    context->current_stage  = &(stage_table->stages[0]); 
    context->recovery_mode  = false; 

}


/*
 * Execute the entire stage table. 
 *
 * Function will iterate through each stage and execute its function. 
 * If a stage fails, enter the recovery procedure
 *
 * Returns: 
 *  - STAGE_TABLE_SUCCESS: Full table execution successful
 *  - STAGE_TABLE_FAILURE_RECOVERED: Failure with successful recovery 
 *  - STAGE_TABLE_FAILURE_UNRECOVERED: Failure with unsuccessful recovery
 */
table_status_e 
execute_stage_table(stage_table_t* stage_table,
                    stage_table_context_t* context)
{
    // Execution loop 
    uint8_t stage_index;
    stage_execution_status_e stage_status; 
    for (stage_index = 0; stage_index < stage_table->number_of_stages; stage_index++) {
        // Execute the stage
        stage_status = execute_stage(context->current_stage, context);

        // Check status
        if (stage_status) {
            // Print the error
            printf("\n== Failure:\n"
                   "==   Stage: %s\n"
                   "==   Error: %d - %s\n\n", 
                    context->current_stage->name, 
                    context->status, 
                    context->error_message);

            // Begin the recovery procedure 
            recovery_status_e recovery_status = recovery_procedure(stage_table, context);  

            // Check if recovery was successful
            if (recovery_status == RECOVERY_FAILURE) {
                printf("\n== Recovery Unsuccessful:\n"
                       "==   Stage: %s\n"
                       "==   Error: %d - %s\n\n",
                        context->current_stage->name,
                        context->status,
                        context->error_message); 

                free_context(context); 
                return STAGE_TABLE_FAILURE_UNRECOVERED; 
            }
            
            free_context(context);
            return STAGE_TABLE_FAILURE_RECOVERED; 
        }

        // Move on to the next stage
        context->current_stage++; 
    }

    free_context(context);
    return STAGE_TABLE_SUCCESS;
}


/*
 * Execute a single stage. 
 *
 * Each stage is handed the context object to be updated.
 *
 * Returns: 
 *   - STAGE_EXEC_SUCCESS: Success
 *   - STAGE_EXEC_FAILURE: Failure
 */
stage_execution_status_e
execute_stage(stage_t* stage, 
              stage_table_context_t* context)
{
    stage_execution_status_e stage_exec_status = stage->function(context); 
    return stage_exec_status;
}


/* 
 * Recovery procedure. 
 *
 * Loop backwards from the current stage and execture each stage's recovery function. 
 * This should undo the entire process. 
 *
 * Returns: 
 *  - RECOVERY_SUCCESS: Success
 *  - RECOVERY_FAILURE: Failure
 */ 
recovery_status_e 
recovery_procedure(stage_table_t* stage_table, 
                   stage_table_context_t* context) 
{
    printf("Executing recovery procedure...\n"); 
    context->recovery_mode = true; 

    bool complete = false; 
    stage_execution_status_e stage_status;
    while (!complete) {
        if (context->current_stage->recovery_function == NULL) { 
            continue; 
        }

        stage_status = context->current_stage->recovery_function(context);  

        if (stage_status) {
            printf("== Recovery Failure:\n"
                   "==   Stage: %s\n"
                   "==   Error: %d - %s\n", 
                    context->current_stage->name, 
                    context->status, 
                    context->error_message == NULL ? "N/A" : context->error_message);           
            
            return RECOVERY_FAILURE;
        }

        if (context->current_stage == stage_table->stages) { 
            printf("Recovery procedure complete.\n"); 
            complete = true; 
        }

        context->current_stage--; 
    }

    return RECOVERY_SUCCESS; 
}


/*
 * Free any allocated memory in the context structure
 */
void
free_context(stage_table_context_t* context)
{
    free(context->error_message); 
    return;
}
