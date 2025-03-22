#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Para Sleep()
//holi

using namespace std;

// 🔹 Constantes globales (UPPER_SNAKE_CASE)
const int TAMANO_MAX = 50; // Tamaño máximo permitido

// 🔹 Declaración de funciones (snake_case)
void inicializar_tablero(vector<vector<int>>& tablero, int tamano, bool patron);
int calcular_vecinos_vivos(const vector<vector<int>>& tablero, int fila, int columna, int tamano);
void actualizar_tablero(vector<vector<int>>& tablero, int tamano);
void imprimir_tablero(const vector<vector<int>>& tablero, int tamano);

int main() {
    int tamano, num_generaciones;
    bool usar_patron;

    // 🟢 Entrada del usuario
    cout << "Ingrese tamano del tablero (maximo " << TAMANO_MAX << "): ";
    cin >> tamano;
    if (tamano > TAMANO_MAX) tamano = TAMANO_MAX; // Límite de seguridad

    cout << "Ingrese numero de generaciones a simular: ";
    cin >> num_generaciones;

    cout << "Desea inicializar con un patron predefinido (1 = Sí, 0 = No): ";
    cin >> usar_patron;

    // 🔹 Creación del tablero
    vector<vector<int>> tablero(tamano, vector<int>(tamano, 0));
    inicializar_tablero(tablero, tamano, usar_patron);

    // 🔄 Simulación
    for (int i = 0; i < num_generaciones; ++i) {
        imprimir_tablero(tablero, tamano);
        actualizar_tablero(tablero, tamano);
        Sleep(200); // Pausa de 200ms para ver el cambio en Windows
        system("cls"); // Limpiar pantalla
    }

    return 0;
}

// 🔹 Función para inicializar el tablero
void inicializar_tablero(vector<vector<int>>& tablero, int tamano, bool patron) {
    srand(time(0));

    if (patron) {
        // 🟢 Patrón Planeador
        int x = 1, y = 1;
        tablero[x][y + 1] = 1;
        tablero[x + 1][y + 2] = 1;
        tablero[x + 2][y] = 1;
        tablero[x + 2][y + 1] = 1;
        tablero[x + 2][y + 2] = 1;
    }
    else {
        // 🔹 Inicialización aleatoria
        for (int i = 0; i < tamano; ++i) {
            for (int j = 0; j < tamano; ++j) {
                tablero[i][j] = rand() % 2;
            }
        }
    }
}

// 🔹 Función para contar vecinos vivos
int calcular_vecinos_vivos(const vector<vector<int>>& tablero, int fila, int columna, int tamano) {
    int vecinos = 0;
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; i++) {
        int nx = fila + dx[i], ny = columna + dy[i];
        if (nx >= 0 && nx < tamano && ny >= 0 && ny < tamano) {
            vecinos += tablero[nx][ny];
        }
    }
    return vecinos;
}

// 🔹 Función para actualizar el tablero según las reglas del juego
void actualizar_tablero(vector<vector<int>>& tablero, int tamano) {
    vector<vector<int>> nuevo_tablero = tablero;

    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            int vecinos = calcular_vecinos_vivos(tablero, i, j, tamano);
            if (tablero[i][j] == 1) {
                // 🔹 Muere por subpoblación o sobrepoblación
                if (vecinos < 2 || vecinos > 3) {
                    nuevo_tablero[i][j] = 0;
                }
            }
            else {
                // 🔹 Nace una célula por reproducción
                if (vecinos == 3) {
                    nuevo_tablero[i][j] = 1;
                }
            }
        }
    }
    tablero = nuevo_tablero;
}

// 🔹 Función para imprimir el tablero
void imprimir_tablero(const vector<vector<int>>& tablero, int tamano) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            cout << (tablero[i][j] ? "■ " : "  ");
        }
        cout << endl;
    }
}
