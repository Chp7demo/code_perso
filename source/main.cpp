#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include <fstream>
#include <map>
#include <list>
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

int max(int a, int b){
    if(a>b)return a;
    if(b>a)return b;
    return -1;}

int min(int a, int b){
    if(a>b)return b;
    if(b>a)return a;
    return -1;}


struct cmp_pos{
    bool operator()(const mPos& mp_1, const mPos& mp_2) const {
       if(mp_1.x <= mp_2.x && mp_1.y < mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y > mp_2.y) return false;
    if(mp_1.x <= mp_2.x && mp_1.y > mp_2.y) return true;
    if(mp_1.x >= mp_2.x && mp_1.y < mp_2.y) return false;
    return false;
    }
};

int coord_pict(int coord_non_pict)
{
    int c_pict=2*coord_non_pict;
    return c_pict;
}

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

class Bridge{

Node* ptr_node1;
Node* ptr_node2;

int power=0; //  1 ou 2 ponts

public:

Bridge(Node* node_1,Node* node_2) : ptr_node1{node_1},ptr_node2{node_2}{
    
ptr_node1->set_power((ptr_node1->get_power())-1);
ptr_node2->set_power((ptr_node2->get_power())-1);
power++;

};

int get_power(){return power;}
void set_power(int _power){power=_power;}



};

class grid
{
//vector<Node> all_nodes; // todo, a changer, associer une position ?
vector<Node> all_nodes;
vector<vector<int>> bridge_matr;//matrice ind node- ind node avec l'indice du bridge ds la liste ou -1;  
gridMatr grid_picture;
vector<Bridge> bridge_list;

public:

grid(gridMatr gm);
gridMatr get_gpicture(){return grid_picture;} // penser à allerger, avec string_view par exemple
void ajouner_picture();

bool make_bridge(int, int);
vector<Node>* nodes_ptr(){return &all_nodes;}

};

void grid::ajouner_picture()
{
    int cpt_node=0;
    int cpt_li=0;
    for(auto el:grid_picture){ // colonne (un string ligne)
        int cpt_col=0;
       for(auto lettre:el){
        if(lettre!='.' && lettre != '|' && lettre != '-'){
            char ch='0'+(all_nodes.at(cpt_node).get_power());
            grid_picture.at(cpt_li).at(cpt_col)=ch;
            cpt_node++;
        }
        cpt_col++;
       }
       cpt_li++;
    }
}

void print_nodes(vector<Node>* all_nodes,ofstream& stream_sortie)
{

for(auto el: *all_nodes)
{
    
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

        
    }

//remplir grid picture 


for(int l=0;l<N_ligne;l++)
{
    string ligne_gpicture;
    string ligne_point;
    for(int c=0;c<N_col;c++)
    {
        ligne_gpicture+=gm.at(l).at(c);
        ligne_gpicture+='.';
        ligne_point+="..";
    }
    grid_picture.push_back(ligne_gpicture);
    grid_picture.push_back(ligne_point);
   
}

//mise a zero (-1) de la matrice des ponts

for(int i=0;i<all_nodes.size();i++){
    vector<int> vect_ligne;
    for(int j=0;j<all_nodes.size();j++){
        vect_ligne.push_back(-1);
    }
    bridge_matr.push_back(vect_ligne);
}

}

