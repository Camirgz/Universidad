from datetime import datetime

class Pedido:
    def __init__(self, cliente, productos):
        self.cliente = cliente
        self.productos = productos
        self.fecha = datetime.now()
        self.estado = "pendiente"
        self.id = id(self)
    
    def get_total(self):
        return sum(producto.get_costo() for producto in self.productos)
    
    def get_descripcion(self):
        descripciones = [producto.get_descripcion() for producto in self.productos]
        return f"Pedido de {self.cliente}: {', '.join(descripciones)}"
    
    def marcar_como_preparado(self):
        self.estado = "preparado"
    
    def marcar_como_entregado(self):
        self.estado = "entregado"