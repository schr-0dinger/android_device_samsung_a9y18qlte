/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <string.h>

#include <utils/Unicode.h>

// libutils dropped this after Android 10; libsec-ril still imports it.
extern "C" char16_t* strdup8to16(const char* s, size_t* out_len) {
    if (s == nullptr) {
        return nullptr;
    }

    const size_t src_len = strnlen(s, SIZE_MAX);
    ssize_t len = utf8_to_utf16_length(reinterpret_cast<const uint8_t*>(s), src_len);
    if (len <= 0) {
        return nullptr;
    }

    char16_t* str = static_cast<char16_t*>(calloc(len + 1, sizeof(char16_t)));
    if (str == nullptr) {
        return nullptr;
    }

    utf8_to_utf16(reinterpret_cast<const uint8_t*>(s), src_len, str, len + 1);

    if (out_len != nullptr) {
        *out_len = len;
    }

    return str;
}
