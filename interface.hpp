#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "entidades.hpp" // Para usar as Entidades (Gerente, Hospede, Reserva, etc.)
#include "dominios.hpp"   // Para usar Domínios (EMAIL, Senha, Codigo, etc.)
#include <list>           // Para o método listar

// ====================================================================
// 1. INTERFACE: SUBSISTEMA DE AUTENTICAÇÃO (SA)
// ====================================================================

/**
 * @class ILNAutenticacao
 * @brief Interface para o Módulo de Serviço de Autenticação.
 *
 * @details Define os serviços necessários para verificar a identidade de um Gerente
 * no sistema.
 */
class ILNAutenticacao {
public:
    /**
     * @brief Tenta autenticar um usuário (Gerente) com suas credenciais.
     * * @param email Objeto Domínio EMAIL do Gerente.
     * @param senha Objeto Domínio Senha do Gerente.
     * @return true se as credenciais forem válidas e o Gerente existir no sistema; false caso contrário.
     */
    virtual bool autenticar(const EMAIL& email, const Senha& senha) = 0;
    virtual ~ILNAutenticacao() {}
};


// ====================================================================
// 2. INTERFACE: SUBSISTEMA DE PESSOAS (SP)
// ====================================================================

/**
 * @class ILNPessoa
 * @brief Interface para o Módulo de Serviço de Pessoas (Gerente e Hóspede).
 *
 * @details Define os serviços CRUD e de listagem para as Entidades Gerente e Hóspede.
 */
class ILNPessoa {
public:
    // --- Gerente CRUD ---
    virtual bool criarGerente(const Gerente& gerente) = 0;
    virtual bool deletarGerente(const EMAIL& email) = 0;
    virtual bool atualizarGerente(const Gerente& gerente) = 0;
    virtual Gerente lerGerente(const EMAIL& email) = 0;
    virtual list<Gerente> listarGerentes() = 0;

    // --- Hóspede CRUD ---
    virtual bool criarHospede(const Hospede& hospede) = 0;
    virtual bool deletarHospede(const EMAIL& email) = 0;
    virtual bool atualizarHospede(const Hospede& hospede) = 0;
    virtual Hospede lerHospede(const EMAIL& email) = 0;
    virtual list<Hospede> listarHospedes() = 0;

    virtual ~ILNPessoa() {}
};


// ====================================================================
// 3. INTERFACE: SUBSISTEMA DE RESERVAS (SR)
// ====================================================================

/**
 * @class ILNReserva
 * @brief Interface para o Módulo de Serviço de Reservas (MSR).
 *
 * @details Define os serviços CRUD e de listagem para a Entidade Reserva,
 * incluindo a lógica de negócio de conflito de datas.
 */
class ILNReserva {
public:
    // Métodos CRUD (Chave Primária é Codigo)
    virtual bool criarReserva(const Reserva& reserva) = 0;
    virtual bool deletarReserva(const Codigo& codigo) = 0;
    virtual bool atualizarReserva(const Reserva& reserva) = 0;
    virtual Reserva lerReserva(const Codigo& codigo) = 0;

    // Método para listar todas as reservas
    virtual list<Reserva> listarReservas() = 0;

    virtual ~ILNReserva() {}
};

#endif // INTERFACES_HPP_INCLUDED
