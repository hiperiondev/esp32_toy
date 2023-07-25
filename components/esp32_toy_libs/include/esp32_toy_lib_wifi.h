/*
 * Copyright 2023 Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/esp32_toy *
 *
 * This is based on other projects:
 *    Toy programming language (https://github.com/Ratstail91/Toy)
 *    Others (see individual files)
 *
 *    please contact their authors for more information.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef ESP32_TOY_LIB_WIFI_H_
#define ESP32_TOY_LIB_WIFI_H_

#include "toy_interpreter.h"

/**
 * @fn int Toy_hookWifi(Toy_Interpreter *interpreter, Toy_Literal identifier, Toy_Literal alias)
 * @brief
 *
 * @param interpreter
 * @param identifier
 * @param alias
 * @return
 */
int Toy_hookWifi(Toy_Interpreter *interpreter, Toy_Literal identifier, Toy_Literal alias);

#define TOY_OPAQUE_TAG_WIFI 300

#endif /* ESP32_TOY_LIB_WIFI_H_ */
