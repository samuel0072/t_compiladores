#ifndef CATEGORY_H
#define CATEGORY_H
/*
Categoria dos tokens/lexemas
*/
enum  Category {
CtrlIf = 1, CtrlElse, LoopWhile, LoopFor,  Break,
Return, Input, Output, Integer, Float, Char, Void,String, Boolean, 
Parenth1, Parenth2, Braces1,Braces2, Bracket1, Bracket2, OpAdd, 
OpMinus, OpDiv, OpMult, OpRem, OpConcat, OpGreater, OpLesser, OpGEqual,
OpLEqual, OpEqual, OpDiff, OpBinXor,OpNot, OpAnd, OpOr, Assign, Comma, 
Terminator, Error, Id, CteInt, CteFloat, CteChar, CteString, CteBool, Eof };

/*
Estados possíveis para o analisador léxico
*/
enum  State_types {
   Init = 1, Inter, End, State_Error, Caracter, Comment_End, Ctrl_String
};

/*
Esse enum representa os tipos de produção
Rule é para regras de produção
Lexema é para regras que o handle é somente um lexema
Error é para representar os erros da tabela de analise
Empty é para representar produções vazias
*/
enum Prod_types {
   Rule = 1, Lexeme, Error, Empty
};

/*
Não terminais da linguagem ordenados conforme ordem de aparição
na tabela de análise
Indexados a partir do 0 
*/
enum N_Term {
   Decls = 0, Decl, DeclAux, DeclBux, ParamDef,
   ParamDAux, StmList, Stm, ElseStm, NormalStm,
   VarDecl, VarList, Init, InitAux, Array,
   ArrayAux, OpConc, OpCoAux, OpCoBux, OpOr,
   OpOrAux, OpAndXor, OpAXAux, OpEquate, OpEAux,
   OpCompare, OpCAux, OpAdd, OpAddAux, OpMult,
   OpMAux, OpUnary, Value, ValueAux, ParamList,
   ParamLAux, OpCList, Type, Empty,
   CtrlIf, CtrlElse, LoopWhile, LoopFor,  Break,
   Return, Input, Output, Integer, Float, Char, Void,String, Boolean, 
   Parenth1, Parenth2, Braces1,Braces2, Bracket1, Bracket2, OpAddT, 
   OpMinus, OpDiv, OpMultT, OpRem, OpConcat, OpGreater, OpLesser, OpGEqual,
   OpLEqual, OpEqual, OpDiff, OpBinXor,OpNot, OpAnd, OpOrT, Assign, Comma, 
   Terminator, Error, Id, CteInt, CteFloat, CteChar, CteString, CteBool, Eof
};

#endif