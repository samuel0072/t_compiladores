# Compiladores

Repositório dedicado à  Implementação de um analisador léxico e sintático para um subconjunto modificado da linguagem C

## AB1

- Os requisitos da AB1 foram feitos em AB1/

- Documentos estão na pasta AB1/docs
  - Compiladores AB1.odt: Documento de especificação da linguagem
  - Compiladores AB1.pdf: Documento de especificação da linguagem
  - Compiladores_automato.pdf: Automato usado no analisador léxico
 
- Implementações em AB1/src
  - exemplos/: Pasta com os exemplos requisitados e seus resultados da analise léxica
  - category.h: Arquivo que define algumas enumerações uteis
  - lexicalanalyzer.cpp: Implementação de funções da classe LexicalAnalyzer
  - lexicalanalyzer.h: Definição da classe LexicalAnalyzer
  - main.cpp: Arquivo com um programa utlizando a classe LexicalAnalyzer

## AB2

- Os requisitos da AB1 foram feitos em AB2/
- O tipo de analisador escolhido foi **Descendente Preditivo Tabular**

- Documentos estão na pasta AB2/docs
  - Tabela de Analise Gramatica LL(1) - 1 página.pdf: Tabela de análise da gramática LL(1) em uma página
  - Tabela de Analise Gramatica LL(1) -4 páginas.pdf: Tabela de análise da gramática LL(1) em 4 páginas
  - gramatica: Arquivo de texto com a definição da gramática usada
  - gramatica LL(1): Arquivo de texto com a definição LL(1) da gramática usada
 
- Implementações em AB2/src
  - lexicalanalyzer.cpp: Implementação de funções da classe LexicalAnalyzer
  - lexicalanalyzer.h: Definição da classe LexicalAnalyzer
  - syntaticanalyzer.cpp: Implementação de funções da classe SyntaticAnalyzer
  - syntaticanalyzer.h: Definição da classe SyntaticAnalyzer
