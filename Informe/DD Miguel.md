Evaluación de Desempeño – Proyecto del Videojuego IA vs Pensamiento Crítico
Autor: Miguel Málaga
Formato: Markdown

1. Introducción

El proyecto nace de la necesidad de crear un videojuego que combine lógica, exploración, habilidades de pensamiento crítico y una temática narrativa centrada en la interacción entre la IA y el razonamiento humano.

La solución propuesta fue el desarrollo de un videojuego en C++ (Windows Forms) que integra:

Menú principal y secciones informativas (Reglas, Créditos, Intro).

Gameplay con movimiento fluido, colisiones, recolección de orbes y tiempo límite.

Dos mapas jugables con diferentes estructuras.

Transiciones narrativas con efectos visuales.

Sprites personalizados creados para el personaje, orbes y portal.

El resultado es un prototipo funcional y narrativo, respaldado por código completo, sprites propios y un informe técnico detallado.

2. Objetivos

🎯 Objetivo General

Desarrollar un videojuego que presente mecánicas de navegación, toma de decisiones, recolección de objetos y presión temporal, integradas en una narrativa sobre IA y pensamiento crítico.

📌 Objetivos Específicos

Crear e integrar un menú dinámico con pantallas informativas.

Implementar movimiento, animación y colisiones del personaje.

Programar orbes móviles con comportamiento autónomo.

Diseñar e integrar sprites personalizados.

Incluir un sistema de tiempo límite por nivel.

Implementar un portal que habilite la progresión.

Crear dos mapas independientes con dificultad escalonada.

Documentar todo en un informe técnico.

Entregar código, sprites y documentación completa.

3. Desarrollo del Proyecto
🛠️ Herramientas Utilizadas

C++ – CLR / Windows Forms

Visual Studio 2022

System::Drawing (renderizado 2D)

Timers, eventos, Graphics, sprites personalizados

Entregables del Proyecto

Tipo	Descripción
Código Fuente	Sistema de menús, gameplay, colisiones, animaciones, orbes, portal, transiciones y renderizado.
Sprites Usados	Personaje animado, orbes con gradiente, portal dinámico, mapas.
Informe Detallado	Documentación técnica sobre diseño, arquitectura, decisiones y resultados del proyecto.
🚧 Retos Encontrados

Implementar un sistema de colisiones basado en tiles y pixel sampling.

Gestionar movimiento autónomo de orbes con destinos aleatorios.

Evitar posiciones inválidas del jugador y objetos en paredes.

Sincronizar animaciones con Timers (60 FPS aprox).

Crear efectos visuales como:

pulso luminiscente,

sombras dinámicas,

gradientes,

partículas,

transición tipo “máquina de escribir”.

Integrar dos mapas completamente funcionales con tiempos distintos.

🧾 Evidencias del Desarrollo

Archivos de código:

MenuSystem.h

GameForm.h

main.cpp

Sprites generados manualmente con Graphics.

Capturas visuales del juego en funcionamiento (mapas, portal, orbes).

Flujo completo del juego:
Menú → Intro → Nivel 1 → Transición → Nivel 2 → Final.

Implementación real de efectos y mecánicas descritas en el informe.

🟩 4. Conclusiones

El proyecto cumplió todos los objetivos planteados, entregando un videojuego funcional con:

Mecánicas completas (movimiento, colisiones, orbes, portal).

Narrativa coherente con la temática IA vs pensamiento crítico.

Interfaz amigable y secuencias de introducción, reglas y créditos.

Sprites y efectos visuales creados especialmente para el proyecto.

Arquitectura de código organizada y separada por módulos.

El desarrollo permitió reforzar competencias de programación, diseño visual, lógica de videojuegos y documentación técnica, demostrando un desempeño sólido en el manejo de herramientas y resolución de problemas.
