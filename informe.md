classDiagram
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
