#include "containers.hpp"
#include <iostream>
#include <algorithm> 

using namespace std;

// ====================================================================
// 1. IMPLEMENTAÇÃO: CONTAINER RESERVA
// Chave Primária (PK): Codigo
// ====================================================================

bool ContainerReserva::incluir(const Reserva& reserva) {
    // Verifica se a PK já existe
    for (const Reserva& r : container) {
        if (r.getCodigo().getValor() == reserva.getCodigo().getValor()) {
            return false; // Falha: Código (PK) duplicado
        }
    }

    // Inclui o novo objeto
    container.push_back(reserva);
    return true; // Sucesso
}

bool ContainerReserva::remover(const Codigo& codigo) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getCodigo().getValor() == codigo.getValor()) {
            container.erase(it); // Remove o elemento na posição 'it'
            return true; // Sucesso
        }
    }
    return false; // Falha: Reserva não encontrada
}

bool ContainerReserva::pesquisar(Reserva* reserva) const {
    const Codigo& codigoPesquisa = reserva->getCodigo();

    for (const Reserva& r : container) {
        if (r.getCodigo().getValor() == codigoPesquisa.getValor()) {
            *reserva = r; // Atribui os dados encontrados ao objeto apontado
            return true; // Sucesso
        }
    }
    return false; // Falha: Reserva não encontrada
}

bool ContainerReserva::atualizar(const Reserva& reserva) {
    for (Reserva& r : container) {
        if (r.getCodigo().getValor() == reserva.getCodigo().getValor()) {
            r = reserva; // Atualiza (sobrescreve) o objeto existente
            return true; // Sucesso
        }
    }
    return false; // Falha: Reserva não encontrada
}


// ====================================================================
// 2. IMPLEMENTAÇÃO: CONTAINER GERENTE
// Chave Primária (PK): EMAIL
// ====================================================================

bool ContainerGerente::incluir(const Gerente& gerente) {
    for (const Gerente& g : container) {
        if (g.getEmail().getValor() == gerente.getEmail().getValor()) {
            return false; // Falha: Email (PK) duplicado
        }
    }

    container.push_back(gerente);
    return true;
}

bool ContainerGerente::remover(const EMAIL& email) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getEmail().getValor() == email.getValor()) {
            container.erase(it);
            return true; // Sucesso
        }
    }
    return false;
}

bool ContainerGerente::pesquisar(Gerente* gerente) const {
    const EMAIL& emailPesquisa = gerente->getEmail();

    for (const Gerente& g : container) {
        if (g.getEmail().getValor() == emailPesquisa.getValor()) {
            *gerente = g; // Atribui os dados encontrados ao objeto apontado
            return true;
        }
    }
    return false;
}

bool ContainerGerente::atualizar(const Gerente& gerente) {
    for (Gerente& g : container) {
        if (g.getEmail().getValor() == gerente.getEmail().getValor()) {
            g = gerente; // Atualiza (sobrescreve) o objeto existente
            return true;
        }
    }
    return false;
}


// ====================================================================
// 3. IMPLEMENTAÇÃO: CONTAINER HOSPEDE
// Chave Primária (PK): EMAIL
// ====================================================================

bool ContainerHospede::incluir(const Hospede& hospede) {
    for (const Hospede& h : container) {
        if (h.getEmail().getValor() == hospede.getEmail().getValor()) {
            return false; // Falha: Email (PK) duplicado
        }
    }
    container.push_back(hospede);
    return true;
}

bool ContainerHospede::remover(const EMAIL& email) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getEmail().getValor() == email.getValor()) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerHospede::pesquisar(Hospede* hospede) const {
    const EMAIL& emailPesquisa = hospede->getEmail();
    for (const Hospede& h : container) {
        if (h.getEmail().getValor() == emailPesquisa.getValor()) {
            *hospede = h; 
            return true;
        }
    }
    return false;
}

bool ContainerHospede::atualizar(const Hospede& hospede) {
    for (Hospede& h : container) {
        if (h.getEmail().getValor() == hospede.getEmail().getValor()) {
            h = hospede;
            return true;
        }
    }
    return false;
}


// ====================================================================
// 4. IMPLEMENTAÇÃO: CONTAINER HOTEL
// Chave Primária (PK): Codigo
// ====================================================================

bool ContainerHotel::incluir(const Hotel& hotel) {
    for (const Hotel& h : container) {
        if (h.getCodigo().getValor() == hotel.getCodigo().getValor()) {
            return false; 
        }
    }
    container.push_back(hotel);
    return true;
}

bool ContainerHotel::remover(const Codigo& codigo) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getCodigo().getValor() == codigo.getValor()) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerHotel::pesquisar(Hotel* hotel) const {
    const Codigo& codigoPesquisa = hotel->getCodigo();
    for (const Hotel& h : container) {
        if (h.getCodigo().getValor() == codigoPesquisa.getValor()) {
            *hotel = h;
            return true;
        }
    }
    return false;
}

bool ContainerHotel::atualizar(const Hotel& hotel) {
    for (Hotel& h : container) {
        if (h.getCodigo().getValor() == hotel.getCodigo().getValor()) {
            h = hotel;
            return true;
        }
    }
    return false;
}


// ====================================================================
// 5. IMPLEMENTAÇÃO: CONTAINER QUARTO
// Chave Primária (PK): Numero
// ====================================================================

bool ContainerQuarto::incluir(const Quarto& quarto) {
    for (const Quarto& q : container) {
        if (q.getNumero().getValor() == quarto.getNumero().getValor()) {
            return false; 
        }
    }
    container.push_back(quarto);
    return true;
}

bool ContainerQuarto::remover(const Numero& numero) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getNumero().getValor() == numero.getValor()) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerQuarto::pesquisar(Quarto* quarto) const {
    const Numero& numeroPesquisa = quarto->getNumero();
    for (const Quarto& q : container) {
        if (q.getNumero().getValor() == numeroPesquisa.getValor()) {
            *quarto = q;
            return true;
        }
    }
    return false;
}

bool ContainerQuarto::atualizar(const Quarto& quarto) {
    for (Quarto& q : container) {
        if (q.getNumero().getValor() == quarto.getNumero().getValor()) {
            q = quarto;
            return true;
        }
    }
    return false;
}
