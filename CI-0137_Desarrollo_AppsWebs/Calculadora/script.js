// Estado de la calculadora
let current = '0',  // número que se está escribiendo
    history = '',   // expresión acumulada (ej: "3+5*")
    justCalc = false; // indica que el último resultado fue calculado

// Referencias a los elementos del display
const mainEl    = document.getElementById('main');
const historyEl = document.getElementById('history');

// Actualiza los dos displays con el estado actual
function update() {
  mainEl.textContent = current;
  mainEl.className = 'display-main' + (current.length > 9 ? ' small' : ''); // reduce fuente si es largo
  historyEl.textContent = history;
}

// Agrega un dígito al número actual
function inputNum(n) {
  if (justCalc) { current = n; history = ''; justCalc = false; } // empieza nuevo cálculo tras "="
  else current = current === '0' ? n : current + n; // reemplaza el "0" inicial
  update();
}

// Agrega el punto decimal si no existe ya
function inputDot() {
  if (justCalc) { current = '0.'; justCalc = false; }
  else if (!current.includes('.')) current += '.';
  update();
}

// Agrega un operador (+, -, *, /, %) a la expresión
function inputOp(op) {
  justCalc = false;
  const last = history.slice(-1);
  // Reemplaza el operador si el anterior ya era uno
  if (['+','-','*','/','.','%'].includes(last)) {
    history = history.slice(0,-1) + op;
  } else {
    history += current + op;
  }
  current = '0';
  update();
}

// Evalúa la expresión completa y muestra el resultado
function calculate() {
  if (!history) return;
  const expr = history + current;
  history = expr + ' =';
  try {
    // Usa Function para evaluar la expresión de forma segura en strict mode
    const res = Function('"use strict"; return (' + expr + ')')();
    current = parseFloat(res.toFixed(10)).toString(); // elimina imprecisiones flotantes
  } catch { current = 'ERROR'; }
  justCalc = true;
  update();
}

// Limpia todo y vuelve al estado inicial
function clearAll() { current = '0'; history = ''; justCalc = false; update(); }

// Borra el último carácter del número actual
function deleteLast() {
  if (justCalc) return;
  current = current.length > 1 ? current.slice(0,-1) : '0';
  update();
}

// Soporte de teclado para operar la calculadora sin mouse
document.addEventListener('keydown', e => {
  if ('0123456789'.includes(e.key)) inputNum(e.key);
  else if (e.key === '.') inputDot();
  else if (['+','-','*','/','%'].includes(e.key)) inputOp(e.key);
  else if (e.key === 'Enter' || e.key === '=') calculate();
  else if (e.key === 'Backspace') deleteLast();
  else if (e.key === 'Escape') clearAll();
});
