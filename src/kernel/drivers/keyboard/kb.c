#include "../../../kernel/arch/i386/interrupt_handlers/isr.h"
#include "../../../inc/vga/vga.h"
#include "../../../inc/IO/io.h"
#include "kb.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/// detectar se a tecla SHIFT foi pressionada
bool is_shift_pressed = false; 

static uint8_t keyboard_map[2][128] = {
    {
        KEY_NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
        'i', 'o', 'p', '[', ']', KEY_ENTER, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
        'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
        ',', '.', '/', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
        KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
        KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
        KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
    },

    {
	    KEY_NULL, KEY_ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
        '_', '+', KEY_BACKSPACE, KEY_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
        'I', 'O', 'P',   '{', '}', KEY_ENTER, 0, 'A', 'S', 'D', 'F', 'G', 'H',
        'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
        'M', '<', '>', '?', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4,
        KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
        KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
        KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
    }
};

/// este handler é executado quando a interrupção int $33 é chamada
void keyboard_handler(registers reg) { 
	// tecla que foi pressionada
    uint8_t scancode = inportb(KEYBOARD_PORT);
	
	if (scancode == KEY_LSHIFT + 128 || scancode == KEY_RSHIFT + 128) {
        is_shift_pressed = false;
	}

	else {
	    if(scancode == KEY_LSHIFT || scancode == KEY_RSHIFT) { 
	        is_shift_pressed = true;
	        return;
	    } 

        // caracter esta nos limites ASCII?
	    if (scancode > 128 ) { return; } 

        if (scancode == 0xe) {
            vga_backspace();
            return;
        }
        // vga_write_formated_str(DEFAULT_COL, "%x\t", scancode);

 	    is_shift_pressed ? vga_putchar(DEFAULT_COL, keyboard_map[1][scancode]) : vga_putchar(DEFAULT_COL, keyboard_map[0][scancode]);
    }
}