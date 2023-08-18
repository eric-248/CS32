
#include <iostream>
#include <stack>
#include <string>
#include <cassert>

using namespace std;

string infix_to_postfix(string infix);
int precedence(char ch);
int check_parenthesis(string infix);

int evaluate(string infix, string& postfix, bool& result)
{
	//gaurd against invalid strings
	if (check_parenthesis(infix) == 1) {
		return 1;
	}

	postfix = infix_to_postfix(infix);

	if (infix.empty() || postfix == "invalid") {
		return 1;
	}

	stack <bool> o_stack;

	for (int i = 0; i < postfix.size(); i++) {

		char ch = postfix[i];

		if (ch == 'T' || ch == 'F') {
			if (ch == 'T') {
				o_stack.push(true);
			}
			else {
				o_stack.push(false);
			}
		}
		else {

			if (o_stack.size() < 2) {
				return 1;
			}

			char operand2 = o_stack.top();
			o_stack.pop();
			char operand1 = o_stack.top();
			o_stack.pop();

			//apply the operation that ch represents to operand1 and
			//operand2, and push the result onto the stack


			if (ch == '^') {
				o_stack.push(operand1 || operand2);
			}
			else if (ch == '&') {
				o_stack.push(operand1 && operand2);
			}
			else {
				o_stack.push(operand1);
				o_stack.push(!operand2);
			}
		}
	}

	/*When the loop is finished, the operand stack will contain one item,
	the result of evaluating the expression*/

	if (o_stack.size() != 1) {
		return 1;
	}
	
	result = o_stack.top();

	return 0;

}

string infix_to_postfix(string infix) {

	//edge case guards
	if (infix[0] == '&' || infix[0] == '^') {
		return "invalid";
	}


	string postfix = "";

	//operator stack
	stack <char> o_stack;

	for (int i = 0; i < infix.size(); i++) {

		char ch = infix[i];

		//make sure no random characters
		if (ch != 'F' && ch != 'T' && ch != '&' && ch != '!' && ch != '^' && ch != ' ' && ch != '(' && ch != ')') {
			return "invalid";
		}

		switch (ch) {

			//operands
		case 'T':
		case 'F':
			if (i > 0 && (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')')) {
				return "invalid";
			}
			//append ch to end of postfix
			postfix += ch;
			break;

		case '(':
			if (i > 0 && (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')')) {
				return "invalid";
			}
			o_stack.push(ch);
			break;


		case ')':
			if (i > 0 && (infix[i - 1] == '(' || infix[i - 1] == '!' || infix[i - 1] == '^' || infix[i - 1] == '&')) {
				return "invalid";
			}
			// pop stack until matching '('
			while (o_stack.top() != '(') {
				postfix += o_stack.top();
				o_stack.pop();
			}
			o_stack.pop(); //remove the '('
			break;

			//operators
		case '&':
		case '^':
		case '!':
			if (i > 0 && (infix[i - 1] == '(' || infix[i - 1] == '^' || infix[i - 1] == '!' || infix[i - 1] == '&')){
				return "invalid";
			}
			
			while (!o_stack.empty() && o_stack.top() != '(' && precedence(ch) < precedence(o_stack.top())) {
				postfix += o_stack.top();
				o_stack.pop();

			}
			o_stack.push(ch);
			break;

		}

	}

	while (!o_stack.empty()) {
		postfix += o_stack.top();
		o_stack.pop();
	}

	return postfix;
}

int precedence(char ch) {
	switch (ch) {
	case '^':
		return 1;
	case '&':
		return 2;
	case '!':
		return 3;
	default:
		return 4;
	}
}

int check_parenthesis(string infix) {
	stack<char> s;
	string postfix = "";

	if (infix.size() == 0) {
		return 1;
	}

	for (int i = 0; i < infix.size(); i++){

		if (infix[i] == ' '){

			infix = infix.substr(0, i) + infix.substr(i + 1, infix.size());
			i--;
		}
		else{

			if (infix[i] == '('){

				s.push('(');
			}
			if (infix[i] == ')'){

				if (s.empty()){

					return 1;
				}
				else{
					s.pop();
				}

			}

			if (infix[i] != 'T' && infix[i] != 'F' && infix[i] != '(' && infix[i] != ')' && infix[i] != '!' && infix[i] != '&' && infix[i] != '^'){
				return 1;
			}
		}


	}
	if (!s.empty()){
		return 1;
	}

	return 0;
}

int main() {

	string pf;
	bool answer;

	
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);

	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer); 

	assert(evaluate("bruh", pf, answer) == 1);
	assert(evaluate("1^F", pf, answer) == 1);
	assert(evaluate("!()", pf, answer) == 1);
	assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("T&T", pf, answer) == 0 && pf == "TT&" && answer);
	assert(evaluate("T^(F)", pf, answer) == 0 && answer);
	assert(evaluate("(T))", pf, answer) == 1);

	//assert(evaluate("T^ F& F", pf, answer) == 0 && !answer);
	//assert(evaluate("!T&F", pf, answer) == 0 && !answer);
	//assert(evaluate("!(T&F)", pf, answer) == 0 && answer);
	//assert(evaluate("T ^ !F", pf, answer) == 0 && !answer);
	//assert(evaluate("(T))", pf, answer) == 1);


	cout << "Passed all tests" << endl;

}

