#include <iostream>
#include <stdexcept>
#include <locale.h>

// Inclui todas as camadas
#include "dominios.hpp"
#include "entidades.hpp"
#include "interfaces.hpp"
#include "containers.hpp"
#include "servicos.hpp"
#include "apresentacao.hpp"

using namespace std;

int main() {
    // Configura acentuação para o console (pode variar dependendo do SO)
    setlocale(LC_ALL, "Portuguese");

    cout << "Iniciando Sistema de Gestao Hoteleira..." << endl;

    try {
        // ====================================================================
        // 1. INSTANCIAÇÃO DOS CONTAINERS (BANCO DE DADOS EM MEMÓRIA)
        // ====================================================================
        ContainerGerente   cGerente;
        ContainerHospede   cHospede;
        ContainerHotel     cHotel;
        ContainerQuarto    cQuarto;
        ContainerReserva   cReserva;

        // ====================================================================
        // 2. INSTANCIAÇÃO DA CAMADA DE SERVIÇO (MS)
        // ====================================================================
        CntrMSAutenticacao msAutenticacao;
        CntrMSPessoa       msPessoa;
        CntrMSReserva      msReserva;

        // INJEÇÃO DE DEPENDÊNCIA: SERVIÇO -> CONTAINER
        msAutenticacao.setContainer(&cGerente);

        msPessoa.setContainerGerente(&cGerente);
        msPessoa.setContainerHospede(&cHospede);

        msReserva.setContainerReserva(&cReserva);
        msReserva.setContainerHotel(&cHotel);
        msReserva.setContainerQuarto(&cQuarto);

        // ====================================================================
        // 3. INSTANCIAÇÃO DA CAMADA DE APRESENTAÇÃO (MA)
        // ====================================================================
        CntrMAAutenticacao maAutenticacao;
        CntrMAPessoal      maPessoal;
        CntrMAReserva      maReserva;

        // INJEÇÃO DE DEPENDÊNCIA: APRESENTAÇÃO -> SERVIÇO
        maAutenticacao.setISAutenticacao(&msAutenticacao);

        maPessoal.setISPessoa(&msPessoa);

        maReserva.setISReserva(&msReserva);
        maReserva.setISPessoa(&msPessoa); // MAR precisa listar hóspedes

        // ====================================================================
        // 4. INSTANCIAÇÃO E CONFIGURAÇÃO DA INTEGRAÇÃO (MAI)
        // ====================================================================
        CntrMAIntegracao mai;

        // INJEÇÃO DE DEPENDÊNCIA: INTEGRAÇÃO -> MÓDULOS DE APRESENTAÇÃO
        mai.setCntrAutenticacao(&maAutenticacao);
        mai.setCntrPessoal(&maPessoal);
        mai.setCntrReserva(&maReserva);

        // ====================================================================
        // 5. CARGA INICIAL DE DADOS (PARA TESTE FUMAÇA)
        // ====================================================================
        // Criar um Gerente padrão para permitir o primeiro login.
        try {
            Gerente admin;

            Nome nome; nome.setValor("Administrador");
            EMAIL email; email.setValor("admin@hotel.com");
            Senha senha; senha.setValor("A1b!2"); // 5 chars: Maiusc, Minusc, Digito, Especial
            Ramal ramal; ramal.setValor(1);

            admin.setNome(nome);
            admin.setEmail(email);
            admin.setSenha(senha);
            admin.setRamal(ramal);

            // Usa o serviço para incluir (valida regras de negócio)
            // Como estamos acessando direto o container para setup, podemos usar o método incluir direto
            // ou usar o serviço msPessoa. Vamos usar o container direto para setup rápido.
            cGerente.incluir(admin);

            cout << "\n[SETUP] Usuario Admin criado com sucesso!" << endl;
            cout << "EMAIL: admin@hotel.com" << endl;
            cout << "SENHA: A1b!2" << endl;
            cout << "-------------------------------------------------------" << endl;

        } catch (const exception& e) {
            cout << "[ERRO SETUP] Falha ao criar usuario admin: " << e.what() << endl;
            return 1;
        }

        // ====================================================================
        // 6. EXECUÇÃO DO SISTEMA
        // ====================================================================
        mai.executar();

    } catch (const exception& e) {
        cout << "ERRO FATAL NO SISTEMA: " << e.what() << endl;
        return 1;
    }

    cout << "\nSistema encerrado. Obrigado!" << endl;
    return 0;
}
