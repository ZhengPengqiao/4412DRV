# sdram程序说明

* clock_init_tiny4412.S
    ```C
        /*
        * system_clock_init: Initialize core clock and bus clock.
        * void system_clock_init(void)
        */

            .globl system_clock_init
        system_clock_init:
    ```
* mem_init_tiny4412.S
    ```C
            .globl mem_ctrl_asm_init
        mem_ctrl_asm_init:

        /*
        * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
        * void uart_asm_init(void)
        */
            .globl uart_asm_init
        uart_asm_init:

                .globl uart_asm_putc
        uart_asm_putc:

            .globl uart_asm_putx
        uart_asm_putx:
    ```

* mmc_relocate.c
    ```C
        void copy_code_to_dram(void);
    ```