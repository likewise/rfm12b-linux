/* rfm12b-linux: linux kernel driver for the rfm12(b) RF module by HopeRF
*  Copyright (C) 2013 Georg Kaindl
*  
*  This file is part of rfm12b-linux.
*  
*  rfm12b-linux is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 2 of the License, or
*  (at your option) any later version.
*  
*  rfm12b-linux is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with rfm12b-linux.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(__RFM12_PLAT_OLINUXINOMAXI_H__)
#define __RFM12_PLAT_OLINUXINOMAXI_H__

#include <linux/ioport.h>
#include <asm/io.h>
#include <mach/mxs.h>

/*
   This file handles pinmuxing on Raspberry Pi.
   
   If you want to change the default hardware settings for RPi, this
   is the place to look.
*/


// the amount of RFM12 modules connected to the raspberry pi
// per default, we have settings for one board. if you want
// more boards, you need to add the necessary settings below
// as well.
#define NUM_RFM12_BOARDS         1

/*
*  default config for raspberry pi (one RFM12 module)
*
*  Raspberry Pi          RFM12B
*  ---------------------------------
*  P1/17                 VDD (+3.3V)
*  P1/19                 SDI
*  P1/21                 SDO
*  P1/22                 nIRQ
*  P1/23                 SCK
*  P1/25                 GND
*  P1/26                 nSEL
*
*  make sure the SPI driver is loaded before loading this
*  module!
*
*  modprobe spi-bcm2708
*/

struct spi_rfm12_board_config board_configs[NUM_RFM12_BOARDS] = {
   {
      //.irq_pin      = 25,   // gpio 25
      .irq_pin      = MXS_GPIO_NR(2, 28),
      .spi_bus      = 32766,   // SSP2
      .spi_cs      = 0   // CS #0
   }
};

static int
spi_rfm12_init_pinmux_settings(void);
static int
spi_rfm12_cleanup_pinmux_settings(void);

static int
spi_rfm12_init_pinmux_settings(void)
{

#if 0
// taken from https://github.com/bootc/linux/blob/rpi-i2cspi/drivers/spi/spi-bcm2708.c
   
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

   int pin;
   u32* gpio = ioremap(0x20200000, SZ_16K);
   
   // SPI0 is on gpio 7..11
   for (pin = 7; pin <= 11; pin++) {
      INP_GPIO(pin);
      SET_GPIO_ALT(pin, 0);
   }
   
   // irq pin
   INP_GPIO(25);
   SET_GPIO_ALT(25, 0);
   
   iounmap(gpio);

#undef INP_GPIO
#undef SET_GPIO_ALT
#endif //0
   return 0;
}

static int
spi_rfm12_cleanup_pinmux_settings(void)
{
   return 0;
}

#endif // __RFM12_PLAT_OLINUXINOMAXI_H__
