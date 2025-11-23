#include <iostream>
#include <stdexcept>
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "servicos.hpp"
#include "containers.hpp"
#include "apresentacao.hpp" // Contém CntrIUAutenticacao, CntrIUIntegracao, CntrIUReserva
#include "testes.hpp"     // Contém TUNumero, TUPessoa, TUSenha, TUGerente

using namespace std;

// Funcao auxiliar para rodar e reportar o resultado dos testes
void rodarTestes() {
    cout << "=========================================\n";
    cout << "         EXECUTANDO TESTES DE UNIDADE\n";
    cout << "=========================================\n";
    
    TUNumero tuNumero;
    TUSenha tuSenha;
    TUGerente tuGerente;
    
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
    // ... Declarar outros containers
    
    // --- Controladoras de Serviço (Camada de Serviço - LN) ---
    CntrLNAutenticacao ctrlLNAutenticacao;
    CntrIUReserva ctrlIUReserva; // Seu módulo de Apresentação
    CntrIUIntegracao ctrlIUIntegracao; // Menu Principal
    
    // --- Interfaces de Apresentação (IU) ---
    CntrIUAutenticacao ctrlIUAutenticacao;
    
    // 3. INJEÇÃO DE DEPENDÊNCIA (LIGANDO AS CAMADAS)
    
    // A. Ligar Controladoras de Serviço aos seus Contêineres (Dados)
    ctrlLNAutenticacao.setContainer(&containerGerentes);
    // ... Ligar CntrLNReserva ao containerReservas, etc.

    // B. Ligar Camada de Apresentação à Camada de Serviço (Interfaces)
    
    // Ligar Login ao Serviço de Autenticação
    ctrlIUAutenticacao.setInterfaceServico(&ctrlLNAutenticacao);

    // Ligar Módulos de Apresentação entre si e ao Serviço
    // O Módulo de Login precisa saber para onde ir após o sucesso (Ctrl de Integração)
    ctrlIUAutenticacao.setControladorIntegracao(&ctrlIUIntegracao);

    // O Menu Principal (Ctrl Integração) precisaria de referências para os outros menus...
    // ctrlIUIntegracao.setCtrlReserva(&ctrlIUReserva); 
    
    // 4. PREPARAÇÃO DE DADOS INICIAIS (Smoke Test)
    // Inserir um Gerente válido para testar a autenticação
    try {
        EMAIL emailInicial;
        emailInicial.setValor("admin@hotel.com");
        
        Senha senhaInicial;
        senhaInicial.setValor("A1!b#"); // Senha válida para o teste
        
        Gerente gerenteInicial;
        gerenteInicial.setEmail(emailInicial);
        gerenteInicial.setSenha(senhaInicial);
        // ... setar Nome, Ramal, etc.

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
