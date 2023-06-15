#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <string>


class Graph {
    std::vector<std::vector<int> > G;
    int vert_num;
    int edge_num;

public:
    Graph(int v);
    void load_graph();
    void load_from_file(const std::string& filename);
    void print_graph();  

    bool hasEulerPath();
    bool hasEulerCycle();
    void hierholzer(bool T);
private:
    void DFS(int v, std::vector<bool>& visited);
    bool isConnected();  
    void add_edge(int a, int b);
};

void printMenu();
void graf_options();
void algorytmy();
int choose(int n);
void waitForKeypress();