/*
PRACTICA 02 SIMULACION DE UN BANCO

DESCRIPCIÓN: Simula la opereracion de un banco donde existen tres tipos de usuarios en dicho banco: usuarios(personas sin cuenta
			en el banco), clientes(personas con una cuneta en el banco) y preferentes(personas donde tienen mayor prioridad en 
			ser atendidos).

OBSERVACIONES: Se emplean Colas de prioridades para la atencion de los clientes, donde se atenderan a 3 preferentes, dos clientes 
				y al final un usario.

INSTRUCCION DE COMPILACION: gcc Bancoppel.c TADColaDin.c presentacionWin.c -o Bancoppel
EJECUCIÓN: Bancoppel.exe 

AUTOR:  

Ericka Ruiz López              (C) Marzo 2021

*/
#include<stdio.h>
#include "presentacion.h"
#include "TADColaDin.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
//#include "TADColaEst.h"
#define TIEMPO_BASE	500		     //Tiempo base en ms
#define TIEMPO_USUARIOS 1
//#define TIEMPO_ATENCION_CLIENTES	3		
#define TIEMPO_CLIENTES	2	
//#define TIEMPO_ATENCION_USUARIOS	5	
#define TIEMPO_PREFERENTES 3	
//#define TIEMPO_ATENCION_PREFERENTES	2	
#define TIEMPO_ATENCION	5


//Prototipos de funciones
void cuadroDatos();
void imprimeAtendiendo(clienteBanco *usuarios_banco,int i);
void dibujarCuadro(int x1,int y1,int x2,int y2);//posicon incial en x, posicion incial en y, posiscion final en x , posicion final en y 
void dibujarDatos(int x, int y, cola * clientes);

//Funcion principal
void main(){
    BorrarPantalla();
    cola usuario,cliente, preferente;
    clienteBanco usuarios_banco;
    int tiempo=0, i, j=0,numcajas;
    int clientes=0, usuarios=0, preferentes=0;
    cola ventanillas[10]; 
    elemento e;

    Initialize(&cliente); //clientes
    Initialize(&usuario); //usuarios
    Initialize(&preferente); //preferentes 
    for(i=0;i<10;i++){
        Initialize(&ventanillas[i]);
    }

   
    while(numcajas<1 || numcajas>10){
    	printf("\nIngrese el numero de ventanillas abiertas (10): ");
    	scanf("%d",&numcajas);
	}

    BorrarPantalla();
    system("mode con: cols=150 lines=35");
	system("COLOR 0B");
	cuadroDatos();
    
    while(1)
	{
        Sleep(TIEMPO_BASE);		//Esperar el tiempo base
		tiempo++;				//Incrementar el contador de tiempo
        if (tiempo % TIEMPO_ATENCION == 0)
		{	
            for(i=0;i<numcajas;i++){
                if (Empty(&ventanillas[i]))
                {
                    if(!Empty(&preferente) && j < 3){
                        e = Dequeue(&preferente);
                        Queue(&ventanillas[i], e);
                        j++;
                    }else{
                        if(!Empty(&cliente) && j <= 4){
                            e = Dequeue(&cliente);
                            Queue(&ventanillas[i], e);
                            j++;
                        }else{
                            if(!Empty(&usuario)){
                                if(j==5 || Empty(&preferente) || Empty(&cliente)){
                                    e = Dequeue(&usuario);
                                    Queue(&ventanillas[i], e);
                                    j=0;
                                }
                            }
                        }
                    }
                        
                }
            
                if (!Empty(&ventanillas[i])){
                    e = Dequeue(&ventanillas[i]);
                    imprimeAtendiendo(&e.b,i); 
                }
            }
		}
        if (tiempo % TIEMPO_CLIENTES == 0)
        {
            clientes++;										//Incrementar el numero de clientes
            usuarios_banco.ncliente = clientes;				//Dar el numero que identifica al cliente
            strcpy(usuarios_banco.TipoUsuario,"Cliente");	//Poner que cliente se esta metiendo
            e.b=usuarios_banco;				
            Queue(&cliente,e);                              //Formarse en la cola correspondiente
        }
        if (tiempo % TIEMPO_USUARIOS == 0)
        {
            usuarios++;										
            usuarios_banco.ncliente = usuarios;				
            strcpy(usuarios_banco.TipoUsuario,"Usuario");	
            e.b=usuarios_banco;						
            Queue(&usuario, e);
        }
        if (tiempo % TIEMPO_PREFERENTES == 0)
        {
            preferentes++;		//Incrementar el numero de clientes
            usuarios_banco.ncliente = preferentes;				//Dar el numero que identifica al cliente
            strcpy(usuarios_banco.TipoUsuario,"Preferente");	//Poner que cliente se esta metiendo
            e.b=usuarios_banco;				
            Queue(&preferente, e);//Formarse en la fila seleccionada
        }
		
        dibujarDatos(95, 15, &preferente);
        dibujarDatos(75, 15, &cliente);
        dibujarDatos(55, 15, &usuario);
    }
}

