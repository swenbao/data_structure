#include <iostream>
#include <string>
#include <fstream>
#include <array>

void trace_code(std::array<int, 26>& dist);

int main() {

    // open File
    std::string fileName;
    std::cout << "enter file name : ";
    std::cin >> fileName;
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName);
    outFile.open("output_d.txt");
    if(inFile.fail() || outFile.fail()){
        std::cout << "Fail to open file" << std::endl;
        return 1;
    }
    fileName.clear(); // free up space fileName
    
    // file input
    int n_edge;
    inFile >> n_edge;

    int edge[26][26];
    // initialize edge to infinity
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            if(i == j)
                edge[i][j] = 0;
            else
                edge[i][j] = std::numeric_limits<int>::max();
        }
    }

    char vertex1, vertex2, start;
    int weight;

    for(int i = 0; i < n_edge; i++){
        inFile >> vertex1;
        //std::cout << vertex1 << " ";
        inFile >> vertex2;
        //std::cout << vertex2 << " ";
        inFile >> weight;
        //std::cout << weight << " ";
        edge[vertex1-'a'][vertex2-'a'] = weight;
    }

    // print adjacency matrix for debugging
    /*
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            //std::cout << edge[i][j] << " ";
            outFile << edge[i][j] << " ";
        }   
        //std::cout << "\n";
        outFile << "\n";
    }
    */

    inFile >> start;
    //std::cout << start << "\n";
    
    std::array<int, 26> dist;
    std::array<int, 26> visited;
    visited.fill(false);

    // starting point
    visited[start-'a'] = true;
    for(int i = 0; i < 26; i++){
        dist[i] = edge[start-'a'][i];
    }
    //trace_code(dist);

    int min;
    int index;
    for(int i = 0; i < 26; i++){

        min = std::numeric_limits<int>::max();
        for(int i = 0; i < 26; i++){
            if(!visited[i] && dist[i] < min){
                min = dist[i];
                index = i;
            }
        }
        if(min == std::numeric_limits<int>::max()) break;

        //vertex1 = (char)index+'a';
        //std::cout << min << std::endl;
        //std::cout << index << " " <<  vertex1 << std::endl << std::endl << std::endl;

        visited[index] = true;

        /*bool empty = true;
        for(int i = 0; i < 26; i++){
            if(edge[index][i])
                empty = false;
        }
        if(empty) continue;*/

        for(int i = 0; i < 26; i++){
            //std::cout << "index : " << index << "\ni : " << i << "\n";
            //std::cout << edge[index][i] << std::endl;
            if(0 < edge[index][i] && edge[index][i] < std::numeric_limits<int>::max()){
                
                //std::cout << "index : " << index << "\ni : " << i << "\n";
                //std::cout << min << " + " << edge[index][i] << std::endl;
                //std::cout << dist[i] << std::endl;

                if(min + edge[index][i] < dist[i])
                    dist[i] = min + edge[index][i];
            }
        }

        //trace_code(dist);
    }

    while(true){
        min = std::numeric_limits<int>::max();
        for(int j = 0; j < 26; j++){
            if(dist[j] < min){
                min = dist[j];
                index = j;
            }
        }

        if(min == std::numeric_limits<int>::max()) break;

        vertex1 = index+'a';
        std::cout << vertex1 << " " << min << std::endl;
        outFile << vertex1 << " " << min << std::endl;

        dist[index] = std::numeric_limits<int>::max();
    }

}


void trace_code(std::array<int, 26>& dist){
    
    std::cout << std::endl;    
    for(int i = 0; i < 26; i++){
        char a = 'a' + i;
        std::cout << a << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < dist.size(); i++){
        if(dist[i] == std::numeric_limits<int>::max())
            std::cout << ". ";
        else
            std::cout << dist[i] << " ";
    }   
    std::cout << std::endl;
}
