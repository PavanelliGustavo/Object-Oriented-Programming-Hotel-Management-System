#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp"
#include "dominios.hpp"
#include <iostream>

using namespace std;

// Forward Declaration do Menu Principal (para ser usado após autenticação)
class CntrIUIntegracao;

// ====================================================================
// INTERFACE DE APRESENTAÇÃO (GERAL)
// ====================================================================

/**
 * @class IUIAutenticacao
 * @brief Interface para o Módulo de Apresentação de Autenticação (MAA).
 *
 * @details Define o contrato para a interação com o usuário na tela de login.
 */
class IUIAutenticacao {
public:
    virtual void setInterfaceServico(ILNAutenticacao* interface) = 0;
    virtual void setControladorIntegracao(CntrIUIntegracao* controlador) = 0;
    virtual bool executar() = 0; // Retorna true se a autenticação for bem-sucedida
    virtual ~IUIAutenticacao() {}
};


// ====================================================================
// CONTROLADORA DE APRESENTAÇÃO: AUTENTICAÇÃO (MAA)
// ====================================================================

/**
 * @class CntrIUAutenticacao
 * @brief Implementa a lógica da tela de login.
 *
 * @details Coleta EMAIL e Senha do usuário e delega a verificação à Camada de Serviço.
 */
class CntrIUAutenticacao : public IUIAutenticacao {
private:
    ILNAutenticacao* servicoAutenticacao; // Referência à Camada de Serviço
    CntrIUIntegracao* controladorIntegracao; // Referência ao Menu Principal

public:
    // Métodos de Injeção de Dependência
    void setInterfaceServico(ILNAutenticacao* interface) override {
        this->servicoAutenticacao = interface;
    }
    void setControladorIntegracao(CntrIUIntegracao* controlador) override {
        this->controladorIntegracao = controlador;
    }

    // Método principal de execução
    bool executar() override;
};


// ====================================================================
// CONTROLADORA DE APRESENTAÇÃO: INTEGRAÇÃO (MAI) - PASSO 6
// ====================================================================

/**
 * @class CntrIUIntegracao
 * @brief Controladora de Integração e Menu Principal do Sistema (MAI).
 *
 * @details Gerencia a navegação de alto nível após o login e o encerramento do sistema.
 */
class CntrIUIntegracao {
private:
    // Referências para as Controladoras de Apresentação de cada subsistema
    // (A ser injetada no main.cpp)
    IUIReserva* ctrlReserva;
    // IUIPessoa* ctrlPessoa;

    bool autenticado; // Flag para saber se o usuário está logado

public:
    CntrIUIntegracao() : autenticado(false) {}

    void setCtrlReserva(IUIReserva* ctrl) { this->ctrlReserva = ctrl; }

    void executar() {
        // Lógica do menu principal (será implementada no .cpp)
    }

    void setAutenticado(bool status) {
        this->autenticado = status;
    }
};

// ====================================================================
// INTERFACE DE APRESENTAÇÃO (GERAL)
// ====================================================================

/**
 * @class IUIReserva
 * @brief Interface para o Módulo de Apresentação de Reservas (MAR).
 *
 * @details Define o contrato para a interação com o usuário, exigindo uma referência
 * à interface de Serviço de Reservas para acessar a lógica de negócio.
 */
class IUIReserva {
public:
    virtual void setInterfaceServico(ILNReserva* interface) = 0;
    virtual void executar() = 0; // Método principal que exibe o menu/inicia a interação
    virtual ~IUIReserva() {}
};

// ====================================================================
// CONTROLADORA DE APRESENTAÇÃO (MAR)
// ====================================================================

/**
 * @class CntrIUReserva
 * @brief Implementação da controladora de Interface com o Usuário para Reservas.
 *
 * @details É responsável por coletar dados do usuário, validar o formato inicial (usando Domínios)
 * e delegar as ações à Camada de Serviço através da interface ILNReserva.
 */
class CntrIUReserva : public IUIReserva {
private:
    ILNReserva* servicoReservas; // Referência à interface de SERVIÇO (MSR)

public:
    // Método de Injeção de Dependência (implementa IUIReserva)
    void setInterfaceServico(ILNReserva* interface) override {
        this->servicoReservas = interface;
    }

    // Método de Execução (implementa IUIReserva)
    void executar() override;

    // Funções auxiliares específicas para cada serviço CRUD (para organizar o menu)
    void executarCriarReserva();
    void executarDeletarReserva();
    void executarAtualizarReserva();
    void executarPesquisarReserva();
    void executarListarReservas();

    // Função auxiliar para coletar e validar dados de Reserva
    bool coletarDadosReserva(Reserva* reserva);
};

#endif // APRESENTACAO_HPP_INCLUDED
