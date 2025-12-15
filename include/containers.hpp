#ifndef CONTAINERS_HPP_INCLUDED
#define CONTAINERS_HPP_INCLUDED

#include "entities.hpp"
#include <list>
#include <stdexcept>

using namespace std;

// ====================================================================
// ORGANIZAÇÃO DOS DADOS (5 CONTÊINERES)
// ====================================================================

/**
 * @class ContainerGerente
 * @brief Classe responsável pelo armazenamento em memória de objetos Gerente.
 * @details Simula uma tabela de banco de dados usando std::list.
 */
class ContainerGerente {
private:
    std::list<Gerente> container;
public:
    /**
     * @brief Insere um novo gerente no container.
     * @param gerente Objeto a ser inserido.
     * @return true se inserido com sucesso (chave única respeitada).
     */
    bool incluir(const Gerente& gerente);
    bool remover(const EMAIL& email);
    bool pesquisar(Gerente* gerente) const;
    bool atualizar(const Gerente& gerente);
    std::list<Gerente> listar() const { return container; }
};

/**
 * @class ContainerHospede
 * @brief Classe responsável pelo armazenamento em memória de objetos Hospede.
 */
class ContainerHospede {
private:
    std::list<Hospede> container;
public:
    bool incluir(const Hospede& hospede);
    bool remover(const EMAIL& email);
    bool pesquisar(Hospede* hospede) const;
    bool atualizar(const Hospede& hospede);
    std::list<Hospede> listar() const { return container; }
};

/**
 * @class ContainerHotel
 * @brief Classe responsável pelo armazenamento em memória de objetos Hotel.
 */
class ContainerHotel {
private:
    std::list<Hotel> container;
public:
    bool incluir(const Hotel& hotel);
    bool remover(const Codigo& codigo);
    bool pesquisar(Hotel* hotel) const;
    bool atualizar(const Hotel& hotel);
    std::list<Hotel> listar() const { return container; }
};

/**
 * @class ContainerQuarto
 * @brief Classe responsável pelo armazenamento em memória de objetos Quarto.
 */
class ContainerQuarto {
private:
    std::list<Quarto> container;
public:
    bool incluir(const Quarto& quarto);
    bool remover(const Numero& numero);
    bool pesquisar(Quarto* quarto) const;
    bool atualizar(const Quarto& quarto);
    std::list<Quarto> listar() const { return container; }
};

/**
 * @class ContainerReserva
 * @brief Classe responsável pelo armazenamento em memória de objetos Reserva.
 */
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
