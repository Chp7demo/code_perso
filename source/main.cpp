#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include <fstream>
#include <map>
#include <string>

#include <stdio.h>
#include <stdlib.h>


using namespace std;

/**
 * The machines are gaining ground. Time to show them what we're really made of...
 **/
typedef vector<string> gridMatr; 

struct mPos{
int x;
int y;
mPos()=default;
mPos(int _x, int _y) : x{_x},y{_y}{};
};

class Node
{

    mPos pos;
    int power;
    int nb_bridge;
    int v_up, v_down, v_left, v_right; // index des voisins -1 si pas de voisins


    public:
    void set_power(int _power){power=_power;}
    int get_power(){return power;}
    
    int get_v_up(){return v_up;}
    int get_v_down(){return v_down;}
    int get_v_left(){return v_left;}
    int get_v_right(){return v_right;}
    
    
    int set_v_up(int _v_up){v_up=_v_up;}
    int set_v_down(int _v_down){v_down=_v_down;}
    int set_v_left(int _v_left){v_left=_v_left;}
    int set_v_right(int _v_rigth){v_right=v_right;}
    
};

class grid
{
//vector<Node> all_nodes; // todo, a changer, associer une position ?
map<mPos,Node> all_nodes;
map<int,int> bridge_map;

public:

grid(gridMatr gm);

};


grid::grid(gridMatr gm)
{
 // liste des nodes   
 // todo associer une position au nodes
    int cpt_ligne=0;
    for(auto ligne:gm)
    {
        cpt_ligne++;
        int cpt_col=0;
        for(auto col:ligne){
            cpt_col++;
            if(col!='.'){
                Node new_node;
                string col_s;
                col_s=col;
                int power=std::stoi(col_s);
                new_node.set_power(power);             
                mPos pos(cpt_ligne,cpt_col);
                all_nodes[pos]=new_node;
                }
            }
    }

 // parcourir la liste des node pour attribuer les voisins   




}


int main(int argc, char * argv[])
{
    int width; // the number of cells on the X axis
    //cin >> width; cin.ignore();
    width=10;// a changer selon le jeu simulé 

    int height; // the number of cells on the Y axis
    //cin >> height; cin.ignore();
    height=10; // a changer selon jeu simulé 

    /*for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line); // width characters, each either a number or a '.'
    }*/


    ifstream inputFile;
    inputFile.open(argv[1]);
    
    gridMatr gm;
    
    string lignefich;
    while(getline(inputFile,lignefich)){gm.push_back(lignefich);} 

    //verif matrice
    for(auto el: gm) cout <<el<< endl;



    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // Two coordinates and one integer: a node, one of its neighbors, the number of links connecting them.
    cout << "rien pour l'instant" << endl;

    return 0;
}
