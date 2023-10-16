### L.EIC Schedules

Projeto de AED |
Entrega até 3/11  
Duarte Assunção, Guilherme Matos, João Ferreira

---

#### ToDo

1. *Parse data:* Ler e guardar a informação em memória (vice-versa)
2. Funcionalidades de gestão de horários
3. Listagens de dados (totais e parciais)
   > [!IMPORTANT]
   > Ainda por decidir. Alguns exemplos dados na descrição do projeto:  
   > "i.Consult the schedule of a given student or class;  
   > ii.Consult the students within a given class, course or year;  
   > iii.Consult the number of students registered in at least n UCs;  
   > iv.Consult the class/year/UC occupation (sorting by UC, ascending or descending order, …);  
   > v.Consult the UCs with the greatest number of students;"  
   
4. Pedidos de mudanças
   - Mudanças de cadeiras
   - Mudanças de turmas
5. Registo cronológico de todas as mudanças e permitir restauro de mudanças recentes
6. Documentação Doxygen

---
#### Estrutura em memória
> [!NOTE]
> Este ainda é um design inicial e está suscetível a alterações, nomeadamente a favor de eficiência em certa funções.

A informação será guardada em memória numa estrutura muito semelhante aos ficheiros .csv.  
Isto facilita imenso o parsing, porém ao custo da eficiência de algumas funções.

Por cada ficheiro ``x.csv``, haverá uma classe ``appX`` que terá todos os seus métodos e um vetor de classes ``x`` que cada um representa uma linha do ficheiro.

---

#### Apresentação em 7 de Novembro

(TBD)
