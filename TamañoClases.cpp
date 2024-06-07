#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

struct Usuario {
    long long user_id;         // 8 bytes
    string user_name;          // 24 bytes (estimado)
    string university;         // 24 bytes (estimado)
    int number_tweets;         // 4 bytes
    int friends_count;         // 4 bytes
    int followers_count;       // 4 bytes
    string created_at;         // 24 bytes (estimado)
    
    static size_t get_size() {
        return sizeof(long long) + 3 * sizeof(string) + 3 * sizeof(int);
    }
};

class UserIDTablaHashOpen {
private:
    struct Node {
        long long user_id;    // 8 bytes
        Usuario dato;         // 112 bytes
        Node* next;           // 8 bytes (puntero)
        
        static size_t get_size() {
            return sizeof(long long) + Usuario::get_size() + sizeof(Node*);
        }
    };
    
    Node** tabla;              // 8 bytes (puntero a puntero)
    long long size_;           // 8 bytes
    
public:
    UserIDTablaHashOpen(long long size) : size_(size) {
        tabla = new Node*[size_];
        for (long long i = 0; i < size_; i++) {
            tabla[i] = nullptr;
        }
    }

    ~UserIDTablaHashOpen() {
        for (long long i = 0; i < size_; i++) {
            Node* actual = tabla[i];
            while (actual != nullptr) {
                Node* next = actual->next;
                delete actual;
                actual = next;
            }
        }
        delete[] tabla;
    }

    void insert(long long user_id, const Usuario& dato) {
        long long i = fhashID(user_id);
        Node* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->user_id == user_id) {
                actual->dato = dato;
                return;
            }
            actual = actual->next;
        }
        Node* newNode = new Node;
        newNode->user_id = user_id;
        newNode->dato = dato;
        newNode->next = tabla[i];
        tabla[i] = newNode;
    }

    Usuario* search(long long user_id) {
        long long i = fhashID(user_id);
        Node* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->user_id == user_id) {
                return &actual->dato;
            }
            actual = actual->next;
        }
        return nullptr;
    }

    size_t get_size() const {
        size_t size = sizeof(Node*) * size_ + sizeof(size_);
        for (long long i = 0; i < size_; i++) {
            Node* actual = tabla[i];
            while (actual != nullptr) {
                size += Node::get_size();
                actual = actual->next;
            }
        }
        return size;
    }

private:
    long long fhashID(long long user_id) {
        return user_id % size_;
    }
};

class UserNameTablaHashOpen {
private:
    struct Node {
        string user_name;    // 24 bytes (estimado)
        Usuario dato;        // 112 bytes
        Node* next;          // 8 bytes (puntero)
        
        static size_t get_size() {
            return sizeof(string) + Usuario::get_size() + sizeof(Node*);
        }
    };
    
    Node** tabla;            // 8 bytes (puntero a puntero)
    long long size_;         // 8 bytes
    
public:
    UserNameTablaHashOpen(long long size) : size_(size) {
        tabla = new Node*[size_];
        for (long long i = 0; i < size_; i++) {
            tabla[i] = nullptr;
        }
    }

    ~UserNameTablaHashOpen() {
        for (long long i = 0; i < size_; i++) {
            Node* actual = tabla[i];
            while (actual != nullptr) {
                Node* next = actual->next;
                delete actual;
                actual = next;
            }
        }
        delete[] tabla;
    }

    void insert(const string& user_name, const Usuario& dato) {
        long long i = fhashNAME(user_name);
        Node* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->user_name == user_name) {
                actual->dato = dato;
                return;
            }
            actual = actual->next;
        }
        Node* newNode = new Node;
        newNode->user_name = user_name;
        newNode->dato = dato;
        newNode->next = tabla[i];
        tabla[i] = newNode;
    }

    Usuario* search(const string& user_name) {
        long long i = fhashNAME(user_name);
        Node* actual = tabla[i];
        while (actual != nullptr) {
            if (actual->user_name == user_name) {
                return &actual->dato;
            }
            actual = actual->next;
        }
        return nullptr;
    }

    size_t get_size() const {
        size_t size = sizeof(Node*) * size_ + sizeof(size_);
        for (long long i = 0; i < size_; i++) {
            Node* actual = tabla[i];
            while (actual != nullptr) {
                size += Node::get_size();
                actual = actual->next;
            }
        }
        return size;
    }

private:
    long long fhashNAME(const string& user_name) {
        long long fhashNAME = 0;
        for (char c : user_name) {
            fhashNAME = (fhashNAME << 5) + c;
        }
        return fhashNAME % size_;
    }
};

class LinealProbing {
private:
    int size_;               // 4 bytes
    vector<Usuario> tabla;   // tamaño del vector (24 bytes en 64 bits)
    
public:
    LinealProbing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int i = funcionLineal(user_id);
        while (tabla[i].user_id != 0) {
            i = (i + 1) % size_;
        }
        tabla[i] = dato;
    }

    void insertn(string user_name, Usuario dato) {
        int i = funcionLinealN(user_name);
        while (tabla[i].user_name != "") {
            i = (i + 1) % size_;
        }
        tabla[i] = dato;
    }

    Usuario search(long long user_id) {
        int i = funcionLineal(user_id);
        while (tabla[i].user_id != user_id && tabla[i].user_id != 0) {
            i = (i + 1) % size_;
        }
        if (tabla[i].user_id == user_id) {
            return tabla[i];
        } else {
            return Usuario();
        }
    }

    Usuario searchn(string user_name) {
        int i = funcionLinealN(user_name);
        while (tabla[i].user_name != user_name && tabla[i].user_name != "") {
            i = (i + 1) % size_;
        }
        if (tabla[i].user_name == user_name) {
            return tabla[i];
        } else {
            return Usuario();
        }
    }

    size_t get_size() const {
        return sizeof(int) + sizeof(tabla) + sizeof(Usuario) * size_;
    }