//Funciones
void cuadroDatos(){
	dibujarCuadro(105,15,105,25);
	dibujarCuadro(85,15,85,25);
	dibujarCuadro(65,15,65,25);
	dibujarCuadro(45,15,45,25);
    MoverCursor(55,12);
    printf("USUARIOS");
    MoverCursor(75,12);
    printf("CLIENTES");
    MoverCursor(95,12);
    printf("PREFERENTES");

	MoverCursor(65,3);
	printf("------ BANCOOPEL ------");

	dibujarCuadro(3,5,20,8);
	MoverCursor(4,6);
	printf("--Ventanilla 1--");
	MoverCursor(4,7);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(3,9,20,12);
	MoverCursor(4,10);
	printf("--Ventanilla 2--");
	MoverCursor(4,11);
    printf("Atendiendo a: "); 

    dibujarCuadro(3,13,20,16);
	MoverCursor(4,14);
	printf("--Ventanilla 3--");
	MoverCursor(4,15);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(3,17,20,20);
	MoverCursor(4,18);
	printf("--Ventanilla 4--");
	MoverCursor(4,19);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(3,21,20,24);
	MoverCursor(4,22);
	printf("--Ventanilla 5--");
	MoverCursor(4,23);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(124,5,141,8);
	MoverCursor(125,6);
	printf("--Ventanilla 6--");
	MoverCursor(125,7);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(124,9,141,12);
	MoverCursor(125,10);
	printf("--Ventanilla 7--");
	MoverCursor(125,11);
    printf("Atendiendo a: "); 
	

	dibujarCuadro(124,13,141,16);
	MoverCursor(125,14);
	printf("--Ventanilla 8--");
	MoverCursor(125,15);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(124,17,141,20);
	MoverCursor(125,18);
	printf("--Ventanilla 9--");
	MoverCursor(125,19);
    printf("Atendiendo a: "); 
	
	dibujarCuadro(124,21,141,24);
	MoverCursor(125,22);
	printf("-Ventanilla 10-");
	MoverCursor(125,23);
    printf("Atendiendo a: "); 
	

}
void imprimeAtendiendo(clienteBanco *usuarios_banco, int ventanilla){
    switch(ventanilla)
    {
        case 0:  
        MoverCursor(17,7);
        printf("   ");
        MoverCursor(17,7);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(22,7);
        printf("           ");
        MoverCursor(22,7);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 1:  
        MoverCursor(17,11);
        printf("   ");
        MoverCursor(17,11);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(22,11);
        printf("           ");
        MoverCursor(22,11);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 2:  
        MoverCursor(17,15);
        printf("   ");
        MoverCursor(17,15);
        printf("%d",usuarios_banco->ncliente);
        MoverCursor(22,15);
        printf("           ");
        MoverCursor(22,15);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 3:  
        MoverCursor(17,19);
        printf("   ");
        MoverCursor(17,19);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(22,19);
        printf("           ");
        MoverCursor(22,19);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 4:  
        MoverCursor(17,23);
        printf("   ");
        MoverCursor(17,23);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(22,23);
        printf("           ");
        MoverCursor(22,23);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 5:  
        MoverCursor(138,7);
        printf("   ");
        MoverCursor(138,7);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(115,7);
        printf("         ");
        MoverCursor(115,7);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 6:  
        MoverCursor(138,11);
        printf("   ");
        MoverCursor(138,11);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(115,11);
        printf("         ");
        MoverCursor(115,11);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 7:  
        MoverCursor(138,15);
        printf("   ");
        MoverCursor(138,15);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(115,15);
        printf("         ");
        MoverCursor(115,15);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 8:  
        MoverCursor(138,19);
        printf("   ");
        MoverCursor(138,19);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(115,19);
        printf("         ");
        MoverCursor(115,19);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
        case 9:  
        MoverCursor(138,23);
        printf("   ");
        MoverCursor(138,23);
        printf("%d", usuarios_banco->ncliente);
        MoverCursor(115,23);
        printf("         ");
        MoverCursor(115,23);
        printf("%s", usuarios_banco->TipoUsuario);
        break;
    }

}
void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;

    for (i=x1;i<x2;i++){
        MoverCursor(i,y1); 
        printf("\304"); //linea horizontal superior
        MoverCursor(i,y2); 
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
        MoverCursor(x1,i); 
        printf("\263"); //linea vertical izquierda
        MoverCursor(x2,i); 
        printf("\263"); //linea vertical derecha
    }

    MoverCursor(x1,y1); 
    printf("\332");
    MoverCursor(x1,y2); 
    printf("\300");
    MoverCursor(x2,y1); 
    printf("\277");
    MoverCursor(x2,y2); 
    printf("\331");
}

void dibujarDatos(int x, int y, cola * clientes){
	int j=0;
	int i=0;
	int tam = Size(clientes);
	if(tam>7){
		for(i=0;i<7;i++){
			printf("   ");
			MoverCursor(x,y+j); printf("%d",Element(clientes,i+1).b.ncliente);
			j++;
		}
		MoverCursor(x,y+8); printf("   ");
		MoverCursor(x,y+8); printf("+%d",tam-7);
	}else{
		if(tam==7){
			MoverCursor(x,y+8); printf("   ");
		}
      
        for(i=0;i<7;i++){
            MoverCursor(x,y+i); printf("   ");

        }
        
		i=0;
		while(i<tam){
			printf("   ");
			MoverCursor(x,y+j); printf("%d",Element(clientes,i+1).b.ncliente);
			j++;
			i++;
		}
	}
}