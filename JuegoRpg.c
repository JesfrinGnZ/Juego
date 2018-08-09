/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jesfrin
 *
 * Created on 5 de agosto de 2018, 12:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 
 */

//Variables usadas a lo largo del programa


//Estrucuturas

typedef struct {//Contador para crear personajes
    int n;
} Contador;

typedef struct {//Personajes que se podran usar a lo largo del juego
    //Estado Inicial
    char nombre[20]; //Dado por el usuario
    int codigo; //Dado automaticamente
    int puntosDeVida; //100
    int puntosDeMana; //Sirven para curar al personaje, solo se consume un punto por curacion,10
    int nivel; //Dado automaticamente,(Luego se tratara segun experiencia),0
    int experiencia; //Sirve para subir de nivel,0
    int oro; //Sirve para comprar cosas de la tienda,0
    int cantidadDeVictorias; //Sirven para el punteo(archivos),0
    int cantidadDeDerrotas; //Sirven para el punteo(archivos),0
    int cantidadDePotion; //0
    int cantidadDeHiPotion; //0
    int cantidadDeMPotion; //0
} Personaje;

typedef struct {
    char nombre[20];
    int codigo;
    int puntosDeVida;
    int factorDeAtaque;
} Enemigo;

typedef struct {
    int precio;
    int curacion;
} Pocion;

void iniciarPersonaje(Personaje *personajeCreado) {
    (*personajeCreado).codigo = buscarCodigo();
    (*personajeCreado).puntosDeVida = 100;
    (*personajeCreado).puntosDeMana = 10;
    (*personajeCreado).nivel = 0;
    (*personajeCreado).experiencia = 0;
    (*personajeCreado).oro = 0;
    (*personajeCreado).cantidadDeVictorias = 0;
    (*personajeCreado).cantidadDeDerrotas = 0;
    (*personajeCreado).cantidadDePotion = 0;
    (*personajeCreado).cantidadDeHiPotion = 0;
    (*personajeCreado).cantidadDeMPotion = 0;
}

void volverAEstadoInicial(Personaje *personajeCreado) {
    (*personajeCreado).puntosDeVida = 100;
    (*personajeCreado).puntosDeMana = 10;
    (*personajeCreado).nivel = 0;
    (*personajeCreado).experiencia = 0;
    (*personajeCreado).oro = 0;
    (*personajeCreado).cantidadDePotion = 0;
    (*personajeCreado).cantidadDeHiPotion = 0;
    (*personajeCreado).cantidadDeMPotion = 0;
}

struct Posion {
};

