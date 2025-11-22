#include "containers.hpp"
#include <iostream>
#include <algorithm> // Para usar std::find_if (embora loops manuais sejam mais claros em C++ inicial)

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
    // Percorre o contêiner para encontrar a reserva pelo Código
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getCodigo().getValor() == codigo.getValor()) {
            container.erase(it); // Remove o elemento na posição 'it'
            return true; // Sucesso
        }
    }
    return false; // Falha: Reserva não encontrada
}

bool ContainerReserva::pesquisar(Reserva* reserva) const {
    // Assume que o objeto 'reserva' passado já tem a PK (Codigo) preenchida
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
    // Percorre para encontrar a reserva pelo Código (PK)
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
    // Verifica se a PK (EMAIL) já existe
    for (const Gerente& g : container) {
        if (g.getEmail().getValor() == gerente.getEmail().getValor()) {
            return false; // Falha: Email (PK) duplicado
        }
    }

    container.push_back(gerente);
    return true;
}

bool ContainerGerente::remover(const EMAIL& email) {
    // Percorre o contêiner para encontrar o Gerente pelo Email
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getEmail().getValor() == email.getValor()) {
            container.erase(it);
            return true; // Sucesso
        }
    }
    return false;
}

bool ContainerGerente::pesquisar(Gerente* gerente) const {
    // Assume que o objeto 'gerente' passado já tem a PK (EMAIL) preenchida
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
    // Percorre para encontrar o Gerente pelo Email (PK)
    for (Gerente& g : container) {
        if (g.getEmail().getValor() == gerente.getEmail().getValor()) {
            g = gerente; // Atualiza (sobrescreve) o objeto existente
            return true;
        }
    }
    return false;
}

// ... Implementações similares seriam adicionadas aqui para ContainerHospede, ContainerHotel e ContainerQuarto.
