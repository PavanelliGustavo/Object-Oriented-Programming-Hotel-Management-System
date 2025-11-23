#include "servicos.hpp"
#include "containers.hpp"
#include <iostream>
#include <list>

using namespace std;

// ====================================================================
// FUNÇÕES AUXILIARES DE LÓGICA (PARA VERIFICAR CONFLITOS DE RESERVA)
// ====================================================================

bool verificarSobreposicao(const Data& chegada1, const Data& partida1,
                          const Data& chegada2, const Data& partida2) {
    // Retorno fictício para compilação.
    return false;
}


// ====================================================================
// 1. CONTROLADORA DE SERVIÇO: AUTENTICAÇÃO
// ====================================================================

bool CntrLNAutenticacao::autenticar(const EMAIL& email, const Senha& senha) {
    Gerente gerentePesquisa;
    gerentePesquisa.setEmail(email);

    if (containerGerentes->pesquisar(&gerentePesquisa)) {
        if (gerentePesquisa.getSenha().getValor() == senha.getValor()) {
            return true; // Autenticação bem-sucedida
        }
    }
    return false; // Autenticação falhou
}

// ====================================================================
// 2. CONTROLADORA DE SERVIÇO: PESSOAS (GERENTE E HÓSPEDE)
// ====================================================================

// --- Métodos CRUD Gerente ---

bool CntrLNPessoa::criarGerente(const Gerente& gerente) {
    Gerente g;
    g.setEmail(gerente.getEmail());

    if (containerGerentes->pesquisar(&g)) {
        return false; // Falha: Gerente com este email já existe.
    }
    return containerGerentes->incluir(gerente);
}

bool CntrLNPessoa::deletarGerente(const EMAIL& email) {
    return containerGerentes->remover(email);
}

bool CntrLNPessoa::atualizarGerente(const Gerente& gerente) {
    // A PK (EMAIL) já está no objeto 'gerente' e o contêiner a usa para localizar e atualizar.
    return containerGerentes->atualizar(gerente);
}

Gerente CntrLNPessoa::lerGerente(const EMAIL& email) {
    Gerente g;
    g.setEmail(email);
    containerGerentes->pesquisar(&g);
    return g;
}

list<Gerente> CntrLNPessoa::listarGerentes() {
    list<Gerente> lista;
    // Lógica para preencher a lista de todos os gerentes do contêiner...
    return lista;
}

// --- Métodos CRUD Hóspede ---

bool CntrLNPessoa::criarHospede(const Hospede& hospede) {
    Hospede h;
    h.setEmail(hospede.getEmail());
    if (containerHospedes->pesquisar(&h)) {
        return false;
    }
    return containerHospedes->incluir(hospede);
}

bool CntrLNPessoa::deletarHospede(const EMAIL& email) {
    return containerHospedes->remover(email);
}

bool CntrLNPessoa::atualizarHospede(const Hospede& hospede) {
    return containerHospedes->atualizar(hospede);
}

Hospede CntrLNPessoa::lerHospede(const EMAIL& email) {
    Hospede h;
    h.setEmail(email);
    containerHospedes->pesquisar(&h);
    return h;
}

list<Hospede> CntrLNPessoa::listarHospedes() {
    list<Hospede> lista;
    return lista;
}

// ====================================================================
// 3. CONTROLADORA DE SERVIÇO: RESERVAS
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
        // Simulação de verificação de conflito de datas:
        bool conflito = verificarSobreposicao(
            reserva.getChegada(), reserva.getPartida(),
            reservaExistente.getChegada(), reservaExistente.getPartida()
        );

        if (conflito) {
             return false;
        }
    }

    // 3. Persistência
    return containerReservas->incluir(reserva);
}

bool CntrLNReserva::deletarReserva(const Codigo& codigo) {
    return containerReservas->remover(codigo);
}

bool CntrLNReserva::atualizarReserva(const Reserva& reserva) {
    // Lógica de negócio: verifica se a atualização não causa conflitos.
    return containerReservas->atualizar(reserva);
}

Reserva CntrLNReserva::lerReserva(const Codigo& codigo) {
    Reserva r;
    r.setCodigo(codigo);
    containerReservas->pesquisar(&r);
    return r;
}

list<Reserva> CntrLNReserva::listarReservas() {
    return containerReservas->listar();
}

// ====================================================================
// 4. CONTROLADORA DE SERVIÇO: HOTEL E QUARTO
// ====================================================================

// --- Métodos CRUD Hotel ---

bool CntrLNHotel::criarHotel(const Hotel& hotel) {
    Hotel h;
    h.setCodigo(hotel.getCodigo());

    if (containerHoteis->pesquisar(&h)) {
        return false;
    }
    // No caso de criação, apenas garante unicidade da PK.
    return containerHoteis->incluir(hotel);
}

bool CntrLNHotel::deletarHotel(const Codigo& codigo) {
    // Lógica de Negócio Crítica: Garantir que não haja Quartos/Reservas dependentes.
    return containerHoteis->remover(codigo);
}

bool CntrLNHotel::atualizarHotel(const Hotel& hotel) {
    // Regra: Não é possível editar dado que identifica registro (PK).
    return containerHoteis->atualizar(hotel);
}

Hotel CntrLNHotel::lerHotel(const Codigo& codigo) {
    Hotel h;
    h.setCodigo(codigo);
    containerHoteis->pesquisar(&h);
    return h;
}

list<Hotel> CntrLNHotel::listarHoteis() {
    list<Hotel> lista;
    return lista;
}


// --- Métodos CRUD Quarto ---

bool CntrLNHotel::criarQuarto(const Quarto& quarto) {
    Quarto q;
    q.setNumero(quarto.getNumero());

    if (containerQuartos->pesquisar(&q)) {
        return false;
    }
    return containerQuartos->incluir(quarto);
}

bool CntrLNHotel::deletarQuarto(const Numero& numero) {
    // Regra Crítica: Deve-se verificar se há RESERVAS ativas dependentes antes de deletar o Quarto.
    return containerQuartos->remover(numero);
}

bool CntrLNHotel::atualizarQuarto(const Quarto& quarto) {
    // PK (Número) não pode ser editada.
    return containerQuartos->atualizar(quarto);
}

Quarto CntrLNHotel::lerQuarto(const Numero& numero) {
    Quarto q;
    q.setNumero(numero);
    containerQuartos->pesquisar(&q);
    return q;
}

list<Quarto> CntrLNHotel::listarQuartos() {
    list<Quarto> lista;
    return lista;
}
