#include "presentation.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <iomanip> // Para formatar dinheiro

using namespace std;

// ====================================================================
// FUNÇÕES UTILITÁRIAS
// ====================================================================

void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void esperarEnter() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ====================================================================
// 1. IMPLEMENTAÇÃO: CONTROLADORA DE AUTENTICAÇÃO (MAA)
// ====================================================================

bool CntrMAAutenticacao::autenticar(EMAIL& email) {
    string emailStr, senhaStr;
    cout << "\n--- LOGIN ---\n";
    cout << "Email: "; cin >> emailStr;
    cout << "Senha: "; cin >> senhaStr;

    try {
        EMAIL domEmail; domEmail.setValor(emailStr);
        Senha domSenha; domSenha.setValor(senhaStr);

        if (servicoAutenticacao->autenticar(domEmail, domSenha)) {
            cout << "SUCESSO: Bem-vindo!\n";
            email = domEmail;
            return true;
        } else {
            cout << "FALHA: Credenciais invalidas.\n";
            return false;
        }
    } catch (const exception& e) {
        cout << "ERRO FORMATO: " << e.what() << endl;
        return false;
    }
}

bool CntrMAAutenticacao::cadastrar() {
    cout << "\n--- CRIAR NOVA CONTA (GERENTE) ---\n";
    string nomeStr, emailStr, senhaStr;
    int ramalInt;

    try {
        Nome n; EMAIL e; Senha s; Ramal r;

        limparBuffer(); // Limpa lixo do menu anterior
        cout << "Nome (Maiusc): "; getline(cin, nomeStr); n.setValor(nomeStr);
        cout << "Email: "; cin >> emailStr; e.setValor(emailStr);
        cout << "Senha (5 chars: Aa1!): "; cin >> senhaStr; s.setValor(senhaStr);
        cout << "Ramal (0-50): "; cin >> ramalInt; r.setValor(ramalInt);

        Gerente g;
        g.setNome(n); g.setEmail(e); g.setSenha(s); g.setRamal(r);

        if (servicoPessoa->criarGerente(g)) {
            cout << "SUCESSO: Conta criada! Use suas credenciais para logar.\n";
            return true;
        } else {
            cout << "FALHA: Email ja cadastrado.\n";
            return false;
        }
    } catch (const exception& e) {
        cout << "ERRO DE DADOS: " << e.what() << endl;
        return false;
    }
}

// ====================================================================
// 2. IMPLEMENTAÇÃO: CONTROLADORA PESSOAL (MAP)
// ====================================================================

void CntrMAPessoal::executar(const EMAIL& email) {
    int opcao = 0;
    while (opcao != 3) {
        cout << "\n=========================================\n";
        cout << "           MEU PERFIL (GERENTE)          \n";
        cout << "=========================================\n";
        cout << "Usuario Logado: " << email.getValor() << endl;
        cout << "-----------------------------------------\n";
        cout << "1 - Visualizar Meus Dados\n";
        cout << "2 - Editar Perfil\n";
        cout << "3 - Voltar ao Menu Principal\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: {
                try {
                    Gerente g = servicoPessoa->lerGerente(email);
                    cout << "\n--- DADOS ATUAIS ---\n";
                    cout << "Nome:  " << g.getNome().getValor() << endl;
                    cout << "Email: " << g.getEmail().getValor() << endl;
                    cout << "Ramal: " << g.getRamal().getValor() << endl;
                    cout << "Senha: " << g.getSenha().getValor() << endl;
                } catch (...) {
                    cout << "Erro ao recuperar dados do perfil." << endl;
                }
                esperarEnter();
                break;
            }
            case 2:
                // Chama a função de edição que implementamos abaixo
                editarPerfil(email);
                break;
            case 3:
                break;
            default:
                cout << "Opcao invalida." << endl;
        }
    }
}

