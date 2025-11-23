#ifndef CONTAINERS_HPP_INCLUDED
#define CONTAINERS_HPP_INCLUDED

#include "entidades.hpp" // Dependência das classes Entidade
#include <list>          // Usando std::list para armazenamento
#include <stdexcept>     // Para exceções

using namespace std;

// ====================================================================
// ORGANIZAÇÃO DOS DADOS (5 CONTÊINERES)
// ====================================================================

class ContainerGerente {
private:
    std::list<Gerente> container;
public:
    bool incluir(const Gerente& gerente);
    bool remover(const EMAIL& email);
    bool pesquisar(Gerente* gerente) const;
    bool atualizar(const Gerente& gerente);
    // Método necessário para a funcionalidade "Listar Gerentes"
    std::list<Gerente> listar() const { return container; }
};

// --------------------------------------------------------------------

class ContainerHospede {
private:
    std::list<Hospede> container;
public:
    bool incluir(const Hospede& hospede);
    bool remover(const EMAIL& email);
    bool pesquisar(Hospede* hospede) const;
    bool atualizar(const Hospede& hospede);
    // Método necessário para a funcionalidade "Listar Hóspedes"
    std::list<Hospede> listar() const { return container; }
};

// --------------------------------------------------------------------

class ContainerHotel {
private:
    std::list<Hotel> container;
public:
    bool incluir(const Hotel& hotel);
    bool remover(const Codigo& codigo);
    bool pesquisar(Hotel* hotel) const;
    bool atualizar(const Hotel& hotel);
    // Método necessário para a funcionalidade "Listar Hotéis"
    std::list<Hotel> listar() const { return container; }
};

// --------------------------------------------------------------------

class ContainerQuarto {
private:
    std::list<Quarto> container;
public:
    bool incluir(const Quarto& quarto);
    bool remover(const Numero& numero);
    bool pesquisar(Quarto* quarto) const;
    bool atualizar(const Quarto& quarto);
    // Método necessário para a funcionalidade "Listar Quartos"
    std::list<Quarto> listar() const { return container; }
};

// --------------------------------------------------------------------

class ContainerReserva {
private:
    std::list<Reserva> container;
public:
    bool incluir(const Reserva& reserva);
    bool remover(const Codigo& codigo);
    bool pesquisar(Reserva* reserva) const;
    bool atualizar(const Reserva& reserva);
    std::list<Reserva> listar() const { return container; }
};

#endif // CONTAINERS_HPP_INCLUDED
