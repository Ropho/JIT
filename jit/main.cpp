#include "func.hpp"


int main (void) {
/////////////////////////////////////////////////
    size_t error = 0;
/////////////////////////////////////////////////
    FILE *bin = fopen ("cpu/asm/binary.bin", "rb");
    if  (!bin) {
        perror ("FILE OPEN ERROR");
        return OPEN_FILE_ERROR;
    }

    x86_translator trans = {};

    trans.bin_buff = read_from_file (bin, &error);
    if (error) {
        return error;
    }

    if (fclose (bin)) {
        perror ("CLOSE FILE ERROR");
        return CLOSE_FILE_ERROR;
    } 
/////////////////////////////////////////////////
    trans.bin_trans = ctor_trans (trans.bin_buff, &error);
    if (error) {
        return error;
    }

    error = fillin_trans (trans.bin_trans, trans.bin_buff);
    if (error) {
        return error;
    }

    error = compile_trans (trans.bin_trans);
    if (error) {
        return error;
    }
/////////////////////////////////////////////////
    puts ("SUCCESFUL END OF PROG =)");
    return 0;
}