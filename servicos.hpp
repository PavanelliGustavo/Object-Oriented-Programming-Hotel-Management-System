#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

#include "interfaces.hpp" // Depende das interfaces (ILN...)
// #include "containers.hpp" // Contêineres serão usados na implementação do .cpp

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
    // Note que uma reserva envolve quartos, então esta controladora
    // precisará de uma referência à lógica/dados de quartos para checar conflitos.
    // ContainerQuarto* containerQuartos; // Exemplo de dependência extra

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

#endif // SERVICOS_HPP_INCLUDED
