#include "apresentacao.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>

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

bool CntrMAAutenticacao::executar(EMAIL& email) {
    string emailStr, senhaStr;

    while (true) {
        cout << "\n=========================================\n";
        cout << "          LOGIN - SISTEMA HOTELEIRO      \n";
        cout << "=========================================\n";
        cout << "Digite seu EMAIL (ou 'sair' para encerrar): ";
        cin >> emailStr;

        if (emailStr == "sair") return false;

        cout << "Digite sua SENHA: ";
        cin >> senhaStr;

        try {
            // 1. Validação de formato (Domínios)
            EMAIL domEmail;
            domEmail.setValor(emailStr);

            Senha domSenha;
            domSenha.setValor(senhaStr);

            // 2. Delega para a Camada de Serviço
            if (servicoAutenticacao->autenticar(domEmail, domSenha)) {
                cout << "\n[!] SUCESSO: Autenticado com êxito!" << endl;
                email = domEmail; // Preenche o email do usuário logado para a Integradora
                return true;
            } else {
                cout << "\n[X] FALHA: Email ou Senha incorretos." << endl;
            }

        } catch (const invalid_argument& e) {
            cout << "\n[X] ERRO DE FORMATO: " << e.what() << endl;
        }

        // Limpa buffer residual se necessário antes de repetir
        limparBuffer();
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
        cout << "2 - Editar Perfil (Não implementado)\n";
        cout << "3 - Voltar ao Menu Principal\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: {
                try {
                    // Busca dados atualizados no serviço
                    Gerente gerente = servicoPessoa->lerGerente(email);
                    cout << "\n--- DADOS DO GERENTE ---\n";
                    cout << "Nome:  " << gerente.getNome().getValor() << endl;
                    cout << "Email: " << gerente.getEmail().getValor() << endl;
                    cout << "Ramal: " << gerente.getRamal().getValor() << endl;
                    cout << "Senha: *****" << endl;
                } catch (...) {
                    cout << "Erro ao recuperar dados do perfil." << endl;
                }
                esperarEnter();
                break;
            }
            case 2:
                cout << "Funcionalidade de edicao em desenvolvimento." << endl;
                esperarEnter();
                break;
            case 3:
                break;
            default:
                cout << "Opcao invalida." << endl;
        }
    }
}

