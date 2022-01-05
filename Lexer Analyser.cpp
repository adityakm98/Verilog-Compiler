#include <iostream>
#include <vector>
#include <string>

class func{
    public:
    bool isdelim(const char &ch)
    {
        if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '%' ||
            ch == '}' || ch == '&' || ch == '~' || ch == '!' ||
            ch == '|' || ch == '^')
            return (true);
        return (false);
    }
    
    bool isoperator(const char &ch)
    {
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=' le|| ch == '%' || ch == '&' || 
            ch == '~' || ch == '!' || ch == '|' ||
            ch == '^')
            return (true);
        return (false);
    }
    bool isBinary(const char &ch)
    {
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=' || ch == '&' || ch == '|' )
            return (true);
        return (false);
    }
    
    bool isKeyword(const std::string &str)
    {
        if (!str.compare("assign") || !str.compare("always") || !str.compare("end") || !str.compare("or") || 
        !str.compare("and") || !str.compare("initial") || !str.compare("output") || !str.compare("begin") || 
        !str.compare("posedge") || !str.compare("module"))
            return (true);
        return (false);
    }
    
    bool isInt(const std::string &str)
    {
        int i, len = str.size();
     
        if (len == 0)
            return (false);
        for (i = 0; i < len; i++) {
            if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' || (str[i] == '-' && i > 0))
                return (false);
        }
        return (true);
    }
};

class lexer : public func{
    public:
    std::vector<std::string> temp;
    
    void tokenizer(std::string &s, std::vector<std::vector<std::string>> &v){
        int left=0, right=0;
        int len=s.size();
        while(left<=right && right<=len){
            if(isdelim(s[right])==false){
                right++;
            }
            if(isdelim(s[right])==true && left==right){
                if(isBinary(s[right+1]) && isBinary(s[right+2])){
                    std::string t1(1,s[right]);
                    std::string t2(1,s[right+1]);
                    std::string t3(1,s[right+2]);
                    std::string t=t1+t2+t3;
                    temp.push_back("operator");
                    temp.push_back(t);
                    v.push_back(temp);
                    temp.clear();
                    right+=2;
                    left=right;
                }
                else if(isBinary(s[right+1])){
                    std::string st1(1,s[right]);
                    std::string st2(1,s[right+1]);
                    std::string st=st1+st2;
                    temp.push_back("operator");
                    temp.push_back(st);
                    v.push_back(temp);
                    temp.clear();
                    right+=1;
                    left=right;
                }
                else if(isoperator(s[right])==true){
                    std::string tem(1,s[right]);
                    temp.push_back("operator");
                    temp.push_back(tem);
                    v.push_back(temp);
                    temp.clear();
                }
                else if ((s[right])=='(' || (s[right])==')' || (s[right])==';' || s[right]==','){
                    std::string tem(1,s[right]);
                    temp.push_back("punctuator");
                    temp.push_back(tem);
                    v.push_back(temp);
                    temp.clear();
                }
                right++;
                left=right;
            }
            else if(isdelim(s[right])==true && left!=right || (right==len && left !=right)){
                std::string r=s.substr(left,right-left);
                if (isKeyword(r)==true){
                    temp.push_back("keyword");
                    temp.push_back(r);
                    v.push_back(temp);
                    temp.clear();
                }
                else if (isInt(r)==true){
                    temp.push_back("Integer");
                    temp.push_back(r);
                    v.push_back(temp);
                    temp.clear();
                }
                else if (isdelim(s[right-1])==false){
                    temp.push_back("Identifier");
                    temp.push_back(r);
                    v.push_back(temp);
                    temp.clear();
                }
                left=right;
            }
        }
    }
    
    void printTokens(const std::vector<std::vector<std::string>> &v){
        std::cout<<"["<<std::endl;
        for(int i=0;i<v.size();i++){
            std::cout<<"\t"<<'"'<<"type"<<'"'<<" : "<<'"'<<v[i][0]<<'"'<<','<<std::endl;
            std::cout<<"\t"<<'"'<<"value"<<'"'<<" : "<<'"'<<v[i][1]<<'"'<<std::endl;
        }
        std::cout<<"]"<<std::endl;
    }
    
};

int main(){
    lexer obj;
    std::string s;
    std::vector<std::vector<std::string>> v;
    std::getline(std::cin,s);
    obj.tokenizer(s,v);
    obj.printTokens(v);
    return 0;
}