#include "containers.hpp"

// ====================================================================
// IMPLEMENTAÇÃO: CONTAINER GERENTE
// ====================================================================

bool ContainerGerente::incluir(const Gerente& gerente) {
    for (const auto& item : container) {
        if (item.getEmail().getValor() == gerente.getEmail().getValor()) {
            return false; // Já existe
        }
    }
    container.push_back(gerente);
    return true;
}

bool ContainerGerente::remover(const EMAIL& email) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getEmail().getValor() == email.getValor()) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerGerente::pesquisar(Gerente* gerente) const {
    for (const auto& item : container) {
        if (item.getEmail().getValor() == gerente->getEmail().getValor()) {
            *gerente = item;
            return true;
        }
    }
    return false;
}

bool ContainerGerente::atualizar(const Gerente& gerente) {
    for (auto& item : container) {
        if (item.getEmail().getValor() == gerente.getEmail().getValor()) {
            item = gerente;
            return true;
        }
    }
    return false;
}

// ====================================================================
// IMPLEMENTAÇÃO: CONTAINER HÓSPEDE
// ====================================================================

bool ContainerHospede::incluir(const Hospede& hospede) {
    for (const auto& item : container) {
        if (item.getEmail().getValor() == hospede.getEmail().getValor()) {
            return false;
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
    for (const auto& item : container) {
        if (item.getEmail().getValor() == hospede->getEmail().getValor()) {
            *hospede = item;
            return true;
        }
    }
    return false;
}

bool ContainerHospede::atualizar(const Hospede& hospede) {
    for (auto& item : container) {
        if (item.getEmail().getValor() == hospede.getEmail().getValor()) {
            item = hospede;
            return true;
        }
    }
    return false;
}

// ====================================================================
// IMPLEMENTAÇÃO: CONTAINER HOTEL
// ====================================================================

bool ContainerHotel::incluir(const Hotel& hotel) {
    for (const auto& item : container) {
        if (item.getCodigo().getValor() == hotel.getCodigo().getValor()) {
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
    for (const auto& item : container) {
        if (item.getCodigo().getValor() == hotel->getCodigo().getValor()) {
            *hotel = item;
            return true;
        }
    }
    return false;
}

bool ContainerHotel::atualizar(const Hotel& hotel) {
    for (auto& item : container) {
        if (item.getCodigo().getValor() == hotel.getCodigo().getValor()) {
            item = hotel;
            return true;
        }
    }
    return false;
}

// ====================================================================
// IMPLEMENTAÇÃO: CONTAINER QUARTO
// ====================================================================

bool ContainerQuarto::incluir(const Quarto& quarto) {
    for (const auto& item : container) {
        if (item.getNumero().getValor() == quarto.getNumero().getValor()) {
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
    for (const auto& item : container) {
        if (item.getNumero().getValor() == quarto->getNumero().getValor()) {
            *quarto = item;
            return true;
        }
    }
    return false;
}

bool ContainerQuarto::atualizar(const Quarto& quarto) {
    for (auto& item : container) {
        if (item.getNumero().getValor() == quarto.getNumero().getValor()) {
            item = quarto;
            return true;
        }
    }
    return false;
}

// ====================================================================
// IMPLEMENTAÇÃO: CONTAINER RESERVA
// ====================================================================

bool ContainerReserva::incluir(const Reserva& reserva) {
    for (const auto& item : container) {
        if (item.getCodigo().getValor() == reserva.getCodigo().getValor()) {
            return false;
        }
    }
    container.push_back(reserva);
    return true;
}

bool ContainerReserva::remover(const Codigo& codigo) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it->getCodigo().getValor() == codigo.getValor()) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerReserva::pesquisar(Reserva* reserva) const {
    for (const auto& item : container) {
        if (item.getCodigo().getValor() == reserva->getCodigo().getValor()) {
            *reserva = item;
            return true;
        }
    }
    return false;
}

bool ContainerReserva::atualizar(const Reserva& reserva) {
    for (auto& item : container) {
        if (item.getCodigo().getValor() == reserva.getCodigo().getValor()) {
            item = reserva;
            return true;
        }
    }
    return false;
}
