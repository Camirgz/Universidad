import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

# Configuración de estilo
plt.style.use('seaborn-v0_8')
sns.set_palette("husl")

# Datos de rendimiento
datos = {
    'Implementación': ['pthreads', 'optimized', 'openMP', 'MPI'],
    'Tiempo (segundos)': [406, 54, 56.46, 12.36]
}

df = pd.DataFrame(datos)

# Crear figura con múltiples subplots
fig, axes = plt.subplots(2, 2, figsize=(15, 12))
fig.suptitle('Análisis Comparativo de Rendimiento\nTiempo de Ejecución por Implementación',
             fontsize=16, fontweight='bold')

# Gráfico 1: Gráfico de barras básico
ax1 = axes[0, 0]
bars = ax1.bar(df['Implementación'], df['Tiempo (segundos)'],
               color=['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4'])
ax1.set_title('Tiempo de Ejecución por Implementación', fontweight='bold')
ax1.set_ylabel('Tiempo (segundos)')
ax1.set_xlabel('Implementación')

# Agregar valores en las barras
for bar, valor in zip(bars, df['Tiempo (segundos)']):
    height = bar.get_height()
    ax1.text(bar.get_x() + bar.get_width()/2., height + height*0.01,
             f'{valor}s', ha='center', va='bottom', fontweight='bold')

# Gráfico 2: Speedup relativo (usando pthreads como baseline)
ax2 = axes[0, 1]
baseline = df['Tiempo (segundos)'].iloc[0]  # pthreads como baseline
speedup = baseline / df['Tiempo (segundos)']

bars_speedup = ax2.bar(df['Implementación'], speedup,
                       color=['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4'])
ax2.set_title('Speedup Relativo (vs pthreads)', fontweight='bold')
ax2.set_ylabel('Factor de Aceleración')
ax2.set_xlabel('Implementación')
ax2.axhline(y=1, color='red', linestyle='--', alpha=0.7, label='Baseline (pthreads)')
ax2.legend()

# Agregar valores de speedup
for bar, valor in zip(bars_speedup, speedup):
    height = bar.get_height()
    ax2.text(bar.get_x() + bar.get_width()/2., height + height*0.01,
             f'{valor:.1f}x', ha='center', va='bottom', fontweight='bold')

# Gráfico 3: Gráfico de pastel para mostrar distribución de tiempo
ax3 = axes[1, 0]
colores = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4']
wedges, texts, autotexts = ax3.pie(df['Tiempo (segundos)'],
                                   labels=df['Implementación'],
                                   autopct='%1.1f%%',
                                   colors=colores,
                                   startangle=90)
ax3.set_title('Distribución Porcentual del Tiempo de Ejecución', fontweight='bold')

# Mejorar la legibilidad del texto en el gráfico de pastel
for autotext in autotexts:
    autotext.set_color('white')
    autotext.set_fontweight('bold')

# Gráfico 4: Gráfico de líneas para mostrar la progresión
ax4 = axes[1, 1]
# Reordenar para mostrar progresión lógica
orden_logico = ['pthreads', 'optimized', 'openMP', 'MPI']
tiempos_ordenados = [datos['Tiempo (segundos)'][datos['Implementación'].index(impl)] for impl in orden_logico]

ax4.plot(orden_logico, tiempos_ordenados, marker='o', linewidth=3, markersize=8, color='#2E86AB')
ax4.fill_between(orden_logico, tiempos_ordenados, alpha=0.3, color='#2E86AB')

ax4.set_title('Evolución del Rendimiento por Tecnología', fontweight='bold')
ax4.set_ylabel('Tiempo de Ejecución (segundos)')
ax4.set_xlabel('Implementación')
ax4.grid(True, alpha=0.7)

# Agregar valores en cada punto
for i, (impl, tiempo) in enumerate(zip(orden_logico, tiempos_ordenados)):
    ax4.annotate(f'{tiempo}s', (i, tiempo), textcoords="offset points",
                xytext=(0,10), ha='center', fontweight='bold')

plt.tight_layout()
plt.show()