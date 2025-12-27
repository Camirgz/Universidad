"""
NÚCLEO DEL DOMINIO - Lógica de Negocio Pura

Contiene las reglas de negocio sin depender de detalles técnicos externos.
Puede ser reutilizado por diferentes interfaces (web, CLI, API, etc.).
"""

class ServicioPrestamos:
    """
    Servicio de aplicación que orquesta el préstamo de libros.
    Solo depende de abstracciones (puertos), no de implementaciones concretas.
    """
    
    def __init__(self, repo_libros):
        # Inversión de dependencias - Recibe el repositorio como abstracción
        self.repo_libros = repo_libros

    def prestar_libro(self, id_libro):
        
        try:
            # Usa el puerto para obtener datos
            libro = self.repo_libros.obtener(id_libro)
            
            # Reglas de negocio - Corazón de la aplicación
            if libro["disponible"]:
                libro["disponible"] = False
                # Usa el puerto para persistir cambios
                self.repo_libros.actualizar(libro)
                return f"Libro '{libro['titulo']}' prestado correctamente."
            return "El libro no está disponible."
            
        except StopIteration:
            # Manejo de errores del dominio
            return f"Error: El libro con ID {id_libro} no existe."