#include <iostream>
#include <stdexcept>
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "servicos.hpp"
#include "containers.hpp"
#include "apresentacao.hpp" 
#include "testes.hpp"     
#include <exception> // Para a classe base exception

using namespace std;

// Funcao auxiliar para rodar e reportar o resultado dos testes
void rodarTestes() {
    cout << "=========================================\n";
    cout << "         EXECUTANDO TESTES DE UNIDADE\n";
    cout << "=========================================\n";
    
    TUNumero tuNumero;
    TUSenha tuSenha;
    TUGerente tuGerente;
    // Adicionar outros testes aqui (TUEndereco, TUPessoa, etc.)
    
    // --- Testes de Domínio ---
    cout << "Teste TUNumero (Dominio): " << (tuNumero.run() == SUCESSO ? "SUCESSO" : "FALHA") << endl;
    cout << "Teste TUSenha (Dominio): " << (tuSenha.run() == SUCESSO ? "SUCESSO" : "FALHA") << endl;
    
    // --- Testes de Entidade ---
    cout << "Teste TUGerente (Entidade): " << (tuGerente.run() == SUCESSO ? "SUCESSO" : "FALHA") << endl;
    
    cout << "=========================================\n\n";
}

int main() {
    // 1. RODAR TESTES DE UNIDADE
    rodarTestes();

    // 2. DECLARAÇÃO DE VARIÁVEIS DO SISTEMA
    
    // --- Contêineres (Camada de Dados) ---
    ContainerGerente containerGerentes;
    ContainerReserva containerReservas;
    ContainerHospede containerHospedes;
    ContainerHotel containerHoteis;
    ContainerQuarto containerQuartos;
    
    // --- Controladoras de Serviço (Camada de Serviço - LN) ---
    CntrLNAutenticacao ctrlLNAutenticacao;
    CntrLNPessoa ctrlLNPessoa;
    CntrLNReserva ctrlLNReserva;
    CntrLNHotel ctrlLNHotel;
    
    // --- Controladoras de Apresentação (Camada de Apresentação - IU) ---
    CntrIUAutenticacao ctrlIUAutenticacao;
    CntrIUIntegracao ctrlIUIntegracao; // Menu Principal
    CntrIUReserva ctrlIUReserva; // Seu subsistema (MAR)
    // CntrIUPessoa ctrlIUPessoa; // Outras controladoras IU seriam declaradas aqui.
    // CntrIUHotel ctrlIUHotel;

    // 3. INJEÇÃO DE DEPENDÊNCIA (LIGANDO AS CAMADAS)
    
    // A. Ligar Controladoras de Serviço aos seus Contêineres (Dados)
    ctrlLNAutenticacao.setContainer(&containerGerentes);
    
    ctrlLNPessoa.setContainerGerente(&containerGerentes);
    ctrlLNPessoa.setContainerHospede(&containerHospedes);
    
    ctrlLNReserva.setContainer(&containerReservas);
    // Para checagem de conflito: ctrlLNReserva.setContainerQuarto(&containerQuartos);
    
    ctrlLNHotel.setContainerHotel(&containerHoteis);
    ctrlLNHotel.setContainerQuarto(&containerQuartos);


    // B. Ligar Camada de Apresentação à Camada de Serviço (Interfaces)
    
    // Login -> Serviço de Autenticação
    ctrlIUAutenticacao.setInterfaceServico(&ctrlLNAutenticacao);
    
    // Reservas -> Serviço de Reservas
    ctrlIUReserva.setInterfaceServico(&ctrlLNReserva);


    // C. Ligar Módulos de Apresentação entre si (Navegação)
    
    // Login -> Menu Principal (MAI)
    ctrlIUAutenticacao.setControladorIntegracao(&ctrlIUIntegracao);

    // Menu Principal (MAI) -> Menu de Reservas (MAR)
    ctrlIUIntegracao.setCtrlReserva(&ctrlIUReserva); 
    // Outras ligações: ctrlIUIntegracao.setCtrlPessoa(&ctrlIUPessoa);


    // 4. PREPARAÇÃO DE DADOS INICIAIS (Smoke Test)
    // Inserir um Gerente válido para testar a autenticação (EMAIL e SENHA válidos)
    try {
        EMAIL emailInicial;
        emailInicial.setValor("admin@hotel.com");
        
        Senha senhaInicial;
        senhaInicial.setValor("A1!b#"); 
        
        Nome nomeInicial;
        nomeInicial.setValor("Admin Hotel"); 
        
        Ramal ramalInicial;
        ramalInicial.setValor(10); // Ramal válido
        
        Gerente gerenteInicial;
        gerenteInicial.setEmail(emailInicial);
        gerenteInicial.setSenha(senhaInicial);
        gerenteInicial.setNome(nomeInicial);
        gerenteInicial.setRamal(ramalInicial);

        containerGerentes.incluir(gerenteInicial);
        cout << "SUCESSO: Gerente inicial 'admin@hotel.com' inserido para teste.\n";

    } catch (const exception& e) {
        cerr << "ERRO FATAL: Falha ao inserir dados iniciais: " << e.what() << endl;
        return 1;
    }
    
    // 5. EXECUÇÃO DO SISTEMA (Chamada ao Módulo de Entrada - Login)
    
    if (ctrlIUAutenticacao.executar()) {
        // Se a autenticação foi bem-sucedida, executa o Menu Principal
        ctrlIUIntegracao.executar(); 
    }
    
    return 0;
}
