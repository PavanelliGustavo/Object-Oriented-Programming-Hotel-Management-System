#include "apresentacao.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <limits> // Para manipulação de cin

using namespace std;

// ====================================================================
// CONTROLADORA DE APRESENTAÇÃO: AUTENTICAÇÃO (MAA)
// ====================================================================

bool CntrIUAutenticacao::executar() {
    string emailStr, senhaStr;
    bool autenticacaoSucesso = false;

    // Loop para tentar login
    while (true) {
        cout << "\n--- AUTENTICACAO DO GERENTE ---\n";
        cout << "Digite seu EMAIL (PK): ";
        cin >> emailStr;
        cout << "Digite sua SENHA: ";
        cin >> senhaStr;
        
        try {
            // 1. Validação de formato (Domínio)
            EMAIL domEmail;
            domEmail.setValor(emailStr);

            Senha domSenha;
            domSenha.setValor(senhaStr);
            
            // 2. Delega a verificação para a Camada de Serviço
            if (servicoAutenticacao->autenticar(domEmail, domSenha)) {
                cout << "\nSUCESSO: Gerente autenticado!" << endl;
                
                // 3. Informa o Menu Principal (MAI) que o login foi feito
                controladorIntegracao->setAutenticado(true);
                autenticacaoSucesso = true;
                break;
            } else {
                cout << "\nFALHA: Email ou Senha invalidos. Tente novamente." << endl;
            }

        } catch (const invalid_argument& e) {
            // Captura a exceção lançada pelo Domínio (e.g., Email ou Senha mal formatados)
            cout << "\nERRO DE FORMATO: " << e.what() << endl;
        }
        
        cout << "Pressione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa buffer
        cin.get();
    }
    
    return autenticacaoSucesso;
}

// Funções Auxiliares para Limpar Entrada
void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ====================================================================
// FUNÇÃO AUXILIAR: COLETAR E VALIDAR DADOS DE RESERVA
// ====================================================================

/**
 * @brief Coleta todos os dados de domínio necessários para criar/atualizar uma Reserva,
 * validando o formato de entrada.
 * @return true se todos os dados foram coletados e validados com sucesso; false caso contrário.
 */
bool CntrIUReserva::coletarDadosReserva(Reserva* reserva) {
    string codigoStr, chegadaDiaStr, chegadaMesStr, chegadaAnoStr,
           partidaDiaStr, partidaMesStr, partidaAnoStr, valorStr;

    // Domínios temporários
    Codigo domCodigo;
    Data domChegada, domPartida;
    Dinheiro domValor;

    // Coleta e Validação do Código
    cout << "Digite o Codigo da Reserva (10 caracteres alfanumericos): ";
    cin >> codigoStr;
    try {
        domCodigo.setValor(codigoStr);
        reserva->setCodigo(domCodigo);
    } catch (const invalid_argument& e) {
        cout << "ERRO DE FORMATO: " << e.what() << endl;
        return false;
    }

    // Coleta e Validação de Datas (Simplificado para o exemplo)
    cout << "--- Data de Chegada ---" << endl;
    cout << "Dia (1-31): "; cin >> chegadaDiaStr;
    cout << "Mes (JAN, FEV, ...): "; cin >> chegadaMesStr;
    cout << "Ano (2000-2999): "; cin >> chegadaAnoStr;

    try {
        unsigned short dia = stoi(chegadaDiaStr);
        unsigned short ano = stoi(chegadaAnoStr);
        // O Domínio Data precisa ser capaz de receber strings e convertê-las/validá-las
        domChegada.setValor(dia, chegadaMesStr, ano);
        reserva->setChegada(domChegada);
    } catch (const exception& e) {
        cout << "ERRO DE FORMATO NA DATA DE CHEGADA: " << e.what() << endl;
        return false;
    }

    // Coleta e Validação do Valor
    cout << "Digite o Valor Total (0,01 a 1.000.000,00): ";
    cin >> valorStr;
    try {
        domValor.setValor(valorStr);
        reserva->setValor(domValor);
    } catch (const invalid_argument& e) {
        cout << "ERRO DE FORMATO NO VALOR: " << e.what() << endl;
        return false;
    }

    // Se todos os Domínios validaram, retorna true.
    return true;
}

