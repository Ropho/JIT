/////////////////////////////////////////////////
/////////////////////////////////////////////////
DEF_CMD(end, 0x10, 0,
{
    trans->buff[ip] = 0xC3;
})


DEF_CMD(in, 0x15, 1,
{
    ++ip_bin;
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
//! mov r10, addr
    trans->buff[ip++] = 0x41;
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long) in;

    *((int *)(trans->buff + ip)) = *((int *)&ptr);
    ip += sizeof (int) / sizeof (char);

    SAVE_RSP;
    ALIGN_STACK;

    CALL_R10;
    
    RESTORE_RSP;

    PUSH_RAX;
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
})


DEF_CMD(out, 0x16, 1,
{
    ++ip_bin;

    POP_RDI;

//! mov r10, addr
    trans->buff[ip++] = 0x41;
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long)out;

    *((int *)(trans->buff + ip)) = *((int *)&ptr);
    ip += sizeof (int) / sizeof (char);
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    CALL_R10;
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
})


DEF_CMD(push, 0x11, 1,
{

    ++ip_bin;

    if (bin->buff[ip_bin] == 0x00) {
        ++ip_bin;

        PUSH_NUM;
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

        // ++ip_bin;

        // size_t pos = 
        // PUSH_FROM_RAM()

        
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


DEF_CMD(pop, 0x12, 1,
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


DEF_CMD(jump, 0x20, 1,
{
    JUMP(NO_COMPARE);
})


DEF_CMD(jg, 0x21, 1,
{
    JUMP(COMPARE_JG);
})



DEF_CMD(jge, 0x22, 1,
{
    JUMP(COMPARE_JGE);
})


DEF_CMD(jl, 0x23, 1,
{
    JUMP(COMPARE_JL);
})


DEF_CMD(jle, 0x24, 1,
{
   JUMP(COMPARE_JLE);
})


DEF_CMD(je, 0x25, 1,
{
    JUMP(COMPARE_E);
})


DEF_CMD(jne, 0x26, 1,
{
    JUMP(COMPARE_NE);
})


DEF_CMD(call, 0x40, 1,
{
    ++ip_bin;                                                       
                                                                    
    if (!pass) {                                                    
                                                                    
        CALL_CMP;  
                                                         
        *((int*)(trans->buff + ip)) = (int)0x00;                               
        ip += sizeof (int) / sizeof (char);                                         
    }                                                               
    else {                                                          
                                                                    
        CALL_CMP;                                                   
                                                                    
        int offset = *((int*)(bin->buff + ip_bin));                
        // printf ("OFFSET: %d\n", offset);                
        for (int index = 0; index < bin->cmd_num; ++index) {        
            if (bin->cmd_ip[index] == (char)offset) {                     
                offset = trans->cmd_ip[index] - (ip + sizeof (int) / sizeof (char));           
                break;                                              
            }                                                       
        }                                                           
        // printf ("CALL: %d\n", offset);                                 
                               
        *((int*)(trans->buff + ip)) = offset;                                   
        ip += sizeof (int) / sizeof (char);                                                       
    }                                                               
    ip_bin += sizeof (int) / sizeof (char);                         

})


DEF_CMD(ret, 0x41, 0,
{
    ++ip_bin;

    trans->buff[ip++] = 0xC3;
})


DEF_CMD(add, 0x13, 0,
{
    ++ip_bin;

    POP_RDI;

    POP_RSI;

//! add rdi, rsi
    trans->buff[ip++] = 0x48;
    trans->buff[ip++] = 0x01;
    trans->buff[ip++] = 0xF7;

    PUSH_RDI;
})


DEF_CMD(sub, 0x17, 0,
{
    ++ip_bin;

    POP_RSI;

    POP_RDI;

//! sub rdi, rsi
    trans->buff[ip++] = 0x48;
    trans->buff[ip++] = 0x29;
    trans->buff[ip++] = 0xF7;

    PUSH_RDI;

})


DEF_CMD(mul, 0x14, 0,
{

    ++ip_bin;

    SAVE_RAX;

    SAVE_RDX;

    POP_RDX;
    
    POP_RAX;


    trans->buff[ip++] = 0x48;
    trans->buff[ip++] = 0xF7;

    // trans->buff[ip++] = 0xE2;    //mul
    trans->buff[ip++] = 0xEA;     //imul

    PUSH_RAX;

    RESTORE_RAX;
    
    RESTORE_RDX;
})


DEF_CMD(del, 0x18, 0,
{
    ++ip_bin;

    SAVE_RAX;

    SAVE_RCX;
    
    SAVE_RDX;

/////////////////////////////////////////////////
    POP_RCX;

    POP_RAX;

    trans->buff[ip++] = 0x48;
    trans->buff[ip++] = 0x99;     //cqo
    
    trans->buff[ip++] = 0x48;
    trans->buff[ip++] = 0xF7;
    // trans->buff[ip++] = 0xF1;      //div         
    trans->buff[ip++] = 0xF9;         //idiv         

    PUSH_RAX;
/////////////////////////////////////////////////

    RESTORE_RAX;

    RESTORE_RCX;

    RESTORE_RDX;
})


DEF_CMD(sqrt, 0x19, 0,
{

    ++ip_bin;

    POP_RDI;

    trans->buff[ip++] = 0x41;           //mov r10, out(adress)
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long)r_sqrt;

    *((int *)(trans->buff + ip)) = *((int *)&ptr);
    
    ip += sizeof (int) / sizeof (char);
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    CALL_R10;
/////////////////////////////////////////////////
    PUSH_RAX;

    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
})
