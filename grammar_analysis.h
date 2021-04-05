#ifndef GRAMMAR
#define GRAMMAR

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

enum mark
{
	/*终结符*/
	EOF_, //文本结束
	null_,//空
	program_,
	const_,
	var_,
	array_,
	of_,
	integer_,
	real_,
	boolean_,
	char_,
	procedure_,
	function_,
	begin_,
	end_,
	if_,
	then_,
	for_,
	to_,
	do_,
	read_,
	write_,
	else_,
	not_,
	uminus_,
	id,
	fnum,    //整数
	digits,  //浮点数
	//letter,
	assignop,
	punc_question, //?
	punc_not,      //~
	punc_comma,    //,
	punc_semicolon,//;
	punc_colon,    //:
	punc_point,    //.
	punc_round_left,  //(
	punc_round_right, //)
	punc_square_left, //[
	punc_square_right,//]
	mulop_and,
	mulop_div,   //整除
	mulop_mod,
	mulop_mul,
	mulop_divide,//浮点除法
	addop_or,
	addop_add,
	addop_sub,
	relop_e,     //=
	relop_ne,    //<>
	relop_l,     //<
	relop_le,    //<=
	relop_g,     //>
	relop_ge,    //>=
	single_quote,//'
	letter,      //字符常量  如‘a’‘1’
	Boundary,    //---终结符与非终结符的分界线---
	/*非终结符*/
	S,
	programstruct,
	program_head,
	program_body,
	idlist,
	mulop,
	relop,
	addop,
	num,
	const_declarations,
	const_declaration,
	const_value,
	var_declarations,
	var_declaration,
	type,
	basic_type,
	period,
	subprogram_declarations,
	subprogram,
	subprogram_head,
	formal_parameter,
	parameter_list,
	parameter,
	var_parameter,
	value_parameter,
	subprogram_body,
	compound_statement,
	statement_list,
	statement,
	variable_list,
	variable,
	id_varpart,
	procedure_call,
	else_part,
	expression_list,
	expression,
	simple_expression,
	term,
	factor,

	//NOW //DFA中的点 .
};

typedef vector<mark> sentence;    //每一条语法规则
typedef vector<sentence> Grammar; //所有语法
typedef map<mark, set<mark>> fset;//存first集，follow集
typedef vector<vector<int>> LR_PredictTable;    //LR预测分析表      
typedef struct {
	vector<sentence> sentences;   //存放语句
	vector<int> point_pos;        //点的位置,点的下一个符号是point_pos处的符号
}closure;
typedef struct{
	int from;  
	mark by;   
	int to;
}Go;                              //go(from,by)=to
typedef struct {
	int mark; //对应记号的C++枚举值
	int line; //行号
	string content; //记号内容
}token;

Grammar initGrammer();                           //读入语法规则
fset getFIRST(Grammar grammar);                  //计算FIRST集
fset getFOLLOW(Grammar grammar, fset first);     //计算FOLLOW集
LR_PredictTable getTable(Grammar grammar);       //计算LR分析表
vector<int> control_program(LR_PredictTable LRtable, Grammar grammar); //进行分析动作

void extend_closure(Grammar grammer, closure &c);//完成闭包的扩展
bool in_closure(closure c, sentence s, int pos); //判断一个闭包里是否包含该语句

#endif