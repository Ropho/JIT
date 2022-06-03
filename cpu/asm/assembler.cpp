#include "asm.h"

int main (int argc, const char *argv[]) {
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    if (argc <= 1) {
        puts ("NO FILE GIVEN");
        return 0;
    }

    FILE *in  = fopen (argv[1], "rb");
    //FILE *in  = fopen ("fac.txt", "rb");    //ФАКТОРИАЛ
    //FILE *in  = fopen ("fib.txt", "rb");  //ПАРАМОНАЧИ
    //FILE *in  = fopen ("qua.txt", "rb");  //ПАРАМОНАТКА
    //FILE *in  = fopen ("quadr.txt", "rb");//КВАДРАТЫ ЦЕЛЫХ ЧИСЕЛ
    
    assert (in != nullptr);

    FILE *out = fopen ("binary.bin", "wb");

    assert (out != nullptr);

    TEXT cmd_file = {};

    TEXT_struct_fillin (&cmd_file, in);
    
    asm_type asem = {};

    asem.code = (char*)calloc(MAX_LEN, sizeof (char));
    assert (asem.code != nullptr);

    if (assembler_fillin (&cmd_file, out, 1, &asem))
        puts ("BUGG in 1st asem");
    
    if (assembler_fillin (&cmd_file, out, 2, &asem))
        puts ("BUGG in 2nd asem");

    fclose (in);
    fclose (out);

    free (asem.code);  // jp

    puts ("SUCCESSFUL END OF PROGRAM");

    return 0;
}

int cmd_num (char *cmd) {

    assert (cmd != nullptr);

    #define DEF_CMD(name, number, argc, hash, code)  if (hash == hash_C (cmd)) return number;
    #define DEF_REG(name, number, hash)

    #include "cmds.h"

    #undef DEF_CMD
    #undef DEF_REG

    return 0;
}
