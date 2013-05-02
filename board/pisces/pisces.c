/*
 * (C) Copyright 2010
 * Ingenic Semiconductor, <cwjia@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/jz4770.h>

#define PRINT_VALUE(b,a)  \
	printf(" " #a " is " #b "\n",a) 

static void gpio_init(void)
{
	/*
	 * Initialize UART1 pins
	 */
#if CFG_UART_BASE == UART0_BASE
	__gpio_as_uart0();
#elif CFG_UART_BASE == UART1_BASE
	__gpio_as_uart1();
#elif CFG_UART_BASE == UART2_BASE
	__gpio_as_uart2();
#else /* CFG_UART_BASE == UART1_BASE */
	__gpio_as_uart3();
#endif
}

//----------------------------------------------------------------------
// board early init routine
void board_early_init(void)
{
#if 0
#define CS2  (32*0+23)
	__gpio_as_output(CS2);
	while(1) {
		int i;
		__gpio_set_pin(CS2);
		i=480000;
		while(i--);
		__gpio_clear_pin(CS2);
		i=480000;
		while(i--);
	}
#endif
	gpio_init();
}

#define GPIO_POWER_IND_N (32 * 1 + 30)
static void init_green_led_pin(void)
{
    __gpio_as_output0(GPIO_POWER_IND_N);
}

//----------------------------------------------------------------------
// U-Boot common routines

int checkboard (void)
{
	init_green_led_pin();
	DECLARE_GLOBAL_DATA_PTR;

	printf("Board: Ingenic Pisces (CPU Speed %d MHz)\n",
	       gd->cpu_clk/1000000);

	PRINT_VALUE(%x,REG_DDRC_ST	  );
	PRINT_VALUE(%x,REG_DDRC_CFG	  );
	PRINT_VALUE(%x,REG_DDRC_ST	  );
	PRINT_VALUE(%x,REG_DDRC_CFG	  );
	PRINT_VALUE(%x,REG_DDRC_CTRL	  );
	PRINT_VALUE(%x,REG_DDRC_LMR	  );
	PRINT_VALUE(%x,REG_DDRC_TIMING1	  );
	PRINT_VALUE(%x,REG_DDRC_TIMING2	  );
	PRINT_VALUE(%x,REG_DDRC_REFCNT	  );
	PRINT_VALUE(%x,REG_DDRC_DQS	  );
	PRINT_VALUE(%x,REG_DDRC_DQS_ADJ	  );
	PRINT_VALUE(%x,REG_DDRC_MMAP0	  );
	PRINT_VALUE(%x,REG_DDRC_MMAP1	  );
	PRINT_VALUE(%x,REG_DDRC_MDELAY	  );
	PRINT_VALUE(%x,REG_DDRC_CKEL	  );
	PRINT_VALUE(%x,REG_DDRC_PMEMCTRL0 );
	PRINT_VALUE(%x,REG_DDRC_PMEMCTRL1 );
	PRINT_VALUE(%x,REG_DDRC_PMEMCTRL2 );
	PRINT_VALUE(%x,REG_DDRC_PMEMCTRL3 );

	
	return 0; /* success */
}
