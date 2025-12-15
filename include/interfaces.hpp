#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "entities.hpp"
#include "domains.hpp"
#include <list>

using namespace std;

// ====================================================================
// CAMADA DE SERVIÇO (Service Interfaces)
// ====================================================================

/**
 * @class ISAutenticacao
 * @brief Interface para o serviço de autenticação de usuários.
 *
 * @details Define os métodos necessários para verificar credenciais de gerentes.
 */
class ISAutenticacao {
public:
    /**
     * @brief Autentica um usuário no sistema.
     * @param email Email do usuário.
     * @param senha Senha do usuário.
     * @return true se as credenciais forem válidas, false caso contrário.
     */
    virtual bool autenticar(const EMAIL& email, const Senha& senha) = 0;
    virtual ~ISAutenticacao() {}
};

/**
 * @class ISPessoa
 * @brief Interface para o serviço de gestão de pessoas (Gerentes e Hóspedes).
 *
 * @details Define as operações CRUD (Create, Read, Update, Delete) e de listagem
 * para as entidades Gerente e Hóspede.
 */
class ISPessoa {
public:
    /**
     * @brief Cria um novo gerente no sistema.
     * @param gerente Objeto Gerente com os dados a serem cadastrados.
     * @return true se o cadastro for bem-sucedido, false caso contrário (ex: email já existe).
     */
    virtual bool criarGerente(const Gerente& gerente) = 0;

    /**
     * @brief Remove um gerente do sistema.
     * @param email Email (PK) do gerente a ser removido.
     * @return true se a remoção for bem-sucedida, false se não encontrado.
     */
    virtual bool deletarGerente(const EMAIL& email) = 0;

    /**
     * @brief Atualiza os dados de um gerente existente.
     * @param gerente Objeto Gerente com os dados atualizados (Email deve coincidir com o existente).
     * @return true se a atualização for bem-sucedida.
     */
    virtual bool atualizarGerente(const Gerente& gerente) = 0;

    /**
     * @brief Recupera os dados de um gerente.
     * @param email Email (PK) do gerente.
     * @return Objeto Gerente encontrado.
     * @throw std::runtime_error Se o gerente não for encontrado.
     */
    virtual Gerente lerGerente(const EMAIL& email) = 0;

    /**
     * @brief Lista todos os gerentes cadastrados.
     * @return Lista de objetos Gerente.
     */
    virtual list<Gerente> listarGerentes() = 0;

    // --- CRUD Hóspede (Documentação similar à de Gerente) ---
    virtual bool criarHospede(const Hospede& hospede) = 0;
    virtual bool deletarHospede(const EMAIL& email) = 0;
    virtual bool atualizarHospede(const Hospede& hospede) = 0;
    virtual Hospede lerHospede(const EMAIL& email) = 0;
    virtual list<Hospede> listarHospedes() = 0;

    virtual ~ISPessoa() {}
};

/**
 * @class ISReserva
 * @brief Interface para o serviço de gestão de reservas e infraestrutura hoteleira.
 *
 * @details Centraliza as operações relacionadas a Hotéis, Quartos e Reservas.
 */
class ISReserva {
public:
    // --- CRUD Hotel ---
    virtual bool criarHotel(const Hotel& hotel) = 0;
    virtual bool deletarHotel(const Codigo& codigo) = 0;
    virtual bool atualizarHotel(const Hotel& hotel) = 0;
    virtual Hotel lerHotel(const Codigo& codigo) = 0;
    virtual list<Hotel> listarHoteis() = 0;

    // --- CRUD Quarto ---
    virtual bool criarQuarto(const Quarto& quarto) = 0;
    virtual bool deletarQuarto(const Numero& numero) = 0;
    virtual bool atualizarQuarto(const Quarto& quarto) = 0;
    virtual Quarto lerQuarto(const Numero& numero) = 0;
    virtual list<Quarto> listarQuartos() = 0;

    // --- CRUD Reserva ---
    /**
     * @brief Cria uma nova reserva.
     * @details Deve verificar conflitos de datas antes de confirmar a criação.
     * @param reserva Objeto Reserva a ser criado.
     * @return true se criada com sucesso, false se houver conflito ou erro.
     */
    virtual bool criarReserva(const Reserva& reserva) = 0;
    virtual bool deletarReserva(const Codigo& codigo) = 0;
    virtual bool atualizarReserva(const Reserva& reserva) = 0;
    virtual Reserva lerReserva(const Codigo& codigo) = 0;
    virtual list<Reserva> listarReservas() = 0;

    virtual ~ISReserva() {}
};

// ====================================================================
// CAMADA DE APRESENTAÇÃO (Presentation Interfaces)
// ====================================================================

/**
 * @class IAAutenticacao
 * @brief Interface para a apresentação de autenticação.
 *
 * @details Responsável pela interação com o usuário nas telas de login e cadastro inicial.
 */
class IAAutenticacao {
public:
    /**
     * @brief Executa o fluxo de login.
     * @param email Referência para armazenar o email do usuário autenticado.
     * @return true se o login for bem-sucedido.
     */
    virtual bool autenticar(EMAIL& email) = 0;

    /**
     * @brief Executa o fluxo de cadastro de novo gerente.
     * @return true se o cadastro for bem-sucedido.
     */
    virtual bool cadastrar() = 0;

    /**
     * @brief Injeta a dependência do serviço de autenticação.
     */
    virtual void setISAutenticacao(ISAutenticacao* servico) = 0;

    /**
     * @brief Injeta a dependência do serviço de pessoas (necessário para cadastro).
     */
    virtual void setISPessoa(ISPessoa* servico) = 0;

    virtual ~IAAutenticacao() {}
};

/**
 * @class IAPessoal
 * @brief Interface para a apresentação do módulo pessoal.
 *
 * @details Gerencia a interação com o perfil do usuário logado.
 */
class IAPessoal {
public:
    /**
     * @brief Executa o menu de perfil pessoal.
     * @param email Email do usuário logado.
     */
    virtual void executar(const EMAIL& email) = 0;

    /**
     * @brief Injeta a dependência do serviço de pessoas.
     */
    virtual void setISPessoa(ISPessoa* servico) = 0;

    virtual ~IAPessoal() {}
};

/**
 * @class IAReserva
 * @brief Interface para a apresentação do módulo de reservas.
 *
 * @details Gerencia a interação para cadastro e consulta de hotéis, quartos e reservas.
 */
class IAReserva {
public:
    /**
     * @brief Executa o menu principal de gestão de reservas.
     * @param email Email do usuário logado.
     */
    virtual void executar(const EMAIL& email) = 0;

    virtual void setISReserva(ISReserva* servico) = 0;
    virtual void setISPessoa(ISPessoa* servico) = 0;
    virtual ~IAReserva() {}
};

#endif // INTERFACES_HPP_INCLUDED
