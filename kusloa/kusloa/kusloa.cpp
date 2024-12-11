#include <iostream> 
#include <climits> 
#include <cstdlib> 
#include <ctime> 
#include <conio.h> 


using namespace std;

void initGraph(int** graph, int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 10 - 1;
        }
    }
}


void printGraph(int** graph, int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (graph[i][j] == INT_MAX)
                cout << "Бесконечность... ";
            else
                cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}


bool bellmanFord(int** graph, int vert, int start, int* distance) {
    //int* distance = new int[vert]; 

    for (int i = 0; i < vert; i++) {
        distance[i] = INT_MAX;
    }
    distance[start] = 0;

    for (int i = 1; i < vert; i++) {
        for (int u = 0; u < vert; u++) {
            for (int v = 0; v < vert; v++) {
                if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                    distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    for (int u = 0; u < vert; u++) {
        for (int v = 0; v < vert; v++) {
            if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                cout << "Граф содержит отрицательный цикл!" << endl;
                return true;
            }
        }
    }
    return false;
}

//

void menu() {

    while (true) {
        int choose;

        cout << "MENU\n1.Поиск расстояния до определенной вершины \n2.Об авторе \n3. Выход\n" << endl;

        cout << "Выберите пункт: ";
        cin >> choose;

        switch (choose) {
            case(1): {
                system("cls");

                int vertices;

                cout << "Введите количество вершин: ";
                cin >> vertices;

                while (vertices <= 0) {
                    cout << "Количество вершин должно быть больше нуля." << endl;
                    cout << "Повторите ввод." << endl;
                    cin >> vertices;
                }

                int** graph = new int* [vertices];
                for (int i = 0; i < vertices; i++) {
                    graph[i] = new int[vertices];
                }

                initGraph(graph, vertices);
                cout << "Начальная матрица смежности:" << endl;
                printGraph(graph, vertices);

                int startV;

                while (true) {
                    cout << endl << "Введите начальную вершину (от 0 до " << vertices - 1 << "): ";
                    cin >> startV;

                    if (startV < 0 || startV >= vertices) {
                        cout << "Некорректный номер вершины." << endl;
                        cout << "Повторите ввод." << endl;
                    }
                    else {
                        break;
                    }
                }

                int* distance = new int[vertices];

                // Проверяем на наличие отрицательного цикла
                if (bellmanFord(graph, vertices, startV, distance)) {
                    
                    for (int i = 0; i < vertices; i++) {
                        delete[] graph[i];
                    }
                    delete[] graph;

                    system("pause");
                    system("cls");
                    
                    break;
                }

                int targetV;

                while (true) {

                    cout << endl << "Введите целевую вершину для поиска расстояния (от 0 до " << vertices - 1 << "): ";
                    cin >> targetV;

                    if (targetV < 0 || targetV >= vertices) {
                        cout << "Некорректный номер вершины." << endl;
                        cout << "Повторите ввод." << endl;
                    }
                    else {
                        break;
                    }
                }

                if (distance[targetV] == INT_MAX)
                    cout << endl << "Расстояние до вершины " << targetV << ": Бесконечность" << endl << endl << endl;
                else
                    cout << endl << "Расстояние до вершины " << targetV << ": " << distance[targetV] << endl << endl << endl;

                delete[] distance;

                for (int i = 0; i < vertices; i++) {
                    delete[] graph[i];
                }
                delete[] graph;

                system("pause");
                system("cls");
                menu();
            }

            case(2): {
                system("cls");

                cout << "\n\n\t\t\tРаботу выполнил студент группы 23ВВВ3 Гуреев Денис Романович" << endl << endl << endl;

                system("pause");
                system("cls");
                menu();
            }
            case(3): {
                system("cls");

                cout << "ДО СВИДАНИЯ!!!" << endl;

                exit(0);
            }

            default: {
                cout << "Некорректный выбор. Попробуйте снова." << endl << endl;
                system("pause");
                system("cls");
                menu();
            }               
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    menu();

    return 0;
}