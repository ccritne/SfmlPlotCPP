#include "../include/Evaluate.hpp"

std::vector<std::string> functions{ "sin", "cos", "tan", "cotan", "arcsin", "arccos", "arctan", "arccotan", "sqrt", "log_2", "ln", "log_3", "log_4", "log_5", "log_6", "log_7", "log_8", "log_9", "log", "abs" };

bool isFunction(std::string op){

    if (std::find(functions.begin(), functions.end(), op) != functions.end())
        return true;

    return false;
}

int precedenceOperators(char c)
{
    int precedence = -1;
    switch (c) {
        case '^': precedence = 3;
        case '*': precedence = 2;
        case '/': precedence = 2;
        case '+': precedence = 1;
        case '-': precedence = 1;
    }

    return precedence;
}

int precedenceOperatorsAndFunctions(std::string c)
{
    return (isFunction(c)) ? 4 : precedenceOperators(c[0]);
}

bool isOperation(char op) {
    return (precedenceOperators(op) > 0) ? true : false;
}

bool isOperation(std::string op) {
    if (op.size() > 1)
        return false;
    else
        return (precedenceOperators(op[0]) > 0) ? true : false;
    
    return true;
}

bool isBracket(char str) {
    return (str == '(' or str == ')');
}

bool isBracket(std::string str) {
    return (str == "(" or str == ")");
}

std::vector<std::string> infixToPostfix(std::vector<std::string> s) { 

	std::stack<std::string> st;  
	int l = s.size(); 
	std::vector<std::string> ns; 
	for(int i = 0; i < l; i++) 
	{
		if(!isOperation(s[i]) and !isFunction(s[i]) and !isBracket(s[i]))
		    ns.push_back(s[i]); 
		else 
            if(s[i] == "(") 
               st.push("("); 
		    else 
                if(s[i] == ")"){

			        while(!st.empty() and st.top() != "(") 
			        {  
			            ns.push_back(st.top()); 
				        st.pop(); 
			        } 
			        if(st.top() == "(") 
				        st.pop(); 
		        } 
		        else{ 
			        while(!st.empty() and precedenceOperatorsAndFunctions(s[i]) <= precedenceOperatorsAndFunctions(st.top()))
			        { 
			            ns.push_back(st.top()); 
				        st.pop(); 
			        } 

			        st.push(s[i]); 
		        } 

	}

	while(!st.empty()) 
	{ 
        ns.push_back(st.top()); 
    	st.pop(); 
	} 
	
	return ns;

} 

bool is_number(std::string number_string)
{
    std::string::size_type sz;
    bool is_valid;
    double parsed_number = 0.0;
    try 
    { 
        parsed_number = std::stod(number_string, &sz); 
        is_valid = true; 
    } 
    catch(std::exception& ia) 
	{ 
        is_valid = false; 
    } 

    return is_valid;
}

//TODO Refactor
std::vector<std::string> tokenization(std::string token){
    std::string tmp = "";

    std::vector<std::string> tokens;

    for(int i = 0; i < token.size(); i++){

        if(token[i] != ' '){
            if(isOperation(token[i]) or isBracket(token[i])) {
                if (token[i] == '-' or token[i] == '+') { //I can write -2... or (-2... or +-2
                    if (i > 0 and token[i - 1] != '(' and !isOperation(token[i-1])) {
                        if (!tmp.empty()) 
                            tokens.push_back(tmp);
                        tokens.push_back(std::string(1, token[i]));
                        tmp = "";
                    }
                    else
                            tmp += token[i];
                    
                }
                else {
                    if(!tmp.empty()) 
                        tokens.push_back(tmp);
                    tokens.push_back(std::string(1, token[i]));
                    tmp = "";
                }
            }
            else
                tmp += token[i];
        }

    }

    if(tmp.size() > 0)
        tokens.push_back(tmp);

    return tokens;
}

double apply(double a, double b, char op){

    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }

    return 0;
}

double cbl(double base, double arg){
    return (double)log10(arg)/(double)log10(base);
}

double applyF(double a, std::string op){

    //TODO Refactor maybe with Enum

    if(op == "sin") return sin(a);
    if(op == "cos") return cos(a);
    if(op == "tan") return tan(a);
    if(op == "cotan") return 1/tan(a);
    if(op == "arcsin") return asin(a);
    if(op == "arccos") return acos(a);
    if(op == "arctan") return atan(a);
    if(op == "arccotan") return M_PI/2 - atan(a);
    if(op == "sqrt") return sqrt(a);
    if(op == "log_2") return log2(a);
    if(op == "ln") return log(a);
    if(op == "log_3") return cbl(3,a);
    if(op == "log_4") return cbl(4,a);
    if(op == "log_5") return cbl(5,a);
    if(op == "log_6") return cbl(6,a);
    if(op == "log_7") return cbl(7,a);
    if(op == "log_8") return cbl(8,a);
    if(op == "log_9") return cbl(9,a);
    if(op == "log") return log10(a);
    if(op == "abs") return abs(a);
    return 0;
}


double evaluate(std::string expr){
    std::vector<std::string> tokens = tokenization(expr);
    std::vector<std::string> post = infixToPostfix(tokens);

    std::stack<double> values;
    for(int i = 0; i < post.size(); i++){

        if(isFunction(post[i])){
                double value = values.top();
                values.pop();
                values.push(applyF(value, post[i]));
        }
        else {
            if (isOperation(post[i])) {
                double value1 = values.top();
                values.pop();
                double value2 = values.top();
                values.pop();
                values.push(apply(value2, value1, post[i][0]));
            }
            else
                values.push(stold(post[i]));
        }
    }

    return values.top();
}

std::string change(std::string newstr, double value){
    std::string str = newstr;
    std::string nstr = std::to_string(value);
    std::string nstrE = std::to_string(M_E);
    std::string nstrPI = std::to_string(M_PI);

    size_t indexVariable = str.find('x');
    while(indexVariable != std::string::npos){
        str[indexVariable] = ' ';
        str.insert(indexVariable, nstr);
        indexVariable = str.find('x');
    }

    size_t indexE = str.find('e');
    while(indexE != std::string::npos){
        str[indexE] = ' ';
        str.insert(indexE, nstrE);
        indexE = str.find('e');
    }
    
    size_t indexPI = str.find("pi");
    while(indexPI != std::string::npos){
        str[indexPI] = ' ';
        str[indexPI + 1] = ' ';
        str.insert(indexPI, nstrPI);
        indexPI = str.find("pi");
    }

    return str;
}