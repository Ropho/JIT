/////////////////////////////////////////////////
/////////////////////////////////////////////////
DEF_CMD(end, 0x10, 0, 235619509,
{
    trans->buff[ip] = (char)0xC3;
})


DEF_CMD(in, 0x15, 1, 917538081,
{
    ++ip_bin;
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    trans->buff[ip] = (char)0x41;           //mov r10, in(adress)
    ++ip;
    trans->buff[ip] = (char)0xBA;
    ++ip;
    unsigned long ptr = (unsigned long)in;

    for (size_t index = 0; index < 4; ++index) {
        *(trans->buff + ip + index) = *((char *)&ptr + index);
    }

    ip += sizeof (int) / sizeof (char);

    SAVE_RSP;
    ALIGN_STACK;

    trans->buff[ip] = (char)0x41;
    ++ip;
    trans->buff[ip] = (char)0xFF;           //call r10
    ++ip;
    trans->buff[ip] = (char)0xD2;
    ++ip;

    RESTORE_RSP;

    PUSH_RAX;
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
})


DEF_CMD(out, 0x16, 1, 1461626465,
{
    ++ip_bin;

    POP_RDI;

    trans->buff[ip] = (char)0x41;           //mov r10, out(adress)
    ++ip;
    trans->buff[ip] = (char)0xBA;
    ++ip;
    unsigned long ptr = (unsigned long)out;

    for (size_t index = 0; index < 4; ++index) {
        *(trans->buff + ip + index) = *((char *)&ptr + index);
        // printf ("%X ", *((char *)&ptr + index));

    }
    ip += sizeof (int) / sizeof (char);
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    trans->buff[ip] = (char)0x41;
    ++ip;
    trans->buff[ip] = (char)0xFF;
    ++ip;
    trans->buff[ip] = (char)0xD2;
    ++ip;                                   //call r10
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
})


DEF_CMD(push, 0x11, 1, 1721897475,
{

    ++ip_bin;

    if (bin->buff[ip_bin] == 0x00) {
        ++ip_bin;
        PUSH_NUM;

        *((int*)(trans->buff + ip)) = *((int*)(bin->buff + ip_bin));
        ip     += sizeof (int) / sizeof (char);
        ip_bin += sizeof (int) / sizeof (char);

    }
    else if (bin->buff[ip_bin] == 0x01) {
        
        ++ip_bin;
        
        switch (bin->buff[ip_bin]) {
            case 0x01:
                PUSH_RAX;
            break;
            
            case 0x02:
                PUSH_RBX;
            break;
            
            case 0x03:
                PUSH_RCX;
            break;

            case 0x04:
                PUSH_RDX;
            break;

            default:
                abort();
            break;
        }
        ++ip_bin;
    }
    else if (bin->buff[ip_bin] == 0x02) {

        // ++ip;
        // pushka  (head, cpu->ram[(int)cpu->regs[cpu->code[ip]]])
        //Sleep (1000);
        // ++ip;
    }
    else if (bin->buff[ip_bin] == 0x03) {

        // ++ip;
        // pushka (head, cpu->ram[(int)*(type*)(cpu->code + ip)])
        //Sleep (1000);
        // ip += sizeof (type) / sizeof (char);
    }
    else {
        abort ();
    }
})


DEF_CMD(pop, 0x12, 1, 1872004450,
{

    ++ip_bin;

    if (bin->buff[ip_bin] == 0x01) {
        
        ++ip_bin;
        switch (bin->buff[ip_bin]) {
            case 0x01:
                POP_RAX;
            break;

            case 0x02:
                POP_RBX;
            break;

            case 0x03:
                POP_RCX;
            break;
            
            case 0x04:
                POP_RDX;
            break;
        }
        ++ip_bin;
    }
    else if (bin->buff[ip_bin] == 0x02) {

        // ++ip;
        // cpu->ram[(int)cpu->regs[cpu->code[ip]]] = pop (head);
        // // Sleep (1000);
        // ++ip;
    }
    else if (bin->buff[ip_bin] == 0x03) {

        // ++ip;
        // cpu->ram[(int)*((type*)(cpu->code + ip))] = pop (head);
        // // Sleep (1000);
        // ip += sizeof (type) / sizeof (char);
    }
    else {
        abort();
    }
})


DEF_CMD(jump, 0x20, 1, 1563107817,
{
    JUMP(NO_COMPARE);
})


DEF_CMD(ja, 0x21, 1, 1714451963,
{
    JUMP(COMPARE_JA);
})


DEF_CMD(jae, 0x22, 1, 707756480,
{
    JUMP(COMPARE_JAE);
})


DEF_CMD(jb, 0x23, 1, 1062963264,
{
    JUMP(COMPARE_JB);
})


DEF_CMD(jbe, 0x24, 1, 105038799,
{
   JUMP(COMPARE_JBE);
})


DEF_CMD(je, 0x25, 1, 973582470,
{
    JUMP(COMPARE_E);
})


DEF_CMD(jne, 0x26, 1, 1561585812,
{
    JUMP(COMPARE_NE);
})


DEF_CMD(call, 0x40, 1, 46998724,
{
     
    // ++ip;
    // pushka (cpu->func, ip + sizeof (int) / sizeof (char))
    // ip = *(int*)(cpu->code + ip);


})


DEF_CMD(ret, 0x41, 0, 1832507332,
{
    
    // ip = pop (cpu->func);
})


DEF_CMD(add, 0x13, 0, 1278523110,
{
    ++ip_bin;

    POP_RDI;

    POP_RSI;

    trans->buff[ip] = 0x48;
    ++ip;
    trans->buff[ip] = 0x01;
    ++ip;
    trans->buff[ip] = 0xF7;     //add rdi, rsi
    ++ip;

    PUSH_RDI;
})


DEF_CMD(sub, 0x17, 0, 1756310217,
{
    ++ip_bin;

    POP_RSI;

    POP_RDI;

    trans->buff[ip] = 0x48;
    ++ip;
    trans->buff[ip] = 0x29;
    ++ip;
    trans->buff[ip] = 0xF7;     //sub rdi, rsi
    ++ip;

    PUSH_RDI;

})


DEF_CMD(mul, 0x14, 0, 1281615354,
{

    ++ip_bin;

    SAVE_RAX;

    SAVE_RDX;

    POP_RDX;
    
    POP_RAX;

    trans->buff[ip] = 0x48;
    ++ip;
    trans->buff[ip] = 0xF7;     //mul
    ++ip;
    trans->buff[ip] = 0xE2;
    ++ip;

    PUSH_RAX;

    RESTORE_RAX;
    
    RESTORE_RDX;
})


DEF_CMD(del, 0x18, 0, 952552813,
{
    ++ip_bin;

    SAVE_RAX;

    SAVE_RCX;
    
    SAVE_RDX;

/////////////////////////////////////////////////
    POP_RCX;

    POP_RAX;

    trans->buff[ip] = 0x48;
    ++ip;
    trans->buff[ip] = 0xF7;         //div
    ++ip;
    trans->buff[ip] = 0xF1;
    ++ip;

    PUSH_RAX;
/////////////////////////////////////////////////

    RESTORE_RAX;

    RESTORE_RCX;

    RESTORE_RDX;
})


DEF_CMD(sqrt, 0x19, 0, 729115097,
{
    // pushka (head, sqrt (pop (head)))
    // ++ip;
})
