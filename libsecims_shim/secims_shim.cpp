/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/types.h>

#include <utils/Unicode.h>

// libutils dropped utf8_length after Android 10; libsec-ims still imports it,
// and the dlopen failure is swallowed by StackIF's catch of UnsatisfiedLinkError,
// so the only symptom is initStack() having no implementation.
//
// Reimplemented to match the AOSP 10 behaviour: walk the string, validate the
// UTF-8 encoding, and return the byte length, or -1 if any sequence is
// malformed or encodes a codepoint above U+10FFFF.
extern "C" ssize_t utf8_length(const char* src) {
    if (src == nullptr) {
        return -1;
    }

    const char* cur = src;
    size_t ret = 0;

    while (*cur != '\0') {
        const char first_char = *cur++;

        if ((first_char & 0x80) == 0) {  // ASCII
            ret += 1;
            continue;
        }

        // A leading byte is 110xxxxx, 1110xxxx or 11110xxx - never 10xxxxxx.
        if ((first_char & 0x40) == 0) {
            return -1;
        }

        int32_t mask = 0x40;
        int32_t to_ignore_mask = 0x80;
        size_t num_to_read = 1;
        char32_t utf32 = 0;

        for (; num_to_read < 5 && (first_char & mask);
             num_to_read++, to_ignore_mask |= mask, mask >>= 1) {
            if ((*cur & 0xC0) != 0x80) {  // continuation bytes are 10xxxxxx
                return -1;
            }
            utf32 = (utf32 << 6) + (*cur++ & 0x3F);
        }

        if (num_to_read == 5) {
            return -1;
        }

        to_ignore_mask |= mask;
        utf32 |= ((~to_ignore_mask) & first_char) << (6 * (num_to_read - 1));

        if (utf32 > 0x10FFFF) {
            return -1;
        }

        ret += num_to_read;
    }

    return static_cast<ssize_t>(ret);
}
