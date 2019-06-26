#ifndef STAGE_TABLE_HEADER
#define STAGE_TABLE_HEADER

#include <stdint.h> 
#include <stdbool.h> 


/* 
 * Return code enumerations 
 * 
 *   table_status_e: Final status for the entire table execution
 *      - Returned by execute_stage_table() 
 *   stage_execution_status_e: Non-detailed generic status of the execution of a single stage
 *      - Returned by execute_stage()
 *   stage_status_e: Detailed and targeted error messages for the table context
 *      - Used for context.status, set by each stage. 
 *   recovery_status_e: Status of the recovery procedure
 *      - Returned by recovery_procedure() 
 */ 
typedef enum {
    STAGE_TABLE_SUCCESS, 
    STAGE_TABLE_FAILURE_RECOVERED, 
    STAGE_TABLE_FAILURE_UNRECOVERED, 
} table_status_e; 

typedef enum {
    STAGE_EXEC_SUCCESS, 
    STAGE_EXEC_FAILURE, 
} stage_execution_status_e;

typedef enum {
    STAGE_SUCCESS, 
    STAGE_FAILURE,
} stage_status_e; 

typedef enum { 
    RECOVERY_SUCCESS, 
    RECOVERY_FAILURE,
} recovery_status_e; 


/* Structure type definitions */
typedef struct stage_table_context_s stage_table_context_t;
typedef struct stage_s stage_t; 
typedef struct stage_table_s stage_table_t; 

/* Stage functions type definitions  */ 
typedef stage_execution_status_e (*stage_table_function_t)(stage_table_context_t*); 
typedef stage_execution_status_e (*stage_table_recovery_function_t)(stage_table_context_t*); 


/* Stage definition */ 
struct stage_s {
    const char*                     name; 
    stage_table_function_t          function; 
    stage_table_recovery_function_t recovery_function; 
}; 

/* Stage table context definition */ 
struct stage_table_context_s {
    stage_status_e  status; 
    char*           error_message; 
    stage_t*        current_stage;
    bool            recovery_mode;  
};

/* Stage table definition */
struct stage_table_s { 
    stage_table_context_t*  context; 
    uint8_t                 number_of_stages;
    stage_t*                stages; 
};

#endif 
