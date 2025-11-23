#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "entidades.hpp"
#include "dominios.hpp"
#include <list>

using namespace std;

// ====================================================================
// CAMADA DE SERVIÇO (Service Interfaces)
// Definições usadas pelos Módulos de Apresentação (MAA, MAP, MAR)
// ====================================================================

/**
 * @class ISAutenticacao (ISA no diagrama)
 * @brief Interface para o Serviço de Autenticação.
 */
class ISAutenticacao {
public:
    virtual bool autenticar(const EMAIL& email, const Senha& senha) = 0;
    virtual ~ISAutenticacao() {}
};

/**
 * @class ISPessoa (ISP no diagrama)
 * @brief Interface para o Serviço de Pessoas.
 */
class ISPessoa {
public:
    virtual bool criarGerente(const Gerente& gerente) = 0;
    virtual bool deletarGerente(const EMAIL& email) = 0;
    virtual bool atualizarGerente(const Gerente& gerente) = 0;
    virtual Gerente lerGerente(const EMAIL& email) = 0;
    virtual list<Gerente> listarGerentes() = 0;

    virtual bool criarHospede(const Hospede& hospede) = 0;
    virtual bool deletarHospede(const EMAIL& email) = 0;
    virtual bool atualizarHospede(const Hospede& hospede) = 0;
    virtual Hospede lerHospede(const EMAIL& email) = 0;
    virtual list<Hospede> listarHospedes() = 0;

    virtual ~ISPessoa() {}
};

/**
 * @class ISReserva (ISR no diagrama)
 * @brief Interface para o Serviço de Reservas e Infraestrutura.
 */
class ISReserva {
public:
    // Infraestrutura (Hotel/Quarto)
    virtual bool criarHotel(const Hotel& hotel) = 0;
    virtual bool deletarHotel(const Codigo& codigo) = 0;
    virtual bool atualizarHotel(const Hotel& hotel) = 0;
    virtual Hotel lerHotel(const Codigo& codigo) = 0;
    virtual list<Hotel> listarHoteis() = 0;

    virtual bool criarQuarto(const Quarto& quarto) = 0;
    virtual bool deletarQuarto(const Numero& numero) = 0;
    virtual bool atualizarQuarto(const Quarto& quarto) = 0;
    virtual Quarto lerQuarto(const Numero& numero) = 0;
    virtual list<Quarto> listarQuartos() = 0;

    // Reservas
    virtual bool criarReserva(const Reserva& reserva) = 0;
    virtual bool deletarReserva(const Codigo& codigo) = 0;
    virtual bool atualizarReserva(const Reserva& reserva) = 0;
    virtual Reserva lerReserva(const Codigo& codigo) = 0;
    virtual list<Reserva> listarReservas() = 0;

    virtual ~ISReserva() {}
};

// ====================================================================
// CAMADA DE APRESENTAÇÃO (Presentation Interfaces)
// Definições usadas pelo Módulo de Acesso e Interface (MAI)
// ====================================================================

/**
 * @class IAAutenticacao (IAA no diagrama)
 * @brief Interface para o Módulo de Apresentação de Autenticação.
 * @details Responsável por exibir telas de login/cadastro.
 */
class IAAutenticacao {
public:
    /**
     * @brief Executa o fluxo de autenticação.
     * @param email Referência para armazenar o email autenticado em caso de sucesso.
     * @return true se o login foi bem sucedido, false caso contrário.
     */
    virtual bool executar(EMAIL& email) = 0;

    /**
     * @brief Define o serviço de autenticação a ser utilizado.
     * @details Permite injetar a dependência do serviço (ISA).
     */
    virtual void setISAutenticacao(ISAutenticacao* servico) = 0;

    virtual ~IAAutenticacao() {}
};

/**
 * @class IAPessoal (IAP no diagrama)
 * @brief Interface para o Módulo de Apresentação Pessoal.
 * @details Responsável pelo perfil do gerente.
 */
class IAPessoal {
public:
    /**
     * @brief Executa o menu de perfil pessoal.
     * @param email O email do gerente logado.
     */
    virtual void executar(const EMAIL& email) = 0;

    /**
     * @brief Define o serviço de pessoas a ser utilizado.
     * @details Permite injetar a dependência do serviço (ISP).
     */
    virtual void setISPessoa(ISPessoa* servico) = 0;

    virtual ~IAPessoal() {}
};

/**
 * @class IAReserva (IAR no diagrama)
 * @brief Interface para o Módulo de Apresentação de Reservas.
 * @details Responsável pela gestão do hotel (Reservas, Quartos, Hóspedes).
 */
class IAReserva {
public:
    /**
     * @brief Executa o menu de gestão de reservas e infraestrutura.
     * @param email O email do gerente logado (para logs ou permissões).
     */
    virtual void executar(const EMAIL& email) = 0;

    /**
     * @brief Define os serviços a serem utilizados.
     * @details Injeta dependências de Reservas e Pessoas (necessário para gerir hóspedes).
     */
    virtual void setISReserva(ISReserva* servico) = 0;
    virtual void setISPessoa(ISPessoa* servico) = 0; // MAR também lida com hóspedes

    virtual ~IAReserva() {}
};

#endif // INTERFACES_HPP_INCLUDED
