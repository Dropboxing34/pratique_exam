/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    tp1_v2.c
 * @brief   TP1 - Utilisation du RTC sur la carte FRDM-KL28Z
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL28Z7.h"
#include "fsl_debug_console.h"
#include "fsl_rtc.h"

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Initialisation du matériel de la carte */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    PRINTF("===========================================\r\n");
    PRINTF(" TP1 : Utilisation du RTC sur la FRDM-KL28Z\r\n");
    PRINTF("===========================================\r\n\r\n");

    /* Déclaration des structures de données pour le RTC */
    rtc_datetime_t date;
    rtc_config_t rtcConfig;

    /* Configuration initiale du RTC */
    RTC_GetDefaultConfig(&rtcConfig);
    RTC_Init(RTC, &rtcConfig);

    /* Arrêter le RTC avant initialisation */
    RTC_StopTimer(RTC);

    /* Initialisation de l'heure de départ (00:00:00, 1 janvier 2025) */
    date.year = 2025;
    date.month = 1;
    date.day = 1;
    date.hour = 0;
    date.minute = 0;
    date.second = 0;

    /* Appliquer la date de départ */
    RTC_SetDatetime(RTC, &date);

    /* Démarrer le RTC */
    RTC_StartTimer(RTC);

    PRINTF("Taper une touche pour afficher l'heure\r\n\r\n");

    /* Boucle principale */
    while (1) {
        /* Attente d'une touche de l'utilisateur */
        GETCHAR();

        /* Lire le temps courant */
        RTC_GetDatetime(RTC, &date);

        /* Afficher l'heure */
        PRINTF("Heure actuelle : %02d:%02d:%02d\r\n", date.hour, date.minute, date.second);
        PRINTF("Taper une touche pour afficher l'heure\r\n\r\n");
    }

    return 0;
}
