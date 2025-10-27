#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>
#include <queue>
#include "graph.hpp"
using namespace std;

class Graph {
    
private:

    struct Edge { //Данные о элементе графа
        int y; //информация о смежности
        struct Edge *next; //указатель на след. ребро
        #ifdef 1
        Edge(int vertex) : y(vertex), next(nullptr) {}
        #endif
    };

    //Основные данные графа

    vector<Edge*> edges;    //степени смежности
    vector<int> degree;                         //степени узлов
public:
    int nvertices;                              //кол-во узлов 
private:   
    int nedges;                                 //кол-во ребер
    vector<int> color;                       //"цвет" узла
    bool dir;
    vector<bool> visited;  //    2 переменные для обхода в ширину
    vector<bool> processed; //   ||||||||||||||||||||||||||||||||
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

    void process_edge(int x, int y); //доопределим потом

    void pred_bfs(Graph *g){        
        g->visited.assign(g->nvertices, false);
        g->processed.assign(g->nvertices, false);
    }
    void bfs(Graph *g, int start){  //Обход в ширину

        queue<int> q;
        int v;
        int y;
        Edge *p;

        g->visited[start] = 1;
        q.push(start);

        while (!q.empty()) {
            v = q.front();
            q.pop();
            #ifdef 1
            process_vertex_early(v); //пояснение ниже
            #endif
            g->processed[v] = 1;
            p = g->edges[v];
            while (p != NULL){
                y = p->y;
                if ((!g->processed[y])||(g->dir)){
                    process_edge(g, v, y); //пояснение ниже
                }
                if (!g->visited[y]){
                    q.push(y);
                    g->visited[y] = true;
                }
            p = p->next;
            }

        }
    }
    
    //process_vetrex_early и process_edge - функции обработки узла и ребра соотвественно
    //process_vetrex_early - early потому что обрабатываем при извлечении вершины из очерди
    //можем ввести process_vetrex_late после обработки всех соседей
    //эти функции мы редактируем под свои задачи, оставляем пустыми или удаляем

    //в алгоритме расскраски двумя цветами нам нужно только process_edge
    //определим его 
private:

    void process_edge(Graph *g, int x, int y) {
        if (g->color[x] == g->color[y]){
        cout << "Граф не является двудольным, раскраска в два цвета невозможна :"<<endl;
        return;            
        }
        g->color[y] = rev(g->color[x]);     
    }
    
    int rev(int x){  //функция обратного значения для int 
        return 1-x;
    }

public:

    void two_color(Graph *g){
        for (int i = 0; i < g->nvertices; i++) g->color[i] = 2;
        pred_bfs(g);
        for (int i = 0; i < g->nvertices; i++){
            if (!g->visited[i]){
                g->color[i] = 0;
                bfs(g, i);
            }
        }
   
    }

    void print_color_graph(Graph *g){
        Edge *p;
        for (int i = 0; i < g->nvertices; i++){
            cout << i <<"(Цвет: "<< g->color[i] << " ) ";
            p = g->edges[i];
            while (p != nullptr){
                cout << "-> "<< p->y << "(Цвет: "<< g->color[p->y]<< ") "; 
                p = p->next;
            }
        cout << endl;
        }
}
};


