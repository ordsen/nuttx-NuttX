/****************************************************************************
 * arch/arm/src/bcm2780/bcm_lowputc.h
 *
 *   Copyright (C) 2017 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_BCM2708_BCM_LOWPUTC_H
#define __ARCH_ARM_SRC_BCM2708_BCM_LOWPUTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "up_internal.h"
#include "chip.h"

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* This structure describes the configuration of an UART */

struct uart_config_s
{
  uint32_t baud;          /* Configured baud */
  uint8_t  parity;        /* 0=none, 1=odd, 2=even */
  uint8_t  bits;          /* Number of bits (5-9) */
  bool     stopbits2;     /* true: Configure with 2 stop bits instead of 1 */
#ifdef CONFIG_SERIAL_IFLOWCONTROL
  bool     iflow;         /* true: Input flow control enabled */
#endif
#ifdef CONFIG_SERIAL_OFLOWCONTROL
  bool     oflow;         /* true: Output flow control enabled. */
#endif
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: bcm_lowsetup
 *
 * Description:
 *   Called at the very beginning of _start.  Performs low level
 *   initialization including setup of the console UART.  This UART done
 *   early so that the serial console is available for debugging very early
 *   in the boot sequence.
 *
 ****************************************************************************/

void bcm_lowsetup(void);

/****************************************************************************
 * Name: bcm_[mini|pl011]uart_configure
 *
 * Description:
 *   Configure the Mini- or PL011 UART for non-interrupt driven operation
 *
 ****************************************************************************/

#ifdef CONFIG_BCM2708_MINI_UART
int bcm_miniuart_configure(FAR const struct uart_config_s *config);
#endif

#ifdef CONFIG_BCM2708_PL011_UART
int bcm_pl011uart_configure(FAR const struct uart_config_s *config);
#endif

/************************************************************************************
 * Name: bcm_lowputc
 *
 * Description:
 *   Output a byte with as few system dependencies as possible.  This will even work
 *   BEFORE the console is initialized if we are booting from U-Boot (and the same
 *   UART is used for the console, of course.)
 *
 ************************************************************************************/

#if defined(BCM_HAVE_UART) && defined(CONFIG_DEBUG_FEATURES)
void bcm_lowputc(int ch);
#else
#  define bcm_lowputc(ch)
#endif

#endif /* __ARCH_ARM_SRC_BCM2708_BCM_LOWPUTC_H */
