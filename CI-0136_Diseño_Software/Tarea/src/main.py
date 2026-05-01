from models.productos import (
    Cafe, Te, Espresso, Croissant, Tostada, Muffin,
    LecheDecorator, CanelaDecorator, CremaDecorator, 
    DobleDecorator, RellenoChocolateDecorator, ToppingDecorator
)
from models.pedidos import Pedido
from models.notificaciones import SistemaNotificacion, Cliente, Barista, Pastelero

def simular_cafeteria():
    print("**Simulación de cafetería ---**\n")
    
    # Inicializar sistema
    sistema_notificacion = SistemaNotificacion()
    barista = Barista()
    pastelero = Pastelero()
    
    # Crear clientes y registrarlos como observers
    ana = Cliente("Ana")
    carlos = Cliente("Carlos")
    
    sistema_notificacion.attach(ana)
    sistema_notificacion.attach(carlos)
    
    # Pedido de Ana
    print("Cliente: Ana")
    
    # Café con leche y canela
    cafe_ana = Cafe()
    cafe_ana = LecheDecorator(cafe_ana)
    cafe_ana = CanelaDecorator(cafe_ana)
    print(f"Ordena un {cafe_ana.get_descripcion()}")
    
    # Croissant con relleno de chocolate
    croissant_ana = Croissant()
    croissant_ana = RellenoChocolateDecorator(croissant_ana)
    print(f"Ordena un {croissant_ana.get_descripcion()}\n")
    
    pedido_ana = Pedido("Ana", [cafe_ana, croissant_ana])
    
    # Pedido de Carlos
    print("Cliente: Carlos")
    
    # Té verde
    te_carlos = Te()
    print(f"Ordena un {te_carlos.get_descripcion()}")
    
    # Café doble espresso con crema
    espresso_carlos = Espresso()
    espresso_carlos = DobleDecorator(espresso_carlos)
    espresso_carlos = CremaDecorator(espresso_carlos)
    print(f"Ordena un {espresso_carlos.get_descripcion()}\n")
    
    pedido_carlos = Pedido("Carlos", [te_carlos, espresso_carlos])
    
    # Procesar pedidos
    print("--- Procesando pedidos ---")
    
    # Preparar pedido de Ana
    barista.preparar_bebida(pedido_ana)
    pastelero.preparar_alimento(pedido_ana)
    sistema_notificacion.agregar_pedido_listo(pedido_ana)
    
    print()
    
    # Preparar pedido de Carlos
    barista.preparar_bebida(pedido_carlos)
    # Carlos no ordenó alimentos, así que no llamamos al pastelero
    sistema_notificacion.agregar_pedido_listo(pedido_carlos)
    
    print("\n--- Resumen de pedidos ---")
    print(f"Total de Ana: ${pedido_ana.get_total():.2f}")
    print(f"Total de Carlos: ${pedido_carlos.get_total():.2f}")

if __name__ == "__main__":
    simular_cafeteria()