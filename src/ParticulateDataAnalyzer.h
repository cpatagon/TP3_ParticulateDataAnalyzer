/*
 * Nombre del archivo: ParticulateDataAnalyzer.h
 * Versión: 0.1
 * Descripción:
 *  Este programa es software libre: puedes redistribuirlo y/o modificarlo
 *  bajo los términos de la Licencia Pública General GNU publicada por
 *  la Free Software Foundation, ya sea la versión 3 de la Licencia, o
 *  (a tu elección) cualquier versión posterior.
 * Autor: Luis Gómez P.
 * Derechos de Autor: (C) 2023 CESE
 * Licencia: GNU General Public License v3.0
 *
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo
 * bajo los términos de la Licencia Pública General GNU publicada por
 * la Free Software Foundation, ya sea la versión 3 de la Licencia, o
 * (a tu elección) cualquier versión posterior.
 *
 * Este programa se distribuye con la esperanza de que sea útil,
 * pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita
 * de COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
 * Licencia Pública General GNU para más detalles.
 *
 * Deberías haber recibido una copia de la Licencia Pública General GNU
 * junto con este programa. Si no es así, visita <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-only
 *
 */

#include <stdint.h>

#ifndef PARTICULATEDATAANALYZER_H
#define PARTICULATEDATAANALYZER_H

/**
 * @file ParticulateDataAnalyzer.h
 * @brief Declaraciones de la API para análisis de datos de material particulado.
 *
 * Contiene funciones para calcular estadísticas de datos obtenidos por sensores de calidad del aire:
 * - calculateAverage: Calcula el promedio de datos validados.
 * - findMaxValue: Identifica el valor máximo en los datos.
 * - findMinValue: Identifica el valor mínimo en los datos.
 * - calculateStandardDeviation: Calcula la desviación estándar.
 *
 * Adecuado para sistemas de monitoreo de calidad del aire.
 */



/* === Headers files inclusions ================================================================ */

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define  EMPTIE_DATA {};
  
/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */


/**
 * @brief Calcula el promedio de un conjunto de datos.
 *
 * Esta función calcula el promedio de un array de datos flotantes, excluyendo aquellos valores
 * que no cumplen con las condiciones de validez especificadas por la función maskIsDataTrue.
 *
 * @param data Un array de datos flotantes.
 * @param n_data El número de elementos en el array.
 * @return El promedio calculado de los valores válidos. Retorna MSN_VOID_ARRAY_VALUE si el
 *         array está vacío o todos los datos son inválidos.
 */
float calculateAverage(float data[], int n_data);


/**
 * @brief Encuentra el valor máximo en un conjunto de datos.
 *
 * Esta función recorre un array de datos flotantes para encontrar el valor máximo,
 * considerando solo aquellos valores que cumplen con las condiciones de validez
 * especificadas por la función maskIsDataTrue.
 *
 * @param data Un array de datos flotantes.
 * @param n_data El número de elementos en el array.
 * @return El valor máximo encontrado entre los datos válidos. Retorna MSN_VOID_ARRAY_VALUE si
 *         el array está vacío o todos los datos son inválidos.
 */
float findMaxValue(float data[], int n_data);


/**
 * @brief Encuentra el valor mínimo en un conjunto de datos.
 *
 * Esta función recorre un array de datos flotantes para encontrar el valor mínimo,
 * considerando solo aquellos valores que cumplen con las condiciones de validez
 * especificadas por la función maskIsDataTrue.
 *
 * @param data Un array de datos flotantes.
 * @param n_data El número de elementos en el array.
 * @return El valor mínimo encontrado entre los datos válidos. Retorna MSN_VOID_ARRAY_VALUE si
 *         el array está vacío o todos los datos son inválidos.
 */
float findMinValue(float data[], int n_data);


/**
 * @brief Calcula la desviación estándar de un conjunto de datos.
 *
 * Esta función determina la desviación estándar de un array de datos flotantes. Se calcula
 * la media de los datos, y luego se usa para determinar la suma de los cuadrados de las diferencias
 * entre cada dato y la media. Solo se consideran los valores que cumplen con las condiciones
 * de validez de la función maskIsDataTrue.
 *
 * @param data Un array de datos flotantes.
 * @param n El número de elementos en el array.
 * @return La desviación estándar calculada de los datos válidos. Retorna 0 si el número de
 *         elementos válidos es menor o igual a 1 o si el array está vacío.
 */
float calculateStandardDeviation(float data[], int n);


  

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* PARTICULATEDATAANALYZER_H */
