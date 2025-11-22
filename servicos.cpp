#include "servicos.hpp"
#include "containers.hpp"
#include <iostream>

using namespace std;

// ====================================================================
// FUNÇÕES AUXILIARES DE LÓGICA (PARA VERIFICAR CONFLITOS DE RESERVA)
// ====================================================================

/**
 * @brief Verifica se duas reservas, dadas suas datas, se sobrepõem.
 * @details A sobreposição ocorre se a nova reserva começar antes do final da existente
 * e terminar depois do início da existente.
 * Assume que a Entidade Data é comparável (o que precisaria ser implementado na classe Data).
 */
bool verificarSobreposicao(const Data& chegada1, const Data& partida1,
                          const Data& chegada2, const Data& partida2) {
    // Para simplificar, assumimos que as datas têm um método de comparação lógica (>, <, ==).
    // Na prática, você precisaria converter as datas para um formato comparável (e.g., inteiro de dias)
    // if (chegada1 < partida2 && partida1 > chegada2) {
    //     return true;
    // }
    return false; // Retorno fictício para compilação
}


// ====================================================================
// 1. CONTROLADORA DE SERVIÇO: AUTENTICAÇÃO
// ====================================================================

bool CntrLNAutenticacao::autenticar(const EMAIL& email, const Senha& senha) {
    Gerente gerentePesquisa;
    gerentePesquisa.setEmail(email);

    // 1. Pesquisa no contêiner se o email existe
    if (containerGerentes->pesquisar(&gerentePesquisa)) {
        // 2. Se o gerente existe, verifica se a senha corresponde
        if (gerentePesquisa.getSenha().getValor() == senha.getValor()) {
            return true; // Autenticação bem-sucedida
        }
    }
    return false; // Autenticação falhou
}

// ====================================================================
// 2. CONTROLADORA DE SERVIÇO: PESSOAS (Exemplo: criarGerente)
// ====================================================================

bool CntrLNPessoa::criarGerente(const Gerente& gerente) {
    // Lógica de negócio: O Gerente a ser criado não deve ter um EMAIL já existente.

    // 1. Tenta pesquisar se a PK (EMAIL) já existe no contêiner
    Gerente g;
    g.setEmail(gerente.getEmail());

    if (containerGerentes->pesquisar(&g)) {
        return false; // Falha: Gerente com este email já existe.
    }

    // 2. Se não existe, inclui no contêiner
    return containerGerentes->incluir(gerente);
}

// Implementação dos outros métodos CRUD da CntrLNPessoa seguiria aqui...


// ====================================================================
// 3. CONTROLADORA DE SERVIÇO: RESERVAS (SEU SUBSISTEMA - MSR)
// ====================================================================

bool CntrLNReserva::criarReserva(const Reserva& reserva) {
    // 1. Lógica de Negócio: Verificar se o Código (PK) já existe
    Reserva r;
    r.setCodigo(reserva.getCodigo());
    if (containerReservas->pesquisar(&r)) {
        return false; // Falha: Código de reserva já existe.
    }

    // 2. Lógica de Negócio CRÍTICA: Não podem ocorrer conflitos entre reservas.
    list<Reserva> todasReservas = containerReservas->listar();

    for (const Reserva& reservaExistente : todasReservas) {
        // O teste de conflito deve ser feito apenas para reservas no mesmo QUARTO!
        // (Assumindo que o objeto Reserva tem uma referência ou PK do Quarto, que não implementamos
        // nas Entidades ainda, mas que seria essencial aqui.)

        // Simulação de verificação de conflito de datas:
        bool conflito = verificarSobreposicao(
            reserva.getChegada(), reserva.getPartida(),
            reservaExistente.getChegada(), reservaExistente.getPartida()
        );

        // if (reservaExistente.getQuartoPK().getValor() == reserva.getQuartoPK().getValor() && conflito) {
        //     return false; // Conflito de data/quarto!
        // }
    }

    // 3. Persistência
    return containerReservas->incluir(reserva);
}

bool CntrLNReserva::deletarReserva(const Codigo& codigo) {
    // Simplesmente delega a remoção ao Contêiner
    return containerReservas->remover(codigo);
}

bool CntrLNReserva::atualizarReserva(const Reserva& reserva) {
    // Antes de atualizar, a lógica de negócio deve garantir que a atualização
    // (e.g., mudança de data) não cause novos conflitos.

    // 1. Delega a verificação de conflito (com exceção da própria reserva)

    // 2. Atualiza
    return containerReservas->atualizar(reserva);
}

Reserva CntrLNReserva::lerReserva(const Codigo& codigo) {
    Reserva r;
    r.setCodigo(codigo);
    containerReservas->pesquisar(&r);
    return r; // Retorna o objeto (se não encontrar, retorna objeto padrão).
}

list<Reserva> CntrLNReserva::listarReservas() {
    return containerReservas->listar();
}
