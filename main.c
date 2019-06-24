#include <stdio.h> 
#include <stdint.h> 
#include "stage_table_definitions.h" 
#include "stage_table_control.h" 
#include "stage_functions.h" 

/* Define the stage table */ 
static stage_t test_table[] = {
    { "stage 1", stage_1, NULL },
    { "stage 2", stage_2, NULL }, 
    { "stage 3", stage_3, NULL },
};

int 
main(int    argc, 
     char   *argv[])
{ 
    // Create a stage table 
    stage_table_t stage_table; 
    stage_table.stages = test_table; 

    // Create a stage table context 
    stage_table_context_t context; 
    initialize_context(&context, &stage_table); 
    stage_table.context = &context; 

    // Compute table size
    stage_table.number_of_stages = sizeof(test_table) / sizeof(stage_t);

    // Begin executing the table
    table_status_e table_status = execute_stage_table(&stage_table, &context); 

    // Check status
    if (table_status) {
        switch (table_status) {
            case STAGE_TABLE_FAILURE_RECOVERED: 
                printf("Execution failure, system recovered.\n"); 
                return 1; 
            case STAGE_TABLE_FAILURE_UNRECOVERED: 
                printf("Execution failure, system was unable to recover.\n");
                return 1; 
            default: 
                printf("Execution failure.\n"); 
       }
    }

    return 0; 
}
