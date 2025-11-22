   <img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/3af7b134-8e9e-4a75-99c4-02b5c4c30655" />
 


HITO 1 – Investigación y Storyboard
1.	Investigación de casos reales (mínimo 6)
Casos de decisiones tomadas por IA (2 casos):
-ChatGPT en educación universitaria (UNESCO, 2023): Se reporta que el uso de IA en la redacción de ensayos facilita la productividad, pero reduce la práctica del pensamiento crítico cuando no se enseña a cuestionar los resultados.
-Conducción autónoma de Tesla (2022): Un caso en EE. UU. mostró cómo el piloto automático tomó decisiones rápidas, pero generó un accidente por no evaluar adecuadamente un escenario imprevisto.
Casos de decisiones tomadas solo por humanos (2 casos):
3. Cirugía de emergencia en Perú (2021): Un equipo médico decidió realizar una operación de urgencia sin apoyo de IA, priorizando la experiencia práctica y el criterio clínico.
4. Decisión judicial en España (2019): Un juez resolvió un caso de custodia familiar considerando factores emocionales y sociales imposibles de evaluar con un algoritmo.
Casos de colaboración IA + humanos (2 casos):
5. Diagnóstico médico con IA (Mayo Clinic, 2023): Microsoft afirma estar un paso más cerca de la superinteligencia médica, después de que una nueva herramienta de inteligencia artificial (IA) superara a los médicos en el diagnóstico de problemas médicos complejos. Los gigantes tecnológicos se apresuran a desarrollar la superinteligencia, es decir, un sistema de IA que supere en todos los aspectos las capacidades intelectuales humanas, y prometen utilizarla para trastocar los sistemas sanitarios de todo el mundo.

6. Propuesta educativa en Corea del Sur (2024): Corea del Sur está implementando IA mediante la aprobación de su Ley Básica de IA en diciembre de 2024, que busca un desarrollo seguro y ético mientras impulsa la innovación, la cual entrará en vigor en enero de 2026. El país también está invirtiendo en infraestructura, con Samsung desarrollando chips de IA y Hyundai invirtiendo en semiconductores, y está aplicando la IA en el sector educativo, la industria de la belleza y la defensa. 
Conclusiones preliminares:
•	La IA ofrece rapidez, eficiencia y análisis masivo de datos, pero puede fallar en contextos ambiguos o imprevistos.
•	El humano aporta creatividad, empatía y flexibilidad, pero se limita en velocidad y manejo de grandes volúmenes de información.
•	El modelo colaborativo potencia lo mejor de ambos, aunque genera tensiones en la confianza y en la definición de roles.
________________________________________
2.	Storyboard narrativo y visual (versión inicial)

Mundo 1 – IA: “La Máquina Suprema”
•	Contexto: Algoritmos rígidos controlan el entorno, enemigos repetitivos, alta eficiencia, pero sin libertad.
•	Interacciones:
o	Confianza en datos vs desconfianza en resultados.
o	Cooperación obligada con un aliado-robot.
•	Pregunta reflexiva inicial: ¿Hasta qué punto delegarías tus decisiones en una máquina?
Mundo 2 – Humano: “La Luz del Pensamiento”
•	Contexto: Recursos limitados, sin automatización. Todo se aprende por prueba y error.
•	Interacciones:
o	Vulnerabilidad frente a enemigos más fuertes.
o	Intercambio de información con un aliado sabio.
•	Pregunta reflexiva inicial: ¿Prefieres equivocarte por ti mismo antes que dejar que una máquina decida?
Mundo 3 – Colaborativo: “El Puente del Futuro”
•	Contexto: IA y humanos coexisten, pero con tensiones. Existen mecánicas mixtas.
•	Interacciones:
o	Ambigüedad moral de un personaje que puede traicionar.
o	Transformación de roles: un enemigo se convierte en aliado.
•	Pregunta reflexiva inicial: ¿Es posible equilibrar confianza en la IA y pensamiento crítico humano?
Propuesta de mensaje final crítico:
“Ni la máquina ni el humano, sino la colaboración consciente permite un futuro sostenible y justo”.
________________________________________
3.	Diagrama de clases UML (versión inicial)
```classDiagram
class Juego {
+mundo actual
-Ejecutar()
}
class Entidad{
+posX:int
+posY:int
-setVida():void
-mover(int dx, int dy):void
-getPosX():int
-getPosY():int
-mostrar():void
}
class Mundo {
+Nombre:string 
-getLimiteX():int
-getLimiteY():int
-int enemigoseliminados()
-generarEnemigos()
-verificarColisiones()
}
class Enemigos {
-disparar():Proyectil   
-dano():int
-cooldownDisparo():void
-moverAutomatico()

}
class Jugador {
-disparar():Proyectil   
-dano():int
-cooldownDisparo():void
}
class Proyectil {
+posX:int
+posY:int
-mover()
-getPosX():int
-getPosY():int
-getDano():int

}
class aliado {
+string Ayuda
-ayudar(Jugador* jugador)
}

Juego<--Mundo
Entidad-->Jugador
Entidad-->aliado
Entidad-->Enemigos
Mundo<--Entidad
Proyectil<--Jugador
Proyectil<--Enemigos
```

4.	Plan de actividades (Versión inicial – ejemplo)
<img width="665" height="331" alt="image" src="https://github.com/user-attachments/assets/d923e90c-99b9-41df-bc82-45b65b00970d" />




