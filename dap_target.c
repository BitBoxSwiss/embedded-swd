/*
 * Copyright (c) 2014-2016, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*- Includes ----------------------------------------------------------------*/
#include "dap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*- Definitions -------------------------------------------------------------*/
#define DFSR 0xE000ED30 // Debug Fault Status
#define DHCSR 0xE000EDF0 // Debug Halting Control and Status
#define DCRSR 0xE000EDF4 // Debug Core Register Selector
#define DCRDR 0xE000EDF8 // Debug Core Register Data
#define DEMCR 0xE000EDFC // Debug Exception and Monitor Control
#define AIRCR 0xE000ED0C // Application Interrupt and Reset Control

// DHCSR
#define DBGKEY 0xA05F0000
#define C_DEBUGEN 1
#define C_HALT 2
#define S_REGRDY (1 << 16)

// DCRSR
#define REGWnR (1 << 16)
#define MSP 17
#define DebugReturnAddress 15

// DEMCR
#define VC_CORERESET 1

// AIRCR
#define VECTKEY 0x05FA0000
#define SYSRESETREQ 4
/*- Implementations ---------------------------------------------------------*/

//-----------------------------------------------------------------------------
void dap_target_select(void)
{
    // Request core to halt, enable debug
    dap_write_word(DHCSR, DBGKEY | C_DEBUGEN | C_HALT);
    // Enable reset vector catch
    dap_write_word(DEMCR, VC_CORERESET);
    // request a reset
    dap_write_word(AIRCR, VECTKEY | SYSRESETREQ);
}

//-----------------------------------------------------------------------------
void dap_target_deselect(void)
{
    // Disable reset vector catch
    dap_write_word(DEMCR, 0);
    //  Set C_HALT = 0 starts running the core
    dap_write_word(DHCSR, DBGKEY);
    // Issue reset
    dap_write_word(AIRCR, VECTKEY | SYSRESETREQ);
}
