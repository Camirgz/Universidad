from abc import ABC, abstractmethod

# Observable
class SistemaNotificacion:
    def __init__(self):
        self._observers = []
        self._pedidos_listos = []
    
    def attach(self, observer):
        self._observers.append(observer)
    
    def detach(self, observer):
        self._observers.remove(observer)
    
    def notify(self, pedido):
        for observer in self._observers:
            observer.update(pedido)
    
    def agregar_pedido_listo(self, pedido):
        pedido.marcar_como_preparado()
        self._pedidos_listos.append(pedido)
        print(f"[Sistema]: Pedido listo para {pedido.cliente}")
        self.notify(pedido)

# Observer
class Observer(ABC):
    @abstractmethod
    def update(self, pedido):
        pass

# Observers concretos
class Cliente(Observer):
    def __init__(self, nombre):
        self.nombre = nombre
    
    def update(self, pedido):
        if pedido.cliente == self.nombre:
            print(f"Notificación para {self.nombre}: ¡Tu pedido está listo! - {pedido.get_descripcion()}")

class Barista:
    def preparar_bebida(self, pedido):
        bebidas = [p for p in pedido.productos if any(keyword in p.get_descripcion().lower() 
                  for keyword in ['café', 'té', 'espresso'])]
        
        for bebida in bebidas:
            print(f"[Barista]: Preparo bebida: {bebida.get_descripcion()}")
        
        return len(bebidas) > 0

class Pastelero:
    def preparar_alimento(self, pedido):
        alimentos = [p for p in pedido.productos if any(keyword in p.get_descripcion().lower() 
                    for keyword in ['croissant', 'tostada', 'muffin'])]
        
        for alimento in alimentos:
            print(f"[Pastelero]: Preparo alimento: {alimento.get_descripcion()}")
        
        return len(alimentos) > 0