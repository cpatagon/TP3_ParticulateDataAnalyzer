/*
 * Nombre del archivo: test_ParticulateDataAnalyzer.c
 * Descripción: Pruebas orientadas a analizar conjuntos de datos entregados por los sensores de
 * MP (Material Particulado). Para su desarrollo, se utilizó la técnica de Desarrollo Guiado por
 * Pruebas (TDD, por sus siglas en inglés). El objetivo es implementar un conjunto de pruebas
 * unitarias que guíen el desarrollo del software de manera iterativa.
 * Autor: Luis Gómez P.
 * Derechos de Autor: (C) 2023 CESE FIUBA
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
/*
//////////////////////////////////////////////
// *** lista de pruebas pendientes ***
07.- Prender leds que ya están prendidos antes.
08.- Apagar los leds que ya estén apagados.
09.- Comprobar valores prohibidos.
10.- Comprobar los valores de borde o límite.
///////////////////////////////////////////////
*/

/**
 * @file  test_ParticulateDataAnalyzer.c
 * @brief Este archivo contiene pruebas unitarias para el módulo ParticulateDataAnalyzer, el cual
 *        analiza conjuntos de datos de Material Particulado (MP) recopilados por sensores.
 *        Las pruebas están diseñadas siguiendo la metodología de Desarrollo Guiado por Pruebas
 *        (Test-Driven Development - TDD). Este enfoque asegura que el desarrollo del software
 *        sea iterativo y guiado por las necesidades específicas de validación de los datos de MP,
 *        lo que ayuda a garantizar la precisión y fiabilidad del módulo bajo prueba.
 *
 *
 * @test Pruebas unitarias implementadas:
 *       1.1 verificar la función promedio (calculateAverage) con datos estándar de MP.
 *       1.2 calcula el promedio de un arreglo de MP omitiendo valores cero
 *       1.3 cálculo del promedio para un arreglo con valores atípicos (negativos).
 *       1.4 calcula el promedio de un arreglo omitiendo valores cero.
 *       1.5 calcula el promedio de un arreglo excluyendo valores extremos superiores.
 *       2.1 encuentra el valor máximo en un arreglo de datos estándar
 *       2.2 identifica el valor máximo en un conjunto de datos que incluye un valor fuera de rango
 *       2.3 identifica el valor máximo en un conjunto de datos que incluye menor al valor mínimo
 * detectable. 2.4 Prueba la función findMaxValue con un conjunto de datos vacíos. 3.1 Prueba la
 * función findMinValue con un conjunto estándar de datos. 3.2 Prueba la función findMinValue con
 * valores sobre el limite máximo de detección. 3.3 Prueba la función findMinValue con un conjunto
 * vacío de datos. 4.1 Prueba la función calculateStandardDeviation con un conjunto estándar de
 * datos. 4.2 Prueba calculateStandardDeviation con un conjunto vacío de datos. 4.3 Prueba
 * calculateStandardDeviation con datos que incluyen valores fuera de rango.
 */

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "ParticulateDataAnalyzer.h"

/* === Macros definitions ====================================================================== */