void menuPrincipal(Personaje *personajeUsado) {

    FILE *archivoPersonajes;
    Personaje nuevoPersonaje;
    int opcion = 0;
    do {

        printf("\n**************************************************************\n");
        printf("\n\n\t\t\tMENU PRINCIPAL\n");
        printf("\n**************************************************************\n");
        printf("\n\t\tIngrese la opcion que desea\n");
        printf("1)A la Carga\n");
        printf("2)Tienda\n");
        printf("3)ZzzZzz\n");
        printf("4)Status\n");
        printf("5)Mejor punteo\n");
        printf("6)Cambiar de personaje\n");
        printf("7)Creear personajes\n");
        printf("8)Salir del juego\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                menuALaCarga(&(*personajeUsado));
                opcion = 0;
                break;
            case 2:
                menuTienda(&(*personajeUsado));
                opcion = 0;
                break;
            case 3:
                //Menu dormir
                printf("\n\t\t\tDORMIR\n");
                printf("Verificando si cuenta con el oro suficiente.........................\n");
                if ((*personajeUsado).oro >= 30) {
                    printf("Cuenta con el oro suficiente, se le restara 30 de %d", (*personajeUsado).oro);
                    (*personajeUsado).oro -= 30;
                    (*personajeUsado).puntosDeMana = (10 * ((*personajeUsado).nivel + 1));
                    (*personajeUsado).puntosDeVida = (100 * ((*personajeUsado).nivel + 1));
                    guardarCambiosDePersonaje(&(*personajeUsado));
                    printf("    ");
                } else {
                    printf("No cuenta con el oro suficiente");
                }
                opcion = 0;
                break;
            case 4:
                mostrarStatusDelPersonaje(&(*personajeUsado));
                printf("\n\n");
                opcion = 0;
                break;
            case 5:
                //menuMejorPunteo();
                break;
            case 6:
                printf("\n\t\tCAMBIO DE PERSONAJE\n");
                cambiarDePersonaje(&(*personajeUsado));
                opcion = 1;
                break;
            case 7:
                archivoPersonajes = fopen("Personajes.bin", "ab"); //Creamos el archivo
                printf("Escriba el nombre de su personaje\n"); //Se piden datos para el personaje
                //Datos del personaje
                scanf("%s", nuevoPersonaje.nombre);
                //            personajeNuevo.codigo = buscarCodigo();
                iniciarPersonaje(&nuevoPersonaje);
                printf("Nivel dado a %s es de %d", nuevoPersonaje.nombre, nuevoPersonaje.nivel);
                //Se guarda el personaje
                fwrite(&nuevoPersonaje, sizeof nuevoPersonaje, 1, archivoPersonajes);
                fread(&nuevoPersonaje, sizeof nuevoPersonaje, 1, archivoPersonajes);
                printf("Personaj Creado\n");
                opcion = 0;
                break;
            case 8:
                printf("\n\t\t\tFIN DEL JUEGO");
                opcion = 2;
                break;
            case 9:
                printf("Se modificar el personaje\n");
                modificar();
                break;
            default:
                printf("\n\n\t\t\t\tINSTRUCCION NO VALIDA, PRUEBE DE NUEVO\n\n");
                opcion = 0;
                break;
        }
    } while (opcion == 0);
}

void informacionDeJugadores(Personaje *personajeActual, Enemigo *enemigoActual) {

    printf("\n*************INFORMACION ACTUAL DE LOS JUGADORES*************\n");
    printf("Personaje:%s\n", (*personajeActual).nombre);
    printf("Puntos de vida:%d\n\n", (*personajeActual).puntosDeVida);
    printf("Enemigo:%s\n", (*enemigoActual).nombre);
    printf("Puntos de vida:%d\n", (*enemigoActual).puntosDeVida);
}

