#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include <string>
using namespace std;


enum class tokenType{
        NUMBER,
        OPERATION,
        BRACKET
};

struct Token{
    string tokenBody;
    tokenType Type;
    Token(tokenType type, std::string body)
      : Type (type), tokenBody(body)  {
    }
};


vector<Token> reverseRecord;
stack<Token> buffer;

int priority(Token token) {
  switch (token.Type) {
    case tokenType::BRACKET:
	  return 1;
	break;
	case tokenType::OPERATION:
	  switch (token.tokenBody[0]) {
	    case '+':
		  return 2;
		  break;
	    case '-':
		  return 2;
		  break;
	    case '*':
		  return 3;
		  break;
	    case '/':
		  return 3;
		  break;
		default:
		break;  
	  }
	break;
	default:
	  return 0;
	break;
  }
  return 0;
}

int prioritySet(const char current) {
	switch (current) {
	case '(':
		return 1;
		break;
	case ')':
		return 1;
		break;
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	case '*':
		return 3;
		break;
	case '/':
		return 3;
		break;
	}
	return 0;
}

bool isNumber(char current) {
	return current >= '0' && current <= '9';
}
bool isOpSymbol(char current) {
	return current == '*'
	|| current == '+'
	|| current == '-' 
	|| current == '/';
}
bool isOpenBracket(char current) {
	return current == '(';
}
bool isCloseBracket(char current) {
	return current == ')';
}
void printVector(vector<Token> toPrint){
	cout << "Reverse record form: ";
	for(auto i : toPrint){
		cout << i.tokenBody;
	}
	cout << endl;
}

Token readNumber (istream& input) {
    string token;
	while(isNumber(input.peek()) && !input.eof()){
        token += input.get();
	}
	return Token(tokenType::NUMBER, token);
}

Token readOperation (istream& input) {
	string token;
	token = input.get();
	return Token(tokenType::OPERATION, token);
}

Token readBracket(istream& input){
	string token;
	token = input.get();
	return Token(tokenType::BRACKET, token);
}

void reverseToPolRecord(){
	for (char current = cin.peek(); !cin.eof(); current = cin.peek()){
		if (isNumber(current)) {
			reverseRecord.push_back(readNumber(cin));
		} 
		else if (isOpSymbol(current)) {
			while (!buffer.empty() && priority(buffer.top()) >= prioritySet(current)) {
				reverseRecord.push_back(buffer.top());
				buffer.pop();
			}
			buffer.push(readOperation(cin));
		} 
		else if (isOpenBracket(current)) {
			buffer.push(readBracket(cin));
		} 
		else if (isCloseBracket(current)) {
			readBracket(cin);
			while (priority(buffer.top()) != 1) {
				reverseRecord.push_back(buffer.top());
				buffer.pop();
			}
			buffer.pop();
		} else {
			break;
		}
	}
	while (!buffer.empty()) {
		reverseRecord.push_back(buffer.top());
		buffer.pop();
	}
}

int symConvert(char symbol){
	switch (symbol) {
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}
	return 0;
}
int pop(stack<int>& buf){
	int num = buf.top();
	buf.pop();
	return num;
}
void divide(stack<int>& toDiv){	
	int first = pop(toDiv);
	int second = pop(toDiv);
	if(first == 0){
		throw exception();
	}
	toDiv.push(second / first);
	return;
}
void multiply(stack<int>& toMul){
	toMul.push(pop(toMul) * pop(toMul));
}
void add(stack<int>& toAdd){
	toAdd.push(pop(toAdd) + pop(toAdd));
	return;
}
void sub(stack<int>& toSub){
	int first = pop(toSub);
	int second = pop(toSub);
	toSub.push(second - first);
	return;
}
int countExpression(){
	stack<int> buffer;
	for(auto current : reverseRecord){
		if(current.Type == tokenType::NUMBER){
			buffer.push(std::stoi(current.tokenBody));
		} else if(current.tokenBody[0] == '*'){
			multiply(buffer);
		} else if(current.tokenBody[0] == '+'){
			add(buffer);
		}else if(current.tokenBody[0] == '-'){
			sub(buffer);
		}else if(current.tokenBody[0] == '/'){
			try{
			divide(buffer);
			} catch(exception){
				cout << "Divide by zero" << endl;
				return 0;
			}
		}
	}
	return buffer.top();
}

int main() {
	
	reverseToPolRecord();

	printVector(reverseRecord);

	int result = countExpression();

	cout << "Result of entered expression: " << result << endl;

	return 0;
}
