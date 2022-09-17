# Simulacion-Banco
Simula la operación de un banco donde existen tres tipos de usuarios: usuarios (personas sin cuenta en el banco), clientes (personas con una cuneta en el banco) y preferentes (personas con mayor prioridad para ser atendidos). Se emplean Colas de prioridades para la atención de clientes, donde se atenderán a 3 preferentes, dos clientes y un usuario.

# COMPILACION
Desde la línea de comandos, ejecutar:

gcc Bancoppel.c TADColaDin.c presentacionWin.c -o Bancoppel

Posteriormente, ejecutar:

Bancoppel.exe

Nota: Se requiere tener implementado los compiladores gcc de MinGW