void CntrMAPessoal::editarPerfil(const EMAIL& email) {
    try {
        // 1. Carrega os dados atuais do gerente para garantir que temos o objeto completo
        Gerente gerenteAtual = servicoPessoa->lerGerente(email);

        int opcao = 0;
        while(opcao != 3) {
            cout << "\n--- EDITAR PERFIL ---\n";
            cout << "1 - Alterar Nome\n";
            cout << "2 - Alterar Senha\n";
            cout << "3 - Voltar\n";
            cout << "Nota: Email (Chave Primaria) nao pode ser alterado.\n";
            cout << "Selecione: ";
            cin >> opcao;

            if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

            if (opcao == 1) {
                // --- ALTERAR NOME ---
                string novoNomeStr;
                cout << "Novo Nome (5-20 caracteres, Maiusc): ";
                limparBuffer(); // Limpa o enter anterior
                getline(cin, novoNomeStr);

                try {
                    Nome novoNome;
                    novoNome.setValor(novoNomeStr); // Valida formato
                    gerenteAtual.setNome(novoNome); // Atualiza objeto local

                    // Persiste no "Banco de Dados"
                    if(servicoPessoa->atualizarGerente(gerenteAtual)) {
                        cout << "SUCESSO: Nome atualizado!\n";
                    } else {
                        cout << "ERRO: Falha ao atualizar no sistema.\n";
                    }
                } catch (const exception& e) {
                    cout << "ERRO FORMATO: " << e.what() << endl;
                }
                esperarEnter();
            }
            else if (opcao == 2) {
                // --- ALTERAR SENHA ---
                string novaSenhaStr;
                cout << "Nova Senha (5 chars, regras de complexidade): ";
                cin >> novaSenhaStr;

                try {
                    Senha novaSenha;
                    novaSenha.setValor(novaSenhaStr); // Valida formato
                    gerenteAtual.setSenha(novaSenha); // Atualiza objeto local

                    // Persiste no "Banco de Dados"
                    if(servicoPessoa->atualizarGerente(gerenteAtual)) {
                        cout << "SUCESSO: Senha atualizada!\n";
                    } else {
                        cout << "ERRO: Falha ao atualizar no sistema.\n";
                    }
                } catch (const exception& e) {
                    cout << "ERRO FORMATO: " << e.what() << endl;
                }
                esperarEnter();
            }
        }

    } catch (const exception& e) {
        cout << "Erro critico ao acessar perfil: " << e.what() << endl;
        esperarEnter();
    }
}

// ====================================================================
// 3. IMPLEMENTAÇÃO: CONTROLADORA DE RESERVAS E INFRA (MAR)
// ====================================================================

void CntrMAReserva::executar(const EMAIL& email) {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n=========================================\n";
        cout << "      GESTÃO DE RESERVAS E HOTEL         \n";
        cout << "=========================================\n";
        cout << "1 - Gerenciar Reservas\n";
        cout << "2 - Gerenciar Hoteis\n";
        cout << "3 - Gerenciar Quartos\n";
        cout << "4 - Gerenciar Hospedes\n";
        cout << "5 - Voltar ao Menu Principal\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch (opcao) {
            case 1: menuReservas(); break;
            case 2: menuHoteis(); break;
            case 3: menuQuartos(); break;
            case 4: menuHospedes(); break;
            case 5: break;
            default: cout << "Opcao invalida." << endl;
        }
    }
}

