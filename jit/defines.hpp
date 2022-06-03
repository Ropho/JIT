#ifndef DEFINES_HPP
#define DEFINES_HPP

/////////////////////////////////////////////////
////////////////////////PUSH/////////////////////
#define PUSH_NUM do {                                                           \
                    trans->buff[ip++] = 0x68;                                   \
                    *((int*)(trans->buff + ip)) = *((int*)(bin->buff + ip_bin));\
                    ip     += sizeof (int) / sizeof (char);                     \
                    ip_bin += sizeof (int) / sizeof (char);                     \
                }while(0)

// #define PUSH_FROM_RAM(pos)   do {                                   \
//                             trans->buff[ip++] = 0x68;               \
//                             *((int*)(trans->buff + ip)) = ram[pos]; \
//                             ip     += sizeof (int) / sizeof (char); \
//                         }while(0)

#define PUSH_RAX do {                               \
                    trans->buff[ip++] = 0x50;       \
                }while(0)


#define PUSH_RBX do {                               \
                    trans->buff[ip++] = 0x53;       \
                }while(0)


#define PUSH_RCX do {                               \
                    trans->buff[ip++] = 0x51;       \
                }while(0)


#define PUSH_RDX do {                               \
                    trans->buff[ip++] = 0x52;       \
                }while(0)


#define PUSH_RDI do {                               \
                    trans->buff[ip++] = 0x57;       \
                }while(0)

#define PUSH_RSI do {                               \
                    trans->buff[ip++] = 0x56;       \
                }while(0)

#define PUSH_R10 do {                               \
                    trans->buff[ip++] = 0x41;       \
                    trans->buff[ip++] = 0x52;       \
                }while(0)

/////////////////////////////////////////////////
////////////////////////POP//////////////////////
#define POP_RAX do {                                \
                    trans->buff[ip++] = 0x58;       \
                }while(0)

#define POP_RBX do {                                \
                    trans->buff[ip++] = 0x5B;       \
                }while(0)

#define POP_RCX do {                                \
                    trans->buff[ip++] = 0x59;       \
                }while(0)

#define POP_RDX do {                                \
                    trans->buff[ip++] = 0x5A;       \
                }while(0)

#define POP_R10 do {                                \
                    trans->buff[ip++] = 0x41;       \
                    trans->buff[ip++] = 0x5A;       \
                }while(0)

#define POP_RDI do {                                \
                    trans->buff[ip++] = 0x5F;       \
                }while(0)


#define POP_RSI do {                                \
                    trans->buff[ip++] = 0x5E;       \
                }while(0)

/////////////////////////////////////////////////
///////////////////SAVE//////////////////////////

//! \brief
//! mov r12, rax
//! SAVE RAX IN R12
#define SAVE_RAX do {                                     \
                    trans->buff[ip++] = 0x49;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xC4;             \
                }while(0)


//! \brief
//! mov r13, rdx
//! SAVE RDX IN R13
#define SAVE_RDX do {                                     \
                    trans->buff[ip++] = 0x49;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xD5;             \
                }while(0)

//! \brief
//! mov r14, rcx
//! SAVE RCX IN R14
#define SAVE_RCX do {                                     \
                    trans->buff[ip++] = 0x49;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xDE;             \
                }while(0)

//! \brief
//! mov r15, rbx
//! SAVE RBX IN R15
#define SAVE_RBX do {                                     \
                    trans->buff[ip++] = 0x49;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xCF;             \
                }while(0)


/////////////////////////////////////////////////
///////////////////RESTORE///////////////////////

//! \brief
//! mov rax, r12
//! RESTORE RAX FROM R12
#define RESTORE_RAX do {                                  \
                    trans->buff[ip++] = 0x4C;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xE0;             \
                }while(0)

//! \brief
//! mov rdx, r13
//! RESTORE RDX FROm R13
#define RESTORE_RDX do {                                  \
                    trans->buff[ip++] = 0x4C;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xEA;             \
                }while(0)

//! \brief
//! mov rcx, r14
//! RESTORE RCX FROM R14
#define RESTORE_RCX do {                                  \
                    trans->buff[ip++] = 0x4C;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xF3;             \
                }while(0)