void accionDePersonajeEnBatalla(Personaje *personajeActual, Enemigo *enemigoActual) {
    int opcion;
    int opcinoMiedo = 0;
    int tipoDePocion;
    int vidaMaxima = (((*personajeActual).nivel + 1)*100);
    int puntosDeManaMaximos = (((*personajeActual).nivel + 1)*10);


    informacionDeJugadores(&(*personajeActual), &(*enemigoActual));
    printf("\n--------------------->ES SU TURNO\n");

    do {
        printf("1)Atacar\n");
        printf("2)Curar\n");
        printf("3)Usar algun Item\n");
        printf("4)Tengo miedo\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("\nAtacando................................\n");
                int ataque = (((*personajeActual).nivel + 1)*10) + numeroAleatorio(10, 20);
                printf("El dano al enemigo fue de: %d\n", ataque);
                (*enemigoActual).puntosDeVida -= ataque;
                break;
            case 2:
                printf("\nVerificando puntos de mana.................................\n");
                if ((*personajeActual).puntosDeMana > 0) {
                    printf("\nCurando...................................................");
                    (*personajeActual).puntosDeMana--;
                    int curacion = (((*personajeActual).nivel + 1)*5 + numeroAleatorio(15, 25));
                    printf("La curacion es de:%d\n", curacion);
                    int vidaNueva = curacion + (*personajeActual).puntosDeVida;
                    int limiteDeVida = (100 * ((*personajeActual).nivel + 1));
                    printf("VIDA NUEVA..%d\n..LIMITE...%d", vidaNueva, limiteDeVida);
                    if (vidaNueva > limiteDeVida) {
                        (*personajeActual).puntosDeVida = limiteDeVida;
                    } else {
                        (*personajeActual).puntosDeVida += curacion;
                    }
                } else {
                    printf("No cuenta con suficientes puntos de mana");
                }
                break;
            case 3:
                printf("Pociones que posee actualmente.........\n");
                printf("1)Potion +25HP:%d\n", (*personajeActual).cantidadDePotion);
                printf("2)HiPotion +75Hp:%d\n", (*personajeActual).cantidadDeHiPotion);
                printf("3)MPotion +10MP:%d\n", (*personajeActual).cantidadDeMPotion);
                printf("n)Salir sin comprar pocion(Perdera su turno)\n");
                scanf("%d", &tipoDePocion);
                printf("Vida maxima:%d\n", vidaMaxima);
                switch (tipoDePocion) {

                    case 1:
                        if ((*personajeActual).cantidadDePotion > 0) {
                            if ((*personajeActual).puntosDeVida + 25 > vidaMaxima) {
                                (*personajeActual).puntosDeVida = vidaMaxima;
                                printf("Vida actual:%d\n", (*personajeActual).puntosDeVida);
                                printf("Vida maxima:%d\n", vidaMaxima);
                            } else {
                                printf("Vida actual:%d\n", (*personajeActual).puntosDeVida);
                                (*personajeActual).puntosDeVida += 25;
                                printf("Vida luego de sumar la pocion:%d\n", (*personajeActual).puntosDeVida);

                            }
                            (*personajeActual).cantidadDePotion--;
                            printf("Se ha aplicado la pocion\n");
                        } else {
                            printf("Ya no cuenta con pociones de este tipo\n");
                        }
                        break;
                    case 2:
                        if ((*personajeActual).cantidadDeHiPotion > 0) {
                            if ((*personajeActual).puntosDeVida + 75 > vidaMaxima) {
                                (*personajeActual).puntosDeVida = vidaMaxima;
                                printf("Vida actual:%d\n", (*personajeActual).puntosDeVida);
                                printf("Vida maxima:%d\n", vidaMaxima);
                            } else {
                                printf("Vida actual:%d\n", (*personajeActual).puntosDeVida);
                                (*personajeActual).puntosDeVida += 75;
                                printf("Vida luego de sumar la pocion:%d\n", (*personajeActual).puntosDeVida);

                            }
                            (*personajeActual).cantidadDeHiPotion--;
                            printf("Se ha aplicado la pocion\n");

                        } else {
                            printf("Ya no cuenta con pociones de este tipo\n");
                        }
                        break;
                    case 3:
                        if ((*personajeActual).cantidadDeMPotion > 0) {
                            if ((*personajeActual).puntosDeMana + 10 > puntosDeManaMaximos) {
                                (*personajeActual).puntosDeMana = puntosDeManaMaximos;
                                printf("Mana actual:%d\n", (*personajeActual).puntosDeMana);
                                printf("Mana maxima:%d\n", puntosDeManaMaximos);

                            } else {
                                printf("Mana Actual:%d\n", (*personajeActual).puntosDeMana);
                                (*personajeActual).puntosDeMana += 10;
                                printf("Manaluego de sumar la pocion:%d\n", (*personajeActual).puntosDeMana);
                            }
                            (*personajeActual).cantidadDeMPotion--;
                            printf("Se ha aplicado la pocion\n");
                        } else {
                            printf("Ya no cuenta con pociones de este tipo\n");
                        }
                        break;
                    default:
                        printf("................................................");
                        break;
                }
                break;
            case 4:
                printf("Tengo Miedo................");
                printf("Verificando cantidad de oro..............");
                int cantidadDeOro = ((*personajeActual).nivel + numeroAleatorio(5, 10));
                if (cantidadDeOro <= (*personajeActual).oro) {
                    printf("Para abandonar la partida necesita:%d\n Cuenta con:%d", cantidadDeOro, (*personajeActual).oro);
                    (*personajeActual).oro -= cantidadDeOro;
                    guardarCambiosDePersonaje(&(*personajeActual));
                    opcinoMiedo = 1;
                } else {
                    printf("No cuenta con el oro suficiente");
                }
                break;
            default:
                printf("ORDEN NO ENCONTRADA PRUEBE DE NUEVO\n");
                opcion = 0;
                break;
        }
    } while (opcion == 0);
    if (opcinoMiedo == 1) {
        menuPrincipal(&(*personajeActual));
    } else {
        if ((*enemigoActual).puntosDeVida > 0) {
            accionDeEnemigoEnBatalla(&(*personajeActual), &(*enemigoActual));
        } else {
            printf("\n\n\t\t\tFELICIDADES HA GANADO LA BATALLA\n");
            (*personajeActual).cantidadDeVictorias++;
            (*personajeActual).experiencia += (numeroAleatorio(2, 5))*((*enemigoActual).factorDeAtaque);
            (*personajeActual).oro += (numeroAleatorio(5, 15))*((*enemigoActual).factorDeAtaque);
            //Asignar experiencia experiencia/50+1=nivel
            int division = (*personajeActual).experiencia / 50;
            (*personajeActual).nivel = division + 1; //quitarle el 1
            //Componer o de la experiencia

            printf("\n===========================HAS RECIBIDO==============================\n");
            printf("Nueva Exeriencia>>>>>>>>%d\n", (*personajeActual).experiencia);
            printf("Oro>>>>>>>>>>>>>>>>>>>>>%d\n", (*personajeActual).oro);
            printf("Nivel>>>>>>>>>>>>>>>>>>>%d\n", (*personajeActual).nivel);

            guardarCambiosDePersonaje(&(*personajeActual));
            //Se le coloca todo lo que implica que gane la batalla, y guardar los datos en archivo
        }
    }


}

