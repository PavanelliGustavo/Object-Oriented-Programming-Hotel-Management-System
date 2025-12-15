#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp"
#include "domains.hpp"
#include <iostream>

using namespace std;

// ====================================================================
// 1. CONTROLADORA DE APRESENTAÇÃO: AUTENTICAÇÃO (MAA)
// ====================================================================

/**
 * @class CntrMAAutenticacao
 * @brief Controlador de Apresentação para o módulo de Autenticação.
 *
 * @details Gerencia as telas de Login e Cadastro de novos gerentes.
 */
class CntrMAAutenticacao : public IAAutenticacao {
private:
    ISAutenticacao* servicoAutenticacao;
    ISPessoa* servicoPessoa;

public:
    void setISAutenticacao(ISAutenticacao* servico) override {
        this->servicoAutenticacao = servico;
    }

    void setISPessoa(ISPessoa* servico) override {
        this->servicoPessoa = servico;
    }

    bool autenticar(EMAIL& email) override;
    bool cadastrar() override;
};


// ====================================================================
// 2. CONTROLADORA DE APRESENTAÇÃO: PESSOAL (MAP)
// ====================================================================

/**
 * @class CntrMAPessoal
 * @brief Controlador de Apresentação para o módulo Pessoal.
 *
 * @details Permite ao gerente visualizar e editar seus próprios dados cadastrais.
 */
class CntrMAPessoal : public IAPessoal {
private:
    ISPessoa* servicoPessoa;

public:
    void setISPessoa(ISPessoa* servico) override {
        this->servicoPessoa = servico;
    }

    void executar(const EMAIL& email) override;

    /**
     * @brief Método auxiliar para exibir o menu de edição de perfil.
     * @param email Email do usuário logado.
     */
    void editarPerfil(const EMAIL& email);
};


// ====================================================================
// 3. CONTROLADORA DE APRESENTAÇÃO: RESERVAS (MAR)
// ====================================================================

/**
 * @class CntrMAReserva
 * @brief Controlador de Apresentação para o módulo de Reservas.
 *
 * @details Centraliza os menus de gestão de Hotéis, Quartos, Reservas e Hóspedes.
 */
class CntrMAReserva : public IAReserva {
private:
    ISReserva* servicoReserva;
    ISPessoa* servicoPessoa;

public:
    void setISReserva(ISReserva* servico) override {
        this->servicoReserva = servico;
    }

    void setISPessoa(ISPessoa* servico) override {
        this->servicoPessoa = servico;
    }

    void executar(const EMAIL& email) override;

    // Submenus auxiliares para organização da UI
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
 * @brief Controlador Principal de Integração (Módulo de Acesso e Interface).
 *
 * @details Atua como o "Hub" central da aplicação, orquestrando a navegação
 * entre a tela inicial, login e os menus funcionais. Mantém o estado da sessão.
 */
class CntrMAIntegracao {
private:
    IAAutenticacao* cntrAutenticacao;
    IAPessoal* cntrPessoal;
    IAReserva* cntrReserva;

    EMAIL emailUsuarioLogado;
    bool autenticado;

public:
    CntrMAIntegracao() : autenticado(false) {}

    void setCntrAutenticacao(IAAutenticacao* cntr) { this->cntrAutenticacao = cntr; }
    void setCntrPessoal(IAPessoal* cntr) { this->cntrPessoal = cntr; }
    void setCntrReserva(IAReserva* cntr) { this->cntrReserva = cntr; }

    /**
     * @brief Inicia o loop principal da aplicação.
     */
    void executar();
};

#endif // APRESENTACAO_HPP_INCLUDED