//! \brief
//! mov rdx, r15
//! RESTORE RDX FROM R15
#define RESTORE_RBX do {                                  \
                    trans->buff[ip++] = 0x49;             \
                    trans->buff[ip++] = 0x89;             \
                    trans->buff[ip++] = 0xF9;             \
                }while(0)


/////////////////////////////////////////////////
//! \brief
//! push rbp
//! mov rbp, rsp
#define SAVE_RSP do {                                  \
                        trans->buff[ip++] = 0x55;      \
                        trans->buff[ip++] = 0x48;      \
                        trans->buff[ip++] = 0x89;      \
                                                       \
                        trans->buff[ip++] = 0xE5;      \
                    }while(0)

//! \brief
//! and rsp, 0xFFFFFFFF0
#define ALIGN_STACK do {                              \
                    trans->buff[ip++] = 0x48;         \
                    trans->buff[ip++] = 0x83;         \
                    trans->buff[ip++] = 0xE4;         \
                    trans->buff[ip++] = 0xF0;         \
            }while(0)                           

//! \brief
//! mov rsp, rbp
//! pop rbp
#define RESTORE_RSP do {                              \
                        trans->buff[ip++] = 0x48;     \
                        trans->buff[ip++] = 0x89;     \
                        trans->buff[ip++] = 0xEC;     \
                        trans->buff[ip++] = 0x5D;     \
                    }while(0)                       
/////////////////////////////////////////////////
///////////////////JUMP//////////////////////////
//! \brief
#define JUMP(CMP) do {                                              \
                                                                    \
    ++ip_bin;                                                       \
                                                                    \
    if (!pass) {                                                    \
                                                                    \
        CMP;                                                        \
        trans->buff[ip++] = 0x00;                                   \
    }                                                               \
    else {                                                          \
                                                                    \
        CMP;                                                        \
                                                                    \
        char offset = *((int*)(bin->buff + ip_bin));                \
                                                                    \
        for (int index = 0; index < bin->cmd_num; ++index) {        \
            if (bin->cmd_ip[index] == offset) {                     \
                offset = trans->cmd_ip[index] - (ip + 1);           \
                break;                                              \
            }                                                       \
        }                                                           \
                                                                    \
        trans->buff[ip++] = offset;                                 \
    }                                                               \
    ip_bin += sizeof (int) / sizeof (char);                         \
                                                                    \
}while (0)


#define NO_COMPARE do {                             \
                        trans->buff[ip++] = 0xEB;   \
                    }while(0) 


#define CALL_CMP do {                           \
                    trans->buff[ip++] = 0xE8;   \
                }while (0)

//! \brief
//! pop rsi
//! pop rdi
//! cmp rdi, rsi
//! je ...



//! cmp rdi, rsi
#define CMP do {                                    \
                    trans->buff[ip++] = 0x48;       \
                    trans->buff[ip++] = 0x39;       \
                    trans->buff[ip++] = 0xF7;       \
            }while (0)

#define COMPARE_E do {                                \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x74;     \
                    }while(0) 

//! \brief
//! pop rsi
//! pop rdi
//! cmp rdi, rsi
//! jne....
#define COMPARE_NE do {                               \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x75;     \
                    }while(0)                      

//! \brief
//! pop rsi
//! pop rdi
//! cmp rdi, rsi
#define COMPARE_JLE do {                              \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x7E;     \
                    }while(0)     

//! \brief
#define COMPARE_JL do {                               \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x7C;     \
                    }while(0)         

//! \brief
//! JG
#define COMPARE_JG do {                               \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x7F;     \
                    }while(0)     

//! \brief
#define COMPARE_JGE do {                              \
                        POP_RSI;                      \
                        POP_RDI;                      \
                        CMP;                          \
                        trans->buff[ip++] = 0x7D;     \
                    }while(0)  

/////////////////////////////////////////////////

#define CALL_R10 do {                                   \
                    trans->buff[ip++] = 0x41;           \
                    trans->buff[ip++] = 0xFF;           \
                    trans->buff[ip++] = 0xD2;           \
                }while(0)

/////////////////////////////////////////////////
// #define EMIT(argc, num, ...) do {            
//                             switch (argc) {
//                                 case 1:
//                                     trans->buff[]
//                                 break;
                                
//                                 default:
//                                     perror ("can't be such a number of param");
//                                     assert (0);
//                                 break;
//                             }
//                         }while(0)      


// EMIT ({0x5E, 0x5F}, "pop rsi");

#endif