void accionDeEnemigoEnBatalla(Personaje *personajeActual, Enemigo *enemigoActual) {
    Personaje personajeInicial;
    printf("\t\t\n--------------------->TURNO DEL ENEMIGO\n");
    int limiteInferior = ((*enemigoActual).factorDeAtaque + (*personajeActual).nivel);
    int limiteSuperior = limiteInferior + 10;
    int ataque = numeroAleatorio(limiteInferior, limiteSuperior);
    printf("El enemigo ataco, causando un dano de:%d\n\n", ataque);
    //(*personajeActual).puntosDeVida=(*personajeActual).puntosDeVida-(*enemigoActual).factorDeAtaque;
    (*personajeActual).puntosDeVida -= ataque;
    if ((*personajeActual).puntosDeVida <= 0) {
        (*personajeActual).cantidadDeDerrotas++;
        printf("\n\n\t\t\t HA PERDIDO LA BATALLA\n");
        iniciarPersonaje(&personajeInicial);
        volverAEstadoInicial(&(*personajeActual));
        //iniciarPersonaje(&(*personajeActual));
        //(*personajeActual).cantidadDeDerrotas++; //Guardar los datos en el archivo
        guardarCambiosDePersonaje(&(*personajeActual));
    } else {
        accionDePersonajeEnBatalla(&(*personajeActual), &(*enemigoActual));
    }
}

Enemigo buscarEnemigo() {
    int numero = generarNumeroAleatorio();
    //nombre, codigo, puntos de vida,factor de ataque 
    Enemigo enemigo1 = {"Dark Wolf", 1, 50, 10};
    Enemigo enemigo2 = {"Dragon", 2, 100, 15};
    Enemigo enemigo3 = {"Mighty Golem", 3, 150, 25};

    if (numero <= 4) {
        return enemigo1;
    } else if (numero > 4 && numero <= 7) {
        return enemigo2;
    } else {
        return enemigo3;
    }
}