bool grid::make_bridge(int a,int b){

if(bridge_matr.at(a).at(b) != -1)
{
if(bridge_list.at(bridge_matr.at(a).at(b)).get_power()>=2)
{
cout << "le pont est déjà un double pont" <<endl;    
return false;
}
if(bridge_list.at(bridge_matr.at(a).at(b)).get_power()==1)
{
bridge_list.at(bridge_matr.at(a).at(b)).set_power(2);
all_nodes.at(a).set_power((all_nodes.at(a).get_power())-1);
all_nodes.at(b).set_power((all_nodes.at(b).get_power())-1);
}
}
else{
Bridge new_bridge(&all_nodes.at(a),&all_nodes.at(b));
new_bridge.set_power(1);
bridge_list.push_back(new_bridge);
bridge_matr.at(a).at(b)= bridge_list.size()-1;//indice dernier element
bridge_matr.at(b).at(a)= bridge_list.size()-1;// "
}

int x_a=all_nodes.at(a).get_pos().x; cout<<"x_a "<<x_a<<endl;
int y_a=all_nodes.at(a).get_pos().y;
int x_b=all_nodes.at(b).get_pos().x; cout<<"x_b "<<x_b<<endl;
int y_b=all_nodes.at(b).get_pos().y;

int x_a_p=coord_pict(x_a);cout<<"x_a_p "<<x_a_p<<endl;
int x_b_p=coord_pict(x_b);cout<<"x_b_p "<<x_a_p<<endl;
int y_a_p=coord_pict(y_a);cout<<"y_a_p "<<x_a_p<<endl;
int y_b_p=coord_pict(y_b);cout<<"y_b_p "<<x_a_p<<endl;



if(x_a!=x_b && y_a!=y_b){cout<<"erreur pont"<<endl;}
else{
if(y_a==y_b){

cout<<"min(x_a_p,x_b_p) "<<min(x_a_p,x_b_p)<<"max(x_a_p,x_b_p) "<<max(x_a_p,x_b_p)<<endl;
for (int i= min(x_a_p,x_b_p)+1;i<max(x_a_p,x_b_p);i++)
{    
    cout<<"i = "<<i<<endl;
    grid_picture.at(y_a_p).at(i)='-';
    //grid_picture.at(i).at(y_a_p)='-';
}

}

if(x_a==x_b){
cout<<"min(y_a_p,y_b_p) "<<min(y_a_p,y_b_p)<<"max(y_a_p,y_b_p) "<<max(y_a_p,y_b_p)<<endl;
for (int i= min(y_a_p,y_b_p)+1;i<max(y_a_p,y_b_p);i++)
{
    grid_picture.at(i).at(x_a_p)='|';
    //grid_picture.at(x_a_p).at(i)='|';
}

}
}
return true;//prov


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
    cout<<"matrice initiale"<<endl;
    for(auto el: gm) cout <<el<< endl;
    


    //string out_file_name="fichier_check_nodes";
    ofstream of_str_check_nodes;
    of_str_check_nodes.open("fichier_check_nodes");

    //->
    grid grid_1(gm);

    cout<<endl;
    cout<<"matrice picture"<<endl;
     for(auto el: grid_1.get_gpicture()) cout <<el<< endl;

    if(grid_1.make_bridge(2,6)){std::cout<<"pont crée"<<endl;}
    if(grid_1.make_bridge(0,1)){std::cout<<"pont crée"<<endl;}
    if(grid_1.make_bridge(7,13)){std::cout<<"pont crée"<<endl;}

    cout<<"matrice picture apres creation de deux ponts"<<endl;
    for(auto el: grid_1.get_gpicture()) cout <<el<< endl;

    grid_1.ajouner_picture();
     cout<<"matrice picture apres ajournement"<<endl;
    for(auto el: grid_1.get_gpicture()) cout <<el<< endl;

    if(grid_1.make_bridge(2,6)){std::cout<<"pont double crée"<<endl;}
    if(grid_1.make_bridge(7,13)){std::cout<<"pont double crée"<<endl;}
    //if(grid_1.make_bridge(0,1)){std::cout<<"pont double crée"<<endl;}

     cout<<"matrice picture apres creation de deux ponts doubles"<<endl;
    for(auto el: grid_1.get_gpicture()) cout <<el<< endl;

    grid_1.ajouner_picture();
     cout<<"matrice picture apres ajournement"<<endl;
    for(auto el: grid_1.get_gpicture()) cout <<el<< endl;

    cout << "tentative de faire un pont d'ordre 3" <<endl;
    grid_1.make_bridge(2,6);
    grid_1.make_bridge(0,1);

    print_nodes(grid_1.nodes_ptr(),of_str_check_nodes);



    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // Two coordinates and one integer: a node, one of its neighbors, the number of links connecting them.
    cout << "rien pour l'instant " << endl;

    return 0;
}
