# Sistema de Gestión de Viajes - Agencia de Viajes

## Descripción

Este proyecto es un sistema de gestión de viajes desarrollado en Java que permite a los usuarios y administradores realizar diversas operaciones relacionadas con reservas de viajes, paquetes turísticos, destinos y reseñas. El sistema incluye funcionalidades para:

- Gestión de usuarios (registro, autenticación, perfil)
- Reservas de viajes y paquetes turísticos
- Administración de destinos disponibles
- Creación y visualización de reseñas
- Historial de actividades de usuarios
- Panel de administración para gestión global

## Características principales

- **Autenticación de usuarios**: Sistema de login para usuarios y administradores
- **Gestión de reservas**: Creación, edición y eliminación de reservas
- **Paquetes turísticos**: Reserva de paquetes completos con servicios incluidos
- **Destinos**: Listado y búsqueda de destinos disponibles
- **Reseñas**: Sistema de valoraciones y comentarios
- **Historial**: Registro detallado de actividades de usuarios
- **Persistencia de datos**: Almacenamiento en archivos de texto

## Estructura del proyecto

El sistema está organizado en varias clases principales:

1. **Controladores**:
   - `ControlDestinos.java`: Gestiona destinos disponibles y seleccionados
   - `ControlPaquetes.java`: Maneja paquetes turísticos
   - `ControlReservas.java`: Administra las reservas de viajes
   - `ControlReseñas.java`: Gestiona las reseñas de usuarios
   - `ControlServicios.java`: Maneja servicios adicionales
   - `ControlUsuarios.java`: Controla la gestión de usuarios

2. **Clases principales**:
   - `Principal.java`: Clase principal que contiene la lógica del menú y flujo de la aplicación
   - `Historial.java`: Gestiona el registro de actividades de usuarios
   - `Sesion.java`: Maneja la sesión de usuarios autenticados

3. **Modelos**:
   - `Usuario.java`: Representa a los usuarios del sistema
   - `Administrador.java`: Representa a los administradores
   - `Reservas.java`: Modela las reservas de viajes
   - `Paquete.java`: Representa paquetes turísticos
   - `ServicioExtra.java`: Modela servicios adicionales
   - `Reseña.java`: Representa las reseñas de usuarios
   - `Destinos.java`: Modela los destinos de viaje

## Instalación y ejecución

1. **Requisitos**:
   - Java JDK 8 o superior
   - Sistema operativo compatible con Java

2. **Ejecución**:
   - Compilar todos los archivos `.java`:
     ```
     javac *.java
     ```
   - Ejecutar la clase principal:
     ```
     java Main
     ```

3. **Estructura de archivos**:
   - El sistema creará automáticamente un directorio `data/` para almacenar:
     - Usuarios registrados
     - Reservas
     - Paquetes
     - Destinos
     - Reseñas
     - Historial de actividades

## Uso

### Para usuarios:
1. Registrarse o iniciar sesión
2. Explorar destinos disponibles
3. Realizar reservas o paquetes turísticos
4. Gestionar reservas existentes
5. Crear y ver reseñas
6. Consultar historial de actividades

### Para administradores:
1. Iniciar sesión con credenciales de administrador
2. Ver todos los paquetes, reservas y reseñas
3. Gestionar historial de usuarios
4. Realizar limpieza de historiales

## Contribución

Este proyecto está abierto a contribuciones. Para sugerencias o reporte de problemas, por favor abra un issue en el repositorio.

## Licencia

Este proyecto está bajo licencia MIT. Ver el archivo LICENSE para más detalles.