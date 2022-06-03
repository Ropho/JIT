#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include <time.h>

#include "defines.hpp"


enum CMD {

    #define DEF_CMD(name, number, argc, code) CMD_##name = number,

    #include "cmd.hpp"

    #undef DEF_CMD
};


typedef struct TEXT {

    size_t buff_size = 0;

    char *buff = nullptr;

    int *cmd_ip = nullptr;

    size_t cmd_num = 0;
}TEXT;



typedef struct x86_translator {

    TEXT *bin_buff = nullptr;

    TEXT *bin_trans = nullptr;

    size_t ram_size = 1024;
    
}x86_translator;


enum ERRORS {

    MEM_ALLOC_ERROR     = 1,
    OPEN_FILE_ERROR     = 2,
    READ_FILE_ERROR     = 3,
    CLOSE_FILE_ERROR    = 4,
    ENCODING_ERROR      = 5,
    SYSTEM_COM_ERROR    = 6,
    WRONG_SIGNATURE     = 7,
    WRONG_VERSION       = 8,
    MPROTECT_ERROR      = 9,
    UNKNOWN_CMD_ERROR   = 10,
};


TEXT *read_from_file    (FILE *in, size_t *error);
TEXT *ctor_trans        (TEXT *buff, size_t *error);
size_t get_file_size    (FILE *in);
size_t fillin_trans     (TEXT *trans, TEXT *bin);
size_t compile_trans    (TEXT *trans);


int r_sqrt              (int input);
int in                  (void);
void out                (long long input);