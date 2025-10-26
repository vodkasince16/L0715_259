#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>
using namespace std;

class Graph {
    
private:

    struct Edge { //Данные о элементе графа
        int y; //информация о смежности
        struct Edge *next; //указатель на след. ребро
        #ifdef 1
        EdgeNode(int vertex) : y(vertex), next(nullptr) {}
        #endif
    };

    //Основные данные графа

    vector<Edge*> edges;    //степени смежности
    vector<int> degree;                         //степени вершин
    int nvertices;                              //кол-во вершин    
    int nedges;                                 //кол-во ребер
    bool dir;
    int max_vertices = 100; //ограничение как у скиены(скорее всего только в знак уважения)

public:

    void init_graph(Graph *g, bool dir){ //инициализация графа
        g->nvertices = 0;
        g->nedges = 0;
        g->dir  = dir;

        for (int i = 0; i < max_vertices; i++)
        {
            g->edges[i] = nullptr;
            g->degree[i] = 0;

        }

    }
    void ins_edge(Graph *g, int x, int y, bool dir) {
        Edge *p;
        p = new Edge;
        p->y = y;
        p->next = g->edges[x];
        g->edges[x] = p;
        g->degree[x]++;

        if (!dir){
            ins_edge(g, y, x, 1);
        }
        else{
        g->nedges++;
        }
    }
    void read_graph(Graph *g, bool dir){  //функция считывания и создания граффа
        int m, x, y;
        cout << "Введите кол-во узлов в графе: ";
        cin >> g->nvertices;
        cout << "Введите кол-во ребер графа: ";
        cin >> m;
        cout << "Функция ввода графа, пишите узлы парами: x y (x->y)"<< endl;
        cout << "Для завершения введите отрицательное значение узла"<< endl;
        
        int m, x, y;

        init_graph(g, dir);
        for (int i = 0 ; i < m; i++){
            cin >> x >> y;
            ins_edge(g ,x, y, dir);
            
            #ifdef 1
            if (x < 1 || x > g->nvertices || y < 1 || y > g->nvertices) {
            cout << "Ошибка: вершины должны быть от 1 до " << g->nvertices << endl;
            i--; // повторяем эту итерацию
            continue;
            }
            #endif   //проверка на дурака
        }
    }

    void print_graph(Graph *g){
        Edge *p;
        for (int i = 0; i < g->nvertices; i++){
            cout << i <<" ";
            p = g->edges[i];
            while (p != nullptr){
                cout << "-> "<< p->y; 
                p = p->next;
            }
        cout << endl;
        }
    }
}
