from abc import ABC, abstractmethod

# Componente base
class Producto(ABC):
    @abstractmethod
    def get_descripcion(self):
        pass
    
    @abstractmethod
    def get_costo(self):
        pass

# Componentes concretos - Bebidas base
class Cafe(Producto):
    def get_descripcion(self):
        return "Café"
    
    def get_costo(self):
        return 2.50

class Te(Producto):
    def get_descripcion(self):
        return "Té"
    
    def get_costo(self):
        return 2.00

class Espresso(Producto):
    def get_descripcion(self):
        return "Espresso"
    
    def get_costo(self):
        return 3.00

# Componentes concretos - Alimentos base
class Croissant(Producto):
    def get_descripcion(self):
        return "Croissant"
    
    def get_costo(self):
        return 3.50

class Tostada(Producto):
    def get_descripcion(self):
        return "Tostada"
    
    def get_costo(self):
        return 2.50

class Muffin(Producto):
    def get_descripcion(self):
        return "Muffin"
    
    def get_costo(self):
        return 3.00

# Decorator base
class ExtraDecorator(Producto):
    def __init__(self, producto):
        self._producto = producto
    
    def get_descripcion(self):
        return self._producto.get_descripcion()
    
    def get_costo(self):
        return self._producto.get_costo()

# Decorators concretos para bebidas
class LecheDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " con leche"
    
    def get_costo(self):
        return self._producto.get_costo() + 0.50

class CanelaDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " y canela"
    
    def get_costo(self):
        return self._producto.get_costo() + 0.30

class CremaDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " con crema"
    
    def get_costo(self):
        return self._producto.get_costo() + 0.70

class DobleDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " doble"
    
    def get_costo(self):
        return self._producto.get_costo() + 1.50

# Decorators concretos para alimentos
class RellenoChocolateDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " con relleno de chocolate"
    
    def get_costo(self):
        return self._producto.get_costo() + 1.00

class ToppingDecorator(ExtraDecorator):
    def get_descripcion(self):
        return self._producto.get_descripcion() + " con topping"
    
    def get_costo(self):
        return self._producto.get_costo() + 0.80