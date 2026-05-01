const { useState, useEffect, useCallback } = React;

// Datos de cada slide: imagen, título, descripción y query de búsqueda
const SLIDES = [
  {
    id: 1,
    src: "https://images.unsplash.com/photo-1518105779142-d975f22f1b0a?w=700&auto=format",
    title: "Volcán Arenal",
    desc: "Icono de Costa Rica, rodeado de selva exuberante y aguas termales.",
    query: "Volcan Arenal Costa Rica"
  },
  {
    id: 2,
    src: "https://images.unsplash.com/photo-1580676875879-f20086f1e729?w=700&auto=format",
    title: "Playa Manuel Antonio",
    desc: "Una de las playas más hermosas, dentro del parque nacional.",
    query: "Playa Manuel Antonio Costa Rica"
  },
  {
    id: 3,
    src: "https://images.unsplash.com/photo-1464822759023-fed622ff2c3b?w=700&auto=format",
    title: "Monteverde",
    desc: "El bosque nuboso más famoso de Centroamérica.",
    query: "Monteverde bosque nuboso Costa Rica"
  },
  {
    id: 4,
    src: "https://images.unsplash.com/photo-1566073771259-6a8506099945?w=700&auto=format",
    title: "Tortuguero",
    desc: "Paraíso de tortugas marinas en el Caribe costarricense.",
    query: "Tortuguero Costa Rica canales"
  },
  {
    id: 5,
    src: "https://images.unsplash.com/photo-1528360983277-13d401cdc186?w=700&auto=format",
    title: "Volcán Poás",
    desc: "Cráter volcánico activo con una laguna de color turquesa.",
    query: "Volcan Poas Costa Rica crater"
  },
  {
    id: 6,
    src: "https://images.unsplash.com/photo-1644334599979-6c7b4d55920e?w=700&auto=format",
    title: "Perezoso Tití",
    desc: "El perezoso de tres dedos, símbolo de la vida silvestre tica.",
    query: "perezoso Costa Rica sloth"
  },
  {
    id: 7,
    src: "https://images.unsplash.com/photo-1502741338009-cac2772e18bc?w=700&auto=format",
    title: "Rana Venenosa",
    desc: "La rana dardo, un ícono colorido de la biodiversidad tropical.",
    query: "rana venenosa Costa Rica poison dart frog"
  },
  {
    id: 8,
    src: "https://images.unsplash.com/photo-1501854140801-50d01698950b?w=700&auto=format",
    title: "Selva Tropical",
    desc: "Costa Rica alberga el 6% de la biodiversidad del planeta.",
    query: "selva tropical Costa Rica biodiversidad"
  },
  {
    id: 9,
    src: "https://images.unsplash.com/photo-1534430480872-3498386e7856?w=700&auto=format",
    title: "Quetzal Resplendente",
    desc: "Ave sagrada de los mayas, vive en los bosques nubosos de altura.",
    query: "quetzal resplendente Costa Rica bird"
  },
  {
    id: 10,
    src: "https://images.unsplash.com/photo-1506905925346-21bda4d32df4?w=700&auto=format",
    title: "Playa Nosara",
    desc: "Destino de surf y yoga, una de las playas más lindas del Pacífico.",
    query: "Playa Nosara Costa Rica surf"
  }
];

function Carousel() {
  // Índice del slide actualmente visible
  const [idx, setIdx] = useState(0);

  // Navega al slide anterior (circular)
  const prev = useCallback(() => setIdx(i => (i - 1 + SLIDES.length) % SLIDES.length), []);
  // Navega al slide siguiente (circular)
  const next = useCallback(() => setIdx(i => (i + 1) % SLIDES.length), []);

  // Autoplay: avanza automáticamente cada 5 segundos
  useEffect(() => {
    const t = setInterval(next, 5000);
    return () => clearInterval(t); // limpia el intervalo al desmontar
  }, [next]);

  // Navegación con teclas de flecha
  useEffect(() => {
    const h = e => { if (e.key === 'ArrowLeft') prev(); if (e.key === 'ArrowRight') next(); };
    window.addEventListener('keydown', h);
    return () => window.removeEventListener('keydown', h);
  }, [prev, next]);

  const slide = SLIDES[idx];

  // Abre una búsqueda de Google sobre el lugar actual
  const openSearch = () => {
    window.open(`https://www.google.com/search?q=${encodeURIComponent(slide.query)}`, '_blank');
  };

  return (
    <div className="page">
      <h1>
        Costa Rica 🌿
        <small>Pura Vida · haz clic en la imagen para buscar</small>
      </h1>

      {/* Imagen principal — clic abre Google */}
      <div className="stage">
        <div className="img-wrap" onClick={openSearch} title={`Buscar: ${slide.query}`}>
          <img src={slide.src} alt={slide.title} key={slide.id} />
          <div className="search-hint">🔍 Google</div>
        </div>

        {/* Título, descripción y contador de slide */}
        <div className="info">
          <div>
            <h2>{slide.title}</h2>
            <p>{slide.desc}</p>
          </div>
          <div className="counter">
            {String(idx + 1).padStart(2, '0')}
            <span>/{SLIDES.length}</span>
          </div>
        </div>

        {/* Botones de navegación anterior / siguiente */}
        <div className="nav">
          <button className="btn" onClick={prev} aria-label="Anterior">◀</button>
          <button className="btn" onClick={next} aria-label="Siguiente">▶</button>
        </div>
      </div>

      {/* Miniaturas clicables para saltar directamente a un slide */}
      <div className="thumbs">
        {SLIDES.map((s, i) => (
          <div
            key={s.id}
            className={`thumb${i === idx ? ' active' : ''}`}
            onClick={() => setIdx(i)}
          >
            <img src={s.src} alt={s.title} />
          </div>
        ))}
      </div>

      <p className="hint">← → teclado · autoplay cada 5s · CI-0137</p>
    </div>
  );
}

// Monta el componente en el div#root
ReactDOM.createRoot(document.getElementById('root')).render(<Carousel />);