/**
 * @def ARRAY_SIZE(arr)
 * @brief Calcula el número de elementos en un arreglo.
 *
 * Esta macro calcula la cantidad de elementos en un arreglo estático utilizando
 * la operación sizeof. Es seguro usarla con arreglos estáticos locales y globales,
 * pero no debe usarse con punteros, ya que devolvería el tamaño del puntero y no
 * el del arreglo completo.
 *
 * @param arr El arreglo cuyo tamaño se desea calcular.
 * @return El número de elementos en el arreglo.
 *
 * @note Esta macro solo es segura para usar en arreglos donde el tamaño del arreglo
 *       es conocido en tiempo de compilación. No es segura para punteros o arreglos
 *       dinámicos.
 *
 * Ejemplo de uso:
 * @code
 * int myArray[10];
 * int size = ARRAY_SIZE(myArray); // size será 10
 * @endcode
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/// @brief Define un conjunto estándar de datos de Material Particulado (MP) para pruebas.
#define SET_STANDAR_DATA_MP                                                                        \
    { 2.0, 4.0, 6.0, 8.0, 10.0 }
/// @brief Promedio esperado para el conjunto estándar de datos de MP.
#define EXPECTED_MEAN_STANDAR_DATA_MP 6.0
/// @brief Valor máximo esperado en el conjunto estándar de datos de MP.
#define EXPECTED_MAX_STANDAR_DATA_MP 10.0
/// @brief Valor mínimo esperado en el conjunto estándar de datos de MP.
#define EXPECTED_MIN_STANDAR_DATA_MP 2.0

/// @brief Define otro conjunto estándar de datos de MP con variaciones para pruebas extendidas.
#define SET_STANDAR_DATA_2_MP                                                                      \
    { 20.0, 30.0, 60, 8.0, 10.0 }
/// @brief Especifica la desviación estándar esperada para el segundo conjunto estándar de datos de
/// MP.
#define EXPECTED_STD_STANDAR_DATA_2_MP 21.13764

/// @brief Define un conjunto vacío de datos de MP para pruebas de manejo de datos vacíos.
#define SET_EMPTY_DATA_MP                                                                          \
    {}
/// @brief Valor de advertencia utilizado para indicar datos vacíos o no disponibles en los
/// resultados de las pruebas.
#define EXPECTED_WARNING_EMPTY_DATA_MP -999

/// @brief Define un conjunto de datos de MP que incluye valores atípicos extremos para pruebas.
#define SET_OUTLIER_DATA_MP                                                                        \
    { 2.0, 1000.0, 600.0, 6.0, 8.0, 10.0 }
/// @brief Promedio esperado para el conjunto de datos de MP que incluye valores atípicos.
#define EXPECTED_MEAN_OUTLIER_DATA_MP 6.5
/// @brief Desviación estándar esperada para el conjunto de datos de MP con valores atípicos.
#define EXPECTED_STD_OUTLIER_DATA_MP 3.41565
/// @brief Valor mínimo esperado en el conjunto de datos de MP con valores atípicos.
#define EXPECTED_MIN_OUTLIER_DATA_MP 2.0
/// @brief Valor máximo esperado en el conjunto de datos de MP con valores atípicos.
#define EXPECTED_MAX_OUTLIER_DATA_MP 10.0

/// @brief Define un conjunto de datos de MP con valores negativos para pruebas.
#define SET_NEGATIVE_DATA_MP                                                                       \
    { 2.0, -4.0, -600.0, 6.0, 8.0, 10.0 }
/// @brief Promedio esperado para el conjunto de datos de MP que incluye valores negativos.
#define EXPECTED_MEAN_NEGATIVE_DATA_MP 6.5

/// @brief Define un conjunto de datos de MP que incluye múltiples ceros para pruebas.
#define SET_CERO_DATA_MP                                                                           \
    { 2.0, 0.0, 6.0, 8.0, 0.0, 0.0, 10.0 }
/// @brief Promedio esperado para el conjunto de datos de MP que incluye ceros.
#define EXPECTED_MEAN_CERO_DATA_MP 6.5
/// @brief Máximo esperado para el conjunto de datos de MP que incluye ceros.
#define EXPECTED_MAX_CERO_DATA_MP 10

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */
/*
LISTA DE PRUEBAS
 */

// Calcula el valor promedio de un set de datos de MP

/** 1.1
 * @brief Prueba unitaria para verificar la función calculateAverage con datos estándar de MP.
 *
 * Esta función de prueba verifica que la función calculateAverage calcule correctamente
 * el promedio de un conjunto predefinido de concentraciones de Material Particulado (MP).
 * Utiliza un arreglo de datos de MP definidos estáticamente y compara el resultado calculado
 * con un valor esperado preestablecido para asegurar que la función funcione como se espera.
 *
 * @test
 * - Inicializa un arreglo con datos de concentración estándar de MP.
 * - Calcula el tamaño del arreglo utilizando la macro ARRAY_SIZE.
 * - Define el valor esperado para el promedio de estos datos.
 * - Ejecuta calculateAverage para calcular el promedio.
 * - Utiliza TEST_ASSERT_EQUAL_FLOAT para verificar que el promedio calculado
 *   coincida con el valor esperado.
 *
 * Se espera que el resultado de calculateAverage sea igual al valor esperado definido,
 * indicando que la función maneja correctamente el conjunto de datos de prueba.
 */
