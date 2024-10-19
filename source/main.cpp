#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include <fstream>
#include <map>
#include <unordered_map>
#include <string>

#include <stdio.h>
#include <stdlib.h>


using namespace std;

/**
 * The machines are gaining ground. Time to show them what we're really made of...
 **/
typedef vector<string> gridMatr; 

struct mPos{
int x=-1;
int y=-1;
mPos()=default;
mPos(int _x, int _y) : x{_x},y{_y}{};

//bool pos_compare(const mPos&,const mPos&){};
};




struct cmp_pos{
    bool operator()(const mPos& mp_1, const mPos& mp_2) const {
       if(mp_1.x <= mp_2.x && mp_1.y < mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y > mp_2.y) return false;
    if(mp_1.x <= mp_2.x && mp_1.y > mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y < mp_2.y) return false;
    return false;
    }
};

/*bool mPos::pos_compare(const mPos& mp_1, const mPos& mp_2)
{
    if(mp_1.x <= mp_2.x && mp_1.y < mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y > mp_2.y) return false;
    if(mp_1.x <= mp_2.x && mp_1.y > mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y < mp_2.y) return false;
    return false;
}*/

class Node
{

    mPos pos;
    int power;
    int nb_bridge;
    int v_up, v_down, v_left, v_right; // index des voisins -1,-1 si pas de voisins



    public:
    Node(){int mpnul=-1;v_up=mpnul;v_down=mpnul;v_left=mpnul;v_right=mpnul;};

    mPos get_pos(){return pos;}
    void set_pos(mPos p){pos=p;}

    void set_power(int _power){power=_power;}
    int get_power(){return power;}
    
    int get_v_up(){return v_up;}
    int get_v_down(){return v_down;}
    int get_v_left(){return v_left;}
    int get_v_right(){return v_right;}
    
    
    void set_v_up(int _v_up){v_up=_v_up;}
    void set_v_down(int _v_down){v_down=_v_down;}
    void set_v_left(int _v_left){v_left=_v_left;}
    void set_v_right(int _v_right){v_right=_v_right;}
    
    
};

class grid
{
//vector<Node> all_nodes; // todo, a changer, associer une position ?
vector<Node> all_nodes;
map<int,int> bridge_map;

public:

grid(gridMatr gm);

vector<Node>* nodes_ptr(){return &all_nodes;}

};

void print_nodes(vector<Node>* all_nodes,ofstream& stream_sortie)
{
/*    
for(auto it=node_map->begin();it!=node_map->end();it++)
{
    stream_sortie << it->first.x <<' ' << it->first.y << endl;
    stream_sortie << '\t'<< "up :" << (*node_map)[it->second.get_v_up()].get_power() << endl;
    stream_sortie << '\t'<< "left :" << (*node_map)[it->second.get_v_left()].get_power() << endl;
    stream_sortie << '\t'<< "right :" << (*node_map)[it->second.get_v_right()].get_power() << endl;
    stream_sortie << '\t'<< "down :" << (*node_map)[it->second.get_v_down()].get_power() << endl;
    stream_sortie <<endl <<endl;
}*/
for(auto el: *all_nodes)
{
    // cout<<"printing nodes"<<endl;
    // cout<<"taille all_nodes"<< all_nodes->size()<<endl;
    stream_sortie << el.get_pos().x <<' ' << el.get_pos().y <<' '<<el.get_power()<< endl;   
    if(el.get_v_up()!=-1)
    stream_sortie << '\t'<< "up :" << all_nodes->at(el.get_v_up()).get_power() << endl;
    if(el.get_v_left()!=-1)
    stream_sortie << '\t'<< "left :" << all_nodes->at(el.get_v_left()).get_power() << endl;
    if(el.get_v_right()!=-1)
    stream_sortie << '\t'<< "right :" << all_nodes->at(el.get_v_right()).get_power() << endl;
    if(el.get_v_down()!=-1)
    stream_sortie << '\t'<< "down :" << all_nodes->at(el.get_v_down()).get_power() << endl;
    stream_sortie <<endl <<endl;
}
};

grid::grid(gridMatr gm)
{
 // liste des nodes   
 // todo associer une position au nodes
     int N_col=gm.at(0).size(); cout<<gm.at(0)<<" N_col:" <<N_col<<endl;
     int N_ligne=gm.size();cout<<"N_ligne"<<N_ligne<<endl;


    int cpt_ligne=0;
    for(auto ligne:gm)
    {
        //cout<<"cpt_ligne: "<<cpt_ligne<<endl;
        int cpt_col=0;
        for(auto col:ligne){
            
            if(col!='.'){
                Node new_node;
                string col_s;
                col_s=col;
                int power=std::stoi(col_s);
                new_node.set_power(power);             
                mPos pos(cpt_col,cpt_ligne);
                new_node.set_pos(pos);
                all_nodes.push_back(new_node);
                
                }
            cpt_col++;
            }
    cpt_ligne++;
    }

 // parcourir les nodes pour attribuer les voisins  left et right 

int cpt_node=0;
 for(size_t i=0;i<N_ligne;i++)
    { 
        bool first_node=true;
        
        for(int ind_col=0;ind_col<N_col;ind_col++){  
            
            
            if(gm.at(i).at(ind_col)!='.'){

               
               //cout <<"cpt node :"<<cpt_node<<endl;

                if(first_node) {first_node=false;}
                else{
                   // cout <<"cpt node :"<<cpt_node<<endl;
                    all_nodes.at(cpt_node).set_v_left(cpt_node-1);
                    all_nodes.at(cpt_node-1).set_v_right(cpt_node);
                }
                 cpt_node++;    
                }
            }
    }
cout<<"passe ici"<<endl;
 // parcourir la liste des nodes pour attribuer les voisins  up  et down 

 for(int col=0;col<N_col;col++) // pas optimal
    { 
        //creaction d'un vect col contenant les indices des nodes
        vector<int> vect_col{};
        for(int k=0; k<all_nodes.size();k++){if(all_nodes.at(k).get_pos().x==col){vect_col.push_back(k);}}
        //cout<<"vect_col.size()"<<vect_col.size()<<endl;

        for(int l=1; l<vect_col.size();l++){
            
            all_nodes.at(vect_col.at(l)).set_v_up(vect_col.at(l-1));
            all_nodes.at(vect_col.at(l-1)).set_v_down(vect_col.at(l));

        }

        /*bool first_node=true;
        int cpt=0;
        for(int ind_li=0;ind_li<N_ligne;ind_li++){  
            
            
            if(gm.at(ind_li).at(col)!='.'){


                if(first_node) {first_node=false;}
                else{
                    all_nodes.at(vect_col.at(cpt)).set_v_up(vect_col.at(cpt-1));
                    all_nodes.at(vect_col.at(cpt-1)).set_v_down(vect_col.at(cpt));
                }
                cpt++;
                }
            }*/
    }
cout<<"pass la "<<endl;
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
    cout << "rien pour l'instant " << endl;

    return 0;
}
