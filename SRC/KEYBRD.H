#ifndef KEYBRD_H
#define KEYBRD_H

typedef enum {
    R_ARROW = 0x4D,
    L_ARROW = 0x4B,
    U_ARROW = 0x48,
    D_ARROW = 0x50,
    ESC = 0x01
} key_code;

void kb_init(void);

void kb_exit(void);

int kb_hit(key_code key);

#endif

