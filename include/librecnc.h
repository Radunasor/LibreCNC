/**
 * @file librecnc.h
 * @brief LibreCNC main Header file.
 *
 * This file defines the interface for initializing LibreCNC library.
 */

#ifndef LIBRECNC_H
#define LIBRECNC_H

#include <stdbool.h>
#include "config/config.h"

/**
 * @brief Initializes the LibreCNC.
 */
void lc_init();

/**
 * @brief Checks if the LibreCNC library has been initialized.
 *
 * @return A boolean indicating whether the CNC library is initialized.
 */
bool lc_get_initialized();

/**
 * @brief Deinitializes the LibreCNC library.
 */
void lc_deinit();

/**
 * @brief LibreCNC library main handler.
 */
void lc_handler();

#endif // LIBRECNC_H