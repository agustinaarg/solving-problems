template<typename T>
string_map<T>::string_map() {
    raiz = nullptr;
    _size = 0;

}


template<typename T>
string_map<T>::~string_map() {
    if (raiz != nullptr) {
        destruir(raiz);
    }
}


template<typename T>
void string_map<T>::destruir(Nodo *elem) {
    for (int i = 0; i < 256; i++) {
        if (elem != nullptr /*&& elem->siguientes[i] != nullptr*/) {
            destruir(elem->siguientes[i]);
        }
    }
    delete elem;

}


template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() {
    *this = aCopiar;
}


template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    if (this->raiz != nullptr) {
        destruir(this->raiz);
    }
    for (pair<string, T> c : d.claves) {
        this->insert(c);
    }
    return *this;
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    int res = 0;
    if (raiz != nullptr) {
        Nodo *temp = raiz;
        int i = 0;
        int c = clave[i];
        while (temp  != nullptr && i < clave.size()) {
            temp  = temp ->siguientes[c];
            i++;
            c = clave[i];
        }
        if (temp != nullptr) {
            if (temp->definicion != nullptr && i == clave.size()) {
                res = 1;
            }
        }

    }
    return res;
}


template<typename T>
void string_map<T>::insert(const pair<string, T> &clave) {
    if (raiz == nullptr) {
        raiz = new Nodo();
    }
    Nodo *temp = raiz;
    for (int i = 0; i < clave.first.length(); i++) {
        int c = clave.first[i];
        if (temp->siguientes[c] == nullptr) {
            temp->siguientes[c] = new Nodo();;
        }
        temp = temp->siguientes[c];
       /* if (i == clave.first.size() - 1) {
            //T *key = clave.second;
            //T *key2 = new T(clave.second);
            temp->definicion = new T(clave.second);
            // delete (key2);
        }*/
    }
    if(temp->definicion != nullptr){
        delete temp->definicion;
        temp->definicion = new T(clave.second);
    } else {
        temp->definicion = new T(clave.second);
    }
    claves.push_back(clave);
    _size++;

}


template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *temp = raiz;
    for (int i = 0; i < clave.length(); i++) {
        int c = clave[i];
        temp = temp->siguientes[c];
    }
    const T &res = *temp->definicion;
    return res;

}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *temp = raiz;
    for (int i = 0; i < clave.length(); i++) {
        int c = clave[i];
        temp = temp->siguientes[c];
    }

    return *temp->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    eraseAux(raiz, clave, 0);
}

template<typename T>
void string_map<T>::eraseAux(Nodo *raiz, string clave, int d) {
    Nodo *ult= raiz;
    Nodo *temp = raiz;
    int i = 0;
    while (i < clave.size()){
        int c = clave[i];
        if (temp != nullptr && temp->definicion != nullptr || tieneHijos(temp)) {
            ult = temp;
        }
        temp = temp->siguientes[c];
        i++;
    }
    if (tieneHijos(temp)) {
        delete temp->definicion;
        temp->definicion = nullptr;
        _size--;
    } else {
        int j = 0;
        while (j < ult->siguientes.size()) {
            if (ult->siguientes[j] != nullptr) {
                eliminarNodo(ult->siguientes[j]);
            }
            j++;
        }
    }
}


/*
template<typename T>
int string_map<T>::hijos(Nodo *temp) {
    int aux = 0;
    for (int i = 0; i < 256; i++) {
        if (temp->siguientes[i] != nullptr) {
            aux++;
        }
    }

    return aux;
    }
*/

template<typename T>
bool string_map<T>::tieneHijos(Nodo *temp) {
    int i = 0;
    bool res = false;
    while (i < temp->siguientes.size()) {
        if (temp->siguientes[i] != nullptr) {
            res = true;
        }
        i++;
    }
    return res;
}

template<typename T>
void string_map<T>::eliminarNodo(Nodo *&temp) {
    if (temp != nullptr) {
        for(int i = 0; i < 256; i++) {
            if (temp->siguientes[i] != nullptr) {
                eliminarNodo(temp->siguientes[i]);
            }
        }
        if (temp->definicion != nullptr) {
            delete temp->definicion;
            temp->definicion = nullptr;
            _size--;
        }
    }
    delete temp;
    temp = nullptr;
}



template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return raiz == nullptr;
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
}






