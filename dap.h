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

#ifndef _DAP_H_
#define _DAP_H_

/*- Includes ----------------------------------------------------------------*/
#include <stdint.h>

/*- Defines --------------------------------------------------------------*/
#define DAP_ERROR_OK 0
#define DAP_ERROR_TIMEOUT 1

/*- Prototypes --------------------------------------------------------------*/
void dap_init(void);
void dap_connect(void);
void dap_disconnect(void);
uint32_t dap_read_word(uint32_t addr);
uint16_t dap_read_hword(uint32_t addr);
void dap_write_word(uint32_t addr, uint32_t data);
void dap_write_hword(uint32_t addr, uint16_t data);
void dap_reset_link(void);
uint32_t dap_read_idcode(void);
void dap_target_prepare(void);

// Target operations
void dap_target_select(void);
void dap_target_deselect(void);
void dap_target_erase(void);
void dap_target_lock(void);
void dap_target_erase_row(uint32_t addr);

#endif // _DAP_H_
