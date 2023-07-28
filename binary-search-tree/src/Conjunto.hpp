#include "Conjunto.h"

template<class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    longitud = 0;

}

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) {
    valor = v;
    der = nullptr;
    izq = nullptr;
    padre = nullptr;
}

template<class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);

}


template<class T>
void Conjunto<T>::destruir(Nodo *elem) {
    if (elem != NULL) {
        destruir(elem->izq);
        destruir(elem->der);
        delete elem;
    }
}


template<class T>

bool Conjunto<T>::pertenece(const T &clave) const {
    bool res = false;
    Nodo *elem = _raiz;
    while (elem != NULL && !res) {
        if (elem->valor == clave) {
            res = true;
        } else if (elem->valor < clave) {
            elem = elem->der;
        } else if (elem->valor > clave) {
            elem = elem->izq;
        }
    }
    return res;
}



template<class T>
void Conjunto<T>::insertar(const T &clave) {
    if (!pertenece(clave)) {
        Nodo *n = new Nodo(clave);
        insertarAux(_raiz, clave, n);
    }
}

template<class T>
void Conjunto<T>::insertarAux(Nodo *elem, const T &clave, Nodo *n) {
    if (_raiz == NULL) {
        _raiz = n;
        _raiz->izq = NULL;
        _raiz->der = NULL;
        _raiz->padre = NULL;
        longitud++;
    } else {
        if (clave > elem->valor) {
            if (elem->der == NULL) {
                elem->der = n;
                n->padre = elem;
                n->izq = NULL;
                n->der = NULL;
                longitud++;
            } else {
                insertarAux(elem->der, clave, n);
            }
        } else {
            if (elem->izq == NULL) {
                elem->izq = n;
                n->padre = elem;
                n->izq = NULL;
                n->der = NULL;
                longitud++;
            } else {
                insertarAux(elem->izq, clave, n);
            }
        }
    }

}


template<class T>
void Conjunto<T>::remover(const T &clave) {
    if (pertenece(clave)) {
        if (_raiz->valor == clave && _raiz->der == NULL && _raiz->izq == NULL) {
            delete (_raiz);
            _raiz = NULL;
            longitud--;
        } else {
            removerAux(_raiz, clave);

        }
    }
}

template<class T>
void Conjunto<T>::removerAux(Nodo *elem, T clave) {
    if (elem != NULL) {
        if (clave < elem->valor) {
            removerAux(elem->izq, clave);
        } else if (clave > elem->valor) {
            removerAux(elem->der, clave);
        } else if (elem->izq == NULL && elem->der == NULL) {
            if ((elem->padre)->izq == elem) {
                (elem->padre)->izq = NULL;
            }
            if ((elem->padre)->der == elem) {
                (elem->padre)->der = NULL;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else if (elem->izq == NULL) {
            Nodo *temp2 = elem->der;
            if (elem->padre != NULL) {
                if ((elem->padre)->der == elem) {
                    (elem->padre)->der = temp2;
                    temp2->padre = elem->padre;
                } else {
                    (elem->padre)->izq = temp2;
                    temp2->padre = elem->padre;
                }
            } else if (_raiz == elem) {
                _raiz = temp2;
                _raiz->padre = NULL;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else if (elem->der == NULL) {
            Nodo *temp2 = elem->izq;
            if (elem->padre != NULL) {
                if ((elem->padre)->der == elem) {
                    (elem->padre)->der = temp2;
                    temp2->padre = elem->padre;
                } else {
                    (elem->padre)->izq = temp2;
                    temp2->padre = elem->padre;
                }
            } else if (_raiz == elem) {
                _raiz = temp2;
                _raiz->padre = NULL;
            }
            delete (elem);
            elem = NULL;
            longitud--;

        } else {
            T min = minimoDe(elem->der);
            elem->valor = min;
            removerAux(elem->der, min);
        }
    }
}


template<class T>
T Conjunto<T>::minimoDe(Nodo *elem) const {
    T min = elem->valor;
    Nodo *temp = elem;
    while (temp->izq != NULL) {
        temp = temp->izq;
        min = temp->valor;
    }
    T res = min;
    return res;

}


template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    Nodo *raiz = _raiz;
    Nodo *padre = _raiz;
    Nodo *res = new Nodo(clave);
    bool encontro = false;
    while (!encontro) {
        if (raiz->valor == clave) {
            if (raiz->der != NULL) {
                Nodo *suc = raiz->der;
                while (suc->izq != NULL) {
                    suc = suc->izq;
                }
                res->valor = suc->valor;
            } else {
                res->valor = padre->valor;
            }
            encontro = true;
        } else {
            padre = raiz;
            if (clave < raiz->valor) {
                raiz = raiz->izq;
            } else {
                raiz = raiz->der;
            }
        }
    }

    raiz->valor = res->valor;
    delete (res);
    return raiz->valor;


}


template<class T>
const T &Conjunto<T>::minimo() const {
    T &min = _raiz->valor;
    Nodo *raiz = _raiz;
    while (raiz->izq != NULL) {
        raiz = raiz->izq;
        min = raiz->valor;
    }
    const T &res = min;
    return res;

}


template<class T>
const T &Conjunto<T>::maximo() const {
    T &max = _raiz->valor;
    Nodo *raiz = _raiz;
    while (raiz->der != NULL) {
        raiz = raiz->der;
        max = raiz->valor;
    }
    const T &res = max;
    return res;

}


template<class T>
unsigned int Conjunto<T>::cardinal() const {

    return longitud;
}


template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}