int menuALaCarga(Personaje *personajeActual) {
    int turno = generarNumeroAleatorio();
    Enemigo enemigoActual = buscarEnemigo();

    printf("\n\t\t\t\tENEMIGO:\n");
    printf("\t\t\tNombre:%s\n", enemigoActual.nombre);
    printf("\t\t\tPuntos de vida:%d\n", enemigoActual.puntosDeVida);

    //Primer Turno
    if (turno <= 5) {//Es turno del personaje
        accionDePersonajeEnBatalla(&(*personajeActual), &enemigoActual);
    } else {//Turno del enemigo
        accionDeEnemigoEnBatalla(&(*personajeActual), &enemigoActual);
    }


}

void menuTienda(Personaje *personajeActual) {
    int tipoDePocion;
    printf("\n\t\t\t\tMENU TIENDA\n");
    printf("Puede comprobar si puede comprar una pocion solamente seleccionandola\n");
    printf("1)Potion....50 oro cura 25 HP\n");
    printf("2)Hi-Potion...100 oro cura 75 HP\n");
    printf("3)M Potion....75 oro recupera 10MP\n ");
    scanf("%d", &tipoDePocion);
    do {
        switch (tipoDePocion) {
            case 1:
                if ((*personajeActual).oro >= 50) {
                    printf("Asignando la posion..............\n");
                    printf("POSION ASIGNADA\n");
                    (*personajeActual).cantidadDePotion++;
                    (*personajeActual).oro -= 50;
                } else {
                    printf("No cuenta con el dinero suficiente para comprar la posion:%d \n", (*personajeActual).oro);
                }
                break;
            case 2:
                if ((*personajeActual).oro >= 100) {
                    printf("Asignando la posion..............\n");
                    printf("POSION ASIGNADA\n");
                    (*personajeActual).cantidadDeHiPotion++;
                    (*personajeActual).oro -= 100;

                } else {
                    printf("No cuenta con el dinero suficiente para comprar la posion:%d \n", (*personajeActual).oro);
                }
                break;
            case 3:
                if ((*personajeActual).oro >= 75) {
                    printf("Asignando la posion..............\n");
                    printf("POSION ASIGNADA\n");
                    (*personajeActual).cantidadDeMPotion++;
                    (*personajeActual).oro -= 75;

                } else {
                    printf("No cuenta con el dinero suficiente para comprar la posion:%d \n", (*personajeActual).oro);
                }
                break;
            default:
                printf("No se ha encontrado la opcion para esta pocion");
                break;
        }
        printf("Desea comprar una nueva pocion??? precione 0\n");
        scanf("%d", &tipoDePocion);
    } while (tipoDePocion == 0);
    guardarCambiosDePersonaje(&(*personajeActual));


}


//Funcones para trabajar con el personaje

int numeroAleatorio(int limiteInferior, int limiteSuperior) {
    int numero;
    srand(time(NULL));
    //limte inferior
    numero = limiteInferior + rand() % ((limiteSuperior + 1) - limiteInferior);
    return numero;
}

int generarNumeroAleatorio() {
    int numero;
    srand(time(NULL));
    //limte inferior
    numero = 1 + rand() % ((10 + 1) - 1);
    return numero;
}

