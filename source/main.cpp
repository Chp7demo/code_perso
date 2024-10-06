#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include <fstream>


using namespace std;

/**
 * The machines are gaining ground. Time to show them what we're really made of...
 **/
typedef vector<string> gridMatr; 



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
