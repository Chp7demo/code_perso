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
    mPos v_up, v_down, v_left, v_right; // index des voisins -1 si pas de voisins


    public:
    mPos get_pos(){return pos;}
    void set_power(int _power){power=_power;}
    int get_power(){return power;}
    
    mPos get_v_up(){return v_up;}
    mPos get_v_down(){return v_down;}
    mPos get_v_left(){return v_left;}
    mPos get_v_right(){return v_right;}
    
    
    void set_v_up(mPos _v_up){v_up=_v_up;}
    void set_v_down(mPos _v_down){v_down=_v_down;}
    void set_v_left(mPos _v_left){v_left=_v_left;}
    void set_v_right(mPos _v_rigth){v_right=v_right;}
    
    
};

class grid
{
//vector<Node> all_nodes; // todo, a changer, associer une position ?
map<mPos,Node> all_nodes;
map<int,int> bridge_map;

public:

grid(gridMatr gm);

map<mPos,Node>* nodes_ptr(){return &all_nodes;}

};

void print_nodes(map<mPos,Node>* node_map,ofstream& stream_sortie)
{
for(auto it=node_map->begin();it==node_map->end();it++)
{
    stream_sortie << it->first.x <<' ' << it->first.x << endl;
    stream_sortie << '\t'<< "up :" << node_map->at(it->second.get_v_up()).get_power();
    stream_sortie << '\t'<< "left :" << node_map->at(it->second.get_v_left()).get_power();
    stream_sortie << '\t'<< "right :" << node_map->at(it->second.get_v_right()).get_power();
    stream_sortie << '\t'<< "down :" << node_map->at(it->second.get_v_down()).get_power();
    stream_sortie <<endl <<endl;
}
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

 // parcourir la liste des nodes pour attribuer les voisins  left et right 
cpt_ligne=0;
 for(auto ligne:gm)
    {
        cpt_ligne++;
        bool first_node=true;
        int cpt_col=0;
        for(auto col:ligne){
            cpt_col++;
            mPos pos(cpt_ligne,cpt_col);
            Node stock_node;
            if(col!='.'){
                stock_node=all_nodes[pos];
                if(first_node) {first_node=false;}
                else{
                    all_nodes[pos].set_v_left(stock_node.get_pos());
                    stock_node.set_v_right(pos);
                }
                }
            }
    }

 // parcourir la liste des nodes pour attribuer les voisins  up  et down 
int cpt_colonne=0;
 for(auto colonne:gm)
    {
        cpt_colonne++;
        bool first_node=true;
        int cpt_li=0;
        for(auto li:colonne){
            cpt_li++;
            mPos pos(cpt_li,cpt_colonne);
            Node stock_node;
            if(li!='.'){
                stock_node=all_nodes[pos];
                if(first_node) {first_node=false;}
                else{
                    all_nodes[pos].set_v_up(stock_node.get_pos());
                    stock_node.set_v_down(pos);
                }
                }
            }
    }

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


    //string out_file_name="fichier_check_nodes";
    ofstream of_str_check_nodes;
    of_str_check_nodes.open("fichier_check_nodes");


    grid grid_1(gm);

    print_nodes(grid_1.nodes_ptr(),of_str_check_nodes);



    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // Two coordinates and one integer: a node, one of its neighbors, the number of links connecting them.
    cout << "rien pour l'instant" << endl;

    return 0;
}
