#ifndef STAGE_TABLE_CONTROL_HEADER
#define STAGE_TABLE_CONTROL_HEADER

#include <stdint.h> 
#include "stage_table_definitions.h"

void                     initialize_context(stage_table_context_t* context, stage_table_t* stage_table); 
table_status_e           execute_stage_table(stage_table_t* stage_table, stage_table_context_t* context); 
stage_execution_status_e execute_stage(stage_t* stage, stage_table_context_t* context); 
recovery_status_e        recovery_procedure(stage_table_t* stage_table, stage_table_context_t* context);
void                     free_context(stage_table_context_t* context);

#endif 
