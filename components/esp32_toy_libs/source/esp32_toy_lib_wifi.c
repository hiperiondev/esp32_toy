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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hal_wifi.h"
#include "esp32_toy_lib_wifi.h"
#include "toy_literal_dictionary.h"
#include "toy_memory.h"

//call the hook
typedef struct Natives {
            char *name;
    Toy_NativeFn fn;
} Natives;

typedef struct wifi_ap_record {
    hal_wifi_ap_record_t *ap_record;
                uint32_t len;
} wifi_ap_record_t;

wifi_ap_record_t wifi_ap_record = {
        .ap_record = NULL,
        .len = 0
};

static int nativeWifiScan(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 0) {
        interpreter->errorOutput("Incorrect number of arguments to wifiScan\n");
        return -1;
    }

    if(wifi_ap_record.ap_record != NULL) {
        free(wifi_ap_record.ap_record);
        wifi_ap_record.ap_record = NULL;
    }

    uint32_t count = wifi_scan(&wifi_ap_record.ap_record);
    wifi_ap_record.len = count;

    return 1;
}

static int nativeWifiScanFree(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 0) {
        interpreter->errorOutput("Incorrect number of arguments to wifiScan\n");
        return -1;
    }

    if (wifi_ap_record.ap_record != NULL) {
        free(wifi_ap_record.ap_record);
        wifi_ap_record.ap_record = NULL;
        wifi_ap_record.len = 0;
    }

    return 1;
}

static int nativeWifiScanLength(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 0) {
        interpreter->errorOutput("Incorrect number of arguments to wifiScan\n");
        return -1;
    }

    Toy_Literal resultLiteral = TOY_TO_INTEGER_LITERAL(wifi_ap_record.len);
    Toy_pushLiteralArray(&interpreter->stack, resultLiteral);

    Toy_freeLiteral(resultLiteral);
    return 1;
}

static int nativeWifiScanSSID(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 1) {
        interpreter->errorOutput("Incorrect number of arguments to wifiScan\n");
        return -1;
    }

    Toy_Literal argLiteral = Toy_popLiteralArray(arguments);
    if (!TOY_IS_INTEGER(argLiteral)) {
        interpreter->errorOutput("Index error: Not integer\n");
        Toy_freeLiteral(argLiteral);
        return -1;
    }
    if (argLiteral.as.integer > wifi_ap_record.len - 1) {
        interpreter->errorOutput("Index error: index too long\n");
        Toy_freeLiteral(argLiteral);
        return -1;
    }

    char ssid[33];
    sprintf(ssid, "%s", wifi_ap_record.ap_record[argLiteral.as.integer].ssid);
    Toy_Literal ssidLiteral = TOY_TO_STRING_LITERAL(Toy_createRefStringLength(ssid, strlen(ssid)));

    Toy_pushLiteralArray(&interpreter->stack, ssidLiteral);

    Toy_freeLiteral(argLiteral);
    Toy_freeLiteral(ssidLiteral);

    return 1;
}

static int nativeWifiConnect(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 2) {
        interpreter->errorOutput("Incorrect number of arguments to wifiConnect\n");
        return -1;
    }

    Toy_Literal ssidLiteral = Toy_popLiteralArray(arguments);
    Toy_Literal passwdLiteral = Toy_popLiteralArray(arguments);
    if (!(TOY_IS_STRING(ssidLiteral) && TOY_IS_STRING(passwdLiteral))) {
        interpreter->errorOutput("Index error: Not string\n");
        Toy_freeLiteral(ssidLiteral);
        Toy_freeLiteral(passwdLiteral);
        return -1;
    }

    Toy_RefString *ssidString = TOY_AS_STRING(ssidLiteral);
    const char *ssid = Toy_toCString(ssidString);
    Toy_RefString *passwdString = TOY_AS_STRING(passwdLiteral);
    const char *passwd = Toy_toCString(passwdString);

    if (wifi_connected)
        wifi_stop();
    wifi_connect_sta(ssid, passwd);

    Toy_freeLiteral(ssidLiteral);
    Toy_freeLiteral(passwdLiteral);

    return 1;
}

static int nativeWifiDisconnect(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments) {
    if (arguments->count != 0) {
        interpreter->errorOutput("Incorrect number of arguments to wifiDisconnect\n");
        return -1;
    }

    if (wifi_connected)
        wifi_stop();

    return 1;
}
int Toy_hookWifi(Toy_Interpreter *interpreter, Toy_Literal identifier, Toy_Literal alias) {
    //build the natives list
    Natives natives[] = {
    //misc. utils
            { "wifiScan", nativeWifiScan },
            { "wifiScanFree", nativeWifiScanFree },
            { "wifiScanLength", nativeWifiScanLength },
            { "wifiScanSSID", nativeWifiScanSSID },
            { "wifiConnect", nativeWifiConnect },
            { "wifiDisconnect", nativeWifiDisconnect },
            { NULL, NULL } };

    //store the library in an aliased dictionary
    if (!TOY_IS_NULL(alias)) {
        //make sure the name isn't taken
        if (Toy_isDeclaredScopeVariable(interpreter->scope, alias)) {
            interpreter->errorOutput("Can't override an existing variable\n");
            Toy_freeLiteral(alias);
            return -1;
        }

        //create the dictionary to load up with functions
        Toy_LiteralDictionary *dictionary = TOY_ALLOCATE(Toy_LiteralDictionary, 1);
        Toy_initLiteralDictionary(dictionary);

        //load the dict with functions
        for (int i = 0; natives[i].name; i++) {
            Toy_Literal name = TOY_TO_STRING_LITERAL(Toy_createRefString(natives[i].name));
            Toy_Literal func = TOY_TO_FUNCTION_NATIVE_LITERAL(natives[i].fn);

            Toy_setLiteralDictionary(dictionary, name, func);

            Toy_freeLiteral(name);
            Toy_freeLiteral(func);
        }

        //build the type
        Toy_Literal type = TOY_TO_TYPE_LITERAL(TOY_LITERAL_DICTIONARY, true);
        Toy_Literal strType = TOY_TO_TYPE_LITERAL(TOY_LITERAL_STRING, true);
        Toy_Literal fnType = TOY_TO_TYPE_LITERAL(TOY_LITERAL_FUNCTION_NATIVE, true);
        TOY_TYPE_PUSH_SUBTYPE(&type, strType);
        TOY_TYPE_PUSH_SUBTYPE(&type, fnType);

        //set scope
        Toy_Literal dict = TOY_TO_DICTIONARY_LITERAL(dictionary);
        Toy_declareScopeVariable(interpreter->scope, alias, type);
        Toy_setScopeVariable(interpreter->scope, alias, dict, false);

        //cleanup
        Toy_freeLiteral(dict);
        Toy_freeLiteral(type);
        return 0;
    }

    //default
    for (int i = 0; natives[i].name; i++) {
        Toy_injectNativeFn(interpreter, natives[i].name, natives[i].fn);
    }

    return 0;
}
