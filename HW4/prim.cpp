#include <iostream>
#include <string>
#include <fstream>
#include <array>


void trace_code(std::array<int, 26> &connect, std::array<int, 26> &shortest, std::array<bool, 26> &visited);

int main(){

    // open File
    std::string fileName;
    std::cout << "enter file name : ";
    std::cin >> fileName;
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName);
    outFile.open("output_p.txt");
    if(inFile.fail() || outFile.fail()){
        std::cout << "Fail to open file" << std::endl;
        return 1;
    }
    fileName.clear(); // free up space fileName
    
    // file input
    int n_edge;
    inFile >> n_edge;

    int adjacent[26][26] = {0};
    char vertex1, vertex2, start;
    int weight;

    for(int i = 0; i < n_edge; i++){
        inFile >> vertex1;
        //std::cout << vertex1 << " ";
        inFile >> vertex2;
        //std::cout << vertex2 << " ";
        inFile >> weight;
        //std::cout << weight << " ";
        adjacent[vertex1-'a'][vertex2-'a'] = weight;
        adjacent[vertex2-'a'][vertex1-'a'] = weight;
    }
    inFile >> start;
    //std::cout << start << "\n";

    // count the number of vertices
    int numVert = 0;
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < 26; j++)
            if(adjacent[i][j]){
                numVert++;
                break;
            }
    std::cout << numVert << std::endl;

    // print adjacency matrix for debugging
    /*
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            std::cout << adjacent[i][j] << " ";
        }
        std::cout << "\n";
    }
    */

    std::array<int, 26> connect;
    std::array<int, 26> shortest;
    std::array<bool, 26> visited;
    connect.fill(-1);
    shortest.fill(std::numeric_limits<int>::max());
    visited.fill(false);

    // starting point 
    shortest[start - 'a'] = 0;
    visited[start - 'a'] = true;

    //trace_code(connect, shortest, visited);
    
    int index = start - 'a';
    int min;

    for(int j = 1; j < numVert; j++){
        
        for(int i = 0; i < 26; i++)
            if(adjacent[index][i])
                if(adjacent[index][i] && adjacent[index][i] < shortest[i]){
                    shortest[i] = adjacent[index][i];
                    connect[i] = index;
                }
        //trace_code(connect, shortest, visited);

        min = std::numeric_limits<int>::max();

        for(int i = 0; i < 26; i++) {
            if(!visited[i])
                if(shortest[i] < min){
                    min = shortest[i];
                    index = i;
                }
        }
        visited[index] = true;
        //trace_code(connect, shortest, visited);
    }

    for(int i = 1; i < numVert; i++){
        min = std::numeric_limits<int>::max();
        for(int i = 0; i < numVert; i++){
            if(shortest[i] && shortest[i] < min){
                min = shortest[i];
                index = i;
            }
        }
        //std::cout << index << " " << shortest[index] << std::endl;
        vertex1 = (char)index+'a';
        vertex2 = (char)connect[index]+'a';
        if(index < connect[index]){
            std::cout << vertex1 << " " << vertex2 << " " << shortest[index] << std::endl;
            outFile << vertex1 << " " << vertex2 << " " << shortest[index] << std::endl;
        }else {
            std::cout << vertex2 << " " << vertex1 << " " << shortest[index] << std::endl;
            outFile << vertex2 << " " << vertex1 << " " << shortest[index] << std::endl;
        }
        
        shortest[index] = 0;
    }
}


void trace_code(std::array<int, 26>& connect, std::array<int, 26>& shortest, std::array<bool, 26>& visited){
    
    std::cout << std::endl;    

    for(int i = 0; i < connect.size(); i++)
        std::cout << connect[i] << " ";
    std::cout << std::endl;

    for(int i = 0; i < connect.size(); i++){
        if(shortest[i] == std::numeric_limits<int>::max())
            std::cout << ". ";
        else
            std::cout << shortest[i] << " ";
    }   
    std::cout << std::endl;
    
    for(int i = 0; i < connect.size(); i++)
        std::cout << visited[i] << " ";
    std::cout << std::endl;
}