int buscarCodigo() {//Utilizado en buscarPersonaje
    FILE *archivoContador;
    Contador contadorActual = {1};
    int contadorADevolver;

    archivoContador = fopen("Contador.bin", "rb"); //acceder solo a lectura
    if (archivoContador == NULL) {//No existe el archivo
        archivoContador = fopen("Contador.bin", "ab"); //ccedes para escritura sin sobreescribir, lo crea si no existe
        fwrite(&contadorActual, sizeof (contadorActual), 1, archivoContador);
        fread(&contadorActual, sizeof contadorActual, 1, archivoContador);
        return 1;
    } else {
        //No es nulo
        fread(&contadorActual, sizeof (contadorActual), 1, archivoContador); //Se lee el contador actual
        printf("Se ha leido:%d", contadorActual.n);
        contadorActual.n++; //Este es el valor a utilizar y a guardar
        contadorADevolver = contadorActual.n;
        archivoContador = fopen("Contador.bin", "wb"); //Flujo para escritura
        fwrite(&contadorActual, sizeof (contadorActual), 1, archivoContador); //Se escribe el numero que se uso
        printf("Contador:%d\n", contadorActual.n);
        fread(&contadorActual, sizeof (contadorActual), 1, archivoContador); //Se lee el contador actual
        //printf("Se ha leido:%d", contadorActual.n);
        return contadorADevolver;

    }
    fclose(archivoContador);

}

void mostrarPersonajes(FILE *archivoPersonajes) {
    Personaje personajeActual;
    archivoPersonajes = fopen("Personajes.bin", "rb"); //Ya existe el archivo(lectura)
    printf("%-25s", "NOMBRE DEL PERSONAJE");
    printf("%-25s", "CODIGO DEL PERSONAJE");
    printf("%s", "NIVEL\n");
    while (fread(&(personajeActual), sizeof (personajeActual), 1, archivoPersonajes)) {
        printf("%-25s", personajeActual.nombre);
        printf("%-25d", personajeActual.codigo);
        printf("%d\n", personajeActual.nivel);
    }

}

Personaje seleccionarPersonaje(FILE *archivoPersonajes) {
    int codigoDelPersonaje;
    Personaje personajeActual;
    //
    int repeticion = 0;
    do {
        printf("\nIngrese el codigo del personaje que deseea escojer\n");
        fflush(stdin);
        scanf("%d", &codigoDelPersonaje);

        archivoPersonajes = fopen("Personajes.bin", "rb");
        while (fread(&(personajeActual), sizeof (personajeActual), 1, archivoPersonajes)) {
            /*
                        printf("\nCodigo dentro del while:%d y nombre %s\n", personajeActual.codigo, personajeActual.nombre);
             */
            //Error en condicional
            if (personajeActual.codigo == codigoDelPersonaje) {
                //Lo comentado de abajo puede servir para ver como funciona el while 
                //printf("\nCodigo dentro del while:%d\n y nombre %s", personajeActual.codigo, personajeActual.nombre);
                return personajeActual;
            }
        }
        printf("No se ha encontrado al personaje, pruebe de nuevo\n");
    } while (repeticion == 0);

}

Personaje buscarPersonaje() {//El general, busca ara mostrar o crear 

    FILE *archivoPersonaje;
    Personaje personajeNuevo;

    archivoPersonaje = fopen("Personajes.bin", "rb"); //Accedemos solo a lectura
    if (archivoPersonaje == NULL) {
        printf("\n......No existen personajes.Cree el suyo\n");
        archivoPersonaje = fopen("Personajes.bin", "ab"); //Creamos el archivo
        printf("Escriba el nombre de su personaje\n"); //Se piden datos para el personaje
        //Datos del personaje
        scanf("%s", personajeNuevo.nombre);
        //        personajeNuevo.codigo = buscarCodigo();
        iniciarPersonaje(&personajeNuevo);
        //Se guarda el personaje
        fwrite(&personajeNuevo, sizeof (personajeNuevo), 1, archivoPersonaje);


    } else {
        int opcion;
        printf("\n\nDesea crear un nuevo personaje[0], o usar alguno de los siguientes[1]??\n\n");
        mostrarPersonajes(&archivoPersonaje);
        scanf("%d", &opcion);
        if (opcion == 0) {
            archivoPersonaje = fopen("Personajes.bin", "ab"); //Creamos el archivo
            printf("Escriba el nombre de su personaje\n"); //Se piden datos para el personaje
            //Datos del personaje
            scanf("%s", personajeNuevo.nombre);
            //            personajeNuevo.codigo = buscarCodigo();
            iniciarPersonaje(&personajeNuevo);
            printf("Nivel dado:%d\n", personajeNuevo.nivel);
            //Se guarda el personaje
            fwrite(&personajeNuevo, sizeof (personajeNuevo), 1, archivoPersonaje);
            fread(&personajeNuevo, sizeof personajeNuevo, 1, archivoPersonaje);
            printf("Nivel dado luego de ser escrito:%d\n", personajeNuevo.nivel);
            printf("Personaje Creado\n");
        } else {
            printf("\n\t\t\tESCOJA SU PERSONAJE\n");
            //            mostrarPersonajes(&archivoPersonaje);
            personajeNuevo = seleccionarPersonaje(&archivoPersonaje);
            printf("\nNombre del personaje seleccionado:%s\n", personajeNuevo.nombre);
        }



    }
    fclose(archivoPersonaje);
    return personajeNuevo;
}

