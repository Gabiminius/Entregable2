#include <iostream>
#include <string>
#include <vector>

using namespace std;
 struct Usuario{
        long long user_id;
        string user_name;
        string university;
        int number_tweets;
        int friends_count;
        int followers_count;
        string created_at;
    };


// clase para el id
class UserIDTablaHashOpen {
private:
  struct Node {
        long long user_id;
        Usuario dato;
        Node* next;
    };
    
    Node** tabla;
    long long size_= 21089;

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
            while (actual!= nullptr) {
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
        while (actual!= nullptr) {
            if (actual->user_id == user_id) {
                // Actualizar datos si la clave ya existe
                actual->dato = dato;
                return;
            }
            actual = actual->next;
        }
        // Insertar nuevo nodo al principio de la lista
        Node* newNode = new Node;
        newNode->user_id = user_id;
        newNode->dato = dato;
        newNode->next = tabla[i];
        tabla[i] = newNode;
    }

    Usuario* search(long long user_id) {
        long long i = fhashID(user_id);
        Node* actual = tabla[i];
        while (actual!= nullptr) {
            if (actual->user_id == user_id) {
                return &actual->dato;
            }
            actual = actual->next;
        }
        return nullptr;
    }

private:
    long long fhashID(long long user_id) {
        return user_id % size_;
    }
};

// clase para el nombre
class UserNameTablaHashOpen {
private:
   struct Node {
        string user_name;
        Usuario dato;
        Node* next;
    };
    
    Node** tabla;
    long long size_= 21089;

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
                // Actualizar datos si la clave ya existe
                actual->dato = dato;
                return;
            }
            actual = actual->next;
        }
        // Insertar nuevo nodo al principio de la lista
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

private:
    long long fhashNAME(const string& user_name) {
        long long fhashNAME = 0;
        for (char c : user_name) {
            fhashNAME = (fhashNAME << 5) + c;
        }
        return fhashNAME % size_;
    }
};
class LinealProbing{
private:
    int size_=21089;
    vector<Usuario> tabla;
    

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

public:
    LinealProbing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int i = funcionLineal(user_id);
        while (tabla[i].user_id!= 0) {
            i = (i + 1) % size_;
        }
        tabla[i] = dato;
    }

    void insertn(string user_name, Usuario dato) {
        int i = funcionLinealN(user_name);
        while (tabla[i].user_name!= "") {
            i = (i + 1) % size_;
        }
        tabla[i] = dato;
    }

    Usuario search(long long user_id) {
        int i = funcionLineal(user_id);
        while (tabla[i].user_id!= user_id && tabla[i].user_id!= 0) {
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
        while (tabla[i].user_name!= user_name && tabla[i].user_name!= "") {
            i = (i + 1) % size_;
        }
        if (tabla[i].user_name == user_name) {
            return tabla[i];
        } else {
            return Usuario();
        }
    }
};

//pruba cuadratica
class QuadraticProbing {
private:
    int size_ = 21089;
    vector<Usuario> tabla;
    

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

public:
    QuadraticProbing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int i = 0;
        int h = funcionCuadratica(user_id, i);
        while (tabla[h].user_id!= 0) {
            i++;
            h = funcionCuadratica(user_id, i);
        }
        tabla[h] = dato;
    }

    void insertn(string user_name, Usuario dato) {
        int i = 0;
        int h = funcionCuadratica(user_name, i);
        while (tabla[h].user_name!= "") {
            i++;
            h = funcionCuadratica(user_name, i);
        }
        tabla[h] = dato;
    }

    Usuario search(long long user_id) {
        int i = 0;
        int h = funcionCuadratica(user_id, i);
        while (tabla[h].user_id!= user_id && tabla[h].user_id!= 0) {
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
        while (tabla[h].user_name!= user_name && tabla[h].user_name!= "") {
            i++;
            h = funcionCuadratica(user_name, i);
        }
        if (tabla[h].user_name == user_name) {
            return tabla[h];
        } else {
            return Usuario();
        }
    }
};

// dloble hashing
class DoubleHashing {
private:
    int size_=21089;
    vector<Usuario> tabla;
    

    int funcionHash1(long long key) {
        return key % size_;
    }

    int funcionHash2(long long key) {
        return (10 - (key % 10)) % size_;
    }

    int funcionHash1(string key) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash % size_;
    }

    int funcionHash2(string key) {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return (10 - (hash % 10)) % size_;
    }

public:
    DoubleHashing(int size) : size_(size), tabla(size) {}

    void insert(long long user_id, Usuario dato) {
        int h1 = funcionHash1(user_id);
        int h2 = funcionHash2(user_id);
        int i = h1;
        while (tabla[i].user_id!= 0) {
            i = (i + h2) % size_;
        }
        tabla[i] = dato;
    }

    void insert(string user_name, Usuario dato) {
        int h1 = funcionHash1(user_name);
        int h2 = funcionHash2(user_name);
        int i = h1;
        while (tabla[i].user_name!= "") {
            i = (i + h2) % size_;
        }
        tabla[i] = dato;
    }

    Usuario search(long long user_id) {
        int h1 = funcionHash1(user_id);
        int h2 = funcionHash2(user_id);
        int i = h1;
        while (tabla[i].user_id!= user_id && tabla[i].user_id!= 0) {
            i = (i + h2) % size_;
        }
        if (tabla[i].user_id == user_id) {
            return tabla[i];
        } else {
            return Usuario();
        }
    }

    Usuario search(string user_name) {
        int h1 = funcionHash1(user_name);
        int h2 = funcionHash2(user_name);
        int i = h1;
        while (tabla[i].user_name!= user_name && tabla[i].user_name!= "") {
            i = (i + h2) % size_;
        }
        if (tabla[i].user_name == user_name) {
            return tabla[i];
        } else {
            return Usuario();
        }
    }
};

