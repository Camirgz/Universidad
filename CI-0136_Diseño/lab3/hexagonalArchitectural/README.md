# Resumen: Arquitectura Hexagonal (Ports & Adapters)

## ¿Qué es?
Arquitectura que busca crear componentes de aplicación débilmente acoplados, conectables con su entorno mediante puertos y adaptadores. Propuesta por Alistair Cockburn en 2005.

## Tipo de Arquitectura
- **Orientada a:** Modularidad, Independencia, Separación de preocupaciones
- **Relacionada con:** Arquitecturas Limpias, Arquitecturas por Capas

## Problema que Resuelve
La lógica de negocio suele enlazarse demasiado a frameworks, bases de datos e interfaces de usuario, haciendo difícil realizar cambios.

### Propuesta
Aislar el núcleo de la lógica de negocio de los detalles de infraestructura, permitiendo intercambiar adaptadores sin cambiar el núcleo.

## Beneficios

### Mantenimiento
Los cambios en infraestructura o UI no afectan el núcleo de negocio al separar claramente responsabilidades.

### Escalabilidad
Facilita añadir nuevos adaptadores (nuevo UI, nueva DB) sin reescribir la lógica.

### Testabilidad
El núcleo puede probarse en aislamiento, reduciendo el coste de pruebas.

### Flexibilidad
Permite posponer decisiones tecnológicas y cambiarlas cuando sea necesario.

## Partes Principales
1. **Núcleo de la App** - Business Logic
2. **Puertos** - Interfaces
3. **Adaptadores** - Implementaciones externas

## Ventajas y Desventajas

### Ventajas
- Acoplamiento débil entre núcleo y detalles
- Alta testabilidad
- Flexibilidad para cambiar adaptadores tecnológicos
- Enfoque en el dominio de negocio

### Desventajas
- Mayor complejidad inicial (más interfaces, adaptadores)
- Indirección adicional puede afectar rendimiento o debugging
- Curva de aprendizaje más pronunciada

## Concurrencia
La arquitectura facilita la implementación de concurrencia porque el núcleo está aislado de la infraestructura. La concurrencia se maneja en los adaptadores mediante colas de mensajes, eventos o threads.

## Patrones Relacionados
- **Domain-Driven Design (DDD)** - Para estructurar el dominio en el núcleo
- **Patrón Adaptador** - Los adaptadores implementan interfaces definidas en puertos
- **Microservicios** - Para diseñar servicios independientes con núcleo desunido de infraestructura

## Datos Importantes
- El nombre "hexagonal" refiere a la convención gráfica de representar el núcleo como un hexágono para múltiples puertos
- No siempre necesario en aplicaciones muy simples
- Puede ser sobre-arquitectura en proyectos pequeños