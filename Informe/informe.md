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
```
classDiagram
    direction TB


    class MainMenuForm {
        +MainMenuForm()
        -Label lblTitle
        -Button btnPlay
        -Button btnRules
        -Button btnCredits
        -Button btnExit
        +btnPlay_Click()
        +btnRules_Click()
        +btnCredits_Click()
        +btnExit_Click()
    }

    class RulesForm {
        +RulesForm()
        -Label lblTitle
        -RichTextBox txtRules
        -Button btnBack
        +btnBack_Click()
    }

    class CreditsForm {
        +CreditsForm()
        -Label lblTitle
        -Label lblCredits
        -Button btnBack
        +btnBack_Click()
    }

    class IntroForm {
        +IntroForm()
        -PictureBox picGif
        -Label lblStory
        -Timer typewriterTimer
        -String fullText
        -int currentCharIndex
        +typewriterTimer_Tick()
        +IntroForm_KeyDown()
    }

    class GameForm {
        +GameForm()
        -PictureBox gameCanvas
        -Timer gameTimer
        -Bitmap mapImage
        -Bitmap characterSprite
        -List~Orb~ orbs
        -Portal portal
        -float playerX
        -float playerY
        -float currentTime
        +GameTimer_Tick()
        +GameCanvas_Paint()
        +CheckCollision()
        +CheckOrbCollection()
        +CheckPortalEntry()
        +LoadSecondMap()
        +InitializeGame()
    }

    class TransitionForm {
        +TransitionForm()
        -Label lblStory
        -Timer typewriterTimer
        -Timer autoCloseTimer
        -String fullText
        +typewriterTimer_Tick()
        +autoCloseTimer_Tick()
    }

    class Orb {
        +float x
        +float y
        +bool collected
        +float velocityX
        +float velocityY
        +float targetX
        +float targetY
        +float moveTimer
        +UpdateMovement()
        +SetRandomTarget()
    }

    class Portal {
        +float x
        +float y
        +bool isActive
        +float animPhase
    }

    MainMenuForm --> GameForm : 
    MainMenuForm --> RulesForm : 
    MainMenuForm --> CreditsForm : 
    MainMenuForm --> IntroForm : 

    IntroForm --> GameForm : 

    GameForm --> TransitionForm : 
    GameForm --> Orb : 
    GameForm --> Portal : 


```

4.	Plan de actividades (Versión inicial – ejemplo)
   
| N° | Actividad | Responsable | Estado s11 | Estado s12 | Estado s13 | Estado s14 | Observaciones |
|----|-----------|-------------|------------|------------|------------|------------|---------------|
| 1 | Diseño del diagrama de clase | Miguel | X | | | | En proceso |
| 2 | Prototipo de la solución | Miguel | | | | | En proceso |
| 3 | Definir interface del videojuego | Lucas | X | | | | En proceso |
| 4 | Definir estructura de datos | Lucas | | | | | En proceso |
| 5 | Implementar herencia | Miguel | X | | | | En proceso |
| 6 | Clase controladora | Miguel | | | | | En proceso |
| 7 | Elaborar el menú | Justin | | | | | En proceso |
| 8 | Clases complementarias | Miguel | | | | | En proceso |
| 9 | Gestión archivos | Justin | | | | | En proceso |
| 10 | Integrar clases complementarias al proyecto | Miguel | | | | | En proceso |
| 11 | Pruebas integrales | Miguel | | | | | En proceso |
| 12 | Redactar el informe | Lucas | | | | | En proceso |
| 13 | Preparar la exposición | Justin | | | | | En proceso |






