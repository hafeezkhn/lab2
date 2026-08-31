/**
 * @file endian_utils.h
 * @brief Endianness conversion utilities using union-based approach.
 *
 * This module provides functions to convert integers between
 * big-endian and little-endian formats. It supports sizes from
 * 1 to 8 bytes (8, 16, 24, 32, 64-bit values).
 *
 * ## Why Endianness Conversion?
 * - Networking protocols use big-endian (network byte order).
 * - x86 systems are little-endian.
 * - Embedded systems often switch between both (CAN, SPI, I2C).
 *
 * Example:
 *   Input  : 0xAABBCCDD
 *   Output : 0xDDCCBBAA
 * 
 */

#ifndef ENDIAN_UTILS_H
#define ENDIAN_UTILS_H

#include <stdint.h>
#include <stddef.h>

/**
 * @union endian_u
 * @brief Union to access an integer as raw bytes.
 *
 * This union allows interpreting the same memory region as both
 * an integer (`uint64_t`) and an array of bytes (`uint8_t`).
 *
 * Example usage:
 *   endian_u u;
 *   u.value = 0xAABBCCDD;
 *   printf("%X %X %X %X\n", u.bytes[0], u.bytes[1], u.bytes[2], u.bytes[3]);
 */
typedef union {
    uint64_t value;   /**< Integer view (up to 64 bits). */
    uint8_t  bytes[8];/**< Byte-wise view. */
} endian_u;

/**
 * @brief Convert the endianness of an integer.
 *
 * Reverses the byte order of an input integer of given width.
 *
 * @param input       The input integer value (up to 64 bits).
 * @param byte_count  Number of bytes in the integer (1, 2, 3, 4, 8).
 * @return The endian-swapped integer as `uint64_t`.
 *
 * @warning Caller must cast the result to the correct type.
 * @warning Undefined behavior if `byte_count > 8`.
 *
 * ## Edge Cases:
 * - If `byte_count == 1`, the function returns the input unchanged.
 * - Symmetric values (e.g., 0x11223311) remain valid.
 */
static inline uint64_t convert_endian(uint64_t input, size_t byte_count) {
    endian_u src, dst;
    src.value = input;

    for (size_t i = 0; i < byte_count; i++) {
        dst.bytes[i] = src.bytes[byte_count - 1 - i]; // reverse order
    }

    return dst.value;
}

#endif // ENDIAN_UTILS_H
