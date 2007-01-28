/*
 * Copyright (c) 2006 Bjorn Andersson <flex@kryo.se>, Erik Ekman <yarrick@kryo.se>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "md5.h"

/* Needs a 16byte array for output, and 32 bytes password */
void login_calculate(char *out, int len, char *pass, int seed) {
	char temp[32];
	md5_state_t ctx;
	int i;
	int k;
	int *ix;

	if (len < 16) {
		return;
	}

	memcpy(temp, pass, 32);
	ix = (int*) temp;
	for (i = 0; i < 8; i++) {
		k = ntohl(*ix);
		k ^= seed;
		*ix++ = htonl(k);
	}
	md5_init(&ctx);
	md5_append(&ctx, temp, 32);
	md5_finish(&ctx, out);
}
