"""
CONTRATOS/PUERTOS - Interfaces del Sistema

Define las operaciones que el dominio necesita, sin especificar cómo se implementan.
Estas interfaces permiten cambiar la tecnología subyacente sin afectar el núcleo.
"""

class RepositorioLibros:
    """
    Puerto de salida - Operaciones necesarias para gestionar libros.
    Cualquier adaptador debe implementar estos métodos.
    """
    
    def obtener(self, id_libro):
        # Obtiene un libro por su ID.
        raise NotImplementedError
    
    def actualizar(self, libro):
        # Actualiza la información de un libro.
        raise NotImplementedError