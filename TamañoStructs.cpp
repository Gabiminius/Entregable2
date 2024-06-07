#include <iostream>
#include <string>
using namespace std;
struct Usuario {
    long long user_id;       // 8 bytes
    string user_name;   // generalmente 32 bytes en 64 bits
    string university;  // generalmente 32 bytes en 64 bits
    int number_tweets;       // 4 bytes
    int friends_count;       // 4 bytes
    int followers_count;     // 4 bytes
    string created_at;  // generalmente 32 bytes en 64 bits
};

struct Node {
    long long user_id;       // 8 bytes
    Usuario dato;            // tamaño de Usuario
    Node* next;              // 8 bytes
};

int main() {
    cout << "Tamaño de long long: " << sizeof(long long) << " bytes" << endl;
    cout << "Tamaño de string: " << sizeof(string) << " bytes" << endl;
    cout << "Tamaño de Usuario: " << sizeof(Usuario) << " bytes" << endl;
    cout << "Tamaño de Node*: " << sizeof(Node*) << " bytes" << endl;
    cout << "Tamaño de Node: " << sizeof(Node) << " bytes" << endl;
    return 0;
}
