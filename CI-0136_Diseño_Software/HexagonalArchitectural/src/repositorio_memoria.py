"""
ADAPTADOR  - Implementación en Memoria

Implementa el puerto RepositorioLibros usando una lista en memoria.
Puede ser reemplazado por implementaciones con SQL, APIs externas, archivos, etc.
"""

from repositorios import RepositorioLibros

class RepositorioLibrosMemoria(RepositorioLibros):
    """
    Adaptador de salida que almacena libros en memoria.
    El dominio no conoce los detalles de esta implementación.
    """
    
    def __init__(self):
        # Datos de ejemplo en memoria
        self.libros = [
            {"id": 1, "titulo": "1984", "disponible": True},
            {"id": 2, "titulo": "Cien años de soledad", "disponible": False},
        ]

    def obtener(self, id_libro):
        # Busca un libro por ID. Lanza StopIteration si no existe.
        return next(libro for libro in self.libros if libro["id"] == id_libro)

    def actualizar(self, libro):
        # Actualiza la información de un libro existente.
        for i, libro_existente in enumerate(self.libros):
            if libro_existente["id"] == libro["id"]:
                self.libros[i] = libro
                break