void CntrMAPessoal::editarPerfil(const EMAIL& email) {
    // Implementação futura
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

// --- SUB-MENU: RESERVAS ---

void CntrMAReserva::menuReservas() {
    int opcao = 0;
    while (opcao != 5) {
        cout << "\n--- MENU RESERVAS ---\n";
        cout << "1 - Criar Nova Reserva\n";
        cout << "2 - Listar Reservas\n";
        cout << "3 - Pesquisar Reserva (por Codigo)\n";
        cout << "4 - Cancelar/Deletar Reserva\n";
        cout << "5 - Voltar\n";
        cout << "Selecione: ";
        cin >> opcao;

        if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

        switch(opcao) {
            case 1: {
                // Lógica de Criar Reserva
                Reserva novaReserva;
                // Coleta de dados manual para demonstração
                try {
                    string codigoStr, valStr, diaI, mesI, anoI, diaF, mesF, anoF;
                    Codigo cod; Data dtIni; Data dtFim; Dinheiro val;

                    cout << "Codigo (10 carac): "; cin >> codigoStr;
                    cod.setValor(codigoStr);

                    cout << "Data Chegada (DD MMM AAAA): "; cin >> diaI >> mesI >> anoI;
                    dtIni.setValor(stoi(diaI), mesI, stoi(anoI));

                    cout << "Data Partida (DD MMM AAAA): "; cin >> diaF >> mesF >> anoF;
                    dtFim.setValor(stoi(diaF), mesF, stoi(anoF));

                    cout << "Valor (00.00): "; cin >> valStr;
                    // Conversão simples de string para double
                    val.setValor(stod(valStr));

                    novaReserva.setCodigo(cod);
                    novaReserva.setChegada(dtIni);
                    novaReserva.setPartida(dtFim);
                    novaReserva.setValor(val);

                    if(servicoReserva->criarReserva(novaReserva))
                        cout << "Reserva criada com sucesso!\n";
                    else
                        cout << "Falha ao criar reserva (Conflito ou Erro).\n";

                } catch (const exception& e) {
                    cout << "Erro nos dados: " << e.what() << endl;
                }
                break;
            }
            case 2: {
                // Listar
                list<Reserva> lista = servicoReserva->listarReservas();
                if(lista.empty()) cout << "Nenhuma reserva encontrada.\n";
                for(const auto& r : lista) {
                    cout << "Reserva: " << r.getCodigo().getValor()
                         << " | Valor: " << r.getValor().getValor() << endl;
                }
                esperarEnter();
                break;
            }
            case 3: {
                // Pesquisar
                string codStr;
                cout << "Codigo da Reserva: "; cin >> codStr;
                try {
                    Codigo cod; cod.setValor(codStr);
                    Reserva r = servicoReserva->lerReserva(cod);
                    // Verifica se retornou algo válido (implementação do stub vai definir isso)
                    if(r.getCodigo().getValor() == codStr)
                        cout << "Encontrada! Chegada: " << r.getChegada().getDia() << "/" << r.getChegada().getMes() << endl;
                    else
                        cout << "Nao encontrada.\n";
                } catch (...) { cout << "Erro de formato.\n"; }
                esperarEnter();
                break;
            }
            case 4: {
                // Deletar
                string codStr;
                cout << "Codigo para deletar: "; cin >> codStr;
                try {
                    Codigo cod; cod.setValor(codStr);
                    if(servicoReserva->deletarReserva(cod)) cout << "Reserva deletada.\n";
                    else cout << "Reserva nao encontrada.\n";
                } catch(...) { cout << "Erro.\n"; }
                break;
            }
            case 5: break;
        }
    }
}

// --- STUBS DOS OUTROS SUB-MENUS (HOTEL, QUARTO, HOSPEDE) ---
// Implementação simplificada para cumprir o contrato

void CntrMAReserva::menuHoteis() {
    cout << "\n[Funcionalidade de Hoteis acessada via Controlador de Reservas]\n";
    cout << "1. Listar Hoteis\n2. Voltar\nSelecione: ";
    int op; cin >> op;
    if(op == 1) {
        list<Hotel> hoteis = servicoReserva->listarHoteis();
        if(hoteis.empty()) cout << "Nenhum hotel cadastrado.\n";
        else cout << "Hoteis listados com sucesso.\n";
    }
}

void CntrMAReserva::menuQuartos() {
    cout << "\n[Funcionalidade de Quartos acessada via Controlador de Reservas]\n";
    // Lógica similar usando servicoReserva->criarQuarto, etc.
    esperarEnter();
}

void CntrMAReserva::menuHospedes() {
    cout << "\n[Funcionalidade de Hospedes acessada via Controlador de Reservas]\n";
    // Aqui usamos servicoPessoa pois hóspede é Pessoa
    // Lógica similar usando servicoPessoa->criarHospede, etc.
    esperarEnter();
}

// ====================================================================
// 4. IMPLEMENTAÇÃO: CONTROLADORA DE INTEGRAÇÃO (MAI)
// ====================================================================

void CntrMAIntegracao::executar() {
    while (true) {
        // 1. Tenta autenticar
        if (cntrAutenticacao->executar(emailUsuarioLogado)) {
            autenticado = true;

            // 2. Loop do Menu Principal (Pós-Login)
            while (autenticado) {
                cout << "\n=========================================\n";
                cout << "        MENU PRINCIPAL (Logado)          \n";
                cout << "=========================================\n";
                cout << "1 - Meu Perfil (Dados Pessoais)\n";
                cout << "2 - Gestao de Hotel e Reservas\n";
                cout << "3 - Logout (Sair da conta)\n";
                cout << "Selecione: ";

                int opcao;
                cin >> opcao;
                if (cin.fail()) { cin.clear(); limparBuffer(); continue; }

                switch (opcao) {
                    case 1:
                        if (cntrPessoal) cntrPessoal->executar(emailUsuarioLogado);
                        else cout << "Erro: Modulo Pessoal nao inicializado.\n";
                        break;
                    case 2:
                        if (cntrReserva) cntrReserva->executar(emailUsuarioLogado);
                        else cout << "Erro: Modulo Reserva nao inicializado.\n";
                        break;
                    case 3:
                        autenticado = false;
                        cout << "Deslogando...\n";
                        break;
                    default:
                        cout << "Opcao invalida.\n";
                }
            }
        } else {
            // Se autenticação falhar ou usuário pedir para sair no menu de login
            cout << "Encerrando sistema. Ate logo!\n";
            break;
        }
    }
}
