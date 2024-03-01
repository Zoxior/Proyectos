#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;

struct Jugador {
    string nombre;
    int puntaje;
};

void mostrarPuntajes(const vector<Jugador>& jugadores) {
    cout << "Puntajes:\n";
    for (vector<Jugador>::const_iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
        cout << it->nombre << ": " << it->puntaje << endl;
    }
}

int validarEntrada() {
    int eleccion;
    cout << "Seleccione una opcion:\n";
   cout << "1. Piedra\n";
cout << "  ***\n";
cout << "*******\n";
cout << " *****\n";
cout << "  **\n\n";

cout << "2. Papel\n";
cout << " *******\n";
cout << " *******\n";
cout << " *******\n";
cout << " *******\n\n";

cout << "3. Tijera\n";
cout << "   0   0\n";
cout << "    * *\n";
cout << "     *\n";
cout << "    * *\n";
cout << "   *   *\n";
cout << "  *     *\n";
    cin >> eleccion;
    while (eleccion < 1 || eleccion > 3) {
        cout << "Opción invalida. Seleccione nuevamente:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> eleccion;
    }
    return eleccion;
}

void determinarGanador(const int& eleccionJugador1, const int& eleccionJugador2, Jugador& jugador1, Jugador& jugador2) {
    if (eleccionJugador1 == eleccionJugador2) {
        cout << "Empate.\n";
    } else if ((eleccionJugador1 == 1 && eleccionJugador2 == 3) ||
               (eleccionJugador1 == 2 && eleccionJugador2 == 1) ||
               (eleccionJugador1 == 3 && eleccionJugador2 == 2)) {
        cout << jugador1.nombre << " FELICIDADES GANASTE !!!.\n";
        jugador1.puntaje++;
    } else {
        cout << jugador2.nombre << " FELICIDADES GANASTE !!!.\n";
        jugador2.puntaje++;
    }
}

void jugar(vector<Jugador>& jugadores) {
    if (jugadores.size() < 2) {
        cout << "Debe haber al menos dos jugadores para jugar.\n";
        return;
    }
    string nombreJugador1, nombreJugador2;
    cout << "Ingrese el nombre del Jugador 1: ";
    cin >> nombreJugador1;
    cout << "Ingrese el nombre del Jugador 2: ";
    cin >> nombreJugador2;
    
    jugadores[0].nombre = nombreJugador1; // Asignar el nombre ingresado al primer jugador
    jugadores[1].nombre = nombreJugador2; // Asignar el nombre ingresado al segundo jugador
    
    system("cls");
    
    int eleccionJugador1, eleccionJugador2;
    cout << jugadores[0].nombre << ", "; // Mostrar el nombre del primer jugador
    
    
    eleccionJugador1 = validarEntrada();
    
    system("cls");
    cout << jugadores[1].nombre << ", "; // Mostrar el nombre del segundo jugador
    
    
    eleccionJugador2 = validarEntrada(); // Cambiado: Ahora ambos jugadores eligen antes de determinar el ganador
    system("cls");
    determinarGanador(eleccionJugador1, eleccionJugador2, jugadores[0], jugadores[1]);

    // Preguntar si quieren jugar otra ronda
    char jugarOtraVez;
    cout << "¿Quieres jugar otra ronda? (S/N): ";
    cin >> jugarOtraVez;
    if (jugarOtraVez == 'S' || jugarOtraVez == 's') {
        jugar(jugadores); // Jugar otra ronda
    }
}


void menu_principal();

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

int menu(const char *titulo, const char *opciones[], int n) {
    int opcionSeleccionada = 1;
    int tecla;
    bool repite = true;

    do {
        system("cls");
        gotoxy(15, 2); cout << titulo;
        for (int i = 0; i < n; i++) {
            gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
        }
        gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
        do {
            tecla = getch();
        } while(tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);
        switch(tecla) {
            case TECLA_ARRIBA:
                opcionSeleccionada --;
                if (opcionSeleccionada < 1) {
                    opcionSeleccionada = n;
                }
                break;
            case TECLA_ABAJO:
                opcionSeleccionada ++;
                if (opcionSeleccionada > n) {
                    opcionSeleccionada = 1;
                }
                break;
            case ENTER:
                repite = false;
                break;
        }
    } while(repite);
    return opcionSeleccionada;
}

void menu_principal() {
	void gotoxy(int x, int y);
    bool repite = true;
    int opcion;

    const char *titulo = "------------MENU PRINCIPAL [PIEDRA,PAPEL o TIJERA] -----------";
    const char *opciones[] = {"Jugar", "Puntajes", "Salir", "Creditos"};
    int n = 4;

    vector<Jugador> jugadores;
    jugadores.push_back({"Jugador 1", 0});
    jugadores.push_back({"Jugador 2", 0});

    do {
        opcion = menu(titulo, opciones, n);
        
		system("cls");
		
		
		
        switch (opcion) {
            case 1:
                jugar(jugadores);
                cin.get(); 
                break;
            case 2:
                mostrarPuntajes(jugadores);
                cin.get(); 
                break;
            case 3:
                cout << "Saliendo del juego.\n";
                repite = false;
                break;
            case 4:
    					cout << "Desarrollado por: Kevin Gomez, Andres Palacios\n";
    					cout << "Presione enter para volver al menu principal.\n";
    					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el búfer de entrada
    					cin.get(); // Esperar hasta que el usuario presione enter
    			break;
            default:
                cout << "Opción no valida. Por favor, seleccione una opción valida.\n";
        }
        
        // Limpiar el búfer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while(repite);
}


int main() {
	system("COLOR AF");
    menu_principal();
    return 0;
}
