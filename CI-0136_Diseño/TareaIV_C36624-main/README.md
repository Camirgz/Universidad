# Sistema de Gestión de Pedidos para Cafetería
# Tarea 4 - Camila Rodríguez - C36624

## Descripción
Sistema completo para gestionar pedidos en una cafetería que permite ordenar bebidas y alimentos personalizados, prepararlos y notificar a los clientes cuando están listos.

## Patrones de Diseño Implementados

### 1. Patrón Decorator
**Ubicación**: `models/productos.py`

**Justificación**:
- Permite agregar dinámicamente responsabilidades (extras) a los productos base sin modificar su estructura
- Facilita la personalización de bebidas y alimentos con diferentes combinaciones de ingredientes
- Ejemplo: Un `Cafe` base puede decorarse con `LecheDecorator` y `CanelaDecorator` para crear "Café con leche y canela"

**Ventajas**:
- Flexibilidad para crear combinaciones ilimitadas
- Cumple con el principio Open/Closed (abierto para extensión, cerrado para modificación)
- Código mantenible y escalable

### 2. Patrón Observer
**Ubicación**: `models/notificaciones.py`

**Justificación**:
- Permite que múltiples clientes (observers) sean notificados cuando sus pedidos están listos
- El sistema de notificación (subject) mantiene una lista de observers y los notifica automáticamente
- Separación clara entre la lógica de preparación y la notificación

**Ventajas**:
- Acoplamiento débil entre subject y observers
- Fácil agregar nuevos tipos de notificaciones
- Los clientes pueden registrarse/deregistrarse dinámicamente


....