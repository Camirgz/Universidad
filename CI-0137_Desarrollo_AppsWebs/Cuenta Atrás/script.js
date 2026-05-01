// Lee la fecha final desde el atributo data-fecha del contenedor
const contenedor = document.querySelector('.contador');
let fechaFinal = new Date(contenedor.dataset.fecha);

// Actualiza la fecha destino cuando el usuario elige una nueva
function cambiarFecha() {
  const valor = document.getElementById('inputFecha').value;
  if (!valor) return;
  fechaFinal = new Date(valor);
  contenedor.dataset.fecha = valor;
}

// Rellena con cero a la izquierda si el número es menor a 10
function pad(n) { return String(n).padStart(2, '0'); }

// Calcula el tiempo restante y actualiza los elementos del DOM
function actualizar() {
  const ahora = new Date();
  const diff = fechaFinal - ahora;

  // Si la fecha ya pasó, mostrar ceros en todo
  if (diff <= 0) {
    document.getElementById('dias').textContent    = '00';
    document.getElementById('horas').textContent   = '00';
    document.getElementById('minutos').textContent = '00';
    document.getElementById('segundos').textContent = '00';
    return;
  }

  // Calcula días, horas, minutos y segundos restantes
  const dias    = Math.floor(diff / (1000 * 60 * 60 * 24));
  const horas   = Math.floor((diff % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
  const minutos = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
  const segundos = Math.floor((diff % (1000 * 60)) / 1000);

  document.getElementById('dias').textContent     = pad(dias);
  document.getElementById('horas').textContent    = pad(horas);
  document.getElementById('minutos').textContent  = pad(minutos);
  document.getElementById('segundos').textContent = pad(segundos);
}

// Referencia al intervalo para poder detenerlo
let intervalo = null;

// Detiene o reanuda la cuenta atrás
function detener() {
  const btn = document.querySelector('.btn-stop');
  if (intervalo) {
    clearInterval(intervalo);
    intervalo = null;
    btn.textContent = 'Reanudar';
  } else {
    intervalo = setInterval(actualizar, 1000);
    btn.textContent = 'Detener';
  }
}

// Ejecuta de inmediato y luego cada segundo
actualizar();
intervalo = setInterval(actualizar, 1000);
