#ifndef STAGE_FUNCTIONS_HEADER
#define STAGE_FUNCTIONS_HEADER

#include <stdio.h>
#include <stdint.h> 
#include "stage_table_definitions.h" 

stage_execution_status_e stage_1(stage_table_context_t* context);
stage_execution_status_e stage_1_recovery(stage_table_context_t* context); 

stage_execution_status_e stage_2(stage_table_context_t* context); 
stage_execution_status_e stage_2_recovery(stage_table_context_t* context); 

stage_execution_status_e stage_3(stage_table_context_t* context); 
stage_execution_status_e stage_3_recovery(stage_table_context_t* context); 

#endif
