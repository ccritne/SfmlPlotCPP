#include "../include/Evaluate.hpp"

std::vector<std::string> functions{ "sin", "cos", "tan", "cotan", "arcsin", "arccos", "arctan", "arccotan", "sqrt", "log_2", "ln", "log_3", "log_4", "log_5", "log_6", "log_7", "log_8", "log_9", "log", "abs" };

bool isF(std::string op){

    if (std::find(functions.begin(), functions.end(), op) != functions.end())
        return true;

    return false;
}

int prec(std::string c) 
{ 
    if(isF(c))
        return 4;
	if(c == "^") 
	    return 3; 
	
    if(c == "*" || c == "/") 
	    return 2; 
	
    if(c == "+" || c == "-") 
	    return 1; 

	return -1; 
} 

bool isO(std::string op){
    return (prec(op) > 0 || isF(op))? true : false;
}

std::vector<std::string> infixToPostfix(std::vector<std::string> s) { 
	std::stack<std::string> st;  
	int l = s.size(); 
	std::vector<std::string> ns; 
	for(int i = 0; i < l; i++) 
	{
		if(isO(s[i]) == false && isF(s[i]) == false && s[i] != "(" && s[i] != ")") 
		    ns.push_back(s[i]); 

		else 
            if(s[i] == "(") st.push("("); 

		else if(s[i] == ")") 
		{ 
			while(!st.empty() && st.top() != "(") 
			{  
			    ns.push_back(st.top()); 
				st.pop(); 
			} 
			if(st.top() == "(") 
				st.pop(); 
		} 
		else{ 
			while(!st.empty() && prec(s[i]) < prec(st.top())) 
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
    std::vector<std::string> ret;
    for(int i = 0; i < token.size(); i++){
        std::string x(1, token[i]) ;
        if(x != " "){
            if(isO(x) || x == "(" || x == ")" ){
                    ret.push_back(tmp);
                    ret.push_back(x);
                    tmp = "";
            }
            else
                tmp += x;
        }else
            continue;
    }

    if(tmp.size() > 0)
        ret.push_back(tmp);

    std::vector<std::string> retret;
    for(auto x : ret)
        if(x != "")
            retret.push_back(x);

    std::vector<std::string> newretret;
    bool flag = false;
    for(int i = 0; i < retret.size(); i++)
        if(i > 0 && i + 1 < retret.size() && (isO(retret[i-1]) || retret[i-1] == "(") && retret[i] == "-" && is_number(retret[i+1]))
            newretret.push_back("-" + retret[i+1]), i++;
        else        
            newretret.push_back(retret[i]);

    return newretret;
}

double apply(double a, double b, std::string op){

    if(op == "+") return a + b;
    if(op == "-") return a - b;
    if(op == "*") return a * b;
    if(op == "/") return a / b;
    if(op == "^") return pow(a,b);

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
        if(isF(post[i]) || isO(post[i])){
            if(isF(post[i])){
                double value = values.top();
                values.pop();
                values.push(applyF(value, post[i]));
            }else{
                double value1 = values.top();
                values.pop();
                double value2 = values.top();
                values.pop();
                values.push(apply(value2, value1, post[i]));
            }
        }else
            values.push(stold(post[i]));
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