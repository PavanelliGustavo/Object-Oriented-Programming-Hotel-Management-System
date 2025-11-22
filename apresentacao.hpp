#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp"
#include "dominios.hpp"

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
