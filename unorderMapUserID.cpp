#include "todohash.h"
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    unordered_map<long long, Usuario> um_userID;
    cout << "Tamaño base de un unordered_map: " << sizeof(um_userID) << " bytes" << endl;
    
    ifstream file("universities_followers.csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    string line, word;
    getline(file, line);  

    vector<Usuario> usuarios;
    while (getline(file, line)) {
        stringstream s(line);
        Usuario usuario;

        getline(s, usuario.university, ',');
        getline(s, word, ',');
        usuario.user_id = stoll(word);
        getline(s, usuario.user_name, ',');
        getline(s, word, ',');
        usuario.number_tweets = stoi(word);
        getline(s, word, ',');
        usuario.friends_count = stoi(word);
        getline(s, word, ',');
        usuario.followers_count = stoi(word);
        getline(s, usuario.created_at, ',');

        usuarios.push_back(usuario);
    }
    file.close();

    long long inserciones[] = {1000, 5000, 10000, 15000, 20000};
    int num_inserciones = sizeof(inserciones) / sizeof(inserciones[0]);

    
    {
        auto start = chrono::high_resolution_clock::now();
        for (long long j = 0; j < 20000 && j < usuarios.size(); ++j) {
            um_userID.find(usuarios[j].user_id);
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Tiempo para buscar usuarios en unordered_map (userID): " << duration.count() << " segundos" << endl;
    }
    
    
    for (int i = 0; i < num_inserciones; ++i) {
        long long inserciones_size = inserciones[i];

        
        {
            auto start = chrono::high_resolution_clock::now();
            for (long long j = 0; j < inserciones_size && j < usuarios.size(); ++j) {
                um_userID[usuarios[j].user_id] = usuarios[j];
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            cout << "Tiempo para insertar " << inserciones_size << " usuarios en unordered_map (userID): " << duration.count() << " segundos" << endl;
        }
    }

    return 0;
}