void test_calculateAverage_StandardSet(void) {
    float data[] = SET_STANDAR_DATA_MP; // Datos de prueba para el promedio con valores estándar
    float result =
        calculateAverage(data, ARRAY_SIZE(data)); // Llamada a la función para calcular el promedio
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MEAN_STANDAR_DATA_MP, result); // Verifica que el resultado
                                                                    // sea como el esperado
}

/** 1.2
 * @brief Prueba la respuesta de calculateAverage con un array vacío.
 *
 * Evalúa si calculateAverage retorna correctamente el valor de error WARNING_EMPTY_DATA_MP
 * cuando se le pasa un array sin elementos, asegurando el manejo adecuado de casos vacíos.
 *
 * @test
 * - Utiliza un array definido como vacío.
 * - Verifica que el resultado de calculateAverage sea el valor de error esperado.
 */
void test_calculateAverage_EmptySet(void) {
    float data[] = SET_EMPTY_DATA_MP;                        // Inicialización de un array vacío
    float result = calculateAverage(data, ARRAY_SIZE(data)); // Cálculo del promedio
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_WARNING_EMPTY_DATA_MP, result); // Comprobación de que el
                                                                     // resultado es correcto
}

/** 1.3
 * @brief Prueba el cálculo del promedio para un arreglo con valores atípicos.
 *
 * Esta prueba verifica que calculateAverage maneje correctamente arreglos que incluyen
 * valores negativos y extremadamente altos, asegurando que el promedio calculado
 * sea el esperado según los datos válidos.
 *
 * @test
 * - Configura un arreglo con valores atípicos, incluyendo negativos y muy altos.
 * - Comprueba que el promedio calculado coincida con el valor esperado.
 */
void test_calculate_average_and_remove_negative_value(void) {
    float data[] = SET_NEGATIVE_DATA_MP; // Inicializa arreglo con valores atípicos
    float result = calculateAverage(data, ARRAY_SIZE(data));         // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MEAN_NEGATIVE_DATA_MP, result); // Verifica que el
                                                                     // resultado sea el esperado
}

/** 1.4
 * @brief Prueba que calcula el promedio de un arreglo omitiendo valores cero.
 *
 * Esta prueba verifica que la función calculateAverage pueda calcular correctamente
 * el promedio de un conjunto de datos que incluye valores cero, asegurando que estos
 * valores no afecten el cálculo del promedio.
 *
 * @test
 * - Utiliza un arreglo que incluye valores cero.
 * - Verifica que el promedio calculado excluya los valores cero y coincida con el valor esperado.
 */
void test_calculate_average_and_remove_cero_value(void) {
    float data[] = SET_CERO_DATA_MP;                         // datos de prueba
    float result = calculateAverage(data, ARRAY_SIZE(data)); // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MEAN_CERO_DATA_MP,
                            result); // verificación de la función probada
}

/** 1.5
 * @brief Prueba que calcula el promedio de un arreglo excluyendo valores extremos superiores.
 *
 * Esta prueba asegura que la función calculateAverage maneje adecuadamente la presencia de valores
 * que superan un umbral máximo establecido, excluyéndolos del cálculo del promedio para obtener
 * una media más representativa de los demás datos.
 *
 * @test
 * - Utiliza un arreglo que incluye al menos un valor extremadamente alto.
 * - Verifica que el promedio calculado no incluya dicho valor y sea igual al valor esperado.
 */
void test_calculate_average_and_remove_over_max_value(void) {
    float data[] = SET_OUTLIER_DATA_MP;                      // datos de prueba
    float result = calculateAverage(data, ARRAY_SIZE(data)); // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MEAN_OUTLIER_DATA_MP,
                            result); // verificación de la función probada
}

