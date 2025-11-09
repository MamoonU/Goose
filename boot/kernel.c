//GCC provided header files

#include <stddef.h>
#include <stdint.h>

//Basic checks to see if x86-elf cross compiler is in use correctly

#if defined (__linux__)                                                         //Y/N Linux?
    #error "Code must be compiled with cross-compiler"
#elif !defined(__i386__)                                                        //Y/N architecture = 32-bit x86?
    #error "Code must be compiled with x86-elf compiler"
#endif

//x86 architecture's VGA textmode buffer
//Write data to this memory location to display text (0xB8000)

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;        //VGA textmode buffer has a size of 80x25 characters
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint16_t term_colour = 0x0F;    //colours

void term_init() {

    for (int col = 0; col < VGA_COLS; col ++) {
        for (int row = 0; row < VGA_ROWS; row ++) {
            const size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)term_colour << 8) | ' ';
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
        const size_t index = (VGA_COLS * term_row) + term_col;
        vga_buffer[index] = ((uint16_t)term_colour << 8) | c;
        term_col ++;
        break;
        }

    }

    if (term_col >= VGA_COLS) {

        term_col = 0;
        term_row++;

    }

    if (term_row >= VGA_ROWS) {

        term_col = 0;
        term_row = 0;

    }

}

void term_print(const char* str) {

        for (size_t i = 0 ; str[i] != '\0'; i ++)
            term_putc(str[i]);

    }

void kernel_main() {

    term_init();

    term_print("@kernel - hello world");

}