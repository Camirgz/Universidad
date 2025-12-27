# README

**Sistema de Sospechosos del OIJ**

Bienvenido al Sistema de Sospechosos del Organismo de Investigación Judicial (OIJ) de Costa Rica. Este programa automatiza la búsqueda de personas en casos criminales, facilitando la comparación de características y generando un índice de coincidencia. Aquí se detallan las instrucciones y características clave:

### **Funcionalidades Principales:**

1. **Carga de Información:**
    - El programa carga datos de personas sospechosas desde un archivo "Sospechas.csv".
    - Cada línea representa a una persona con información detallada (nombre, provincia, cantón, edad, género, estado civil, color de pelo, altura).
2. **Búsqueda y Índice de Coincidencia:**
    - Realiza consultas comparando características del crimen con registros existentes.
    - Calcula un índice de coincidencia según criterios dados.
3. **Resultados y Eliminación:**
    - Muestra resultados ordenados por índice de coincidencia descendente.
    - Permite eliminar sospechosos de los resultados.
4. **Clases.Historial de Búsquedas:**
    - Almacena un historial de búsquedas realizadas.

### Formato de Sospechas.csv

```java
Nombre,Provincia,Canton,Edad,Genero,Estado civil,Pelo,Altura
```

**Especificaciones para una persona válida**

- `Nombre, provincia, cantón` : No puede tener números
- `Edad`: En años cumplidos, entre 18 y 100
- `Género` : Masculino, femenino u otro
- `Estado civil`: Casado, soltero, viudo o divorciado
- `Pelo`: Negro, moreno, castanno y rubio
- `Altura`: En centímetros de 100 a 200

### Integrantes

- Camila Rodríguez Águila
    - C36624
- Liqing Yosery Zheng Lu
    - C38680
