#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp" // Contém IAAutenticacao, IAPessoal, IAReserva
#include "dominios.hpp"
#include <iostream>

using namespace std;

// ====================================================================
// 1. CONTROLADORA DE APRESENTAÇÃO: AUTENTICAÇÃO (MAA)
// ====================================================================

/**
 * @class CntrMAAutenticacao
 * @brief Implementa a interface IAAutenticacao (definida em interfaces.hpp).
 * @details Responsável por interagir com o usuário para Login e Cadastro.
 */
class CntrMAAutenticacao : public IAAutenticacao {
private:
    ISAutenticacao* servicoAutenticacao;

public:
    // Implementação do método de injeção de dependência
    void setISAutenticacao(ISAutenticacao* servico) override {
        this->servicoAutenticacao = servico;
    }

    // Implementação do fluxo principal
    // Retorna true se autenticou, e preenche o objeto 'email' com o logado
    bool executar(EMAIL& email) override;
};


// ====================================================================
// 2. CONTROLADORA DE APRESENTAÇÃO: PESSOAL (MAP)
// ====================================================================

/**
 * @class CntrMAPessoal
 * @brief Implementa a interface IAPessoal.
 * @details Responsável por mostrar dados do gerente e permitir edição/exclusão.
 */
class CntrMAPessoal : public IAPessoal {
private:
    ISPessoa* servicoPessoa;

public:
    void setISPessoa(ISPessoa* servico) override {
        this->servicoPessoa = servico;
    }

    void executar(const EMAIL& email) override;

    // Métodos auxiliares internos
    void editarPerfil(const EMAIL& email);
};


// ====================================================================
// 3. CONTROLADORA DE APRESENTAÇÃO: RESERVAS (MAR)
// ====================================================================

/**
 * @class CntrMAReserva
 * @brief Implementa a interface IAReserva.
 * @details Gerencia Hotéis, Quartos e Reservas.
 */
class CntrMAReserva : public IAReserva {
private:
    ISReserva* servicoReserva;
    ISPessoa* servicoPessoa; // Necessário para listar hóspedes ao criar reservas

public:
    void setISReserva(ISReserva* servico) override {
        this->servicoReserva = servico;
    }

    void setISPessoa(ISPessoa* servico) override {
        this->servicoPessoa = servico;
    }

    void executar(const EMAIL& email) override;

    // Métodos auxiliares para organizar o menu interno
    void menuHoteis();
    void menuQuartos();
    void menuReservas();
    void menuHospedes();
};


// ====================================================================
// 4. CONTROLADORA DE INTEGRAÇÃO (MAI)
// ====================================================================

/**
 * @class CntrMAIntegracao
 * @brief Módulo de Acesso e Interface (Hub Principal).
 * @details Não herda de interface específica, pois é o ponto de entrada (main).
 */
class CntrMAIntegracao {
private:
    // Referências para as interfaces dos módulos de apresentação
    IAAutenticacao* cntrAutenticacao;
    IAPessoal* cntrPessoal;
    IAReserva* cntrReserva;

    // Estado do usuário logado
    EMAIL emailUsuarioLogado;
    bool autenticado;

public:
    CntrMAIntegracao() : autenticado(false) {}

    // Injeção das controladoras de apresentação
    void setCntrAutenticacao(IAAutenticacao* cntr) { this->cntrAutenticacao = cntr; }
    void setCntrPessoal(IAPessoal* cntr) { this->cntrPessoal = cntr; }
    void setCntrReserva(IAReserva* cntr) { this->cntrReserva = cntr; }

    // Loop principal do sistema
    void executar();
};

#endif // APRESENTACAO_HPP_INCLUDED
