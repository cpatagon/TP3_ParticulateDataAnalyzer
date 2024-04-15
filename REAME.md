# Trabajo Práctico 3: TDD para API de Analizador de Material Particulado (ParticulateDataAnalyzer)

## Especialización en Sistemas de Software Embebido - Curso de Embebidos Testing

**Autor: Luis Gómez**

### Descripción

Este repositorio contiene el trabajo práctico 3 (TP3), centrado en el desarrollo de una API denominada `ParticulateDataAnalyzer`, orientada a analizar conjuntos de datos entregados por los sensores de MP (Material Particulado). Para su desarrollo, se utilizó la técnica de Desarrollo Guiado por Pruebas (TDD, por sus siglas en inglés). El objetivo es implementar un conjunto de pruebas unitarias que guíen el desarrollo del software de manera iterativa.

## Requisitos para la API ParticulateDataAnalyzer

### Funcionalidad de Cálculo del Promedio
1. **Cálculo con Datos Estándar:**
    - Debe calcular correctamente el promedio cuando se alimenta con un arreglo de valores de MP dentro del rango válido.

2. **Exclusión de Valores Cero:**
    - Debe excluir valores cero del cálculo del promedio para asegurar que no afecten el resultado.

3. **Exclusión de Valores Atípicos:**
    - Debe excluir valores atípicos negativos y extremadamente altos para evitar distorsiones en el promedio.

### Funcionalidad de Identificación del Valor Máximo
1. **Identificación en Datos Estándar:**
    - Debe identificar el valor máximo correctamente en un arreglo de datos dentro de un rango esperado.

2. **Manejo de Datos con Valores Fuera de Rango:**
    - Debe identificar el valor máximo correctamente incluso cuando se incluyen valores fuera del rango aceptable.

3. **Manejo de Conjuntos de Datos Vacíos:**
    - Debe retornar un indicador específico de que el conjunto de datos está vacío.

### Funcionalidad de Identificación del Valor Mínimo
1. **Identificación en Datos Estándar:**
    - Debe determinar el valor mínimo correctamente de un conjunto estándar de datos de MP.

2. **Manejo de Valores Sobre el Límite Máximo:**
    - Debe excluir valores que superen el límite máximo predefinido del cálculo del valor mínimo.

3. **Manejo de Conjuntos de Datos Vacíos:**
    - Debe manejar y reportar correctamente un conjunto de datos vacío sin error.

### Funcionalidad de Cálculo de la Desviación Estándar
1. **Cálculo con Datos Estándar:**
    - Debe calcular la desviación estándar de un conjunto de datos estándar precisamente.

2. **Manejo de Conjuntos de Datos Vacíos:**
    - Debe retornar un valor especial o error cuando el conjunto de datos está vacío.

3. **Exclusión de Valores Fuera de Rango:**
    - Debe calcular la desviación estándar excluyendo datos que caigan fuera del rango válido.


## Casos de Prueba Implementados para ParticulateDataAnalyzer

1. **Verificar la Función Promedio (calculateAverage)**
       - 1.1 Verificar la función promedio con datos estándar de MP.
       - 1.2 Calcula el promedio de un arreglo de MP omitiendo valores cero.
       - 1.3 Cálculo del promedio para un arreglo con valores atípicos (negativos).
       - 1.4 Calcula el promedio de un arreglo omitiendo valores cero.
       - 1.5 Calcula el promedio de un arreglo excluyendo valores extremos superiores.

2. **Encuentra el Valor Máximo**
       - 2.1 Encuentra el valor máximo en un arreglo de datos estándar.
       - 2.2 Identifica el valor máximo en un conjunto de datos que incluye un valor fuera de rango.
       - 2.3 Identifica el valor máximo en un conjunto de datos que incluye menor al valor mínimo detectable.
       - 2.4 Prueba la función findMaxValue con un conjunto de datos vacíos.

3. **Prueba la función que encuentra el valor minimo (findMinValue)**
       - 3.1 Prueba la función findMinValue con un conjunto estándar de datos.
       - 3.2 Prueba la función findMinValue con valores sobre el límite máximo de detección.
       - 3.3 Prueba la función findMinValue con un conjunto vacío de datos.

4. **Prueba la función de cálculo de la desviación estandar calculateStandardDeviation**
       - 4.1 Prueba la función calculateStandardDeviation con un conjunto estándar de datos.
       - 4.2 Prueba calculateStandardDeviation con un conjunto vacío de datos.
       - 4.3 Prueba calculateStandardDeviation con datos que incluyen valores fuera de rango.



### Estructura del Repositorio

El repositorio está organizado de la siguiente manera:

    |TP3_ParticulateDataAnalyzer/
    │
    ├── src/ - Código fuente del controlador de LEDs.
    │ ├── ParticulateDataAnalyzer.c
    │ └── ParticulateDataAnalyzer.h
    │
    ├── test/ - Pruebas unitarias.
    │ └── test_ParticulateDataAnalyzer.c
    │
    └── README.md - Este archivo.
