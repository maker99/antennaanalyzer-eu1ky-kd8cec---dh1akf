#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdint.h>
#include <stdbool.h>

#define SHELL_MAX_TOKENS              10
#define SHELL_MAX_COMMAND_LINE        150
#define SHELL_MAX_CMD_LINE_HISTORY    10

#define SHELL_INVALIDATE_CACHE SCB_InvalidateDCache
#define SHELL_CLEAN_DCACHE SCB_CleanDCache

typedef bool (*shell_proc)(uint32_t argc, char* const argv[]);

typedef struct {
    char*        cmd_name;
    char*        cmd_help;
    shell_proc   cmd_proc;
    uint32_t     prot_group;
} shell_cmd_t;

#define SHELL_PROT_GROUP_ALL           UINT32_MAX
#define SHELL_PROT_GROUP_INITIAL       0
#define SHELL_PROT_GROUP_NANOVNA       1
#define SHELL_PROT_GROUP_RIGEXPERT     2

#define SHELL_CMD(_command_name, _help_str, _command_proc)      \
   static const shell_cmd_t _shell_##_command_name              \
    __attribute__ ((section(".SHELLCMD")))                      \
    __attribute__ ((used))                                      \
    = {.cmd_name = #_command_name,                              \
       .cmd_help = (_help_str),                                 \
       .cmd_proc = (_command_proc),                             \
       .prot_group = SHELL_PROT_GROUP_INITIAL                   \
      }

#define SHELL_CMD_PROTO(_command_name, _help_str, _command_proc, _protocol_group)        \
   static const shell_cmd_t _shell_grp##_protocol_group##_command_name   \
    __attribute__ ((section(".SHELLCMD")))                      \
    __attribute__ ((used))                                      \
    = {.cmd_name = #_command_name,                              \
       .cmd_help = (_help_str),                                 \
       .cmd_proc = (_command_proc),                             \
       .prot_group = (_protocol_group)                          \
      }

#ifdef __cplusplus
 extern "C" {
#endif

void uart_rx_proc(void);

void shell_init(const char* prompt);
void shell_task(char key);
void shell_run(char* str);
void shell_prompt(void);
void shell_str2num(char* p_str, uint32_t* pNum);
void shell_get_args(uint32_t argv[]);
int32_t shell_argtoi(char* arg);
void shell_set_protocol_group(uint32_t protocol_group);

#ifdef __cplusplus
}
#endif

#endif // _SHELL_H_