// Encuentra Valor Máximo de un arreglo de concentraciones de MP

/** 2.1
 * @brief Prueba la función findMaxValue con un conjunto estándar de datos.
 *
 * Esta prueba verifica que la función findMaxValue pueda identificar correctamente
 * el valor máximo dentro de un conjunto predefinido de datos. La prueba asegura que
 * el valor máximo encontrado coincida con el valor máximo esperado, definido por
 * EXPECTED_MAX_STANDAR_DATA_MP.
 *
 * @test
 * - Inicializa un arreglo con datos de prueba estándar.
 * - Calcula el valor máximo utilizando la función findMaxValue.
 * - Verifica que el valor máximo calculado sea igual al valor máximo esperado.
 */
void test_findMaxValue(void) {
    float data[] = SET_STANDAR_DATA_MP; // Incluye valores sobre el rango de detección de sensor
    float result = findMaxValue(data, ARRAY_SIZE(data)); // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MAX_STANDAR_DATA_MP,
                            result); // verificación de la función probada
}

/** 2.2
 * @brief Prueba que identifica el valor máximo en un conjunto de datos que incluye un valor
 * extremadamente alto.
 *
 * Esta prueba verifica que la función findMaxValue pueda identificar correctamente el valor máximo
 * en un conjunto de datos que incluye valores atípicos extremos, asegurándose de que dichos valores
 * no sean considerados en el cálculo.
 *
 * @test
 * - Configura un arreglo con un valor extremadamente alto.
 * - Verifica que el valor máximo identificado excluya el valor extremo y coincida con el máximo
 * esperado.
 */
void test_findMaxValue_withOutlierValues(void) {
    float data[] = SET_OUTLIER_DATA_MP; // Incluye valores sobre el rango de detección de sensor
    float result = findMaxValue(data, ARRAY_SIZE(data)); // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MAX_OUTLIER_DATA_MP,
                            result); // verificación de la función probada
}

/** 2.3
 * @brief Prueba que identifica el valor máximo en un conjunto de datos que incluye valor 0.
 *
 * Esta prueba verifica que la función findMaxValue pueda identificar correctamente el valor máximo
 * en un conjunto de datos que incluye valores atípicos como cero, asegurándose de que dichos
 * valores no sean considerados en el cálculo.
 *
 * @test
 * - Configura un arreglo con un valor cero.
 * - Verifica que el valor máximo identificado excluya el valor cero  y coincida con el máximo
 * esperado.
 */
void test_findMaxValue_withCeroValues(void) {
    float data[] = SET_CERO_DATA_MP; // Incluye valores sobre el rango de detección de sensor
    float result = findMaxValue(data, ARRAY_SIZE(data)); // función a probar
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MAX_CERO_DATA_MP,
                            result); // verificación de la función probada
}

/** 2.4
 * @brief Prueba la función findMaxValue con un conjunto de datos vacíos.
 *
 * Esta prueba verifica que findMaxValue maneje adecuadamente un conjunto de datos vacío
 * al retornar un valor de error predefinido que indica la ausencia de datos válidos.
 *
 * @test
 * - Inicializa un arreglo definido como vacío.
 * - Verifica que el resultado de findMaxValue sea igual al valor de error esperado
 *   para conjuntos vacíos.
 */
void test_findMaxValue_in_EmptySet(void) {
    float data[] = SET_EMPTY_DATA_MP;
    float result = findMaxValue(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_WARNING_EMPTY_DATA_MP, result);
}

// Encuentra Valores mínimos de un set de datos de MP

/** 3.1
 * @brief Prueba la función findMinValue con un conjunto estándar de datos.
 *
 * Evalúa si la función findMinValue identifica correctamente el valor mínimo
 * en un conjunto estándar de datos, asegurando que el resultado coincida
 * con el valor mínimo esperado.
 *
 * @test
 * - Configura un arreglo con datos estándar.
 * - Verifica que el valor mínimo encontrado sea igual al esperado.
 */
