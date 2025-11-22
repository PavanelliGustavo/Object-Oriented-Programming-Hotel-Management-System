#ifndef CONTAINERS_HPP_INCLUDED
#define CONTAINERS_HPP_INCLUDED

#include "entidades.hpp" // Dependência das classes Entidade
#include <list>          // Usando std::list para armazenamento
#include <stdexcept>     // Para exceções

// ====================================================================
// ORGANIZAÇÃO DOS DADOS (5 CONTÊINERES)
// ====================================================================

/**
 * @class ContainerGerente
 * @brief Gerencia o armazenamento em memória da coleção de Entidades Gerente.
 * @details Utiliza uma std::list para persistir os objetos Gerente.
 */
class ContainerGerente {
private:
    std::list<Gerente> container;

public:
    bool incluir(const Gerente& gerente);
    bool remover(const EMAIL& email); // PK: EMAIL
    bool pesquisar(Gerente* gerente) const;
    bool atualizar(const Gerente& gerente);
};

// --------------------------------------------------------------------

/**
 * @class ContainerHospede
 * @brief Gerencia o armazenamento em memória da coleção de Entidades Hóspede.
 * @details Utiliza uma std::list para persistir os objetos Hóspede.
 */
class ContainerHospede {
private:
    std::list<Hospede> container;

public:
    bool incluir(const Hospede& hospede);
    bool remover(const EMAIL& email); // PK: EMAIL
    bool pesquisar(Hospede* hospede) const;
    bool atualizar(const Hospede& hospede);
};

// --------------------------------------------------------------------

/**
 * @class ContainerHotel
 * @brief Gerencia o armazenamento em memória da coleção de Entidades Hotel.
 * @details Utiliza uma std::list para persistir os objetos Hotel.
 */
class ContainerHotel {
private:
    std::list<Hotel> container;

public:
    bool incluir(const Hotel& hotel);
    bool remover(const Codigo& codigo); // PK: Codigo
    bool pesquisar(Hotel* hotel) const;
    bool atualizar(const Hotel& hotel);
};

// --------------------------------------------------------------------

/**
 * @class ContainerQuarto
 * @brief Gerencia o armazenamento em memória da coleção de Entidades Quarto.
 * @details Utiliza uma std::list para persistir os objetos Quarto.
 */
class ContainerQuarto {
private:
    std::list<Quarto> container;

public:
    bool incluir(const Quarto& quarto);
    // Nota: Quarto é identificado por Número dentro de um Hotel, mas aqui o Contêiner o gerencia pela PK.
    bool remover(const Numero& numero); // PK: Numero (no contexto do Hotel)
    bool pesquisar(Quarto* quarto) const;
    bool atualizar(const Quarto& quarto);
};

// --------------------------------------------------------------------

/**
 * @class ContainerReserva
 * @brief Gerencia o armazenamento em memória da coleção de Entidades Reserva.
 * @details Utiliza uma std::list para persistir os objetos Reserva.
 */
class ContainerReserva {
private:
    std::list<Reserva> container;

public:
    bool incluir(const Reserva& reserva);
    bool remover(const Codigo& codigo); // PK: Codigo
    bool pesquisar(Reserva* reserva) const;
    bool atualizar(const Reserva& reserva);
    std::list<Reserva> listar() const { return container; } // Adicionando listar para uso pelo Serviço de Reservas
};

#endif // CONTAINERS_HPP_INCLUDED
