"""
PUNTO DE ENTRADA PRINCIPAL - Adaptador Primario

Conecta la aplicación con el "mundo exterior" importando las dependencias.
Este archivo actúa como el que ensambla todos los componentes.
"""

from servicio_prestamos import ServicioPrestamos
from repositorio_memoria import RepositorioLibrosMemoria

# Configuración de dependencias: Puerto + Adaptador concreto
repo = RepositorioLibrosMemoria()
servicio = ServicioPrestamos(repo)

# Ejecución de casos de uso - Simula llamadas desde el exterior
print(servicio.prestar_libro(1))  
print(servicio.prestar_libro(2))  
print(servicio.prestar_libro(3))  