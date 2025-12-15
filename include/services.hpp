#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

#include "interfaces.hpp" // Contém ISAutenticacao, ISPessoa, ISReserva
#include "domains.hpp"
#include <list>

using namespace std;

// Forward declarations dos containers
class ContainerGerente;
class ContainerHospede;
class ContainerHotel;
class ContainerQuarto;
class ContainerReserva;

// ====================================================================
// 1. MÓDULO DE SERVIÇO: AUTENTICAÇÃO (MSA)
// ====================================================================

/**
 * @class CntrMSAutenticacao
 * @brief Controlador de Serviço de Autenticação.
 *
 * @details Implementa a lógica de verificação de credenciais consultando o container de gerentes.
 */
class CntrMSAutenticacao : public ISAutenticacao {
private:
    ContainerGerente* container;

public:
    /**
     * @brief Autentica um usuário verificando email e senha no container.
     * @param email Email fornecido.
     * @param senha Senha fornecida.
     * @return true se as credenciais conferem.
     */
    bool autenticar(const EMAIL& email, const Senha& senha) override;

    /**
     * @brief Define o container de gerentes a ser utilizado.
     * @param container Ponteiro para o container.
     */
    void setContainer(ContainerGerente* container) { this->container = container; }
};

// ====================================================================
// 2. MÓDULO DE SERVIÇO: PESSOAL (MSP)
// ====================================================================

/**
 * @class CntrMSPessoa
 * @brief Controlador de Serviço de Pessoas.
 *
 * @details Implementa a lógica de negócio para Gerentes e Hóspedes, garantindo
 * regras como unicidade de email (PK).
 */
class CntrMSPessoa : public ISPessoa {
private:
    ContainerGerente* containerGerentes;
    ContainerHospede* containerHospedes;

public:
    // Implementação dos métodos da interface ISPessoa para Gerentes
    bool criarGerente(const Gerente& gerente) override;
    bool deletarGerente(const EMAIL& email) override;
    bool atualizarGerente(const Gerente& gerente) override;
    Gerente lerGerente(const EMAIL& email) override;
    list<Gerente> listarGerentes() override;

    // Implementação dos métodos da interface ISPessoa para Hóspedes
    bool criarHospede(const Hospede& hospede) override;
    bool deletarHospede(const EMAIL& email) override;
    bool atualizarHospede(const Hospede& hospede) override;
    Hospede lerHospede(const EMAIL& email) override;
    list<Hospede> listarHospedes() override;

    // Métodos de injeção de dependência
    void setContainerGerente(ContainerGerente* container) { this->containerGerentes = container; }
    void setContainerHospede(ContainerHospede* container) { this->containerHospedes = container; }
};

// ====================================================================
// 3. MÓDULO DE SERVIÇO: RESERVAS E INFRAESTRUTURA (MSR)
// ====================================================================

/**
 * @class CntrMSReserva
 * @brief Controlador de Serviço de Reservas e Infraestrutura.
 *
 * @details Responsável pela lógica de hotéis, quartos e reservas.
 * Inclui a validação crítica de conflito de datas em reservas.
 */
class CntrMSReserva : public ISReserva {
private:
    ContainerReserva* containerReservas;
    ContainerHotel* containerHoteis;
    ContainerQuarto* containerQuartos;

public:
    // Implementação dos métodos da interface ISReserva para Hotéis
    bool criarHotel(const Hotel& hotel) override;
    bool deletarHotel(const Codigo& codigo) override;
    bool atualizarHotel(const Hotel& hotel) override;
    Hotel lerHotel(const Codigo& codigo) override;
    list<Hotel> listarHoteis() override;

    // Implementação dos métodos da interface ISReserva para Quartos
    bool criarQuarto(const Quarto& quarto) override;
    bool deletarQuarto(const Numero& numero) override;
    bool atualizarQuarto(const Quarto& quarto) override;
    Quarto lerQuarto(const Numero& numero) override;
    list<Quarto> listarQuartos() override;

    // Implementação dos métodos da interface ISReserva para Reservas
    bool criarReserva(const Reserva& reserva) override;
    bool deletarReserva(const Codigo& codigo) override;
    bool atualizarReserva(const Reserva& reserva) override;
    Reserva lerReserva(const Codigo& codigo) override;
    list<Reserva> listarReservas() override;

    // Métodos de injeção de dependência
    void setContainerReserva(ContainerReserva* cR) { this->containerReservas = cR; }
    void setContainerHotel(ContainerHotel* cH) { this->containerHoteis = cH; }
    void setContainerQuarto(ContainerQuarto* cQ) { this->containerQuartos = cQ; }
};

#endif // SERVICOS_HPP_INCLUDED