private:
    int funcionLineal(long long key) {
        return key % size_;
    }

    int funcionLinealN(string key) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash % size_;
    }
};

class QuadraticProbing {
private:
    int size_;               // 4 bytes
    vector<Usuario> tabla;   // tamaño del vector (24 bytes en 64 bits)
    
public:
    QuadraticProbing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int i = 0;
        int h = funcionCuadratica(user_id, i);
        while (tabla[h].user_id != 0) {
            i++;
            h = funcionCuadratica(user_id, i);
        }
        tabla[h] = dato;
    }

    void insertn(string user_name, Usuario dato) {
        int i = 0;
        int h = funcionCuadratica(user_name, i);
        while (tabla[h].user_name != "") {
            i++;
            h = funcionCuadratica(user_name, i);
        }
        tabla[h] = dato;
    }

    Usuario search(long long user_id) {
        int i = 0;
        int h = funcionCuadratica(user_id, i);
        while (tabla[h].user_id != user_id && tabla[h].user_id != 0) {
            i++;
            h = funcionCuadratica(user_id, i);
        }
        if (tabla[h].user_id == user_id) {
            return tabla[h];
        } else {
            return Usuario();
        }
    }

    Usuario searchn(string user_name) {
        int i = 0;
        int h = funcionCuadratica(user_name, i);
        while (tabla[h].user_name != user_name && tabla[h].user_name != "") {
            i++;
            h = funcionCuadratica(user_name, i);
        }
        if (tabla[h].user_name == user_name) {
            return tabla[h];
        } else {
            return Usuario();
        }
    }

    size_t get_size() const {
        return sizeof(int) + sizeof(tabla) + sizeof(Usuario) * size_;
    }

private:
    int funcionCuadratica(long long key, int i) {
        return (key + i * i) % size_;
    }

    int funcionCuadratica(string key, int i) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return (hash + i * i) % size_;
    }
};

class DoubleHashing {
private:
    int size_;               // 4 bytes
    vector<Usuario> tabla;   // tamaño del vector (24 bytes en 64 bits)
    
public:
    DoubleHashing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int i = 0;
        int h = funcionDouble(user_id, i);
        while (tabla[h].user_id != 0) {
            i++;
            h = funcionDouble(user_id, i);
        }
        tabla[h] = dato;
    }

    void insertn(string user_name, Usuario dato) {
        int i = 0;
        int h = funcionDouble(user_name, i);
        while (tabla[h].user_name != "") {
            i++;
            h = funcionDouble(user_name, i);
        }
        tabla[h] = dato;
    }

    Usuario search(long long user_id) {
        int i = 0;
        int h = funcionDouble(user_id, i);
        while (tabla[h].user_id != user_id && tabla[h].user_id != 0) {
            i++;
            h = funcionDouble(user_id, i);
        }
        if (tabla[h].user_id == user_id) {
            return tabla[h];
        } else {
            return Usuario();
        }
    }

    Usuario searchn(string user_name) {
        int i = 0;
        int h = funcionDouble(user_name, i);
        while (tabla[h].user_name != user_name && tabla[h].user_name != "") {
            i++;
            h = funcionDouble(user_name, i);
        }
        if (tabla[h].user_name == user_name) {
            return tabla[h];
        } else {
            return Usuario();
        }
    }

    size_t get_size() const {
        return sizeof(int) + sizeof(tabla) + sizeof(Usuario) * size_;
    }

private:
    int funcionDouble(long long key, int i) {
        return (key + i * hash2(key)) % size_;
    }

    int funcionDouble(string key, int i) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return (hash + i * hash2(hash)) % size_;
    }

    int hash2(long long key) {
        return 7 - (key % 7);
    }

    int hash2(string key) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return 7 - (hash % 7);
    }
};

int main() {
    // Crear instancias y realizar inserciones de prueba para mostrar los tamaños calculados
    UserIDTablaHashOpen userIDTable(21089);
    UserNameTablaHashOpen userNameTable(21089);
    LinealProbing linearProbing(21089);
    QuadraticProbing quadraticProbing(21089);
    DoubleHashing doubleHashing(21089);
    
   
    
   
    cout << "Tamaño de UserIDTablaHashOpen: " << userIDTable.get_size() << " bytes" << endl;
    cout << "Tamaño de UserNameTablaHashOpen: " << userNameTable.get_size() << " bytes" << endl;
    cout << "Tamaño de LinealProbing: " << linearProbing.get_size() << " bytes" << endl;
    cout << "Tamaño de QuadraticProbing: " << quadraticProbing.get_size() << " bytes" << endl;
    cout << "Tamaño de DoubleHashing: " << doubleHashing.get_size() << " bytes" << endl;
    
    return 0;
}