void guardarCambiosDePersonaje(Personaje *personajeSeleccionado) {//No cambia el codigo, pero si otras cosas
    FILE *archivoPersonajes;
    Personaje personajeActual;
    personajeActual.codigo = (*personajeSeleccionado).codigo;

    archivoPersonajes = fopen("Personajes.bin", "rb+");
    while (fread(&(personajeActual), sizeof (personajeActual), 1, archivoPersonajes)) {
        printf("\nCodigo dentro del while:%d y nombre %s\n", personajeActual.codigo, personajeActual.nombre);
        //Error en condicional

        if (personajeActual.codigo == (*personajeSeleccionado).codigo) {
            //Lo comentado de abajo puede servir para ver como funciona el while 
            //printf("\nCodigo dentro del while:%d\n y nombre %s", personajeActual.codigo, personajeActual.nombre);
            printf(",,,,,,,,,,,,,,,,,");
            printf(",,,,,,,,,,,,,,,,,");

            printf(",,,,,,,,,,,,,,,,,");

            fseek(archivoPersonajes, ftell(archivoPersonajes) - sizeof (personajeActual), SEEK_SET);
            fwrite(&(*personajeSeleccionado), sizeof ((*personajeSeleccionado)), 1, archivoPersonajes);
            fread(&(*personajeSeleccionado), sizeof ((*personajeSeleccionado)), 1, archivoPersonajes); //MUY IMPORTANTE
            printf("Se han guardado los cambios\n");
            break;
        }
    }

    mostrarPersonajes(&archivoPersonajes);
    fclose(archivoPersonajes);


}

void cambiarDePersonaje(Personaje *personajeSeleccionado) {
    FILE *archivoPersonajes;

    //Guardando cambios
    guardarCambiosDePersonaje(&(*personajeSeleccionado));
    //mostrarPersonajes(&archivoPersonajes);
    (*personajeSeleccionado) = seleccionarPersonaje(&archivoPersonajes);
    printf("Ha cambiado de personaje, ahora esta con:%s\n", (*personajeSeleccionado).nombre);
    menuPrincipal(&(*personajeSeleccionado));
    fclose(archivoPersonajes);

}

//Textos

void tituloPrincipal() {
    int i;
    printf("\n     ======================================================================\n");
    printf("\t\t\t    JUEGO RPG\n");
    printf("\t   Adentrate en un mundo de diversion sin limites\n");
    printf("\t\t    Copyright 2018 | :v :v :v\n");
    printf("     ======================================================================\n");

    i = 0;
    putchar('\n');
    for (; i < 80; i++) {
        putchar('_');
    }
}

/*
void modificarPersonaje(FILE *archivoPersonajes,Personaje *personaje){
    
}
 */


