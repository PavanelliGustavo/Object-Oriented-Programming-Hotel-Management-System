#include <iostream>
#include <stdexcept>
#include <locale.h>

#include "domains.hpp"
#include "entities.hpp"
#include "interfaces.hpp"
#include "containers.hpp"
#include "services.hpp"
#include "presentation.hpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");
    cout << "Iniciando Sistema..." << endl;

    try {
        // 1. Containers
        ContainerGerente   cGerente;
        ContainerHospede   cHospede;
        ContainerHotel     cHotel;
        ContainerQuarto    cQuarto;
        ContainerReserva   cReserva;

        // 2. Serviços
        CntrMSAutenticacao msAutenticacao;
        CntrMSPessoa       msPessoa;
        CntrMSReserva      msReserva;

        msAutenticacao.setContainer(&cGerente);
        msPessoa.setContainerGerente(&cGerente);
        msPessoa.setContainerHospede(&cHospede);
        msReserva.setContainerReserva(&cReserva);
        msReserva.setContainerHotel(&cHotel);
        msReserva.setContainerQuarto(&cQuarto);

        // 3. Apresentação
        CntrMAAutenticacao maAutenticacao;
        CntrMAPessoal      maPessoal;
        CntrMAReserva      maReserva;

        // --- CORREÇÃO AQUI: Injetando dependências extras ---
        maAutenticacao.setISAutenticacao(&msAutenticacao);
        maAutenticacao.setISPessoa(&msPessoa); // Necessário para Cadastrar Gerente

        maPessoal.setISPessoa(&msPessoa);

        maReserva.setISReserva(&msReserva);
        maReserva.setISPessoa(&msPessoa);

        // 4. Integração
        CntrMAIntegracao mai;
        mai.setCntrAutenticacao(&maAutenticacao);
        mai.setCntrPessoal(&maPessoal);
        mai.setCntrReserva(&maReserva);

        // 5. Carga Inicial (Admin)
        // Criando admin inicial para não ficar bloqueado se não quiser criar conta
        try {
            Gerente admin;
            Nome nome; nome.setValor("Administrador");
            EMAIL email; email.setValor("admin@hotel.com");
            Senha senha; senha.setValor("A1b!2"); // Senha válida
            Ramal ramal; ramal.setValor(1);

            admin.setNome(nome);
            admin.setEmail(email);
            admin.setSenha(senha);
            admin.setRamal(ramal);

            cGerente.incluir(admin);
        } catch (...) {}

        // 6. Executar
        mai.executar();

    } catch (const exception& e) {
        cout << "ERRO FATAL: " << e.what() << endl;
        return 1;
    }
    return 0;
}