void test_find_min_value(void) {
    float data[] = SET_STANDAR_DATA_MP;
    float result = findMinValue(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MIN_STANDAR_DATA_MP, result);
}

/** 3.2
 * @brief Prueba la función findMinValue con valores atípicos en el conjunto de datos.
 *
 * Esta prueba verifica que findMinValue pueda calcular correctamente el valor mínimo
 * en un conjunto de datos que incluye valores extremadamente bajos o altos, asegurando
 * que el valor mínimo calculado excluya los valores atípicos y coincida con el esperado.
 *
 * @test
 * - Utiliza un arreglo que incluye valores atípicos.
 * - Verifica que el valor mínimo calculado excluya los valores extremos y sea igual
 *   al valor mínimo esperado.
 */
void test_find_min_value_with_outlier_values(void) {
    float data[] = SET_OUTLIER_DATA_MP;
    float result = findMinValue(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_MIN_OUTLIER_DATA_MP, result);
}

/** 3.3
 * @brief Prueba la función findMinValue con un conjunto vacío de datos.
 *
 * Verifica que findMinValue retorne el valor de error esperado cuando se le pasa un conjunto
 * de datos vacío, indicando correctamente que no hay elementos para evaluar.
 *
 * @test
 * - Configura un arreglo vacío.
 * - Verifica que el resultado sea el valor de error predeterminado para conjuntos vacíos.
 */
void test_findMinValue_inEmptySet(void) {
    float data[] = SET_EMPTY_DATA_MP;
    float result = findMinValue(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_WARNING_EMPTY_DATA_MP, result);
}

// calcula de desviación estadar de un set de datos de mp

/** 4.1
 * @brief Prueba la función calculateStandardDeviation con un conjunto estándar de datos.
 *
 * Asegura que calculateStandardDeviation calcule correctamente la desviación estándar
 * de un conjunto de datos estándar, comparando el resultado con un valor esperado.
 *
 * @test
 * - Utiliza un conjunto estándar de datos para la prueba.
 * - Verifica que la desviación estándar calculada coincida con el valor esperado.
 */
void test_calculateStandardDeviation_standardData(void) {
    float data[] = SET_STANDAR_DATA_2_MP;
    float result = calculateStandardDeviation(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_STD_STANDAR_DATA_2_MP, result);
}

/** 4.2
 * @brief Prueba calculateStandardDeviation con un conjunto vacío de datos.
 *
 * Evalúa si calculateStandardDeviation devuelve un valor de error cuando se
 * intenta calcular la desviación estándar de un conjunto de datos vacío,
 * reflejando adecuadamente la falta de datos.
 *
 * @test
 * - Configura un arreglo definido como vacío.
 * - Verifica que el resultado sea el valor de error esperado para conjuntos vacíos.
 */
void test_calculateStandardDeviation_inEmptySet(void) {
    float data[] = SET_EMPTY_DATA_MP;
    float result = calculateStandardDeviation(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_WARNING_EMPTY_DATA_MP, result);
}

/** 4.3
 * @brief Prueba calculateStandardDeviation con datos que incluyen valores fuera de rango.
 *
 * Esta prueba determina cómo la función calculateStandardDeviation
 * maneja un conjunto de datos que incluye valores atípicos,
 * asegurando que el cálculo de la desviación estándar se realice correctamente
 * incluso en presencia de datos extremos.
 *
 * @test
 * - Configura un arreglo con valores atípicos.
 * - Verifica que la desviación estándar calculada sea igual al valor estándar
 *   esperado para datos con valores atípicos.
 */
void test_calculateStandardDeviation_withOutlierValues(void) {
    float data[] = SET_OUTLIER_DATA_MP;
    float result = calculateStandardDeviation(data, ARRAY_SIZE(data));
    TEST_ASSERT_EQUAL_FLOAT(EXPECTED_STD_OUTLIER_DATA_MP, result);
}

/* === End of documentation ==================================================================== */
