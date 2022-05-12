/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2022, Hugo Lefeuvre <hugo.lefeuvre@manchester.ac.uk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
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

#include <stdio.h>
#include <flexos/isolation.h>
#include <flexos/example/isolated.h>
#include <uk/alloc.h>
#include <stdlib.h>

/* this is a temporary header necessary for EPT, should disappear
 * in the future */
#if CONFIG_LIBFLEXOS_VMEPT
#include <flexos/impl/main_annotation.h>
#endif


/* In the future we want to have all flexos_gate and flexos_gate_r inserted
 * automatically; it will only be a matter of adding flexos_whitelist compiler
 * annotations and this can be automated via static analysis too.
 */

/* a callback called by the library */
void callback(int foo)
{
	printf("callback called!\n");
}

/* static buffer that we pass to the library */
static char static_buf[32];

/* a private static buffer */
static char static_app_secret[32];

int main(int __unused argc, char __unused *argv[])
{
	static_buf[0] =  'A';
	static_app_secret[0] = 'B';

	/* shared stack integer used by the library */
	int stack_int = 21;

	/* shared stack buffer that we pass to the library */
	char stack_buf[32];
	stack_buf[0] = 'C';

	/* call library function */
	lib_func(&callback, static_buf, &stack_int, stack_buf);

	return 0;
}