// ====================================================================
// MÉTODOS DE EXECUÇÃO (MAR)
// ====================================================================

void CntrIUReserva::executarCriarReserva() {
    Reserva novaReserva;
    cout << "\n--- EXECUTAR CRIAR RESERVA ---\n";

    if (!coletarDadosReserva(&novaReserva)) {
        cout << "Operacao abortada devido a erro de formato de dados." << endl;
        return;
    }

    // Delega a ação para a Camada de Serviço (MSR)
    if (servicoReservas->criarReserva(novaReserva)) {
        cout << "SUCESSO: Reserva criada e salva!" << endl;
    } else {
        cout << "FALHA: Nao foi possivel criar a reserva (codigo duplicado ou conflito)." << endl;
    }
}

void CntrIUReserva::executarDeletarReserva() {
    string codigoStr;
    cout << "\n--- EXECUTAR DELETAR RESERVA ---\n";
    cout << "Digite o Codigo da Reserva a ser deletada: ";
    cin >> codigoStr;

    try {
        Codigo domCodigo;
        domCodigo.setValor(codigoStr);

        if (servicoReservas->deletarReserva(domCodigo)) {
            cout << "SUCESSO: Reserva deletada." << endl;
        } else {
            cout << "FALHA: Reserva nao encontrada." << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "ERRO DE FORMATO: " << e.what() << endl;
    }
}

void CntrIUReserva::executarPesquisarReserva() {
    string codigoStr;
    cout << "\n--- EXECUTAR PESQUISAR RESERVA ---\n";
    cout << "Digite o Codigo da Reserva para pesquisa: ";
    cin >> codigoStr;

    try {
        Codigo domCodigo;
        domCodigo.setValor(codigoStr);

        Reserva resultado = servicoReservas->lerReserva(domCodigo);

        // Critério para saber se a reserva foi encontrada:
        // A chave primária (Codigo) do resultado é diferente de um valor padrão.
        if (resultado.getCodigo().getValor() == domCodigo.getValor()) {
             cout << "SUCESSO: Reserva encontrada. Codigo: " << resultado.getCodigo().getValor() << endl;
             // Aqui mostraria outros dados como datas e valor.
        } else {
            cout << "FALHA: Reserva nao encontrada." << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "ERRO DE FORMATO: " << e.what() << endl;
    }
}

void CntrIUReserva::executarListarReservas() {
    cout << "\n--- LISTA DE RESERVAS ---\n";
    list<Reserva> reservas = servicoReservas->listarReservas();

    if (reservas.empty()) {
        cout << "Nenhuma reserva cadastrada." << endl;
        return;
    }

    for (const Reserva& r : reservas) {
        cout << " - Codigo: " << r.getCodigo().getValor() << " | [Detalhes omitidos]" << endl;
    }
}

void CntrIUReserva::executar() {
    // Menu simples para demonstrar a navegação
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU RESERVAS (MAR) ---\n";
        cout << "1 - Criar Reserva\n";
        cout << "2 - Deletar Reserva\n";
        cout << "3 - Pesquisar Reserva\n";
        cout << "4 - Listar Reservas\n";
        cout << "5 - Voltar\n";
        cout << "Selecione uma opcao: ";

        if (!(cin >> opcao)) {
            cout << "Opcao invalida. Tente novamente." << endl;
            cin.clear();
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: executarCriarReserva(); break;
            case 2: executarDeletarReserva(); break;
            case 3: executarPesquisarReserva(); break;
            case 4: executarListarReservas(); break;
            case 5: break;
            default: cout << "Opcao invalida.\n";
        }
    }
}

void CntrIUReserva::executarAtualizarReserva() {
    cout << "Funcionalidade de Atualizar Reserva ainda nao implementada." << endl;
    // Esta função chamaria coletarDadosReserva() e depois servicoReservas->atualizarReserva()
}
