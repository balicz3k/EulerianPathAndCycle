#include <iostream>
#include "grafy.h"

int main(){
    bool end=false;
    while(!end){
        bool option=false;
        Graph g(0);
        printMenu();
        switch(choose(4)){
            case 1:
                g.load_graph();
                waitForKeypress();
                break;
            case 2:
                g.load_from_file("graf1");
                waitForKeypress();
                break;
            case 3:
                g.load_from_file("graf2");
                waitForKeypress();
                break;
            case 4:
                end=true;
                break;
        }
        if(!end){
            while (!option){
                bool option2=false;
                graf_options();
                switch(choose(7)){
                case 1:
                    g.print_graph();
                    waitForKeypress();
                    break;
                case 2:
                    if(g.hasEulerPath())
                        std::cout<<"Graf ma drogę Eulera.\n";
                    else 
                        std::cout<<"Graf nie ma drogi Eulera.\n";
                    waitForKeypress();
                    break;
                case 3:
                    if(g.hasEulerCycle())
                        std::cout<<"Graf ma cykl Eulera.\n";
                    else 
                        std::cout<<"Graf nie ma cyklu Eulera.\n";
                    waitForKeypress();
                    break;
                case 4:
                    g.hierholzer(1);
                    waitForKeypress();
                    break;
                case 5:
                    g.hierholzer(0);
                    waitForKeypress();
                    break;
                case 6:
                        option=true;
                        break;
                case 7:
                        option=true;
                        end=true;
                        break;
                }
            }
        }
    }
}