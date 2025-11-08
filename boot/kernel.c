//GCC provided header files

#include <stddef.h>
#include <stdint.h>

//Basic checks to see if x86-elf cross compiler is in use correctly

#if defined (__linux__)
    #error "Code must be compiled with cross-compiler"
#elif !defined(__i386__)
    #error "Code must be compiled with x86-elf compiler"
#endif

//x86 architecture's VGA textmode buffer
//Write data to this memory location to display text (0xB8000)

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;        //VGA textmode buffer has a size of 80x25 characters
const int VGA_ROWS = 25;


void term_init() {

    for (int col = 0; col < VGA_COLS; col +++) {
        for (int row = 0; row < VGA_ROWS; row +++) {
            const size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
        }
    }

}

void term_putc(char c) {

    switch (c) {

        case '\n': {
            term_col = 0;
            term_row ++;
            break;
        }

    default: {
        const size_t index = (VGA_COLS * term_row) + 
    }

    }

}