void modificar() {//Prueba para modificar
    int nivelNuevo;
    Personaje personajeSeleccionado;
    Personaje personajeActual;
    FILE *archivoPersonajes;

    printf("Escoja el codigo del personaje que desea cambiar\n");
    //archivoPersonajes = fopen("Personajes.bin", "rb");
    mostrarPersonajes(&archivoPersonajes);
    personajeSeleccionado = seleccionarPersonaje(&archivoPersonajes);
    printf("Cual sera el nuevo nivel??");
    scanf("%d", &nivelNuevo);


    //Abriendo el archivo para lectura y escritura
    archivoPersonajes = fopen("Personajes.bin", "rb+");
    while (fread(&(personajeActual), sizeof (personajeActual), 1, archivoPersonajes)) {
        printf("\nCodigo dentro del while:%d y nombre %s\n", personajeActual.codigo, personajeActual.nombre);
        //Error en condicional

        if (personajeActual.codigo == personajeSeleccionado.codigo) {
            //Lo comentado de abajo puede servir para ver como funciona el while 
            //printf("\nCodigo dentro del while:%d\n y nombre %s", personajeActual.codigo, personajeActual.nombre);
            personajeActual.codigo = nivelNuevo;
            fseek(archivoPersonajes, ftell(archivoPersonajes) - sizeof (personajeActual), SEEK_SET);
            fwrite(&personajeActual, sizeof (personajeActual), 1, archivoPersonajes);
            fread(&personajeActual, sizeof (personajeActual), 1, archivoPersonajes);
            printf("Personajes modificado\n");
            break;
        }
    }

    mostrarPersonajes(&archivoPersonajes);
    fclose(archivoPersonajes);


}


//Opciones en menu


//4

void mostrarStatusDelPersonaje(Personaje *personaje) {

    FILE *archivoDePersonajes;
    Personaje personajeAuxiliar;

    printf("\n\t\t\t============================================================\n");
    printf("\t\t\t\t\tSTATUS DEL PERSONAJE");
    printf("\n\t\t\t============================================================\n");

    archivoDePersonajes = fopen("Personajes.bin", "rb"); //SOlo de lectura
    while (fread(&(personajeAuxiliar), sizeof (personajeAuxiliar), 1, archivoDePersonajes)) {
        if (personajeAuxiliar.codigo == (*personaje).codigo) {
            printf("\t\t\t\tNombre :%s\n", personajeAuxiliar.nombre);
            printf("\t\t\t\tNivel:%d\n", personajeAuxiliar.nivel);
            printf("\t\t\t\tCodigo :%d\n", personajeAuxiliar.codigo);
            printf("\t\t\t\tPuntos de vida:%d\n", personajeAuxiliar.puntosDeVida);
            printf("\t\t\t\tPuntos de mana:%d\n", personajeAuxiliar.puntosDeMana);
            printf("\t\t\t\tOro:%d\n", personajeAuxiliar.oro);
            printf("\t\t\t\tExperiencia :%d\n", personajeAuxiliar.experiencia);
            printf("\t\t\t\tNumero de derrotas:%d\n", personajeAuxiliar.cantidadDeDerrotas);
            printf("\t\t\t\tNumero de victorias:%d\n", personajeAuxiliar.cantidadDeVictorias);
            printf("\t\t\t\tNumero de MPotion:%d\n", personajeAuxiliar.cantidadDeMPotion);
            printf("\t\t\t\tNumero de HiPotion:%d\n", personajeAuxiliar.cantidadDeHiPotion);
            printf("\t\t\t\tNumero de Potion:%d\n", personajeAuxiliar.cantidadDePotion);

            break;
        }
    }
    fclose(archivoDePersonajes);
}


//Enemigos

int main(int argc, char** argv) {
    Personaje personajeUsado;
    FILE *arch;
    /*
        Contador nuevo;
        nuevo.n=5;
        printf("Numeo es 5::%i", nuevo.n);
     */
    tituloPrincipal();
    personajeUsado = buscarPersonaje();
    menuPrincipal(&personajeUsado);

}