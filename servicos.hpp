#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

#include "interfaces.hpp" // Depende das interfaces (ILN...)

// ====================================================================
// Declarações Forward (Para evitar includes desnecessários no .hpp)
// Assume-se que estas classes Contêineres existem
// ====================================================================

class ContainerGerente;
class ContainerHospede;
class ContainerHotel;
class ContainerQuarto;
class ContainerReserva;

// ====================================================================
// 1. CONTROLADORA DE SERVIÇO: AUTENTICAÇÃO
// ====================================================================

class CntrLNAutenticacao : public ILNAutenticacao {
private:
    ContainerGerente* containerGerentes; // Referência ao contêiner de dados

public:
    // Implementação da interface
    bool autenticar(const EMAIL& email, const Senha& senha) override;

    // Método de Injeção de Dependência
    void setContainer(ContainerGerente* container) { this->containerGerentes = container; }
};

// ====================================================================
// 2. CONTROLADORA DE SERVIÇO: PESSOAS (GERENTE E HÓSPEDE)
// ====================================================================

class CntrLNPessoa : public ILNPessoa {
private:
    ContainerGerente* containerGerentes;
    ContainerHospede* containerHospedes;

public:
    // Implementação dos métodos de Gerente
    bool criarGerente(const Gerente& gerente) override;
    bool deletarGerente(const EMAIL& email) override;
    bool atualizarGerente(const Gerente& gerente) override;
    Gerente lerGerente(const EMAIL& email) override;
    list<Gerente> listarGerentes() override;

    // Implementação dos métodos de Hóspede
    bool criarHospede(const Hospede& hospede) override;
    bool deletarHospede(const EMAIL& email) override;
    bool atualizarHospede(const Hospede& hospede) override;
    Hospede lerHospede(const EMAIL& email) override;
    list<Hospede> listarHospedes() override;

    // Métodos de Injeção de Dependência
    void setContainerGerente(ContainerGerente* container) { this->containerGerentes = container; }
    void setContainerHospede(ContainerHospede* container) { this->containerHospedes = container; }
};

// ====================================================================
// 3. CONTROLADORA DE SERVIÇO: RESERVAS (SEU SUBSISTEMA)
// ====================================================================

class CntrLNReserva : public ILNReserva {
private:
    ContainerReserva* containerReservas;
    // Opcional: ContainerQuarto* containerQuartos; para lógica de conflito.

public:
    // Implementação dos métodos da interface ILNReserva
    bool criarReserva(const Reserva& reserva) override;
    bool deletarReserva(const Codigo& codigo) override;
    bool atualizarReserva(const Reserva& reserva) override;
    Reserva lerReserva(const Codigo& codigo) override;
    list<Reserva> listarReservas() override;

    // Método de Injeção de Dependência
    void setContainer(ContainerReserva* container) { this->containerReservas = container; }
};

// ====================================================================
// 4. INTERFACE E CONTROLADORA DE SERVIÇO DE HOTEL/QUARTO
// ====================================================================

/**
 * @class ILNHotel
 * @brief Interface para o Módulo de Serviço de Hotel e Quarto.
 *
 * @details Define os serviços CRUD e de listagem para as Entidades Hotel e Quarto.
 */
class ILNHotel {
public:
    // --- Hotel CRUD ---
    virtual bool criarHotel(const Hotel& hotel) = 0;
    virtual bool deletarHotel(const Codigo& codigo) = 0;
    virtual bool atualizarHotel(const Hotel& hotel) = 0;
    virtual Hotel lerHotel(const Codigo& codigo) = 0;
    virtual list<Hotel> listarHoteis() = 0;

    // --- Quarto CRUD ---
    virtual bool criarQuarto(const Quarto& quarto) = 0;
    virtual bool deletarQuarto(const Numero& numero) = 0;
    virtual bool atualizarQuarto(const Quarto& quarto) = 0;
    virtual Quarto lerQuarto(const Numero& numero) = 0;
    virtual list<Quarto> listarQuartos() = 0;

    virtual ~ILNHotel() {}
};


/**
 * @class CntrLNHotel
 * @brief Controladora que implementa a lógica de negócio para Hotel e Quarto.
 */
class CntrLNHotel : public ILNHotel {
private:
    ContainerHotel* containerHoteis;
    ContainerQuarto* containerQuartos;

public:
    // Implementação dos métodos de ILNHotel
    bool criarHotel(const Hotel& hotel) override;
    bool deletarHotel(const Codigo& codigo) override;
    bool atualizarHotel(const Hotel& hotel) override;
    Hotel lerHotel(const Codigo& codigo) override;
    list<Hotel> listarHoteis() override;

    bool criarQuarto(const Quarto& quarto) override;
    bool deletarQuarto(const Numero& numero) override;
    bool atualizarQuarto(const Quarto& quarto) override;
    Quarto lerQuarto(const Numero& numero) override;
    list<Quarto> listarQuartos() override;

    // Métodos de Injeção de Dependência
    void setContainerHotel(ContainerHotel* container) { this->containerHoteis = container; }
    void setContainerQuarto(ContainerQuarto* container) { this->containerQuartos = container; }
};

#endif // SERVICOS_HPP_INCLUDED
