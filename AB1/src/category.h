
enum  Category {
CtrlIf = 1, CtrlElse, LoopWhile, LoopFor,  Break,
Return, Input, Output, Integer, Float, Char, Void,String, Boolean, 
Parenth1, Parenth2, Braces1,Braces2, Bracket1, Bracket2, OpAdd, 
OpMinus, OpDiv, OpMult, OpRem, OpConcat, OpGreater, OpLesser, OpGEqual,
OpLEqual, OpEqual, OpDiff, OpBinXor,OpNot, OpAnd, OpOr, Assign, Comma, 
Terminator, Error, Id, CteInt, CteFloat, CteChar, CteString, CteBool, Eof };

enum  State_types {
   Init = 1, Inter, End, State_Error, Caracter, Comment_End, Ctrl_String
};