// --------------------------------------------------------------------
// IMPLEMENTAÇÃO: MENU DE RESERVAS
// --------------------------------------------------------------------
void CntrMAReserva::menuReservas() {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU RESERVAS ---\n";
        cout << "1 - Criar Nova Reserva\n";
        cout << "2 - Listar Reservas\n";
        cout << "3 - Pesquisar Reserva\n";
        cout << "4 - Deletar Reserva\n";
        cout << "5 - Voltar\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: {
                try {
                    Reserva r;
                    string codStr, valStr, dI, mI, aI, dF, mF, aF;
                    Codigo cod; Data ini; Data fim; Dinheiro val;

                    cout << "Codigo (10 carac): "; cin >> codStr; cod.setValor(codStr);
                    cout << "Chegada (DD MMM AAAA): "; cin >> dI >> mI >> aI; ini.setValor(stoi(dI), mI, stoi(aI));
                    cout << "Partida (DD MMM AAAA): "; cin >> dF >> mF >> aF; fim.setValor(stoi(dF), mF, stoi(aF));
                    cout << "Valor (00.00): "; cin >> valStr; val.setValor(stod(valStr));

                    r.setCodigo(cod); r.setChegada(ini); r.setPartida(fim); r.setValor(val);

                    if(servicoReserva->criarReserva(r)) cout << "SUCESSO: Reserva criada.\n";
                    else cout << "FALHA: Codigo duplicado ou conflito de datas.\n";
                } catch (const exception& e) { cout << "ERRO: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 2: {
                list<Reserva> lista = servicoReserva->listarReservas();
                if(lista.empty()) cout << "Nenhuma reserva.\n";
                for(const auto& r : lista) cout << "Reserva: " << r.getCodigo().getValor() << " | Valor: " << r.getValor().getValor() << endl;
                esperarEnter();
                break;
            }
            case 3: {
                string codStr; cout << "Codigo: "; cin >> codStr;
                try {
                    Codigo c; c.setValor(codStr);
                    Reserva r = servicoReserva->lerReserva(c); // Pode lançar exceção se não achar
                    // Se a implementação do serviço retornar obj vazio em vez de throw, verificar aqui
                    cout << "Encontrada! Chegada: " << r.getChegada().getDia() << "/" << r.getChegada().getMes() << endl;
                } catch (const exception& e) { cout << "Nao encontrada ou erro: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 4: {
                string codStr; cout << "Codigo: "; cin >> codStr;
                try {
                    Codigo c; c.setValor(codStr);
                    if(servicoReserva->deletarReserva(c)) cout << "Deletada com sucesso.\n";
                    else cout << "Nao encontrada.\n";
                } catch (const exception& e) { cout << "ERRO: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 5: break;
        }
    }
}

// --------------------------------------------------------------------
// IMPLEMENTAÇÃO: MENU DE HOTÉIS (Faltava implementar)
// --------------------------------------------------------------------
void CntrMAReserva::menuHoteis() {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU HOTEIS ---\n";
        cout << "1 - Cadastrar Hotel\n";
        cout << "2 - Listar Hoteis\n";
        cout << "3 - Pesquisar Hotel\n";
        cout << "4 - Deletar Hotel\n";
        cout << "5 - Voltar\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: { // CRIAR
                try {
                    Hotel h;
                    string codStr, nomeStr, endStr, telStr;
                    Codigo c; Nome n; Endereco e; Telefone t;

                    cout << "Codigo (10 carac): "; cin >> codStr; c.setValor(codStr);
                    limparBuffer(); // Limpar enter pendente antes de getline
                    cout << "Nome (5-20, Maiusc): "; getline(cin, nomeStr); n.setValor(nomeStr);
                    cout << "Endereco (5-30): "; getline(cin, endStr); e.setValor(endStr);
                    cout << "Telefone (+15 digitos): "; cin >> telStr; t.setValor(telStr);

                    h.setCodigo(c); h.setNome(n); h.setEndereco(e); h.setTelefone(t);

                    if(servicoReserva->criarHotel(h)) cout << "SUCESSO: Hotel cadastrado.\n";
                    else cout << "FALHA: Codigo ja existe.\n";

                } catch (const exception& e) { cout << "ERRO DADOS: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 2: { // LISTAR
                list<Hotel> lista = servicoReserva->listarHoteis();
                if(lista.empty()) cout << "Nenhum hotel cadastrado.\n";
                for(const auto& h : lista) {
                    cout << "COD: " << h.getCodigo().getValor()
                         << " | NOME: " << h.getNome().getValor() << endl;
                }
                esperarEnter();
                break;
            }
            case 3: { // LER
                string codStr; cout << "Codigo: "; cin >> codStr;
                try {
                    Codigo c; c.setValor(codStr);
                    Hotel h = servicoReserva->lerHotel(c);
                    cout << "--- DETALHES HOTEL ---\n";
                    cout << "Nome: " << h.getNome().getValor() << endl;
                    cout << "End.: " << h.getEndereco().getValor() << endl;
                    cout << "Tel.: " << h.getTelefone().getValor() << endl;
                } catch (const exception& e) { cout << "Nao encontrado: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 4: { // DELETAR
                string codStr; cout << "Codigo: "; cin >> codStr;
                try {
                    Codigo c; c.setValor(codStr);
                    if(servicoReserva->deletarHotel(c)) cout << "Hotel removido.\n";
                    else cout << "Hotel nao encontrado.\n";
                } catch (const exception& e) { cout << "ERRO: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 5: break;
        }
    }
}

// --------------------------------------------------------------------
// IMPLEMENTAÇÃO: MENU DE QUARTOS (Faltava implementar)
// --------------------------------------------------------------------
void CntrMAReserva::menuQuartos() {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU QUARTOS ---\n";
        cout << "1 - Cadastrar Quarto\n";
        cout << "2 - Listar Quartos\n";
        cout << "3 - Pesquisar Quarto\n";
        cout << "4 - Deletar Quarto\n";
        cout << "5 - Voltar\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: { // CRIAR
                try {
                    Quarto q;
                    int num, cap, ram;
                    string valStr;
                    Numero n; Capacidade c; Dinheiro d; Ramal r;

                    cout << "Numero (1-999): "; cin >> num; n.setValor(num);
                    cout << "Capacidade (1-4): "; cin >> cap; c.setValor(cap);
                    cout << "Diaria (00.00): "; cin >> valStr; d.setValor(stod(valStr));
                    cout << "Ramal (0-50): "; cin >> ram; r.setValor(ram);

                    q.setNumero(n); q.setCapacidade(c); q.setDiaria(d); q.setRamal(r);

                    if(servicoReserva->criarQuarto(q)) cout << "SUCESSO: Quarto criado.\n";
                    else cout << "FALHA: Numero ja existe.\n";

                } catch (const exception& e) { cout << "ERRO DADOS: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 2: { // LISTAR
                list<Quarto> lista = servicoReserva->listarQuartos();
                if(lista.empty()) cout << "Nenhum quarto cadastrado.\n";
                for(const auto& q : lista) {
                    cout << "NUM: " << q.getNumero().getValor()
                         << " | CAP: " << q.getCapacidade().getValor()
                         << " | R$: " << q.getDiaria().getValor() << endl;
                }
                esperarEnter();
                break;
            }
            case 3: { // LER
                int num; cout << "Numero: "; cin >> num;
                try {
                    Numero n; n.setValor(num);
                    Quarto q = servicoReserva->lerQuarto(n);
                    cout << "--- DETALHES QUARTO ---\n";
                    cout << "Capacidade: " << q.getCapacidade().getValor() << endl;
                    cout << "Ramal: " << q.getRamal().getValor() << endl;
                } catch (const exception& e) { cout << "Nao encontrado: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 4: { // DELETAR
                int num; cout << "Numero: "; cin >> num;
                try {
                    Numero n; n.setValor(num);
                    if(servicoReserva->deletarQuarto(n)) cout << "Quarto removido.\n";
                    else cout << "Quarto nao encontrado.\n";
                } catch (const exception& e) { cout << "ERRO: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 5: break;
        }
    }
}

// --------------------------------------------------------------------
// IMPLEMENTAÇÃO: MENU DE HÓSPEDES (Faltava implementar)
// --------------------------------------------------------------------
void CntrMAReserva::menuHospedes() {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU HOSPEDES ---\n";
        cout << "1 - Cadastrar Hospede\n";
        cout << "2 - Listar Hospedes\n";
        cout << "3 - Pesquisar Hospede\n";
        cout << "4 - Deletar Hospede\n";
        cout << "5 - Voltar\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: { // CRIAR
                try {
                    Hospede h;
                    string emailStr, nomeStr, endStr, cartaoStr;
                    EMAIL em; Nome n; Endereco e; Cartao c;

                    cout << "Email: "; cin >> emailStr; em.setValor(emailStr);
                    limparBuffer();
                    cout << "Nome (Maiusc): "; getline(cin, nomeStr); n.setValor(nomeStr);
                    cout << "Endereco: "; getline(cin, endStr); e.setValor(endStr);
                    cout << "Cartao (16 dig): "; cin >> cartaoStr; c.setValor(cartaoStr);

                    h.setEmail(em); h.setNome(n); h.setEndereco(e); h.setCartao(c);

                    if(servicoPessoa->criarHospede(h)) cout << "SUCESSO: Hospede cadastrado.\n";
                    else cout << "FALHA: Email ja existe.\n";

                } catch (const exception& e) { cout << "ERRO DADOS: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 2: { // LISTAR
                list<Hospede> lista = servicoPessoa->listarHospedes();
                if(lista.empty()) cout << "Nenhum hospede cadastrado.\n";
                for(const auto& h : lista) {
                    cout << "EMAIL: " << h.getEmail().getValor()
                         << " | NOME: " << h.getNome().getValor() << endl;
                }
                esperarEnter();
                break;
            }
            case 3: { // LER
                string emailStr; cout << "Email: "; cin >> emailStr;
                try {
                    EMAIL em; em.setValor(emailStr);
                    Hospede h = servicoPessoa->lerHospede(em);
                    cout << "--- DETALHES HOSPEDE ---\n";
                    cout << "Nome: " << h.getNome().getValor() << endl;
                    cout << "End.: " << h.getEndereco().getValor() << endl;
                } catch (const exception& e) { cout << "Nao encontrado: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 4: { // DELETAR
                string emailStr; cout << "Email: "; cin >> emailStr;
                try {
                    EMAIL em; em.setValor(emailStr);
                    if(servicoPessoa->deletarHospede(em)) cout << "Hospede removido.\n";
                    else cout << "Hospede nao encontrado.\n";
                } catch (const exception& e) { cout << "ERRO: " << e.what() << endl; }
                esperarEnter();
                break;
            }
            case 5: break;
        }
    }
}

// ====================================================================
// 4. IMPLEMENTAÇÃO: CONTROLADORA DE INTEGRAÇÃO (MAI)
// ====================================================================

void CntrMAIntegracao::executar() {
    int opcao = 0;
    while (true) {
        // MENU INICIAL (Requisito: Acessar, Criar, Sair)
        autenticado = false;
        cout << "\n#########################################\n";
        cout << "#         SISTEMA HOTELEIRO             #\n";
        cout << "#########################################\n";
        cout << "1 - Acessar Conta (Login)\n";
        cout << "2 - Criar Conta (Novo Gerente)\n";
        cout << "0 - Sair\n";
        cout << "Selecione: ";

        cin >> opcao;
        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        if (opcao == 0) {
            cout << "Encerrando o sistema...\n";
            break;
        }
        else if (opcao == 2) {
            // Chama o módulo de autenticação para CADASTRAR
            if(cntrAutenticacao->cadastrar()) {
                esperarEnter();
            } else {
                esperarEnter();
            }
        }
        else if (opcao == 1) {
            // Chama o módulo de autenticação para LOGAR
            if (cntrAutenticacao->autenticar(emailUsuarioLogado)) {
                autenticado = true;

                // LOOP DO USUÁRIO LOGADO
                while (autenticado) {
                    cout << "\n=== MENU PRINCIPAL (Logado: " << emailUsuarioLogado.getValor() << ") ===\n";
                    cout << "1 - Meu Perfil\n";
                    cout << "2 - Gestao de Hotel e Reservas\n";
                    cout << "0 - Logout\n";
                    cout << "Opcao: ";

                    int opLogado;
                    cin >> opLogado;
                    if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

                    switch(opLogado) {
                        case 1: cntrPessoal->executar(emailUsuarioLogado); break;
                        case 2: cntrReserva->executar(emailUsuarioLogado); break;
                        case 0: autenticado = false; cout << "Deslogado.\n"; break;
                        default: cout << "Opcao invalida.\n";
                    }
                }
            } else {
                esperarEnter();
            }
        }
        else {
            cout << "Opcao invalida.\n";
        }
    }
}
