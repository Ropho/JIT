#include "func.hpp"


const size_t SIGN_SIZE = 4;
const size_t VER_SIZE  = 1;
const int    SIGN      = 0xADDEADDE;
const char   VERSION   = 0xA7;
const size_t PAGE_SIZE = 4096;



int in (void) {

//STACK IS (ALIGNED)
    // puts ("START OF SCANF");

    int rax = 0;
    scanf ("%d", &rax); //ломает регистры

    // puts ("END OF SCANF");

    return rax;
}


void out (long long input) {

    // puts ("HEHEHEHEH");
    // asm ("push rax\n\t"
    //     "push rbx\n\t"
    //     "push rcx\n\t"
    //     "push rdx\n\t"
    //     "push rdi\n\t"
    //     "push rsi\n\t"
    //     "push r10\n\t"
    //     "push r11\n\t"
    //     "push r12\n\t"
    //     "push r13\n\t"
    //     "push r14\n\t"
    //     "push r15\n\t");
    
    printf ("%lld\n", input);

    // asm ("pop r15\n\t"
    //     "pop r14\n\t"
    //     "pop r13\n\t"
    //     "pop r12\n\t"
    //     "pop r11\n\t"
    //     "pop r10\n\t"
    //     "pop rsi\n\t"
    //     "pop rdi\n\t"
    //     "pop rdx\n\t"
    //     "pop rcx\n\t"
    //     "pop rbx\n\t"
    //     "pop rax\n\t");
    
    // puts ("EHEHEH");
    return;
}


size_t compile_trans (TEXT *trans) {

    assert (trans);
    assert (trans->buff);

    size_t ip = 0;
////////////////////////////////////////////////////////////////
    for (size_t index = 0; index < trans->buff_size; ++index)
        printf ("%X ", (unsigned char)trans->buff[index]);
    puts ("\n===================================");
////////////////////////////////////////////////////////////////
    void (*func)(void) = (void (*)(void)) trans->buff;


    asm ("push rbx\n\t"
        "push r12\n\t"
        "push r13\n\t"
        "push r14\n\t"
        "push r15\n\t");
    func();
    asm ("pop r15\n\t"
        "pop r14\n\t"
        "pop r13\n\t"
        "pop r12\n\t"
        "pop rbx\n\t");


    return 0;
}


size_t fillin_trans (TEXT *trans, TEXT *bin) {

    assert (trans);
    assert (trans->buff);
    assert (bin);
    assert (bin->buff);

    // puts ("EQEQ");
        size_t ip     = 0;
        size_t ip_bin = 0;

        size_t cmd_num = 0;

    for (size_t pass = 0; pass < 2; ++pass) {

        ip     = 0;
        ip_bin = 0;
        cmd_num = 0;

        while (bin->buff[ip_bin] != CMD_end) {

            printf ("%ld \t BIN: %x \n", pass, bin->buff[ip_bin]);

            if (!pass) {
                // printf ("CMD_NUM: %ld\n", cmd_num);
                trans->cmd_ip[cmd_num]    = ip;
                bin->cmd_ip[cmd_num]      = ip_bin;
                ++cmd_num;
            }
            else {
                    if (bin->buff[ip_bin] != CMD_jump && bin->buff[ip_bin] != CMD_ja && bin->buff[ip_bin] != CMD_jae &&
                    bin->buff[ip_bin] != CMD_jb && bin->buff[ip_bin] != CMD_jbe && bin->buff[ip_bin] != CMD_je &&
                    bin->buff[ip_bin] != CMD_jne && bin->buff[ip_bin]) {
                        ip     = trans->cmd_ip[cmd_num + 1];
                        ip_bin = bin->cmd_ip[cmd_num + 1];
                        ++cmd_num;
                        printf ("IP: %ld \t %ld\n", ip_bin, ip);
                        continue; 
                        puts ("JEJ");  
                    }
            }

            switch (bin->buff[ip_bin]) {

                #define DEF_CMD(name, number, argc, hash, code) case number: code; break;

                #include "cmd.hpp"

                #undef  DEF_CMD

                default: 
                    puts ("WRONG COMMAND");
                    assert (0);
                break;
            }
        }
        
        if (!pass)
            trans->buff[ip] = (char)0xC3;

        trans->cmd_ip[cmd_num]   = ip;
        bin->cmd_ip[cmd_num]     = ip_bin;
        ++cmd_num;

        trans->cmd_num  = cmd_num;
        bin->cmd_num    = cmd_num;
        
        if (!pass) {
            for (size_t index = 0; index < bin->cmd_num; ++index) {
                    printf ("CMD: %d \t %d\n", bin->cmd_ip[index], trans->cmd_ip[index]);
            }
        }

    }
        
    ++ip;
    trans->buff_size = ip;



    if (mprotect (trans->buff, trans->buff_size, PROT_EXEC | PROT_WRITE)) {
        perror ("MPROTECT ERROR");
        return MPROTECT_ERROR;
    }

    puts ("END OF FILLIN\n");
    return 0;
}


