<!DOCTYPE html>
<html>
<head>
    <title>Juego de Asteroides Gratis</title>
    <style>
        body { background: #111; color: #fff; font-family: monospace; text-align: center; margin: 0; padding: 10px; }
        canvas { border: 4px solid #00ff00; background: #000; display: block; margin: 10px auto; box-shadow: 0 0 20px #00ff00; }
        h1 { color: #00ff00; margin: 5px; font-size: 22px; text-shadow: 0 0 10px #00ff00; }
        .info { font-size: 16px; margin-bottom: 10px; color: #00ffff; }
    </style>
</head>
<body>
    <h1>🚀 NAVE VS ASTEROIDES 🚀</h1>
    <div class="info" id="hud">PUNTOS: 0 | VIDAS: ❤️❤️❤️</div>
    <canvas id="pantalla" width="400" height="400"></canvas>
    <p>🕹️ CONTROLES: Moverse con Flechas [⬅️ ➡️] | Disparar con [Espacio]</p>

    <script>
        const canvas = document.getElementById("pantalla");
        const ctx = canvas.getContext("2d");
        const hud = document.getElementById("hud");

        let naveX = 180, naveY = 340;
        let puntos = 0, vidas = 3;
        let balas = [], asteroides = [];
        let teclas = {};

        // Generar 4 asteroides en posiciones aleatorias arriba
        for(let i=0; i<4; i++) {
            asteroides.push({ x: Math.random()*360+10, y: Math.random()*-300, v: Math.random()*2+1.5 });
        }

        // Leer teclado real de tu PC
        window.addEventListener("keydown", e => { teclas[e.code] = true; if(e.code === "Space") e.preventDefault(); });
        window.addEventListener("keyup", e => teclas[e.code] = false);

        function juego() {
            if (vidas <= 0) {
                ctx.fillStyle = "#ff0000"; ctx.font = "bold 30px monospace";
                ctx.fillText("GAME OVER", 115, 180);
                ctx.fillStyle = "#ffffff"; ctx.font = "16px monospace";
                ctx.fillText("Refresca la pagina para reiniciar", 45, 220);
                return;
            }

            // Movimiento fluido de tu nave
            if (teclas["ArrowLeft"] && naveX > 0) naveX -= 5;
            if (teclas["ArrowRight"] && naveX < 360) naveX += 5;
            if (teclas["Space"]) {
                if (balas.length < 4) balas.push({ x: naveX + 18, y: naveY });
                teclas["Space"] = false; // Un disparo por cada pulsación
            }

            // Actualizar Marcador en tiempo real
            hud.innerHTML = `PUNTOS: ${puntos} | VIDAS: ${"❤️".repeat(vidas)}`;

            // Limpiar pantalla vieja
            ctx.clearRect(0, 0, 400, 400);

            // Dibujar tu Nave (Representando tu matriz original)
            ctx.fillStyle = "#00ff00";
            ctx.fillRect(naveX + 16, naveY, 8, 10); // Punta
            ctx.fillRect(naveX + 6, naveY + 10, 28, 10); // Cuerpo
            ctx.fillRect(naveX, naveY + 20, 40, 10); // Alas laterales

            // Mover y dibujar proyectiles
            ctx.fillStyle = "#ffff00";
            balas.forEach((b, index) => {
                b.y -= 7;
                ctx.fillRect(b.x, b.y, 4, 12);
                if(b.y < 0) balas.splice(index, 1);
            });

            // Mover y dibujar asteroides enemigos
            ctx.fillStyle = "#ff5555";
            asteroides.forEach((ast) => {
                ast.y += ast.v;
                // Dibujar forma de roca cuadrada retro
                ctx.fillRect(ast.x, ast.y, 22, 22);

                // Si cae al fondo, vuelve a aparecer arriba
                if(ast.y > 400) { ast.x = Math.random()*360; ast.y = -30; }

                // Detectar si tu disparo le dio al asteroide
                balas.forEach((b, bIndex) => {
                    if(b.x > ast.x && b.x < ast.x+22 && b.y > ast.y && b.y < ast.y+22) {
                        puntos += 10;
                        ast.x = Math.random()*360; ast.y = -40; // Reinicia roca
                        ast.v += 0.1; // Sube un poco la velocidad para dar dificultad
                        balas.splice(bIndex, 1); // Borra la bala
                    }
                });

                // Detectar si el asteroide chocó contra tu nave
                if(ast.x < naveX+40 && ast.x+22 > naveX && ast.y < naveY+30 && ast.y+22 > naveY) {
                    vidas--;
                    ast.x = Math.random()*360; ast.y = -40; // Reinicia roca tras daño
                }
            });

            requestAnimationFrame(juego);
        }
        juego();
    </script>
</body>
</html>
