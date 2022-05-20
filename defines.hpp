#ifndef DEFINES_HPP
#define DEFINES_HPP

/////////////////////////////////////////////////
////////////////////////PUSH/////////////////////
#define PUSH_NUM do {                                   \
                    trans->buff[ip] = (char)0x68;       \
                    ++ip;                               \
                }while(0)

#define PUSH_RAX do {                                   \
                    trans->buff[ip] = (char)0x50;       \
                    ++ip;                               \
                }while(0)


#define PUSH_RBX do {                                   \
                    trans->buff[ip] = (char)0x53;       \
                    ++ip;                               \
                }while(0)


#define PUSH_RCX do {                                   \
                    trans->buff[ip] = (char)0x51;       \
                    ++ip;                               \
                }while(0)


#define PUSH_RDX do {                                   \
                    trans->buff[ip] = (char)0x52;       \
                    ++ip;                               \
                }while(0)


#define PUSH_RDI do {                                   \
                    trans->buff[ip] = (char)0x57;       \
                    ++ip;                               \
                }while(0)

#define PUSH_RSI do {                                   \
                    trans->buff[ip] = (char)0x56;       \
                    ++ip;                               \
                }while(0)

#define PUSH_R10 do {                                   \
                    trans->buff[ip] = (char)0x41;       \
                    ++ip;                               \
                    trans->buff[ip] = (char)0x52;       \
                    ++ip;                               \
                }while(0)

/////////////////////////////////////////////////
////////////////////////POP//////////////////////
#define POP_RAX do {                                    \
                    trans->buff[ip] = (char)0x58;       \
                    ++ip;                               \
                }while(0)

#define POP_RBX do {                                    \
                    trans->buff[ip] = (char)0x5B;       \
                    ++ip;                               \
                }while(0)

#define POP_RCX do {                                    \
                    trans->buff[ip] = (char)0x59;       \
                    ++ip;                               \
                }while(0)

#define POP_RDX do {                                    \
                    trans->buff[ip] = (char)0x5A;       \
                    ++ip;                               \
                }while(0)

#define POP_R10 do {                                    \
                    trans->buff[ip] = (char)0x41;       \
                    ++ip;                               \
                    trans->buff[ip] = (char)0x5A;       \
                    ++ip;                               \
                }while(0)

#define POP_RDI do {                                    \
                    trans->buff[ip] = (char)0x5F;       \
                    ++ip;                               \
                }while(0)


#define POP_RSI do {                                    \
                    trans->buff[ip] = (char)0x5E;       \
                    ++ip;                               \
                }while(0)

/////////////////////////////////////////////////
///////////////////SAVE//////////////////////////

//! SAVE RAX IN R12
#define SAVE_RAX do {                                   \
                    trans->buff[ip] = 0x49;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xC4;             \
                    ++ip;                               \
                }while(0)


//! SAVE RDX IN R13
#define SAVE_RDX do {                                   \
                    trans->buff[ip] = 0x49;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xD5;             \
                    ++ip;                               \
                }while(0)

//! SAVE RCX IN R14
#define SAVE_RCX do {                                   \
                    trans->buff[ip] = 0x49;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xDE;             \
                    ++ip;                               \
                }while(0)

//! SAVE RBX IN R15
#define SAVE_RBX do {                                   \
                    trans->buff[ip] = 0x49;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xCF;             \
                    ++ip;                               \
                }while(0)


/////////////////////////////////////////////////
///////////////////RESTORE///////////////////////

//! RESTORE RAX FROM R12
#define RESTORE_RAX do {                                \
                    trans->buff[ip] = 0x4C;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xE0;             \
                    ++ip;                               \
                }while(0)

//! RESTORE RDX FROm R13
#define RESTORE_RDX do {                                \
                    trans->buff[ip] = 0x4C;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xEA;             \
                    ++ip;                               \
                }while(0)

//! RESTORE RCX FROM R14
#define RESTORE_RCX do {                                \
                    trans->buff[ip] = 0x4C;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xF3;             \
                    ++ip;                               \
                }while(0)

//! RESTORE RCX FROM R15
#define RESTORE_RBX do {                                \
                    trans->buff[ip] = 0x49;             \
                    ++ip;                               \
                    trans->buff[ip] = 0x89;             \
                    ++ip;                               \
                    trans->buff[ip] = 0xF9;             \
                    ++ip;                               \
                }while(0)


///////////////////////////////
//! push rbp
//! mov rbp, rsp
#define SAVE_RSP do {                               \
                        trans->buff[ip] = 0x55;     \
                        ++ip;                       \
                        trans->buff[ip] = 0x48;     \
                        ++ip;                       \
                        trans->buff[ip] = 0x89;     \
                        ++ip;                       \
                                                    \
                        trans->buff[ip] = 0xE5;     \
                        ++ip;                       \
                    }while(0)

//! and rsp, 0xFFFFFFFF0
#define ALIGN_STACK do {                            \
                    trans->buff[ip] = 0x48;         \
                    ++ip;                           \
                    trans->buff[ip] = 0x83;         \
                    ++ip;                           \
                    trans->buff[ip] = 0xE4;         \
                    ++ip;                           \
                    trans->buff[ip] = 0xF0;         \
                    ++ip;                           \
            }while(0)                           

//! mov rsp, rbp
//! pop rbp
#define RESTORE_RSP do {                            \
                        trans->buff[ip] = 0x48;     \
                        ++ip;                       \
                        trans->buff[ip] = 0x89;     \
                        ++ip;                       \
                        trans->buff[ip] = 0xEC;     \
                        ++ip;                       \
                                                    \
                        trans->buff[ip] = 0x5D;     \
                        ++ip;                       \
                    }while(0)                       

#endif