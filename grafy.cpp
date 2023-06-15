#include "grafy.h"

Graph::Graph(int v) {
    vert_num = v;
    edge_num = 0;
    G.resize(v);
}

//wczytywanie i wypisywanie

void Graph::add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
    edge_num++;
}

void Graph::load_graph() {
    std::cout << "Podaj ilość wierzchołków:\n";
    std::cin >> vert_num;
    G.resize(vert_num);
    std::cout << "Podaj ilość krawędzi:\n";
    int edges;
    std::cin >> edges;
    for (int i = 0; i < edges; i++) {
        std::cout << "Podaj krawedź nr "<<i+1<<":\n";
        int a, b;
        std::cin >> a >> b;
        add_edge(a, b);
    }
}

void Graph::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Nie można otworzyć pliku.\n";
        return;
    }
    file >> vert_num;
    G.resize(vert_num);
    for (int i = 0; i < vert_num; ++i) {
        for (int j = 0; j < vert_num; ++j) {
            int val;
            file >> val;
            if (val == 1 && i != j) {
                bool edgeExists = std::find(G[i].begin(), G[i].end(), j) != G[i].end();
                if (!edgeExists) {
                    add_edge(i, j);
                }
            }
        }
    }
    file.close();
}

void Graph::print_graph() {
    std::cout<<"Macierz sąsiedztwa dla wczytanego grafu:\n";
    for (int i = 0; i < vert_num; ++i) {
        for (int j = 0; j < vert_num; ++j) {
            if (std::find(G[i].begin(), G[i].end(), j) != G[i].end())
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

//eulerowe rzeczy 

void Graph::DFS(int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (int i = 0; i < G[v].size(); ++i) {
        int neighbor = G[v][i];
        if (!visited[neighbor])
            DFS(neighbor, visited);
    }
}

bool Graph::isConnected() {
    std::vector<bool> visited(vert_num, false);
    DFS(0, visited);
    for (int i = 0; i < vert_num; ++i) {
        if (!visited[i])
            return false;
    }
    return true;
}

bool Graph::hasEulerCycle() {
    if (!G.empty()) {
        if (!isConnected())
            return false;
        for (int i = 0; i < vert_num; ++i) {
            if (G[i].size() % 2 != 0)
                return false;
        }
        return true;
    }
    return false;
}

bool Graph::hasEulerPath() {
    if (!G.empty()) {
        if (!isConnected())
            return false;
        int oddDegreeCount = 0;
        for (int i = 0; i < vert_num; ++i) {
            if (G[i].size() % 2 != 0) {
                oddDegreeCount++;
                if (oddDegreeCount > 2)
                    return false;
            }
        }
        if(oddDegreeCount%2==0)
            return true;
        return false;
    }
    return false;
}

void Graph::hierholzer(bool T) {

    if(!T){
        if(!hasEulerCycle()){
        std::cout << "Graf nie ma cyklu Eulera." << std::endl;
        return;
        }
    }
    else{
        if (!hasEulerPath()) {
            std::cout << "Graf nie ma drogi Eulera." << std::endl;
            return;
        }
    }
    std::vector<int> path;
    std::vector<std::vector<int> > G_copy = G;
    std::stack<int> st;
    int current_v = 0;
    st.push(current_v);

    while (!st.empty()) {
        current_v = st.top();

        if (!G[current_v].empty()) {
            int next_v = G[current_v].back();
            st.push(next_v);
            G[current_v].pop_back();
            G[next_v].erase(std::find(G[next_v].begin(), G[next_v].end(), current_v));
        }
        else {
            path.push_back(current_v);
            st.pop();
        }
    }

    std::cout << "Droga Eulera (Hierholzera z użyciem stosu):\n";
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;

    G = G_copy;
}

//menu functions
void printMenu(){
    system("clear");
    std::cout<<"Wybierz co chcesz zrobić:\n\n";
    std::cout<<"1 - Wprowadz graf recznie.\n";
    std::cout<<"2 - Wczytaj przykładowy graf nr. 1.\n";
    std::cout<<"3 - Wczytaj przykładowy graf nr. 2.\n";
    std::cout<<"4 - Zakoncz program.\n";
}

void graf_options(){
    system("clear");
    std::cout<<"Wybierz co chcesz zrobić:\n\n";
    std::cout<<"1 - Wypisz graf(macierz sąsiedztwa).\n";
    std::cout<<"2 - Sprawdz czy ma drogę Eulera.\n";
    std::cout<<"3 - Sprawdz czy ma cykl Eulera.\n";
    std::cout<<"4 - Wypisz drogę Eulera.\n";
    std::cout<<"5 - Wypisz cykl Eulera.\n";
    std::cout<<"6 - Wczytaj inny graf.\n";
    std::cout<<"7 - Zakończ program.\n";
}

int choose(int n){
    int a=-1;
    while(!(a>0 and a <=n)){
        std::cout<<"->";
        std::cin>>a;
        if(!(a>0 and a <=n))
            std::cout<<"Podaj właściwy numer!\n";
    }
    return a;
}

void waitForKeypress(){
    std::cout << "Naciśnij dowolny klawisz, aby kontynuować...";
    std::cout.flush();
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    char dummy;
    read(STDIN_FILENO, &dummy, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}