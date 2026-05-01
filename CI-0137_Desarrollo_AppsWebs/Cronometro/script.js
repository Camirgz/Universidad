// Referencias al canvas y constantes del reloj
const canvas = document.getElementById('clock');
const ctx    = canvas.getContext('2d');
const cx = 150, cy = 150, R = 138; // centro y radio del círculo

// Estado del cronómetro
let elapsed = 0, startTime = null, running = false, animId = null, laps = [];

// Rellena con ceros a la izquierda (ej: 5 → "05")
function pad(n, d=2) { return String(Math.floor(n)).padStart(d,'0'); }

// Convierte milisegundos a formato HH:MM:SS.d
function formatTime(ms) {
  const h = ms/3600000|0, m = (ms%3600000)/60000|0,
        s = (ms%60000)/1000|0, t = (ms%1000)/100|0;
  return `${pad(h)}:${pad(m)}:${pad(s)}.${t}`;
}

// Dibuja el reloj analógico completo en el canvas
function drawClock(ms) {
  ctx.clearRect(0,0,300,300);

  // Fondo del reloj
  ctx.beginPath(); ctx.arc(cx,cy,R,0,Math.PI*2);
  ctx.fillStyle = '#ffffff'; ctx.fill();
  ctx.strokeStyle = '#cccccc'; ctx.lineWidth = 2; ctx.stroke();

  // Marcas de minutos (mayores cada 5)
  for (let i=0; i<60; i++) {
    const a = (i/60)*Math.PI*2 - Math.PI/2;
    const isMaj = i%5===0;
    const r1 = isMaj ? R-14 : R-8;
    ctx.beginPath();
    ctx.moveTo(cx + Math.cos(a)*(R-2), cy + Math.sin(a)*(R-2));
    ctx.lineTo(cx + Math.cos(a)*r1,    cy + Math.sin(a)*r1);
    ctx.strokeStyle = isMaj ? '#555555' : '#cccccc';
    ctx.lineWidth = isMaj ? 2 : 1;
    ctx.stroke();
    // Números en las marcas mayores
    if (isMaj) {
      const num = i===0 ? 60 : i/5;
      ctx.font = '11px Arial';
      ctx.fillStyle = '#555555';
      ctx.textAlign = 'center'; ctx.textBaseline = 'middle';
      ctx.fillText(num, cx + Math.cos(a)*(R-26), cy + Math.sin(a)*(R-26));
    }
  }

  // Ángulos de las agujas según el tiempo transcurrido
  const totalSec = ms/1000;
  const minAngle = (totalSec/60)%1 * Math.PI*2 - Math.PI/2; // vuelta completa cada 60s
  const secAngle = totalSec%60 / 60 * Math.PI*2 - Math.PI/2;

  drawNeedle(ctx, cx, cy, minAngle, R-50, 3, '#444444');
  drawNeedle(ctx, cx, cy, secAngle, R-20, 2, '#3a7bc8');

  // Punto central
  ctx.beginPath(); ctx.arc(cx,cy,6,0,Math.PI*2);
  ctx.fillStyle='#3a7bc8'; ctx.fill();
  ctx.beginPath(); ctx.arc(cx,cy,3,0,Math.PI*2);
  ctx.fillStyle='#fff'; ctx.fill();
}

// Dibuja una aguja del reloj
function drawNeedle(ctx,cx,cy,angle,len,w,color) {
  ctx.beginPath();
  ctx.moveTo(cx - Math.cos(angle)*20, cy - Math.sin(angle)*20); // pequeña cola
  ctx.lineTo(cx + Math.cos(angle)*len, cy + Math.sin(angle)*len);
  ctx.strokeStyle = color; ctx.lineWidth = w;
  ctx.lineCap = 'round'; ctx.stroke();
}

// Bucle de animación: actualiza el tiempo y redibuja cada frame
function loop(ts) {
  elapsed = (performance.now() - startTime);
  document.getElementById('digital').textContent = formatTime(elapsed);
  drawClock(elapsed);
  animId = requestAnimationFrame(loop);
}

// Alterna entre iniciar y pausar el cronómetro
function toggleStart() {
  if (!running) {
    startTime = performance.now() - elapsed; // conserva el tiempo acumulado al reanudar
    running = true;
    document.getElementById('btnStart').textContent = 'PAUSE';
    animId = requestAnimationFrame(loop);
  } else {
    cancelAnimationFrame(animId);
    running = false;
    document.getElementById('btnStart').textContent = 'START';
  }
}

// Reinicia todo el cronómetro al estado inicial
function resetTimer() {
  cancelAnimationFrame(animId);
  running = false; elapsed = 0; laps = [];
  startTime = null;
  document.getElementById('btnStart').textContent = 'START';
  document.getElementById('digital').textContent = '00:00:00.0';
  document.getElementById('laps').innerHTML = '';
  drawClock(0);
}

// Guarda el tiempo actual como vuelta y lo muestra en la lista
function addLap() {
  if (!running) return;
  const t = formatTime(elapsed);
  laps.push(t);
  const div = document.createElement('div');
  div.className = 'lap-item';
  div.innerHTML = `<span>Vuelta ${laps.length}</span><span>${t}</span>`;
  document.getElementById('laps').prepend(div); // más reciente arriba
}

// Dibuja el reloj en reposo al cargar la página
drawClock(0);