TEXT *ctor_trans (TEXT *buff, size_t *error) {

    assert (buff);
    assert (error);

    TEXT *trans = (TEXT*)calloc(1, sizeof (TEXT));
    if (!trans) {
        perror ("MEM ALLOC ERROR STRUCT");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }

    trans->buff_size = buff->buff_size;
    trans->buff = (char*)aligned_alloc(PAGE_SIZE, trans->buff_size * sizeof (char));
    if (!trans->buff) {
        perror ("MEM ALLOC ERROR BUFF");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }

    trans->cmd_ip = (int*)calloc(trans->buff_size, sizeof (int));
    if (trans->cmd_ip == nullptr) {
        perror ("MEM ALLOC TROUBLE");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }
    else
        return trans;
}


size_t check_sign (FILE *in) {

    assert (in);

    char *buff = (char*)calloc (SIGN_SIZE + VER_SIZE, sizeof (char));
    if (!buff) {
        perror ("ALLOC MEM ERROR");
        return MEM_ALLOC_ERROR;
    }

    int sign     = 0;
    char version = 0;

    if (fread (&sign, sizeof (int), 1, in) != 1) {
        perror ("SIGN READ ERROR");
        return READ_FILE_ERROR;
    }
    
    if (fread (&version, sizeof (char) / sizeof (char), 1, in) != 1) {
        perror ("VERSION READ ERROR");
        return READ_FILE_ERROR;
    }
        
    if (sign != SIGN) {
        perror ("WRONG SIGNATURE");
        return WRONG_SIGNATURE;
    }
    if (version != VERSION) {
        perror ("WRONG VERSION");
        return WRONG_VERSION;
    }

    return 0;
}


TEXT *read_from_file (FILE *in, size_t *error) {

    assert (in);
    assert (error);

    TEXT *buffer = (TEXT*)calloc(1, sizeof (TEXT));
    if (!buffer) {
        perror ("MEMORY ALLOCATION ERROR");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }
    buffer->buff_size = get_file_size (in) - SIGN_SIZE - VER_SIZE;     // add \0 IN THE END
    
    *error = check_sign (in);
    if (*error)
        return nullptr;


    buffer->buff = (char*)calloc(buffer->buff_size, sizeof (char));
    if (!buffer->buff) {
        perror ("ALLOC MEM ERROR");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }

    if (fread (buffer->buff, sizeof (char), buffer->buff_size, in) != buffer->buff_size) {
        perror ("READING FROM FILE ERROR");
        *error = READ_FILE_ERROR;
        return nullptr;
    }
    
    buffer->cmd_ip = (int*)calloc(buffer->buff_size, sizeof (int));
    if (buffer->cmd_ip == nullptr) {
        perror ("ALLOC MEM TROUBLE");
        *error = MEM_ALLOC_ERROR;
        return nullptr;
    }
    else
        return buffer;
}


size_t get_file_size (FILE *in) {

    assert (in);

    struct stat buff = {};
    fstat (fileno (in), &buff);

    return buff.st_size;
}