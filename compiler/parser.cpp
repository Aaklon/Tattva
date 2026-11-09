#include<bits/stdc++.h>
#include<filesystem>
namespace fs = std::filesystem;
#define vs vector<string>
#define pb push_back
using namespace std;
enum class TokenType {
    /*
        IDENTIFIERS
    */
    Ident,      // Starts with lowercase (e.g., count, addItem)
    Upper,      // Starts with uppercase (e.g., Card, Todo)
    Tag,        // Built-in tag names (e.g., div, span)
    Number,
    Text,       // Text literals
    CssBlock,   // Raw CSS
    JsBlock,    // Raw JS 

    // Declarations
    Element, Page, Layout, App, Model, Global, Persist, 
    Const, Let, Fn, Derived, View, Style,
    
    // Structure
    Slot, Fill, Show, On, Doctitle,
    
    // Control flow
    If, Else, For, In, While, Break, Continue, Return, 
    Throw, Try, Catch, Await,
    
    // Values and operators
    And, Or, Not, True, False, None, Self,
    
    // Interop
    Extern, Script, Js,

    // Reserved Words -2 
    Extends, Class, Import, Export, Async, Yield, Match, Switch, 
    Enum, Interface, New, This, Null, Undefined, Var, Function, 
    Public, Private,

    // Operators and Punctuation
    Dot,            // .
    Comma,          // ,
    Colon,          // :
    Semicolon,      // ;
    Question,       // ?
    Arrow,          // ->
    Range,          // ..
    
    // Brackets
    LParen,         // (
    RParen,         // )
    LBracket,       // [
    RBracket,       // ]
    LBrace,         // {
    RBrace,         // }
    
    // Math & Arithmetic
    Plus,           // +
    Minus,          // -
    Star,           // *
    Slash,          // /
    Percent,        // %
    
    // Assignment
    Assign,         // =
    PlusAssign,     // +=
    MinusAssign,    // -=
    StarAssign,     // *=
    SlashAssign,    // /=
    PercentAssign,  // %=
    
    // Comparison
    Less,           // <
    Greater,        // >
    LessEq,         // <=
    GreaterEq,      // >=
    EqEq,           // ==
    NotEq,          // !=

    // Special / End of File
    EndOfFile,
    Error
};

struct token{
    TokenType tkn;
    string val;
    int line;
};

using vtt=vector<token>;

vtt Tokenize(string& s){
    vtt ans;
    int n=s.length(), i=0, line=1;

    while(i<n){
        char c=s[i];

        if(c==' ' || c=='\t' || c=='\r'){ i++; continue; }
        if(c=='\n'){ line++; i++; continue; }

        if(c=='/' && i+1<n && s[i+1]=='/'){
            while(i<n && s[i]!='\n') i++;
            continue;
        }

        if(c=='/' && i+1<n && s[i+1]=='*'){
            i+=2;
            while(i+1<n && !(s[i]=='*' && s[i+1]=='/')){
                if(s[i]=='\n') line++;
                i++;
            }
            if(i+1<n) i+=2;
            continue;
        }

        if(c=='"' || c=='\''){
            char quote=c;
            string tv="\"";
            i++;
            while(i<n && s[i]!=quote){
                if(s[i]=='\\' && i+1<n){ tv+=s[i++]; tv+=s[i++]; continue; }
                if(s[i]=='\n') line++;
                tv+=s[i];
                i++;
            }
            if(i<n){ tv+='"'; i++; }
            ans.pb(token{TokenType::Text, tv, line});
            continue;
        }

        if(i+1<n){
            string op2=s.substr(i,2);
            if(op2=="=="){ ans.pb(token{TokenType::EqEq, op2, line}); i+=2; continue; }
            else if(op2=="!="){ ans.pb(token{TokenType::NotEq, op2, line}); i+=2; continue; }
            else if(op2=="->"){ ans.pb(token{TokenType::Arrow, op2, line}); i+=2; continue; }
            else if(op2==".."){ ans.pb(token{TokenType::Range, op2, line}); i+=2; continue; }
            else if(op2=="+="){ ans.pb(token{TokenType::PlusAssign, op2, line}); i+=2; continue; }
            else if(op2=="-="){ ans.pb(token{TokenType::MinusAssign, op2, line}); i+=2; continue; }
            else if(op2=="*="){ ans.pb(token{TokenType::StarAssign, op2, line}); i+=2; continue; }
            else if(op2=="/="){ ans.pb(token{TokenType::SlashAssign, op2, line}); i+=2; continue; }
            else if(op2=="%="){ ans.pb(token{TokenType::PercentAssign, op2, line}); i+=2; continue; }
            else if(op2=="<="){ ans.pb(token{TokenType::LessEq, op2, line}); i+=2; continue; }
            else if(op2==">="){ ans.pb(token{TokenType::GreaterEq, op2, line}); i+=2; continue; }
            else if(op2=="&&"){ ans.pb(token{TokenType::And, op2, line}); i+=2; continue; }
            else if(op2=="||"){ ans.pb(token{TokenType::Or, op2, line}); i+=2; continue; }
        }

        if(c=='('){ ans.pb(token{TokenType::LParen, "(", line}); i++; continue; }
        else if(c==')'){ ans.pb(token{TokenType::RParen, ")", line}); i++; continue; }
        else if(c=='{'){ ans.pb(token{TokenType::LBrace, "{", line}); i++; continue; }
        else if(c=='}'){ ans.pb(token{TokenType::RBrace, "}", line}); i++; continue; }
        else if(c=='['){ ans.pb(token{TokenType::LBracket, "[", line}); i++; continue; }
        else if(c==']'){ ans.pb(token{TokenType::RBracket, "]", line}); i++; continue; }
        else if(c=='='){ ans.pb(token{TokenType::Assign, "=", line}); i++; continue; }
        else if(c=='+'){ ans.pb(token{TokenType::Plus, "+", line}); i++; continue; }
        else if(c=='-'){ ans.pb(token{TokenType::Minus, "-", line}); i++; continue; }
        else if(c=='*'){ ans.pb(token{TokenType::Star, "*", line}); i++; continue; }
        else if(c=='/'){ ans.pb(token{TokenType::Slash, "/", line}); i++; continue; }
        else if(c=='%'){ ans.pb(token{TokenType::Percent, "%", line}); i++; continue; }
        else if(c=='<'){ ans.pb(token{TokenType::Less, "<", line}); i++; continue; }
        else if(c=='>'){ ans.pb(token{TokenType::Greater, ">", line}); i++; continue; }
        else if(c=='.'){ ans.pb(token{TokenType::Dot, ".", line}); i++; continue; }
        else if(c==','){ ans.pb(token{TokenType::Comma, ",", line}); i++; continue; }
        else if(c==':'){ ans.pb(token{TokenType::Colon, ":", line}); i++; continue; }
        else if(c==';'){ ans.pb(token{TokenType::Semicolon, ";", line}); i++; continue; }
        else if(c=='?'){ ans.pb(token{TokenType::Question, "?", line}); i++; continue; }
        else if(c=='!'){ ans.pb(token{TokenType::Not, "!", line}); i++; continue; }

        if(isdigit(c)){
            string w="";
            while(i<n && (isdigit(s[i]) || s[i]=='_')) w+=s[i++];
            if(i+1<n && s[i]=='.' && isdigit(s[i+1])){
                w+=s[i++];
                while(i<n && (isdigit(s[i]) || s[i]=='_')) w+=s[i++];
            }
            ans.pb(token{TokenType::Number, w, line});
            continue;
        }

        if(isalpha(c) || c=='_'){
            string w="";
            while(i<n && (isalnum(s[i]) || s[i]=='_')){
                w+=s[i];
                i++;
            }

            if(w=="style"){
                ans.pb(token{TokenType::Style, w, line});
                int j=i;
                while(j<n && (s[j]==' ' || s[j]=='\t' || s[j]=='\r' || s[j]=='\n')){
                    if(s[j]=='\n') line++;
                    j++;
                }
                if(j<n && s[j]=='{'){
                    j++;
                    int depth=1;
                    string css="";
                    while(j<n && depth>0){
                        if(s[j]=='\n') line++;
                        if(s[j]=='{') depth++;
                        else if(s[j]=='}'){
                            depth--;
                            if(depth==0){ j++; break; }
                        }
                        css+=s[j++];
                    }
                    ans.pb(token{TokenType::CssBlock, css, line});
                    i=j;
                }
                continue;
            }

            if(w=="js"){
                ans.pb(token{TokenType::Js, w, line});
                int j=i;
                while(j<n && (s[j]==' ' || s[j]=='\t' || s[j]=='\r' || s[j]=='\n')){
                    if(s[j]=='\n') line++;
                    j++;
                }
                if(j<n && s[j]=='{'){
                    j++;
                    int depth=1;
                    string js="";
                    while(j<n && depth>0){
                        if(s[j]=='\n') line++;
                        if(s[j]=='{') depth++;
                        else if(s[j]=='}'){
                            depth--;
                            if(depth==0){ j++; break; }
                        }
                        js+=s[j++];
                    }
                    ans.pb(token{TokenType::JsBlock, js, line});
                    i=j;
                }
                continue;
            }

            if(w=="element") ans.pb(token{TokenType::Element, w, line});
            else if(w=="page") ans.pb(token{TokenType::Page, w, line});
            else if(w=="layout") ans.pb(token{TokenType::Layout, w, line});
            else if(w=="app") ans.pb(token{TokenType::App, w, line});
            else if(w=="model") ans.pb(token{TokenType::Model, w, line});
            else if(w=="global") ans.pb(token{TokenType::Global, w, line});
            else if(w=="persist") ans.pb(token{TokenType::Persist, w, line});
            else if(w=="const") ans.pb(token{TokenType::Const, w, line});
            else if(w=="let") ans.pb(token{TokenType::Let, w, line});
            else if(w=="fn") ans.pb(token{TokenType::Fn, w, line});
            else if(w=="derived") ans.pb(token{TokenType::Derived, w, line});
            else if(w=="view") ans.pb(token{TokenType::View, w, line});
            else if(w=="slot") ans.pb(token{TokenType::Slot, w, line});
            else if(w=="fill") ans.pb(token{TokenType::Fill, w, line});
            else if(w=="show") ans.pb(token{TokenType::Show, w, line});
            else if(w=="on") ans.pb(token{TokenType::On, w, line});
            else if(w=="doctitle") ans.pb(token{TokenType::Doctitle, w, line});
            else if(w=="if") ans.pb(token{TokenType::If, w, line});
            else if(w=="else") ans.pb(token{TokenType::Else, w, line});
            else if(w=="for") ans.pb(token{TokenType::For, w, line});
            else if(w=="in") ans.pb(token{TokenType::In, w, line});
            else if(w=="while") ans.pb(token{TokenType::While, w, line});
            else if(w=="break") ans.pb(token{TokenType::Break, w, line});
            else if(w=="continue") ans.pb(token{TokenType::Continue, w, line});
            else if(w=="return") ans.pb(token{TokenType::Return, w, line});
            else if(w=="throw") ans.pb(token{TokenType::Throw, w, line});
            else if(w=="try") ans.pb(token{TokenType::Try, w, line});
            else if(w=="catch") ans.pb(token{TokenType::Catch, w, line});
            else if(w=="await") ans.pb(token{TokenType::Await, w, line});
            else if(w=="and") ans.pb(token{TokenType::And, w, line});
            else if(w=="or") ans.pb(token{TokenType::Or, w, line});
            else if(w=="not") ans.pb(token{TokenType::Not, w, line});
            else if(w=="true") ans.pb(token{TokenType::True, w, line});
            else if(w=="false") ans.pb(token{TokenType::False, w, line});
            else if(w=="none") ans.pb(token{TokenType::None, w, line});
            else if(w=="self") ans.pb(token{TokenType::Self, w, line});
            else if(w=="extern") ans.pb(token{TokenType::Extern, w, line});
            else if(w=="script") ans.pb(token{TokenType::Script, w, line});
            else if(w=="extends") ans.pb(token{TokenType::Extends, w, line});
            else if(w=="class") ans.pb(token{TokenType::Class, w, line});
            else if(w=="import") ans.pb(token{TokenType::Import, w, line});
            else if(w=="export") ans.pb(token{TokenType::Export, w, line});
            else if(w=="async") ans.pb(token{TokenType::Async, w, line});
            else if(w=="yield") ans.pb(token{TokenType::Yield, w, line});
            else if(w=="match") ans.pb(token{TokenType::Match, w, line});
            else if(w=="switch") ans.pb(token{TokenType::Switch, w, line});
            else if(w=="enum") ans.pb(token{TokenType::Enum, w, line});
            else if(w=="interface") ans.pb(token{TokenType::Interface, w, line});
            else if(w=="new") ans.pb(token{TokenType::New, w, line});
            else if(w=="this") ans.pb(token{TokenType::This, w, line});
            else if(w=="null") ans.pb(token{TokenType::Null, w, line});
            else if(w=="undefined") ans.pb(token{TokenType::Undefined, w, line});
            else if(w=="var") ans.pb(token{TokenType::Var, w, line});
            else if(w=="function") ans.pb(token{TokenType::Function, w, line});
            else if(w=="public") ans.pb(token{TokenType::Public, w, line});
            else if(w=="private") ans.pb(token{TokenType::Private, w, line});
            else if(isupper(w[0])) ans.pb(token{TokenType::Upper, w, line});
            else ans.pb(token{TokenType::Ident, w, line});
            
            continue;
        }

        string err(1, c);
        ans.pb(token{TokenType::Error, err, line});
        i++;
    }

    ans.pb(token{TokenType::EndOfFile, "", line});
    return ans;
}



struct ASTNode{
        int line_no;
        virtual ~ASTNode()=default;
};

struct Exp : ASTNode{
    public :
        virtual ~Exp()=default;
};

struct binaryExp : Exp{
    string op;
    Exp* left;
    Exp* right;
    
        binaryExp(string o="",Exp* l=nullptr,Exp* r=nullptr):op(o),left(l),right(r){}
        ~binaryExp(){
            delete left;
            delete right;
        }
};

struct unaryExp: Exp{
    string op;
    Exp* expr;
};

struct LiteralExp: Exp{
    string literal;
};

struct identExp: Exp{
    string name;
};

struct listLitExp: Exp{
    vector<Exp*> items;
};

struct mapEntry: ASTNode{
    string key;
    Exp* val;
};

struct mapLitExp: Exp{
    vector<mapEntry*> entries;
};

struct postfixExp: Exp{
    Exp* primary;
    vector<string> members;
    vector<Exp*> args;
    vector<Exp*> indices;
    bool isCall = false;
};

struct lambdaExp: Exp{
    vector<string> params;
    ASTNode* body;
};

struct ifExp: Exp{
    Exp* cond;
    Exp* thenBranch;
    Exp* elseBranch;
};

struct Stmnt : ASTNode{
    public :
        virtual ~Stmnt()=default;
};

struct Block : Stmnt{
    vector<Stmnt*> lines;
};

struct rangeSt: Stmnt{
    int st;
    int end;
};

struct fornor : Stmnt{
    string iter;
    rangeSt* range;
    Block* block;
};

struct forin : Stmnt{
    string iter;
    string index;
    Exp* collcn;
    Block* block;
};

struct letStmnt: Stmnt{
    string name;
    Exp* val;
};

struct constStmnt: Stmnt{
    string name;
    Exp* val;
};

struct assignStmnt: Stmnt{
    Exp* target;
    string op;
    Exp* val;
};

struct ifStmnt: Stmnt{
    Exp* cond;
    Block* thenBlock;
    vector<Exp*> elseIfConds;
    vector<Block*> elseIfBlocks;
    Block* elseBlock;
};

struct whileStmnt: Stmnt{
    Exp* cond;
    Block* block;
};

struct breakStmnt: Stmnt{
};

struct continueStmnt: Stmnt{
};

struct returnStmnt: Stmnt{
    Exp* val;
};

struct throwStmnt: Stmnt{
    Exp* val;
};

struct tryStmnt: Stmnt{
    Block* tryBlock;
    string catchIdent;
    Block* catchBlock;
};

struct callStmnt: Stmnt{
    postfixExp* call;
};

struct viewNode : ASTNode{
    public :
        virtual ~viewNode()=default;
};

struct attrNode: ASTNode{
    string name;
    Exp* val;
};

struct tagNode: viewNode{
    string tag;
    vector<attrNode*> attrs;
    vector<viewNode*> children;
};

struct useNode: viewNode{
    string name;
    vector<attrNode*> args;
    vector<viewNode*> children;
};

struct ifViewNode: viewNode{
    Exp* cond;
    vector<viewNode*> thenNodes;
    vector<viewNode*> elseNodes;
};

struct forViewNode: viewNode{
    string iter;
    string index;
    Exp* collcn;
    Exp* keyExpr;
    vector<viewNode*> children;
};

struct slotNode: viewNode{
    string name;
    vector<viewNode*> fallback;
};

struct fillNode: viewNode{
    string name;
    vector<viewNode*> children;
};

struct showNode: viewNode{
    Exp* val;
};

struct textNode: viewNode{
    string text;
};

struct viewBlock: ASTNode{
    vector<viewNode*> nodes;
};

struct globalDecl: ASTNode{
    bool persist;
    string name;
    Exp* val;
};

struct derivedDecl: ASTNode{
    string name;
    Exp* val;
};

struct paramNode: ASTNode{
    string name;
    Exp* defaultVal;
};

struct fnDecl: ASTNode{
    string name;
    vector<paramNode*> params;
    Block* body;
};

struct hookDecl: ASTNode{
    string type;
    vector<string> deps;
    Block* body;
};

struct styleBlock: ASTNode{
    string css;
};

struct elementDecl: ASTNode{
    string name;
    vector<paramNode*> params;
    vector<ASTNode*> items;
};

struct pageDecl: ASTNode{
    string path;
    bool bare;
    vector<ASTNode*> items;
};

struct layoutDecl: ASTNode{
    vector<ASTNode*> items;
};

struct modelField: ASTNode{
    string name;
    string type;
    bool optional;
    bool required;
    bool unique;
    int minVal;
    int maxVal;
    Exp* defaultVal;
};

struct modelDecl: ASTNode{
    string name;
    vector<modelField*> fields;
};

struct appDecl: ASTNode{
    vector<mapEntry*> configs;
};

struct scriptDecl: ASTNode{
    string url;
};

struct externDecl: ASTNode{
    vector<string> names;
};

struct jsBlock: ASTNode{
    string js;
};

struct Program{
    vector<ASTNode*> prog;
    int appIdx=-1;
    int layoutIdx=-1;
};


class Parser{
    vtt tkn;
    int idx;

    token peek(){ return tkn[idx]; }
    token advance(){ return tkn[idx++]; }
    bool check(TokenType t){ return tkn[idx].tkn==t; }
    bool atEnd(){ return tkn[idx].tkn==TokenType::EndOfFile; }

    token expect(TokenType t){
        if(tkn[idx].tkn!=t){
            cerr<<"line "<<tkn[idx].line<<": expected "<<(int)t<<" got "<<tkn[idx].val<<"\n";
            exit(1);
        }
        return tkn[idx++];
    }

    Exp* parseOr();
    Exp* parseAnd();
    Exp* parseEq();
    Exp* parseCmp();
    Exp* parseAdd();
    Exp* parseMul();
    Exp* parseUnary();
    Exp* parsePostfix();
    Exp* parsePrimary();
    vector<Exp*> parseArgs();

    Stmnt* parseStmnt();
    Block* parseBlock();
    Stmnt* parseFor();
    Stmnt* parseIf();
    Stmnt* parseWhile();
    Stmnt* parseTry();
    Stmnt* parseLetConst(TokenType t);
    Stmnt* parseReturn();
    Stmnt* parseThrow();
    Stmnt* parseExpStmnt();

    viewNode* parseViewNode();
    viewBlock* parseViewBlock();
    attrNode* parseAttr();

    paramNode* parseParam();
    vector<paramNode*> parseParams();

    ASTNode* parseElement();
    ASTNode* parsePage();
    ASTNode* parseLayout();
    ASTNode* parseApp();
    ASTNode* parseModel();
    ASTNode* parseFnDecl();
    ASTNode* parseGlobal(bool persist);
    ASTNode* parseDerived();
    ASTNode* parseStyleBlock();
    ASTNode* parseViewDeclBlock();
    ASTNode* parseOnDecl();
    ASTNode* parseDoctitle();
    ASTNode* parseExtern();
    ASTNode* parseScript();
    ASTNode* parseJsBlock();

    vector<ASTNode*> parseElementBody();
    vector<ASTNode*> parsePageBody();

    public:
        Parser(vtt t):tkn(t),idx(0){}
        Program parse();
        Exp* parseExp();
};

Exp* Parser::parsePrimary(){
    token t=peek();
    if(t.tkn==TokenType::Number){
        advance();
        auto* e=new LiteralExp();
        e->literal=t.val;
        e->line_no=t.line;
        return e;
    }
    if(t.tkn==TokenType::Text){
        advance();
        auto* e=new LiteralExp();
        e->literal=t.val;
        e->line_no=t.line;
        return e;
    }
    if(t.tkn==TokenType::True||t.tkn==TokenType::False){
        advance();
        auto* e=new LiteralExp();
        e->literal=t.val;
        e->line_no=t.line;
        return e;
    }
    if(t.tkn==TokenType::None){
        advance();
        auto* e=new LiteralExp();
        e->literal=t.val;
        e->line_no=t.line;
        return e;
    }
    if(t.tkn==TokenType::Self){
        advance();
        auto* e=new identExp();
        e->name="self";
        e->line_no=t.line;
        return e;
    }
    if(t.tkn==TokenType::Ident||t.tkn==TokenType::Upper){
        int save=idx;
        token id=advance();
        if(check(TokenType::Arrow)){
            advance();
            auto* lam=new lambdaExp();
            lam->line_no=id.line;
            lam->params.pb(id.val);
            if(check(TokenType::LBrace)){
                lam->body=parseBlock();
            } else {
                lam->body=parseExp();
            }
            return lam;
        }
        idx=save;
        advance();
        auto* e=new identExp();
        e->name=id.val;
        e->line_no=id.line;
        return e;
    }
    if(t.tkn==TokenType::LParen){
        advance();
        if(check(TokenType::RParen)){
            advance();
            expect(TokenType::Arrow);
            auto* lam=new lambdaExp();
            lam->line_no=t.line;
            if(check(TokenType::LBrace)){
                lam->body=parseBlock();
            } else {
                lam->body=parseExp();
            }
            return lam;
        }
        if(check(TokenType::Ident)){
            int save=idx;
            bool isLambda=false;
            vector<string> pnames;
            while(check(TokenType::Ident)){
                pnames.pb(advance().val);
                if(check(TokenType::Comma)) advance();
                else break;
            }
            if(check(TokenType::RParen)){
                advance();
                if(check(TokenType::Arrow)){
                    advance();
                    isLambda=true;
                }
            }
            if(isLambda){
                auto* lam=new lambdaExp();
                lam->line_no=t.line;
                lam->params=pnames;
                if(check(TokenType::LBrace)){
                    lam->body=parseBlock();
                } else {
                    lam->body=parseExp();
                }
                return lam;
            }
            idx=save;
        }
        Exp* inner=parseExp();
        expect(TokenType::RParen);
        return inner;
    }
    if(t.tkn==TokenType::LBracket){
        advance();
        auto* e=new listLitExp();
        e->line_no=t.line;
        while(!check(TokenType::RBracket)&&!atEnd()){
            e->items.pb(parseExp());
            if(check(TokenType::Comma)) advance();
        }
        expect(TokenType::RBracket);
        return e;
    }
    if(t.tkn==TokenType::LBrace){
        advance();
        auto* e=new mapLitExp();
        e->line_no=t.line;
        while(!check(TokenType::RBrace)&&!atEnd()){
            auto* entry=new mapEntry();
            entry->line_no=peek().line;
            entry->key=expect(TokenType::Ident).val;
            expect(TokenType::Colon);
            entry->val=parseExp();
            e->entries.pb(entry);
            if(check(TokenType::Comma)) advance();
        }
        expect(TokenType::RBrace);
        return e;
    }
    if(t.tkn==TokenType::If){
        advance();
        auto* e=new ifExp();
        e->line_no=t.line;
        e->cond=parseExp();
        if(check(TokenType::LBrace)){
            advance();
            e->thenBranch=parseExp();
            expect(TokenType::RBrace);
            if(check(TokenType::Else)){
                advance();
                if(check(TokenType::If)){
                    e->elseBranch=parsePrimary();
                } else {
                    expect(TokenType::LBrace);
                    e->elseBranch=parseExp();
                    expect(TokenType::RBrace);
                }
            } else {
                e->elseBranch=nullptr;
            }
            return e;
        }
        expect(TokenType::Question);
        e->thenBranch=parseExp();
        expect(TokenType::Colon);
        e->elseBranch=parseExp();
        return e;
    }
    if(t.tkn==TokenType::Await){
        advance();
        auto* e=new unaryExp();
        e->line_no=t.line;
        e->op="await";
        e->expr=parseExp();
        return e;
    }
    cerr<<"line "<<t.line<<": unexpected token "<<t.val<<"\n";
    exit(1);
}

Exp* Parser::parsePostfix(){
    Exp* e=parsePrimary();
    while(true){
        if(check(TokenType::Dot)){
            advance();
            auto* p=new postfixExp();
            p->line_no=peek().line;
            p->primary=e;
            p->members.pb(expect(TokenType::Ident).val);
            e=p;
        } else if(check(TokenType::LParen)){
            advance();
            auto* p=new postfixExp();
            p->line_no=peek().line;
            p->primary=e;
            p->isCall=true;
            bool hasNamed=false;
            auto* mapExp=new mapLitExp();
            mapExp->line_no=p->line_no;
            while(!check(TokenType::RParen)&&!atEnd()){
                if((check(TokenType::Ident)||check(TokenType::Text)) && idx+1<(int)tkn.size() && tkn[idx+1].tkn==TokenType::Colon){
                    hasNamed=true;
                    auto* entry=new mapEntry();
                    entry->line_no=peek().line;
                    entry->key=advance().val;
                    advance();
                    entry->val=parseExp();
                    mapExp->entries.pb(entry);
                } else {
                    p->args.pb(parseExp());
                }
                if(check(TokenType::Comma)) advance();
            }
            if(hasNamed){
                p->args.pb(mapExp);
            }
            expect(TokenType::RParen);
            e=p;
        } else if(check(TokenType::LBracket)){
            advance();
            auto* p=new postfixExp();
            p->line_no=peek().line;
            p->primary=e;
            p->indices.pb(parseExp());
            expect(TokenType::RBracket);
            e=p;
        } else break;
    }
    return e;
}

Exp* Parser::parseUnary(){
    if(check(TokenType::Not)||check(TokenType::Minus)){
        token t=advance();
        auto* e=new unaryExp();
        e->line_no=t.line;
        e->op=t.val;
        e->expr=parseUnary();
        return e;
    }
    return parsePostfix();
}

Exp* Parser::parseMul(){
    Exp* left=parseUnary();
    while(check(TokenType::Star)||check(TokenType::Slash)||check(TokenType::Percent)){
        token t=advance();
        Exp* right=parseUnary();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseAdd(){
    Exp* left=parseMul();
    while(check(TokenType::Plus)||check(TokenType::Minus)){
        token t=advance();
        Exp* right=parseMul();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseCmp(){
    Exp* left=parseAdd();
    while(check(TokenType::Less)||check(TokenType::Greater)||check(TokenType::LessEq)||check(TokenType::GreaterEq)){
        token t=advance();
        Exp* right=parseAdd();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseEq(){
    Exp* left=parseCmp();
    while(check(TokenType::EqEq)||check(TokenType::NotEq)){
        token t=advance();
        Exp* right=parseCmp();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseAnd(){
    Exp* left=parseEq();
    while(check(TokenType::And)){
        token t=advance();
        Exp* right=parseEq();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseOr(){
    Exp* left=parseAnd();
    while(check(TokenType::Or)){
        token t=advance();
        Exp* right=parseAnd();
        auto* e=new binaryExp(t.val,left,right);
        e->op=t.val; e->left=left; e->right=right;
        e->line_no=t.line;
        left=e;
    }
    return left;
}

Exp* Parser::parseExp(){
    return parseOr();
}

vector<Exp*> Parser::parseArgs(){
    vector<Exp*> args;
    expect(TokenType::LParen);
    while(!check(TokenType::RParen)&&!atEnd()){
        args.pb(parseExp());
        if(check(TokenType::Comma)) advance();
    }
    expect(TokenType::RParen);
    return args;
}

Block* Parser::parseBlock(){
    expect(TokenType::LBrace);
    auto* b=new Block();
    b->line_no=peek().line;
    while(!check(TokenType::RBrace)&&!atEnd()){
        if(check(TokenType::Semicolon)){ advance(); continue; }
        b->lines.pb(parseStmnt());
        if(check(TokenType::Semicolon)) advance();
    }
    expect(TokenType::RBrace);
    return b;
}

Stmnt* Parser::parseFor(){
    token t=advance();
    string iter=expect(TokenType::Ident).val;
    if(check(TokenType::Comma)){
        advance();
        string index=iter;
        iter=expect(TokenType::Ident).val;
        expect(TokenType::In);
        Exp* coll=parseExp();
        Block* blk=parseBlock();
        auto* f=new forin();
        f->line_no=t.line;
        f->iter=iter;
        f->index=index;
        f->collcn=coll;
        f->block=blk;
        return f;
    }
    expect(TokenType::In);
    if(check(TokenType::Number)){
        int save=idx;
        token num1=advance();
        if(check(TokenType::Range)){
            advance();
            token num2=expect(TokenType::Number);
            Block* blk=parseBlock();
            auto* r=new rangeSt();
            r->st=stoi(num1.val);
            r->end=stoi(num2.val);
            r->line_no=t.line;
            auto* f=new fornor();
            f->line_no=t.line;
            f->iter=iter;
            f->range=r;
            f->block=blk;
            return f;
        }
        idx=save;
    }
    if(check(TokenType::Ident)||check(TokenType::Upper)){
        Exp* maybeRange=parseExp();
        if(check(TokenType::Range)){
            advance();
            parseExp();
            Block* blk=parseBlock();
            auto* r=new rangeSt();
            r->line_no=t.line;
            r->st=0; r->end=0;
            auto* f=new fornor();
            f->line_no=t.line;
            f->iter=iter;
            f->range=r;
            f->block=blk;
            return f;
        }
        Block* blk=parseBlock();
        auto* f=new forin();
        f->line_no=t.line;
        f->iter=iter;
        f->index="";
        f->collcn=maybeRange;
        f->block=blk;
        return f;
    }
    Exp* coll=parseExp();
    Block* blk=parseBlock();
    auto* f=new forin();
    f->line_no=t.line;
    f->iter=iter;
    f->index="";
    f->collcn=coll;
    f->block=blk;
    return f;
}

Stmnt* Parser::parseIf(){
    token t=advance();
    Exp* cond=parseExp();
    Block* thenBlk=parseBlock();
    auto* s=new ifStmnt();
    s->line_no=t.line;
    s->cond=cond;
    s->thenBlock=thenBlk;
    s->elseBlock=nullptr;
    while(check(TokenType::Else)){
        advance();
        if(check(TokenType::If)){
            advance();
            s->elseIfConds.pb(parseExp());
            s->elseIfBlocks.pb(parseBlock());
        } else {
            s->elseBlock=parseBlock();
            break;
        }
    }
    return s;
}

Stmnt* Parser::parseWhile(){
    token t=advance();
    Exp* cond=parseExp();
    Block* blk=parseBlock();
    auto* s=new whileStmnt();
    s->line_no=t.line;
    s->cond=cond;
    s->block=blk;
    return s;
}

Stmnt* Parser::parseTry(){
    token t=advance();
    Block* tryBlk=parseBlock();
    expect(TokenType::Catch);
    string catchId="";
    if(check(TokenType::Ident)){
        catchId=advance().val;
    }
    Block* catchBlk=parseBlock();
    auto* s=new tryStmnt();
    s->line_no=t.line;
    s->tryBlock=tryBlk;
    s->catchIdent=catchId;
    s->catchBlock=catchBlk;
    return s;
}

Stmnt* Parser::parseLetConst(TokenType t){
    token tk=advance();
    string name=expect(TokenType::Ident).val;
    expect(TokenType::Assign);
    Exp* val=parseExp();
    if(t==TokenType::Let){
        auto* s=new letStmnt();
        s->line_no=tk.line;
        s->name=name;
        s->val=val;
        return s;
    }
    auto* s=new constStmnt();
    s->line_no=tk.line;
    s->name=name;
    s->val=val;
    return s;
}

Stmnt* Parser::parseReturn(){
    token t=advance();
    auto* s=new returnStmnt();
    s->line_no=t.line;
    s->val=nullptr;
    if(!check(TokenType::RBrace)&&!atEnd()){
        s->val=parseExp();
    }
    return s;
}

Stmnt* Parser::parseThrow(){
    token t=advance();
    auto* s=new throwStmnt();
    s->line_no=t.line;
    s->val=parseExp();
    return s;
}

Stmnt* Parser::parseExpStmnt(){
    Exp* e=parseExp();
    if(check(TokenType::Assign)||check(TokenType::PlusAssign)||check(TokenType::MinusAssign)||
       check(TokenType::StarAssign)||check(TokenType::SlashAssign)||check(TokenType::PercentAssign)){
        token op=advance();
        Exp* val=parseExp();
        auto* s=new assignStmnt();
        s->line_no=op.line;
        s->target=e;
        s->op=op.val;
        s->val=val;
        return s;
    }
    if(auto* pf=dynamic_cast<postfixExp*>(e)){
        auto* s=new callStmnt();
        s->line_no=pf->line_no;
        s->call=pf;
        return s;
    }
    auto* s=new callStmnt();
    s->line_no=e->line_no;
    s->call=nullptr;
    return s;
}

Stmnt* Parser::parseStmnt(){
    token t=peek();
    if(t.tkn==TokenType::For) return parseFor();
    if(t.tkn==TokenType::If) return parseIf();
    if(t.tkn==TokenType::While) return parseWhile();
    if(t.tkn==TokenType::Try) return parseTry();
    if(t.tkn==TokenType::Let) return parseLetConst(TokenType::Let);
    if(t.tkn==TokenType::Const) return parseLetConst(TokenType::Const);
    if(t.tkn==TokenType::Return) return parseReturn();
    if(t.tkn==TokenType::Throw) return parseThrow();
    if(t.tkn==TokenType::Break){ advance(); auto* s=new breakStmnt(); s->line_no=t.line; return s; }
    if(t.tkn==TokenType::Continue){ advance(); auto* s=new continueStmnt(); s->line_no=t.line; return s; }
    return parseExpStmnt();
}

attrNode* Parser::parseAttr(){
    auto* a=new attrNode();
    a->line_no=peek().line;
    a->name=advance().val;
    if(check(TokenType::Colon)||check(TokenType::Assign)) advance();
    a->val=parseExp();
    return a;
}

viewNode* Parser::parseViewNode(){
    token t=peek();
    if(t.tkn==TokenType::Tag||t.tkn==TokenType::Ident){
        advance();
        auto* n=new tagNode();
        n->line_no=t.line;
        n->tag=t.val;
        if(check(TokenType::LParen)){
            advance();
            while(!check(TokenType::RParen)&&!atEnd()){
                n->attrs.pb(parseAttr());
                if(check(TokenType::Comma)) advance();
            }
            expect(TokenType::RParen);
        }
        if(check(TokenType::Text)){
            auto* tn=new textNode();
            tn->line_no=peek().line;
            tn->text=advance().val;
            n->children.pb(tn);
        } else if(check(TokenType::If)){
            n->children.pb(parseViewNode());
        } else if(check(TokenType::LBrace)){
            advance();
            while(!check(TokenType::RBrace)&&!atEnd()){
                n->children.pb(parseViewNode());
            }
            expect(TokenType::RBrace);
        }
        return n;
    }
    if(t.tkn==TokenType::Upper){
        advance();
        auto* n=new useNode();
        n->line_no=t.line;
        n->name=t.val;
        if(check(TokenType::LParen)){
            advance();
            while(!check(TokenType::RParen)&&!atEnd()){
                n->args.pb(parseAttr());
                if(check(TokenType::Comma)) advance();
            }
            expect(TokenType::RParen);
        }
        if(check(TokenType::LBrace)){
            advance();
            while(!check(TokenType::RBrace)&&!atEnd()){
                if(check(TokenType::Fill)){
                    advance();
                    auto* fn=new fillNode();
                    fn->line_no=peek().line;
                    fn->name=expect(TokenType::Ident).val;
                    expect(TokenType::LBrace);
                    while(!check(TokenType::RBrace)&&!atEnd()){
                        fn->children.pb(parseViewNode());
                    }
                    expect(TokenType::RBrace);
                    n->children.pb(fn);
                } else {
                    n->children.pb(parseViewNode());
                }
            }
            expect(TokenType::RBrace);
        }
        return n;
    }
    if(t.tkn==TokenType::If){
        advance();
        auto* n=new ifViewNode();
        n->line_no=t.line;
        n->cond=parseExp();
        expect(TokenType::LBrace);
        while(!check(TokenType::RBrace)&&!atEnd()){
            n->thenNodes.pb(parseViewNode());
        }
        expect(TokenType::RBrace);
        if(check(TokenType::Else)){
            advance();
            expect(TokenType::LBrace);
            while(!check(TokenType::RBrace)&&!atEnd()){
                n->elseNodes.pb(parseViewNode());
            }
            expect(TokenType::RBrace);
        }
        return n;
    }
    if(t.tkn==TokenType::For){
        advance();
        auto* n=new forViewNode();
        n->line_no=t.line;
        n->iter=expect(TokenType::Ident).val;
        n->index="";
        if(check(TokenType::Comma)){
            advance();
            n->index=n->iter;
            n->iter=expect(TokenType::Ident).val;
        }
        expect(TokenType::In);
        n->collcn=parseExp();
        n->keyExpr=nullptr;
        if(check(TokenType::Ident)&&peek().val=="key"){
            advance();
            n->keyExpr=parseExp();
        }
        expect(TokenType::LBrace);
        while(!check(TokenType::RBrace)&&!atEnd()){
            n->children.pb(parseViewNode());
        }
        expect(TokenType::RBrace);
        return n;
    }
    if(t.tkn==TokenType::Slot){
        advance();
        auto* n=new slotNode();
        n->line_no=t.line;
        n->name="";
        if(check(TokenType::Ident)) n->name=advance().val;
        if(check(TokenType::LBrace)){
            advance();
            while(!check(TokenType::RBrace)&&!atEnd()){
                n->fallback.pb(parseViewNode());
            }
            expect(TokenType::RBrace);
        }
        return n;
    }
    if(t.tkn==TokenType::Fill){
        advance();
        auto* n=new fillNode();
        n->line_no=t.line;
        n->name=expect(TokenType::Ident).val;
        expect(TokenType::LBrace);
        while(!check(TokenType::RBrace)&&!atEnd()){
            n->children.pb(parseViewNode());
        }
        expect(TokenType::RBrace);
        return n;
    }
    if(t.tkn==TokenType::Show){
        advance();
        auto* n=new showNode();
        n->line_no=t.line;
        n->val=parseExp();
        return n;
    }
    if(t.tkn==TokenType::Text){
        advance();
        auto* n=new textNode();
        n->line_no=t.line;
        n->text=t.val;
        return n;
    }
    cerr<<"line "<<t.line<<": unexpected view token "<<t.val<<"\n";
    exit(1);
}

viewBlock* Parser::parseViewBlock(){
    auto* vb=new viewBlock();
    vb->line_no=peek().line;
    expect(TokenType::LBrace);
    while(!check(TokenType::RBrace)&&!atEnd()){
        vb->nodes.pb(parseViewNode());
    }
    expect(TokenType::RBrace);
    return vb;
}

paramNode* Parser::parseParam(){
    auto* p=new paramNode();
    p->line_no=peek().line;
    p->name=expect(TokenType::Ident).val;
    p->defaultVal=nullptr;
    if(check(TokenType::Assign)){
        advance();
        p->defaultVal=parseExp();
    }
    return p;
}

vector<paramNode*> Parser::parseParams(){
    vector<paramNode*> params;
    expect(TokenType::LParen);
    while(!check(TokenType::RParen)&&!atEnd()){
        params.pb(parseParam());
        if(check(TokenType::Comma)) advance();
    }
    expect(TokenType::RParen);
    return params;
}

ASTNode* Parser::parseFnDecl(){
    token t=advance();
    auto* f=new fnDecl();
    f->line_no=t.line;
    f->name=expect(TokenType::Ident).val;
    f->params=parseParams();
    f->body=parseBlock();
    return f;
}

ASTNode* Parser::parseGlobal(bool persist){
    token t=advance();
    auto* g=new globalDecl();
    g->line_no=t.line;
    if(check(TokenType::Persist)){
        advance();
        persist=true;
    }
    g->persist=persist;
    g->name=expect(TokenType::Ident).val;
    expect(TokenType::Assign);
    g->val=parseExp();
    return g;
}

ASTNode* Parser::parseDerived(){
    token t=advance();
    auto* d=new derivedDecl();
    d->line_no=t.line;
    d->name=expect(TokenType::Ident).val;
    expect(TokenType::Assign);
    d->val=parseExp();
    return d;
}

ASTNode* Parser::parseStyleBlock(){
    token t=advance();
    auto* s=new styleBlock();
    s->line_no=t.line;
    if(check(TokenType::CssBlock)){
        s->css=advance().val;
        return s;
    }
    expect(TokenType::LBrace);
    int depth=1;
    string css="";
    while(depth>0 && !atEnd()){
        if(check(TokenType::LBrace)){
            depth++;
            css+="{ ";
            advance();
        } else if(check(TokenType::RBrace)){
            depth--;
            if(depth>0) css+="} ";
            advance();
        } else {
            css+=advance().val+" ";
        }
    }
    s->css=css;
    return s;
}

ASTNode* Parser::parseViewDeclBlock(){
    token t=advance();
    return parseViewBlock();
}

ASTNode* Parser::parseOnDecl(){
    token t=advance();
    auto* h=new hookDecl();
    h->line_no=t.line;
    h->type=expect(TokenType::Ident).val;
    if(check(TokenType::LParen)){
        advance();
        while(!check(TokenType::RParen)&&!atEnd()){
            h->deps.pb(expect(TokenType::Ident).val);
            if(check(TokenType::Comma)) advance();
        }
        expect(TokenType::RParen);
    }
    h->body=parseBlock();
    return h;
}

ASTNode* Parser::parseDoctitle(){
    token t=advance();
    auto* d=new derivedDecl();
    d->line_no=t.line;
    d->name="__doctitle__";
    d->val=parseExp();
    return d;
}

ASTNode* Parser::parseExtern(){
    token t=advance();
    auto* e=new externDecl();
    e->line_no=t.line;
    while(check(TokenType::Ident)||check(TokenType::Upper)){
        e->names.pb(advance().val);
        if(check(TokenType::Comma)) advance();
    }
    return e;
}

ASTNode* Parser::parseScript(){
    token t=advance();
    auto* s=new scriptDecl();
    s->line_no=t.line;
    s->url=expect(TokenType::Text).val;
    return s;
}

ASTNode* Parser::parseJsBlock(){
    token t=advance();
    auto* j=new jsBlock();
    j->line_no=t.line;
    if(check(TokenType::JsBlock)){
        j->js=advance().val;
        return j;
    }
    expect(TokenType::LBrace);
    int depth=1;
    string js="";
    while(depth>0 && !atEnd()){
        if(check(TokenType::LBrace)){
            depth++;
            js+="{ ";
            advance();
        } else if(check(TokenType::RBrace)){
            depth--;
            if(depth>0) js+="} ";
            advance();
        } else {
            js+=advance().val+" ";
        }
    }
    j->js=js;
    return j;
}

vector<ASTNode*> Parser::parseElementBody(){
    vector<ASTNode*> items;
    expect(TokenType::LBrace);
    while(!check(TokenType::RBrace)&&!atEnd()){
        token t=peek();
        if(t.tkn==TokenType::Let) items.pb(parseLetConst(TokenType::Let));
        else if(t.tkn==TokenType::Const) items.pb(parseLetConst(TokenType::Const));
        else if(t.tkn==TokenType::Fn) items.pb(parseFnDecl());
        else if(t.tkn==TokenType::Derived) items.pb(parseDerived());
        else if(t.tkn==TokenType::View) items.pb(parseViewDeclBlock());
        else if(t.tkn==TokenType::Style) items.pb(parseStyleBlock());
        else if(t.tkn==TokenType::On) items.pb(parseOnDecl());
        else if(t.tkn==TokenType::Global) items.pb(parseGlobal(false));
        else if(t.tkn==TokenType::Persist) items.pb(parseGlobal(true));
        else if(t.tkn==TokenType::Doctitle) items.pb(parseDoctitle());
        else if(t.tkn==TokenType::Extern) items.pb(parseExtern());
        else if(t.tkn==TokenType::Script) items.pb(parseScript());
        else if(t.tkn==TokenType::Js) items.pb(parseJsBlock());
        else if(t.tkn==TokenType::Ident){
            token id=advance();
            if(check(TokenType::Assign)){
                advance();
                auto* s=new letStmnt();
                s->line_no=id.line;
                s->name=id.val;
                s->val=parseExp();
                items.pb(s);
            } else {
                idx--;
                items.pb(parseStmnt());
            }
        }
        else {
            cerr<<"line "<<t.line<<": unexpected in body "<<t.val<<"\n";
            exit(1);
        }
    }
    expect(TokenType::RBrace);
    return items;
}

vector<ASTNode*> Parser::parsePageBody(){
    vector<ASTNode*> items;
    expect(TokenType::LBrace);
    while(!check(TokenType::RBrace)&&!atEnd()){
        token t=peek();
        if(t.tkn==TokenType::View) items.pb(parseViewDeclBlock());
        else if(t.tkn==TokenType::Doctitle) items.pb(parseDoctitle());
        else if(t.tkn==TokenType::Style) items.pb(parseStyleBlock());
        else if(t.tkn==TokenType::Fn) items.pb(parseFnDecl());
        else if(t.tkn==TokenType::Derived) items.pb(parseDerived());
        else if(t.tkn==TokenType::On) items.pb(parseOnDecl());
        else if(t.tkn==TokenType::Let) items.pb(parseLetConst(TokenType::Let));
        else if(t.tkn==TokenType::Const) items.pb(parseLetConst(TokenType::Const));
        else if(t.tkn==TokenType::Tag||t.tkn==TokenType::Upper||t.tkn==TokenType::Slot||
                t.tkn==TokenType::Fill||t.tkn==TokenType::Show||t.tkn==TokenType::Text){
            items.pb(parseViewNode());
        }
        else if(t.tkn==TokenType::If||t.tkn==TokenType::For){
            items.pb(parseViewNode());
        }
        else if(t.tkn==TokenType::Ident){
            int save=idx;
            token id=advance();
            if(check(TokenType::Assign)){
                advance();
                auto* s=new letStmnt();
                s->line_no=id.line;
                s->name=id.val;
                s->val=parseExp();
                items.pb(s);
            } else {
                idx=save;
                items.pb(parseViewNode());
            }
        }
        else {
            cerr<<"line "<<t.line<<": unexpected in page "<<t.val<<"\n";
            exit(1);
        }
    }
    expect(TokenType::RBrace);
    return items;
}

ASTNode* Parser::parseElement(){
    token t=advance();
    auto* e=new elementDecl();
    e->line_no=t.line;
    e->name=expect(TokenType::Upper).val;
    if(check(TokenType::LParen)){
        e->params=parseParams();
    }
    e->items=parseElementBody();
    return e;
}

ASTNode* Parser::parsePage(){
    token t=advance();
    auto* p=new pageDecl();
    p->line_no=t.line;
    p->path=expect(TokenType::Text).val;
    p->bare=false;
    if(check(TokenType::Ident)&&peek().val=="bare"){
        advance();
        p->bare=true;
    }
    p->items=parsePageBody();
    return p;
}

ASTNode* Parser::parseLayout(){
    token t=advance();
    auto* l=new layoutDecl();
    l->line_no=t.line;
    l->items=parsePageBody();
    return l;
}

ASTNode* Parser::parseApp(){
    token t=advance();
    auto* a=new appDecl();
    a->line_no=t.line;
    expect(TokenType::LBrace);
    while(!check(TokenType::RBrace)&&!atEnd()){
        auto* entry=new mapEntry();
        entry->line_no=peek().line;
        entry->key=expect(TokenType::Ident).val;
        expect(TokenType::Colon);
        entry->val=parseExp();
        a->configs.pb(entry);
        if(check(TokenType::Comma)) advance();
    }
    expect(TokenType::RBrace);
    return a;
}

ASTNode* Parser::parseModel(){
    token t=advance();
    auto* m=new modelDecl();
    m->line_no=t.line;
    m->name=expect(TokenType::Upper).val;
    expect(TokenType::LBrace);
    while(!check(TokenType::RBrace)&&!atEnd()){
        auto* f=new modelField();
        f->line_no=peek().line;
        f->name=expect(TokenType::Ident).val;
        expect(TokenType::Colon);
        f->type=advance().val;
        f->optional=false;
        f->required=false;
        f->unique=false;
        f->minVal=0;
        f->maxVal=0;
        f->defaultVal=nullptr;
        if(check(TokenType::Question)){ advance(); f->optional=true; }
        while(check(TokenType::Ident)){
            string mod=peek().val;
            if(mod=="optional"){ advance(); f->optional=true; }
            else if(mod=="required"){ advance(); f->required=true; }
            else if(mod=="unique"){ advance(); f->unique=true; }
            else if(mod=="min"){ advance(); f->minVal=stoi(expect(TokenType::Number).val); }
            else if(mod=="max"){ advance(); f->maxVal=stoi(expect(TokenType::Number).val); }
            else break;
        }
        if(check(TokenType::Assign)){
            advance();
            f->defaultVal=parseExp();
        }
        m->fields.pb(f);
    }
    expect(TokenType::RBrace);
    return m;
}

Program Parser::parse(){
    Program prog;
    while(!atEnd()){
        token t=peek();
        if(t.tkn==TokenType::Element) prog.prog.pb(parseElement());
        else if(t.tkn==TokenType::Page) prog.prog.pb(parsePage());
        else if(t.tkn==TokenType::Layout){
            prog.layoutIdx=prog.prog.size();
            prog.prog.pb(parseLayout());
        }
        else if(t.tkn==TokenType::App){
            prog.appIdx=prog.prog.size();
            prog.prog.pb(parseApp());
        }
        else if(t.tkn==TokenType::Model) prog.prog.pb(parseModel());
        else if(t.tkn==TokenType::Global) prog.prog.pb(parseGlobal(false));
        else if(t.tkn==TokenType::Persist) prog.prog.pb(parseGlobal(true));
        else if(t.tkn==TokenType::Const) prog.prog.pb(parseLetConst(TokenType::Const));
        else if(t.tkn==TokenType::Let) prog.prog.pb(parseLetConst(TokenType::Let));
        else if(t.tkn==TokenType::Derived) prog.prog.pb(parseDerived());
        else if(t.tkn==TokenType::Fn) prog.prog.pb(parseFnDecl());
        else if(t.tkn==TokenType::Extern) prog.prog.pb(parseExtern());
        else if(t.tkn==TokenType::Script) prog.prog.pb(parseScript());
        else if(t.tkn==TokenType::Js) prog.prog.pb(parseJsBlock());
        else if(t.tkn==TokenType::Style) prog.prog.pb(parseStyleBlock());
        else {
            cerr<<"line "<<t.line<<": unexpected top-level "<<t.val<<"\n";
            exit(1);
        }
    }
    return prog;
}

int globalNodeCounter = 0;

bool isBuiltin(const string& name){
    static const set<string> builtins = {
        "Math", "Date", "JSON", "console", "window", "document", "history", "location", "localStorage",
        "Object", "Array", "String", "Number", "Boolean", "RegExp", "Error",
        "parseInt", "parseFloat", "isNaN", "isFinite", "setTimeout", "setInterval", "clearTimeout", "clearInterval",
        "encodeURIComponent", "decodeURIComponent", "route", "undefined", "null", "true", "false", "this", "self"
    };
    return builtins.count(name) > 0;
}

bool hasInterpolation(const string& s){
    if(s.length() < 3) return false;
    bool inQuotes = (s.front()=='"' && s.back()=='"') || (s.front()=='\'' && s.back()=='\'');
    if(!inQuotes) return false;
    if(s.find('\\') != string::npos && s.find("\\n") != string::npos) return false;
    if(s.find("element ") != string::npos || s.find("model ") != string::npos || s.find("fn ") != string::npos) return false;
    size_t st = s.find('{');
    if(st == string::npos) return false;
    size_t end = s.find('}', st);
    if(end == string::npos) return false;
    string sub = s.substr(st + 1, end - st - 1);
    if(sub.find('\n') != string::npos || sub.find('\r') != string::npos || sub.find('\\') != string::npos) return false;
    return true;
}

string emitExp(Exp* e, const set<string>* localVars=nullptr);
void emitStmnt(Stmnt* s, ostringstream& ss, int indent=2, const set<string>* localVars=nullptr);

string parseInterpolatedString(const string& raw, const set<string>* localVars=nullptr){
    if(raw.length() < 2) return raw;
    string inner = raw.substr(1, raw.length()-2);
    string res = "`";
    size_t i = 0;
    while(i < inner.length()){
        if(inner[i] == '`'){
            res += "\\`";
            i++;
        } else if(inner[i] == '$' && i + 1 < inner.length() && inner[i+1] == '{'){
            res += "\\${";
            i += 2;
        } else if(inner[i] == '\\' && i + 1 < inner.length() && inner[i+1] == '"'){
            res += "\"";
            i += 2;
        } else if(inner[i] == '{'){
            int depth = 1;
            size_t j = i + 1;
            while(j < inner.length() && depth > 0){
                if(inner[j] == '{') depth++;
                else if(inner[j] == '}') depth--;
                if(depth == 0) break;
                j++;
            }
            if(depth == 0){
                string sub = inner.substr(i+1, j - (i + 1));
                if(sub.find('\n') == string::npos && sub.find('\\') == string::npos && sub.find("element") == string::npos && sub.find("model") == string::npos && sub.find("fn ") == string::npos){
                    string em = "";
                    try {
                        vtt subTokens = Tokenize(sub);
                        subTokens.pb(token{TokenType::EndOfFile, "", 0});
                        Parser subParser(subTokens);
                        Exp* subExp = subParser.parseExp();
                        em = emitExp(subExp, localVars);
                    } catch(...) {
                        em = sub;
                    }
                    res += "${text(" + em + ")}";
                    i = j + 1;
                } else {
                    res += inner[i];
                    i++;
                }
            } else {
                res += inner[i];
                i++;
            }
        } else {
            res += inner[i];
            i++;
        }
    }
    res += "`";
    return res;
}

void extractVars(Exp* e, vs& vars){
    if(!e) return;
    if(auto* ie = dynamic_cast<identExp*>(e)){
        if(!isBuiltin(ie->name)) vars.pb(ie->name);
    } else if(auto* lit = dynamic_cast<LiteralExp*>(e)){
        if(hasInterpolation(lit->literal)){
            string inner = lit->literal.substr(1, lit->literal.length()-2);
            size_t i = 0;
            while(i < inner.length()){
                if(inner[i] == '{'){
                    int depth = 1;
                    size_t j = i + 1;
                    while(j < inner.length() && depth > 0){
                        if(inner[j] == '{') depth++;
                        else if(inner[j] == '}') depth--;
                        if(depth == 0) break;
                        j++;
                    }
                    if(depth == 0){
                        string sub = inner.substr(i+1, j - (i + 1));
                        if(sub.find('\n') == string::npos && sub.find('\\') == string::npos && sub.find("element") == string::npos && sub.find("model") == string::npos && sub.find("fn ") == string::npos){
                            try {
                                vtt subTokens = Tokenize(sub);
                                subTokens.pb(token{TokenType::EndOfFile, "", 0});
                                Parser subParser(subTokens);
                                Exp* subExp = subParser.parseExp();
                                extractVars(subExp, vars);
                            } catch(...) {}
                            i = j + 1;
                        } else {
                            i++;
                        }
                    } else {
                        i++;
                    }
                } else {
                    i++;
                }
            }
        }
    } else if(auto* be = dynamic_cast<binaryExp*>(e)){
        extractVars(be->left, vars);
        extractVars(be->right, vars);
    } else if(auto* ue = dynamic_cast<unaryExp*>(e)){
        extractVars(ue->expr, vars);
    } else if(auto* pe = dynamic_cast<postfixExp*>(e)){
        extractVars(pe->primary, vars);
        for(auto* a : pe->args) extractVars(a, vars);
        for(auto* i : pe->indices) extractVars(i, vars);
    } else if(auto* ife = dynamic_cast<ifExp*>(e)){
        extractVars(ife->cond, vars);
        extractVars(ife->thenBranch, vars);
        extractVars(ife->elseBranch, vars);
    } else if(auto* le = dynamic_cast<listLitExp*>(e)){
        for(auto* it : le->items) extractVars(it, vars);
    } else if(auto* me = dynamic_cast<mapLitExp*>(e)){
        for(auto* entry : me->entries) extractVars(entry->val, vars);
    } else if(auto* lam = dynamic_cast<lambdaExp*>(e)){
        vs lamVars;
        if(auto* be = dynamic_cast<Exp*>(lam->body)){
            extractVars(be, lamVars);
        } else if(auto* blk = dynamic_cast<Block*>(lam->body)){
            auto extractFromStmnt = [&](auto& self, Stmnt* st) -> void {
                if(!st) return;
                if(auto* cs = dynamic_cast<callStmnt*>(st)){
                    extractVars(cs->call, lamVars);
                } else if(auto* ifst = dynamic_cast<ifStmnt*>(st)){
                    extractVars(ifst->cond, lamVars);
                    if(ifst->thenBlock) self(self, ifst->thenBlock);
                    for(auto* eib : ifst->elseIfBlocks) self(self, eib);
                    if(ifst->elseBlock) self(self, ifst->elseBlock);
                } else if(auto* ret = dynamic_cast<returnStmnt*>(st)){
                    extractVars(ret->val, lamVars);
                } else if(auto* as = dynamic_cast<assignStmnt*>(st)){
                    extractVars(as->target, lamVars);
                    extractVars(as->val, lamVars);
                } else if(auto* b = dynamic_cast<Block*>(st)){
                    for(auto* l : b->lines) self(self, l);
                }
            };
            for(auto* l : blk->lines) extractFromStmnt(extractFromStmnt, l);
        }
        for(const auto& v : lamVars){
            bool isParam = false;
            for(const auto& p : lam->params){
                if(p == v){ isParam = true; break; }
            }
            if(!isParam) vars.pb(v);
        }
    }
}

string escapeRawNewlines(const string& s){
    string res = "";
    for(size_t i=0; i<s.length(); i++){
        if(s[i] == '\n') res += "\\n";
        else if(s[i] == '\r') res += "\\r";
        else res += s[i];
    }
    return res;
}

string emitExp(Exp* e, const set<string>* localVars){
    if(!e) return "null";
    if(auto* lit = dynamic_cast<LiteralExp*>(e)){
        if(lit->literal == "none") return "null";
        if(hasInterpolation(lit->literal)){
            return parseInterpolatedString(lit->literal, localVars);
        }
        return escapeRawNewlines(lit->literal);
    }
    if(auto* ie = dynamic_cast<identExp*>(e)){
        if(ie->name == "self") return "this";
        if(isBuiltin(ie->name)) return ie->name;
        if(localVars && localVars->count(ie->name)) return ie->name;
        return "(state." + ie->name + " !== undefined ? state." + ie->name + " : (typeof " + ie->name + " !== \"undefined\" ? " + ie->name + " : undefined))";
    }
    if(auto* be = dynamic_cast<binaryExp*>(e)){
        string op = be->op;
        if(op == "and") op = "&&";
        else if(op == "or") op = "||";
        else if(op == "not") op = "!";
        return "(" + emitExp(be->left, localVars) + " " + op + " " + emitExp(be->right, localVars) + ")";
    }
    if(auto* ue = dynamic_cast<unaryExp*>(e)){
        string op = ue->op;
        if(op == "not") op = "!";
        return "(" + op + " " + emitExp(ue->expr, localVars) + ")";
    }
    if(auto* pe = dynamic_cast<postfixExp*>(e)){
        string res = emitExp(pe->primary, localVars);
        for(size_t i=0; i<pe->members.size(); i++){
            res += "." + pe->members[i];
        }
        if(pe->isCall){
            res += "(";
            for(size_t i=0; i<pe->args.size(); i++){
                if(i>0) res += ", ";
                res += emitExp(pe->args[i], localVars);
            }
            res += ")";
        }
        for(auto* idx : pe->indices){
            res += "[" + emitExp(idx, localVars) + "]";
        }
        return res;
    }
    if(auto* ife = dynamic_cast<ifExp*>(e)){
        return "(" + emitExp(ife->cond, localVars) + " ? " + emitExp(ife->thenBranch, localVars) + " : " + emitExp(ife->elseBranch, localVars) + ")";
    }
    if(auto* le = dynamic_cast<listLitExp*>(e)){
        string res = "[";
        for(size_t i=0; i<le->items.size(); i++){
            if(i>0) res += ", ";
            res += emitExp(le->items[i], localVars);
        }
        res += "]";
        return res;
    }
    if(auto* me = dynamic_cast<mapLitExp*>(e)){
        string res = "{";
        for(size_t i=0; i<me->entries.size(); i++){
            if(i>0) res += ", ";
            res += me->entries[i]->key + ": " + emitExp(me->entries[i]->val, localVars);
        }
        res += "}";
        return res;
    }
    if(auto* lam = dynamic_cast<lambdaExp*>(e)){
        set<string> lamLocals;
        if(localVars) lamLocals = *localVars;
        for(const auto& p : lam->params) lamLocals.insert(p);
        string res = "((";
        for(size_t i=0; i<lam->params.size(); i++){
            if(i>0) res += ", ";
            res += lam->params[i];
        }
        res += ") => { ";
        if(auto* exp = dynamic_cast<Exp*>(lam->body)){
            res += "return " + emitExp(exp, &lamLocals) + ";";
        } else if(auto* blk = dynamic_cast<Block*>(lam->body)){
            ostringstream bss;
            for(auto* l : blk->lines) emitStmnt(l, bss, 4, &lamLocals);
            res += "\n" + bss.str() + "  ";
        } else if(auto* st = dynamic_cast<Stmnt*>(lam->body)){
            ostringstream bss;
            emitStmnt(st, bss, 4, &lamLocals);
            res += "\n" + bss.str() + "  ";
        }
        res += " })";
        return res;
    }
    return "null";
}

void emitStmnt(Stmnt* s, ostringstream& ss, int indent, const set<string>* localVars){
    string ind(indent, ' ');
    if(!s) return;
    if(auto* ls = dynamic_cast<letStmnt*>(s)){
        if(localVars && localVars->count(ls->name)){
            ss << ind << "let " << ls->name << " = " << emitExp(ls->val, localVars) << "; setLocal(\"" << ls->name << "\", " << ls->name << ");\n";
        } else {
            ss << ind << "if (state." << ls->name << " !== undefined) { setVar(\"" << ls->name << "\", " << emitExp(ls->val, localVars) << "); } else { state." << ls->name << " = " << emitExp(ls->val, localVars) << "; }\n";
        }
    } else if(auto* cs = dynamic_cast<constStmnt*>(s)){
        ss << ind << "const " << cs->name << " = " << emitExp(cs->val, localVars) << ";\n";
    } else if(auto* as = dynamic_cast<assignStmnt*>(s)){
        if(auto* ie = dynamic_cast<identExp*>(as->target)){
            if(localVars && localVars->count(ie->name)){
                if(as->op == "="){
                    ss << ind << "setLocal(\"" << ie->name << "\", " << emitExp(as->val, localVars) << "); " << ie->name << " = " << emitExp(as->val, localVars) << ";\n";
                } else {
                    string rawOp = as->op.substr(0, as->op.length()-1);
                    ss << ind << ie->name << " = " << ie->name << " " << rawOp << " " << emitExp(as->val, localVars) << "; setLocal(\"" << ie->name << "\", " << ie->name << ");\n";
                }
            } else {
                if(as->op == "="){
                    ss << ind << "setVar(\"" << ie->name << "\", " << emitExp(as->val, localVars) << ");\n";
                } else {
                    string rawOp = as->op.substr(0, as->op.length()-1);
                    ss << ind << "setVar(\"" << ie->name << "\", (state." << ie->name << " || 0) " << rawOp << " " << emitExp(as->val, localVars) << ");\n";
                }
            }
        } else {
            ss << ind << emitExp(as->target, localVars) << " " << as->op << " " << emitExp(as->val, localVars) << ";\n";
        }
    } else if(auto* is = dynamic_cast<ifStmnt*>(s)){
        ss << ind << "if (" << emitExp(is->cond, localVars) << ") {\n";
        if(is->thenBlock){
            for(auto* l : is->thenBlock->lines) emitStmnt(l, ss, indent+2, localVars);
        }
        ss << ind << "}";
        for(size_t i=0; i<is->elseIfConds.size(); i++){
            ss << " else if (" << emitExp(is->elseIfConds[i], localVars) << ") {\n";
            for(auto* l : is->elseIfBlocks[i]->lines) emitStmnt(l, ss, indent+2, localVars);
            ss << ind << "}";
        }
        if(is->elseBlock){
            ss << " else {\n";
            for(auto* l : is->elseBlock->lines) emitStmnt(l, ss, indent+2, localVars);
            ss << ind << "}";
        }
        ss << "\n";
    } else if(auto* ws = dynamic_cast<whileStmnt*>(s)){
        ss << ind << "while (" << emitExp(ws->cond, localVars) << ") {\n";
        if(ws->block){
            for(auto* l : ws->block->lines) emitStmnt(l, ss, indent+2, localVars);
        }
        ss << ind << "}\n";
    } else if(auto* fn = dynamic_cast<fornor*>(s)){
        set<string> forLocals;
        if(localVars) forLocals = *localVars;
        forLocals.insert(fn->iter);
        ss << ind << "for (let " << fn->iter << " = " << fn->range->st << "; " << fn->iter << " <= " << fn->range->end << "; " << fn->iter << "++) {\n";
        if(fn->block){
            for(auto* l : fn->block->lines) emitStmnt(l, ss, indent+2, &forLocals);
        }
        ss << ind << "}\n";
    } else if(auto* fi = dynamic_cast<forin*>(s)){
        set<string> forLocals;
        if(localVars) forLocals = *localVars;
        forLocals.insert(fi->iter);
        ss << ind << "for (let " << fi->iter << " of (" << emitExp(fi->collcn, localVars) << " || [])) {\n";
        if(fi->block){
            for(auto* l : fi->block->lines) emitStmnt(l, ss, indent+2, &forLocals);
        }
        ss << ind << "}\n";
    } else if(auto* rs = dynamic_cast<returnStmnt*>(s)){
        ss << ind << "return " << (rs->val ? emitExp(rs->val, localVars) : "") << ";\n";
    } else if(auto* ts = dynamic_cast<throwStmnt*>(s)){
        ss << ind << "throw " << emitExp(ts->val, localVars) << ";\n";
    } else if(dynamic_cast<breakStmnt*>(s)){
        ss << ind << "break;\n";
    } else if(dynamic_cast<continueStmnt*>(s)){
        ss << ind << "continue;\n";
    } else if(auto* cs = dynamic_cast<callStmnt*>(s)){
        if(cs->call) ss << ind << emitExp(cs->call, localVars) << ";\n";
    }
}

void emitViewNode(viewNode* vn, const string& parentVar, ostringstream& ss, int& localCounter, int indent=2, const set<string>* localVars=nullptr){
    string ind(indent, ' ');
    if(!vn) return;

    if(auto* tn = dynamic_cast<tagNode*>(vn)){
        string elemVar = "el_" + to_string(++localCounter);
        ss << ind << "const " << elemVar << " = document.createElement(\"" << tn->tag << "\");\n";

        for(auto* attr : tn->attrs){
            string aname = attr->name;
            if(aname.front()=='"' && aname.back()=='"') aname = aname.substr(1, aname.length()-2);

            if(aname.substr(0, 2) == "on"){
                string evt = aname.substr(2);
                string handler = emitExp(attr->val, localVars);
                ss << ind << elemVar << ".addEventListener(\"" << evt << "\", (e) => { ";
                if(dynamic_cast<identExp*>(attr->val)){
                    ss << handler << "(e);";
                } else {
                    ss << "(" << handler << ")(e);";
                }
                ss << " });\n";
            } else if(aname == "bind"){
                string targetVar = "";
                if(auto* ie = dynamic_cast<identExp*>(attr->val)) targetVar = ie->name;
                if(localVars && localVars->count(targetVar)){
                    string lid = "loc_" + to_string(++localCounter);
                    ss << ind << elemVar << ".value = text(" << targetVar << ");\n";
                    ss << ind << elemVar << ".addEventListener(\"input\", (e) => { setLocal(\"" << targetVar << "\", e.target.value); " << targetVar << " = e.target.value; });\n";
                    ss << ind << "regLocalNode(\"" << lid << "\", [\"" << targetVar << "\"], (el) => { el.value = text(localState." << targetVar << " !== undefined ? localState." << targetVar << " : " << targetVar << "); }, " << elemVar << ");\n";
                } else {
                    string gid = "ttv_g_" + to_string(++globalNodeCounter);
                    ss << ind << elemVar << ".id = \"" << gid << "\";\n";
                    ss << ind << elemVar << ".value = text(" << emitExp(attr->val, localVars) << ");\n";
                    ss << ind << elemVar << ".addEventListener(\"input\", (e) => { setVar(\"" << targetVar << "\", e.target.value); });\n";
                    ss << ind << "regNode(\"" << gid << "\", [\"" << targetVar << "\"], (el) => { el.value = text(state." << targetVar << "); });\n";
                }
            } else {
                vs allVars;
                extractVars(attr->val, allVars);
                vs localDeps, globalDeps;
                for(const auto& v : allVars){
                    if(isBuiltin(v)) continue;
                    if(localVars && localVars->count(v)) localDeps.pb(v);
                    else globalDeps.pb(v);
                }

                if(aname == "html"){
                    ss << ind << elemVar << ".innerHTML = text(" << emitExp(attr->val, localVars) << ");\n";
                } else if(aname == "class"){
                    ss << ind << elemVar << ".className = toClass(" << emitExp(attr->val, localVars) << ");\n";
                } else {
                    ss << ind << elemVar << ".setAttribute(\"" << aname << "\", text(" << emitExp(attr->val, localVars) << "));\n";
                }

                if(tn->tag == "a" && aname == "href"){
                    ss << ind << elemVar << ".addEventListener(\"click\", (e) => { const h = text(" << emitExp(attr->val, localVars) << "); if (h.startsWith(\"/\")) { e.preventDefault(); go(h); } });\n";
                }

                string applyExpr;
                if(aname == "html") applyExpr = "el.innerHTML = text(" + emitExp(attr->val, localVars) + ");";
                else if(aname == "class") applyExpr = "el.className = toClass(" + emitExp(attr->val, localVars) + ");";
                else applyExpr = "el.setAttribute(\"" + aname + "\", text(" + emitExp(attr->val, localVars) + "));";

                if(!localDeps.empty()){
                    string lid = "loc_" + to_string(++localCounter);
                    ss << ind << "regLocalNode(\"" << lid << "\", [";
                    for(size_t i=0; i<localDeps.size(); i++){
                        if(i>0) ss << ", ";
                        ss << "\"" << localDeps[i] << "\"";
                    }
                    ss << "], (el) => { " << applyExpr << " }, " << elemVar << ");\n";
                }
                if(!globalDeps.empty()){
                    string gid = "ttv_g_" + to_string(++globalNodeCounter);
                    ss << ind << elemVar << ".id = \"" << gid << "\";\n";
                    ss << ind << "regNode(\"" << gid << "\", [";
                    for(size_t i=0; i<globalDeps.size(); i++){
                        if(i>0) ss << ", ";
                        ss << "\"" << globalDeps[i] << "\"";
                    }
                    ss << "], (el) => { " << applyExpr << " });\n";
                }
            }
        }

        for(auto* child : tn->children){
            emitViewNode(child, elemVar, ss, localCounter, indent, localVars);
        }

        ss << ind << parentVar << ".appendChild(" << elemVar << ");\n";
        return;
    }

    if(auto* txt = dynamic_cast<textNode*>(vn)){
        if(hasInterpolation(txt->text)){
            LiteralExp lit; lit.literal = txt->text;
            vs allVars;
            extractVars(&lit, allVars);
            vs localDeps, globalDeps;
            for(const auto& v : allVars){
                if(isBuiltin(v)) continue;
                if(localVars && localVars->count(v)) localDeps.pb(v);
                else globalDeps.pb(v);
            }
            string spanVar = "sp_" + to_string(++localCounter);
            ss << ind << "const " << spanVar << " = document.createElement(\"span\");\n";
            ss << ind << spanVar << ".textContent = text(" << parseInterpolatedString(txt->text, localVars) << ");\n";
            if(!localDeps.empty()){
                string lid = "loc_" + to_string(++localCounter);
                ss << ind << "regLocalNode(\"" << lid << "\", [";
                for(size_t i=0; i<localDeps.size(); i++){
                    if(i>0) ss << ", ";
                    ss << "\"" << localDeps[i] << "\"";
                }
                ss << "], (el) => { el.textContent = text(" << parseInterpolatedString(txt->text, localVars) << "); }, " << spanVar << ");\n";
            }
            if(!globalDeps.empty()){
                string gid = "ttv_g_" + to_string(++globalNodeCounter);
                ss << ind << spanVar << ".id = \"" << gid << "\";\n";
                ss << ind << "regNode(\"" << gid << "\", [";
                for(size_t i=0; i<globalDeps.size(); i++){
                    if(i>0) ss << ", ";
                    ss << "\"" << globalDeps[i] << "\"";
                }
                ss << "], (el) => { el.textContent = text(" << parseInterpolatedString(txt->text, localVars) << "); });\n";
            }
            ss << ind << parentVar << ".appendChild(" << spanVar << ");\n";
        } else {
            ss << ind << parentVar << ".appendChild(document.createTextNode(" << escapeRawNewlines(txt->text) << "));\n";
        }
        return;
    }

    if(auto* sn = dynamic_cast<showNode*>(vn)){
        string spanVar = "sp_" + to_string(++localCounter);
        ss << ind << "const " << spanVar << " = document.createElement(\"span\");\n";
        ss << ind << spanVar << ".textContent = text(" << emitExp(sn->val, localVars) << ");\n";
        vs allVars;
        extractVars(sn->val, allVars);
        vs localDeps, globalDeps;
        for(const auto& v : allVars){
            if(isBuiltin(v)) continue;
            if(localVars && localVars->count(v)) localDeps.pb(v);
            else globalDeps.pb(v);
        }
        if(!localDeps.empty()){
            string lid = "loc_" + to_string(++localCounter);
            ss << ind << "regLocalNode(\"" << lid << "\", [";
            for(size_t i=0; i<localDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << localDeps[i] << "\"";
            }
            ss << "], (el) => { el.textContent = text(" << emitExp(sn->val, localVars) << "); }, " << spanVar << ");\n";
        }
        if(!globalDeps.empty()){
            string gid = "ttv_g_" + to_string(++globalNodeCounter);
            ss << ind << spanVar << ".id = \"" << gid << "\";\n";
            ss << ind << "regNode(\"" << gid << "\", [";
            for(size_t i=0; i<globalDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << globalDeps[i] << "\"";
            }
            ss << "], (el) => { el.textContent = text(" << emitExp(sn->val, localVars) << "); });\n";
        }
        ss << ind << parentVar << ".appendChild(" << spanVar << ");\n";
        return;
    }

    if(auto* un = dynamic_cast<useNode*>(vn)){
        ss << ind << "render_" << un->name << "({";
        for(size_t i=0; i<un->args.size(); i++){
            if(i>0) ss << ", ";
            ss << un->args[i]->name << ": " << emitExp(un->args[i]->val, localVars);
        }
        ss << "}, " << parentVar << ");\n";
        return;
    }

    if(auto* iv = dynamic_cast<ifViewNode*>(vn)){
        string ifContainer = "ifBox_" + to_string(++localCounter);
        ss << ind << "const " << ifContainer << " = document.createElement(\"div\");\n";
        ss << ind << ifContainer << ".style.display = \"contents\";\n";
        ss << ind << "const update_" << ifContainer << " = (box) => {\n";
        ss << ind << "  box.innerHTML = \"\";\n";
        ss << ind << "  if (" << emitExp(iv->cond, localVars) << ") {\n";
        for(auto* c : iv->thenNodes) emitViewNode(c, "box", ss, localCounter, indent+4, localVars);
        ss << ind << "  } else {\n";
        for(auto* c : iv->elseNodes) emitViewNode(c, "box", ss, localCounter, indent+4, localVars);
        ss << ind << "  }\n";
        ss << ind << "};\n";
        ss << ind << "update_" << ifContainer << "(" << ifContainer << ");\n";

        vs allVars;
        extractVars(iv->cond, allVars);
        vs localDeps, globalDeps;
        for(const auto& v : allVars){
            if(isBuiltin(v)) continue;
            if(localVars && localVars->count(v)) localDeps.pb(v);
            else globalDeps.pb(v);
        }
        if(!localDeps.empty()){
            string lid = "loc_" + to_string(++localCounter);
            ss << ind << "regLocalNode(\"" << lid << "\", [";
            for(size_t i=0; i<localDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << localDeps[i] << "\"";
            }
            ss << "], update_" << ifContainer << ", " << ifContainer << ");\n";
        }
        if(!globalDeps.empty()){
            string gid = "ttv_g_" + to_string(++globalNodeCounter);
            ss << ind << ifContainer << ".id = \"" << gid << "\";\n";
            ss << ind << "regNode(\"" << gid << "\", [";
            for(size_t i=0; i<globalDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << globalDeps[i] << "\"";
            }
            ss << "], update_" << ifContainer << ");\n";
        }
        ss << ind << parentVar << ".appendChild(" << ifContainer << ");\n";
        return;
    }

    if(auto* fv = dynamic_cast<forViewNode*>(vn)){
        string forContainer = "forBox_" + to_string(++localCounter);
        ss << ind << "const " << forContainer << " = document.createElement(\"div\");\n";
        ss << ind << forContainer << ".style.display = \"contents\";\n";
        ss << ind << "const update_" << forContainer << " = (box) => {\n";
        ss << ind << "  box.innerHTML = \"\";\n";
        ss << ind << "  const items = " << emitExp(fv->collcn, localVars) << " || [];\n";
        ss << ind << "  for (let " << fv->iter << " of items) {\n";
        set<string> forLocals;
        if(localVars) forLocals = *localVars;
        forLocals.insert(fv->iter);
        if(!fv->index.empty()) forLocals.insert(fv->index);
        for(auto* c : fv->children) emitViewNode(c, "box", ss, localCounter, indent+4, &forLocals);
        ss << ind << "  }\n";
        ss << ind << "};\n";
        ss << ind << "update_" << forContainer << "(" << forContainer << ");\n";

        vs allVars;
        extractVars(fv->collcn, allVars);
        vs localDeps, globalDeps;
        for(const auto& v : allVars){
            if(isBuiltin(v)) continue;
            if(localVars && localVars->count(v)) localDeps.pb(v);
            else globalDeps.pb(v);
        }
        if(!localDeps.empty()){
            string lid = "loc_" + to_string(++localCounter);
            ss << ind << "regLocalNode(\"" << lid << "\", [";
            for(size_t i=0; i<localDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << localDeps[i] << "\"";
            }
            ss << "], update_" << forContainer << ", " << forContainer << ");\n";
        }
        if(!globalDeps.empty()){
            string gid = "ttv_g_" + to_string(++globalNodeCounter);
            ss << ind << forContainer << ".id = \"" << gid << "\";\n";
            ss << ind << "regNode(\"" << gid << "\", [";
            for(size_t i=0; i<globalDeps.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << globalDeps[i] << "\"";
            }
            ss << "], update_" << forContainer << ");\n";
        }
        ss << ind << parentVar << ".appendChild(" << forContainer << ");\n";
        return;
    }

    if(dynamic_cast<slotNode*>(vn)){
        ss << ind << "if (typeof slotFn === \"function\") slotFn(" << parentVar << ");\n";
        return;
    }
}

void emitElement(elementDecl* ed, ostringstream& ss){
    set<string> localVars;
    for(auto* p : ed->params) localVars.insert(p->name);
    for(auto* it : ed->items){
        if(auto* ls = dynamic_cast<letStmnt*>(it)) localVars.insert(ls->name);
        if(auto* cs = dynamic_cast<constStmnt*>(it)) localVars.insert(cs->name);
    }

    ss << "function render_" << ed->name << "(params = {}, parentEl) {\n";
    ss << "  let localNodeCounter = 0;\n";
    ss << "  const localState = {};\n";
    ss << "  const localMap = {};\n";
    ss << "  const localRenderers = {};\n";
    ss << "  const localNodes = {};\n";
    ss << "  function setLocal(k, v) {\n";
    ss << "    localState[k] = v;\n";
    ss << "    if (localMap[k]) {\n";
    ss << "      for (const lid of localMap[k]) {\n";
    ss << "        const el = localNodes[lid];\n";
    ss << "        if (el && localRenderers[lid]) localRenderers[lid](el);\n";
    ss << "      }\n";
    ss << "    }\n";
    ss << "  }\n";
    ss << "  function regLocalNode(lid, varNames, renderer, el) {\n";
    ss << "    localNodes[lid] = el;\n";
    ss << "    localRenderers[lid] = renderer;\n";
    ss << "    for (const v of varNames) {\n";
    ss << "      if (!localMap[v]) localMap[v] = [];\n";
    ss << "      if (!localMap[v].includes(lid)) localMap[v].push(lid);\n";
    ss << "    }\n";
    ss << "  }\n\n";

    for(auto* p : ed->params){
        ss << "  let " << p->name << " = params." << p->name << " !== undefined ? params." << p->name << " : " << (p->defaultVal ? emitExp(p->defaultVal, &localVars) : "null") << ";\n";
        ss << "  localState[\"" << p->name << "\"] = " << p->name << ";\n";
    }

    for(auto* it : ed->items){
        if(auto* ls = dynamic_cast<letStmnt*>(it)){
            ss << "  let " << ls->name << " = " << emitExp(ls->val, &localVars) << ";\n";
            ss << "  localState[\"" << ls->name << "\"] = " << ls->name << ";\n";
        } else if(auto* cs = dynamic_cast<constStmnt*>(it)){
            ss << "  const " << cs->name << " = " << emitExp(cs->val, &localVars) << ";\n";
            ss << "  localState[\"" << cs->name << "\"] = " << cs->name << ";\n";
        } else if(auto* fd = dynamic_cast<fnDecl*>(it)){
            ss << "  function " << fd->name << "(";
            for(size_t i=0; i<fd->params.size(); i++){
                if(i>0) ss << ", ";
                ss << fd->params[i]->name;
            }
            ss << ") {\n";
            if(fd->body){
                for(auto* l : fd->body->lines) emitStmnt(l, ss, 4, &localVars);
            }
            ss << "  }\n";
        } else if(auto* dd = dynamic_cast<derivedDecl*>(it)){
            vs vars;
            extractVars(dd->val, vars);
            ss << "  regDerived(\"" << dd->name << "\", [";
            for(size_t i=0; i<vars.size(); i++){
                if(i>0) ss << ", ";
                ss << "\"" << vars[i] << "\"";
            }
            ss << "], () => (" << emitExp(dd->val, &localVars) << "));\n";
        } else if(auto* hd = dynamic_cast<hookDecl*>(it)){
            if(hd->type == "mount"){
                ss << "  setTimeout(() => {\n";
                if(hd->body){
                    for(auto* l : hd->body->lines) emitStmnt(l, ss, 4, &localVars);
                }
                ss << "  }, 0);\n";
            }
        }
    }

    int localCounter = 0;
    for(auto* it : ed->items){
        if(auto* vb = dynamic_cast<viewBlock*>(it)){
            for(auto* vn : vb->nodes){
                emitViewNode(vn, "parentEl", ss, localCounter, 2, &localVars);
            }
        }
    }
    ss << "}\n\n";
}

void emitPage(pageDecl* pd, ostringstream& ss, int pageIdx){
    set<string> localVars;
    for(auto* it : pd->items){
        if(auto* ls = dynamic_cast<letStmnt*>(it)) localVars.insert(ls->name);
        if(auto* cs = dynamic_cast<constStmnt*>(it)) localVars.insert(cs->name);
    }

    string funcName = "render_Page_" + to_string(pageIdx);
    ss << "function " << funcName << "(parentEl) {\n";
    ss << "  let localNodeCounter = 0;\n";
    ss << "  const localState = {};\n";
    ss << "  const localMap = {};\n";
    ss << "  const localRenderers = {};\n";
    ss << "  const localNodes = {};\n";
    ss << "  function setLocal(k, v) {\n";
    ss << "    localState[k] = v;\n";
    ss << "    if (localMap[k]) {\n";
    ss << "      for (const lid of localMap[k]) {\n";
    ss << "        const el = localNodes[lid];\n";
    ss << "        if (el && localRenderers[lid]) localRenderers[lid](el);\n";
    ss << "      }\n";
    ss << "    }\n";
    ss << "  }\n";
    ss << "  function regLocalNode(lid, varNames, renderer, el) {\n";
    ss << "    localNodes[lid] = el;\n";
    ss << "    localRenderers[lid] = renderer;\n";
    ss << "    for (const v of varNames) {\n";
    ss << "      if (!localMap[v]) localMap[v] = [];\n";
    ss << "      if (!localMap[v].includes(lid)) localMap[v].push(lid);\n";
    ss << "    }\n";
    ss << "  }\n\n";

    int localCounter = 0;
    for(auto* it : pd->items){
        if(auto* ls = dynamic_cast<letStmnt*>(it)){
            ss << "  let " << ls->name << " = " << emitExp(ls->val, &localVars) << ";\n";
            ss << "  localState[\"" << ls->name << "\"] = " << ls->name << ";\n";
        } else if(auto* cs = dynamic_cast<constStmnt*>(it)){
            ss << "  const " << cs->name << " = " << emitExp(cs->val, &localVars) << ";\n";
            ss << "  localState[\"" << cs->name << "\"] = " << cs->name << ";\n";
        } else if(auto* fd = dynamic_cast<fnDecl*>(it)){
            ss << "  function " << fd->name << "() {\n";
            if(fd->body){
                for(auto* l : fd->body->lines) emitStmnt(l, ss, 4, &localVars);
            }
            ss << "  }\n";
        } else if(auto* dd = dynamic_cast<derivedDecl*>(it)){
            if(dd->name == "__doctitle__"){
                ss << "  document.title = text(" << emitExp(dd->val, &localVars) << ");\n";
            }
        } else if(auto* hd = dynamic_cast<hookDecl*>(it)){
            if(hd->type == "mount"){
                ss << "  setTimeout(() => {\n";
                if(hd->body){
                    for(auto* l : hd->body->lines) emitStmnt(l, ss, 4, &localVars);
                }
                ss << "  }, 0);\n";
            }
        } else if(auto* vb = dynamic_cast<viewBlock*>(it)){
            for(auto* vn : vb->nodes) emitViewNode(vn, "parentEl", ss, localCounter, 2, &localVars);
        } else if(auto* vn = dynamic_cast<viewNode*>(it)){
            emitViewNode(vn, "parentEl", ss, localCounter, 2, &localVars);
        }
    }
    ss << "}\n\n";
}

void emitHtml(Program& p, const string& path="index.html"){
    string title = "Tattva App";
    string lang = "en";
    vs scripts;
    if(p.appIdx >= 0){
        auto* app = dynamic_cast<appDecl*>(p.prog[p.appIdx]);
        if(app){
            for(auto* e : app->configs){
                if(e->key == "name" || e->key == "title"){
                    if(auto* lit = dynamic_cast<LiteralExp*>(e->val)){
                        title = lit->literal;
                        if(title.length()>=2 && title.front()=='"' && title.back()=='"') title = title.substr(1, title.length()-2);
                    }
                }
                if(e->key == "lang"){
                    if(auto* lit = dynamic_cast<LiteralExp*>(e->val)){
                        lang = lit->literal;
                        if(lang.length()>=2 && lang.front()=='"' && lang.back()=='"') lang = lang.substr(1, lang.length()-2);
                    }
                }
            }
        }
    }
    for(auto* node : p.prog){
        if(auto* sc = dynamic_cast<scriptDecl*>(node)){
            string url = sc->url;
            if(url.length()>=2 && url.front()=='"' && url.back()=='"') url = url.substr(1, url.length()-2);
            scripts.pb(url);
        }
    }

    ofstream f(path);
    f << "<!DOCTYPE html>\n";
    f << "<html lang=\"" << lang << "\">\n";
    f << "<head>\n";
    f << "  <meta charset=\"UTF-8\">\n";
    f << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    f << "  <title>" << title << "</title>\n";
    f << "  <link rel=\"stylesheet\" href=\"style.css\">\n";
    for(auto& s : scripts){
        f << "  <script src=\"" << s << "\"></script>\n";
    }
    f << "</head>\n";
    f << "<body>\n";
    f << "  <div id=\"app\"></div>\n";
    f << "  <script src=\"app.js\"></script>\n";
    f << "</body>\n";
    f << "</html>\n";
    f.close();
}

void emitCss(Program& p, const string& path="style.css"){
    ofstream f(path);
    auto gatherCss = [&](auto& self, ASTNode* node) -> void {
        if(!node) return;
        if(auto* sb = dynamic_cast<styleBlock*>(node)){
            f << sb->css << "\n";
        }
        if(auto* ed = dynamic_cast<elementDecl*>(node)){
            for(auto* it : ed->items) self(self, it);
        }
        if(auto* pd = dynamic_cast<pageDecl*>(node)){
            for(auto* it : pd->items) self(self, it);
        }
        if(auto* ld = dynamic_cast<layoutDecl*>(node)){
            for(auto* it : ld->items) self(self, it);
        }
    };
    for(auto* n : p.prog){
        gatherCss(gatherCss, n);
    }
    f.close();
}

void emitJs(Program& p, const string& path="app.js"){
    globalNodeCounter = 0;
    bool useHash = false;
    if(p.appIdx >= 0){
        auto* app = dynamic_cast<appDecl*>(p.prog[p.appIdx]);
        if(app){
            for(auto* e : app->configs){
                if(e->key == "router"){
                    if(auto* lit = dynamic_cast<LiteralExp*>(e->val)){
                        string rval = lit->literal;
                        if(rval.length()>=2 && rval.front()=='"' && rval.back()=='"') rval = rval.substr(1, rval.length()-2);
                        if(rval == "hash") useHash = true;
                    }
                }
            }
        }
    }

    ostringstream ss;
    ss << "let gNodeId = 0;\n";
    ss << "const state = {};\n";
    ss << "const varMap = {};\n";
    ss << "const derivedDeps = {};\n";
    ss << "const derivedMap = {};\n";
    ss << "const nodeRenderers = {};\n";
    ss << "const persistKeys = {};\n\n";

    ss << "function regNode(id, varNames, renderer) {\n";
    ss << "  nodeRenderers[id] = renderer;\n";
    ss << "  for (const v of varNames) {\n";
    ss << "    if (!varMap[v]) varMap[v] = [];\n";
    ss << "    if (!varMap[v].includes(id)) varMap[v].push(id);\n";
    ss << "  }\n";
    ss << "}\n\n";

    ss << "function regDerived(dName, deps, computeFn) {\n";
    ss << "  derivedMap[dName] = computeFn;\n";
    ss << "  for (const dep of deps) {\n";
    ss << "    if (!derivedDeps[dep]) derivedDeps[dep] = [];\n";
    ss << "    if (!derivedDeps[dep].includes(dName)) derivedDeps[dep].push(dName);\n";
    ss << "  }\n";
    ss << "  try {\n";
    ss << "    state[dName] = computeFn();\n";
    ss << "  } catch(e) {\n";
    ss << "    state[dName] = null;\n";
    ss << "  }\n";
    ss << "}\n\n";

    ss << "function updateVarDependents(name, visited = new Set()) {\n";
    ss << "  if (visited.has(name)) return;\n";
    ss << "  visited.add(name);\n";
    ss << "  if (derivedDeps[name]) {\n";
    ss << "    for (const d of derivedDeps[name]) {\n";
    ss << "      if (derivedMap[d]) {\n";
    ss << "        try { state[d] = derivedMap[d](); } catch(e) {}\n";
    ss << "        updateVarDependents(d, visited);\n";
    ss << "      }\n";
    ss << "    }\n";
    ss << "  }\n";
    ss << "  if (varMap[name]) {\n";
    ss << "    const activeIds = [];\n";
    ss << "    for (const id of varMap[name]) {\n";
    ss << "      const el = document.getElementById(id);\n";
    ss << "      if (el) {\n";
    ss << "        activeIds.push(id);\n";
    ss << "        if (nodeRenderers[id]) nodeRenderers[id](el);\n";
    ss << "      } else {\n";
    ss << "        delete nodeRenderers[id];\n";
    ss << "      }\n";
    ss << "    }\n";
    ss << "    varMap[name] = activeIds;\n";
    ss << "  }\n";
    ss << "}\n\n";

    ss << "function setVar(name, val) {\n";
    ss << "  state[name] = val;\n";
    ss << "  if (persistKeys[name] && typeof localStorage !== \"undefined\") {\n";
    ss << "    try { localStorage.setItem(name, JSON.stringify(val)); } catch(e) {}\n";
    ss << "  }\n";
    ss << "  updateVarDependents(name);\n";
    ss << "}\n\n";

    ss << "function text(v) { return (v === null || v === undefined) ? \"\" : String(v); }\n";
    ss << "function num(v) { return Number(v) || 0; }\n";
    ss << "function len(v) { return v ? (v.length !== undefined ? v.length : Object.keys(v).length) : 0; }\n";
    ss << "function toClass(v) { if (Array.isArray(v)) return v.flat().filter(Boolean).join(\" \"); return text(v); }\n";
    ss << "function range(st, end) { const r = []; for (let i = st; i <= end; i++) r.push(i); return r; }\n";
    ss << "function push(arr, item, v) { arr.push(item); if (v) setVar(v, arr); }\n";
    ss << "function pop(arr, v) { const r = arr.pop(); if (v) setVar(v, arr); return r; }\n";
    ss << "function insert(arr, i, item, v) { arr.splice(i, 0, item); if (v) setVar(v, arr); }\n";
    ss << "function removeAt(arr, i, v) { const r = arr.splice(i, 1); if (v) setVar(v, arr); return r; }\n";
    ss << "function clear(arr, v) { arr.length = 0; if (v) setVar(v, arr); }\n\n";

    ss << "function createModel(name) {\n";
    ss << "  let nextId = 1;\n";
    ss << "  const records = [];\n";
    ss << "  const model = {\n";
    ss << "    get all() { return records.slice(); },\n";
    ss << "    get count() { return records.length; },\n";
    ss << "    find(id) {\n";
    ss << "      return records.find(r => r.id == id) || null;\n";
    ss << "    },\n";
    ss << "    where(fn) {\n";
    ss << "      return records.filter(fn);\n";
    ss << "    },\n";
    ss << "    create(data) {\n";
    ss << "      const recId = (data && data.id !== undefined) ? Number(data.id) : nextId++;\n";
    ss << "      if (recId >= nextId) nextId = recId + 1;\n";
    ss << "      const rec = { ...data, id: recId };\n";
    ss << "      rec.delete = function() { model.delete(rec.id); };\n";
    ss << "      const proxy = new Proxy(rec, {\n";
    ss << "        set(target, prop, value) {\n";
    ss << "          target[prop] = value;\n";
    ss << "          model._notify();\n";
    ss << "          return true;\n";
    ss << "        }\n";
    ss << "      });\n";
    ss << "      records.push(proxy);\n";
    ss << "      model._notify();\n";
    ss << "      return proxy;\n";
    ss << "    },\n";
    ss << "    update(id, data) {\n";
    ss << "      const rec = records.find(r => r.id == id);\n";
    ss << "      if (rec) {\n";
    ss << "        Object.assign(rec, data);\n";
    ss << "        model._notify();\n";
    ss << "        return rec;\n";
    ss << "      }\n";
    ss << "      return null;\n";
    ss << "    },\n";
    ss << "    delete(id) {\n";
    ss << "      const idx = records.findIndex(r => r.id == id);\n";
    ss << "      if (idx !== -1) {\n";
    ss << "        records.splice(idx, 1);\n";
    ss << "        model._notify();\n";
    ss << "      }\n";
    ss << "    },\n";
    ss << "    clear() {\n";
    ss << "      records.length = 0;\n";
    ss << "      model._notify();\n";
    ss << "    },\n";
    ss << "    _notify() {\n";
    ss << "      updateVarDependents(name);\n";
    ss << "    }\n";
    ss << "  };\n";
    ss << "  return model;\n";
    ss << "}\n\n";

    ss << "const isHashRouter = " << (useHash ? "true" : "false") << ";\n";
    ss << "function getRoutePath() {\n";
    ss << "  if (typeof window === \"undefined\") return \"/\";\n";
    ss << "  if (isHashRouter || window.location.protocol === \"file:\") {\n";
    ss << "    const h = (window.location.hash || \"\").replace(/^#/, \"\");\n";
    ss << "    return h ? (h.startsWith(\"/\") ? h : \"/\" + h) : \"/\";\n";
    ss << "  }\n";
    ss << "  return window.location.pathname || \"/\";\n";
    ss << "}\n\n";

    ss << "const route = {\n";
    ss << "  path: getRoutePath(),\n";
    ss << "  params: {},\n";
    ss << "  query: {},\n";
    ss << "  hash: (typeof window !== \"undefined\" && window.location.hash) ? window.location.hash : \"\"\n";
    ss << "};\n\n";

    ss << "function go(path, replace = false) {\n";
    ss << "  if (typeof window === \"undefined\") return;\n";
    ss << "  if (isHashRouter || window.location.protocol === \"file:\") {\n";
    ss << "    const hashTarget = \"#\" + (path.startsWith(\"/\") ? path : \"/\" + path);\n";
    ss << "    if (replace) history.replaceState(null, \"\", hashTarget);\n";
    ss << "    else window.location.hash = hashTarget;\n";
    ss << "  } else {\n";
    ss << "    if (replace) history.replaceState(null, \"\", path);\n";
    ss << "    else history.pushState(null, \"\", path);\n";
    ss << "  }\n";
    ss << "  route.path = getRoutePath();\n";
    ss << "  setVar(\"route\", route);\n";
    ss << "  renderApp();\n";
    ss << "}\n\n";

    ss << "function back() { if (typeof history !== \"undefined\") history.back(); }\n";
    ss << "if (typeof window !== \"undefined\") {\n";
    ss << "  window.addEventListener(\"popstate\", () => {\n";
    ss << "    route.path = getRoutePath();\n";
    ss << "    setVar(\"route\", route);\n";
    ss << "    renderApp();\n";
    ss << "  });\n";
    ss << "  window.addEventListener(\"hashchange\", () => {\n";
    ss << "    route.path = getRoutePath();\n";
    ss << "    setVar(\"route\", route);\n";
    ss << "    renderApp();\n";
    ss << "  });\n";
    ss << "}\n\n";

    for(auto* n : p.prog){
        if(auto* md = dynamic_cast<modelDecl*>(n)){
            ss << "const " << md->name << " = createModel(\"" << md->name << "\");\n";
            ss << "state[\"" << md->name << "\"] = " << md->name << ";\n";
        }
    }
    ss << "\n";

    for(auto* n : p.prog){
        if(auto* gd = dynamic_cast<globalDecl*>(n)){
            if(gd->persist){
                ss << "persistKeys[\"" << gd->name << "\"] = true;\n";
                ss << "state[\"" << gd->name << "\"] = (typeof localStorage !== \"undefined\" && localStorage.getItem(\"" << gd->name << "\")) ? JSON.parse(localStorage.getItem(\"" << gd->name << "\")) : " << emitExp(gd->val) << ";\n";
            } else {
                ss << "state[\"" << gd->name << "\"] = " << emitExp(gd->val) << ";\n";
            }
        } else if(auto* cs = dynamic_cast<constStmnt*>(n)){
            ss << "const " << cs->name << " = " << emitExp(cs->val) << ";\n";
        } else if(auto* ls = dynamic_cast<letStmnt*>(n)){
            ss << "state[\"" << ls->name << "\"] = " << emitExp(ls->val) << ";\n";
        } else if(auto* dd = dynamic_cast<derivedDecl*>(n)){
            if(dd->name != "__doctitle__"){
                vs vars;
                extractVars(dd->val, vars);
                ss << "regDerived(\"" << dd->name << "\", [";
                for(size_t i=0; i<vars.size(); i++){
                    if(i>0) ss << ", ";
                    ss << "\"" << vars[i] << "\"";
                }
                ss << "], () => (" << emitExp(dd->val) << "));\n";
            }
        } else if(auto* fd = dynamic_cast<fnDecl*>(n)){
            ss << "function " << fd->name << "(";
            for(size_t i=0; i<fd->params.size(); i++){
                if(i>0) ss << ", ";
                ss << fd->params[i]->name;
            }
            ss << ") {\n";
            if(fd->body){
                for(auto* l : fd->body->lines) emitStmnt(l, ss, 2);
            }
            ss << "}\n\n";
        } else if(auto* jb = dynamic_cast<jsBlock*>(n)){
            ss << jb->js << "\n\n";
        }
    }
    ss << "\n";

    for(auto* n : p.prog){
        if(auto* ed = dynamic_cast<elementDecl*>(n)){
            emitElement(ed, ss);
        }
    }

    int pIdx = 0;
    vector<pair<string, string>> routes;
    int layoutIdx = -1;

    for(size_t i=0; i<p.prog.size(); i++){
        if(auto* pd = dynamic_cast<pageDecl*>(p.prog[i])){
            string path = pd->path;
            if(path.length()>=2 && path.front()=='"' && path.back()=='"') path = path.substr(1, path.length()-2);
            string funcName = "render_Page_" + to_string(pIdx);
            routes.pb({path, funcName});
            emitPage(pd, ss, pIdx);
            pIdx++;
        } else if(dynamic_cast<layoutDecl*>(p.prog[i])){
            layoutIdx = i;
        }
    }

    if(layoutIdx >= 0){
        auto* ld = dynamic_cast<layoutDecl*>(p.prog[layoutIdx]);
        set<string> localVars;
        for(auto* it : ld->items){
            if(auto* ls = dynamic_cast<letStmnt*>(it)) localVars.insert(ls->name);
            if(auto* cs = dynamic_cast<constStmnt*>(it)) localVars.insert(cs->name);
        }
        ss << "function render_Layout(slotFn, parentEl) {\n";
        ss << "  let localNodeCounter = 0;\n";
        ss << "  const localState = {};\n";
        ss << "  const localMap = {};\n";
        ss << "  const localRenderers = {};\n";
        ss << "  const localNodes = {};\n";
        ss << "  function setLocal(k, v) {\n";
        ss << "    localState[k] = v;\n";
        ss << "    if (localMap[k]) {\n";
        ss << "      for (const lid of localMap[k]) {\n";
        ss << "        const el = localNodes[lid];\n";
        ss << "        if (el && localRenderers[lid]) localRenderers[lid](el);\n";
        ss << "      }\n";
        ss << "    }\n";
        ss << "  }\n";
        ss << "  function regLocalNode(lid, varNames, renderer, el) {\n";
        ss << "    localNodes[lid] = el;\n";
        ss << "    localRenderers[lid] = renderer;\n";
        ss << "    for (const v of varNames) {\n";
        ss << "      if (!localMap[v]) localMap[v] = [];\n";
        ss << "      if (!localMap[v].includes(lid)) localMap[v].push(lid);\n";
        ss << "    }\n";
        ss << "  }\n\n";

        for(auto* it : ld->items){
            if(auto* ls = dynamic_cast<letStmnt*>(it)){
                ss << "  let " << ls->name << " = " << emitExp(ls->val, &localVars) << ";\n";
                ss << "  localState[\"" << ls->name << "\"] = " << ls->name << ";\n";
            } else if(auto* cs = dynamic_cast<constStmnt*>(it)){
                ss << "  const " << cs->name << " = " << emitExp(cs->val, &localVars) << ";\n";
                ss << "  localState[\"" << cs->name << "\"] = " << cs->name << ";\n";
            } else if(auto* hd = dynamic_cast<hookDecl*>(it)){
                if(hd->type == "mount"){
                    ss << "  setTimeout(() => {\n";
                    if(hd->body){
                        for(auto* l : hd->body->lines) emitStmnt(l, ss, 4, &localVars);
                    }
                    ss << "  }, 0);\n";
                }
            }
        }
        int localCounter = 0;
        for(auto* it : ld->items){
            if(auto* vb = dynamic_cast<viewBlock*>(it)){
                for(auto* vn : vb->nodes) emitViewNode(vn, "parentEl", ss, localCounter, 2, &localVars);
            } else if(auto* vn = dynamic_cast<viewNode*>(it)){
                emitViewNode(vn, "parentEl", ss, localCounter, 2, &localVars);
            }
        }
        ss << "}\n\n";
    }

    ss << "function renderApp() {\n";
    ss << "  const appEl = document.getElementById(\"app\");\n";
    ss << "  if (!appEl) return;\n";
    ss << "  appEl.innerHTML = \"\";\n";
    ss << "  const curPath = route.path || \"/\";\n";

    for(size_t i=0; i<routes.size(); i++){
        ss << "  " << (i>0 ? "else if" : "if") << " (curPath === \"" << routes[i].first << "\") {\n";
        if(layoutIdx >= 0){
            ss << "    render_Layout((slotEl) => { " << routes[i].second << "(slotEl); }, appEl);\n";
        } else {
            ss << "    " << routes[i].second << "(appEl);\n";
        }
        ss << "  }\n";
    }
    if(!routes.empty()){
        ss << "  else {\n";
        if(layoutIdx >= 0){
            ss << "    render_Layout((slotEl) => { " << routes[0].second << "(slotEl); }, appEl);\n";
        } else {
            ss << "    " << routes[0].second << "(appEl);\n";
        }
        ss << "  }\n";
    }
    ss << "}\n\n";
    ss << "if (typeof window !== \"undefined\") window.addEventListener(\"DOMContentLoaded\", renderApp);\n";

    ofstream f(path);
    f << ss.str();
    f.close();
}





int main(int argc, char* argv[]){
    string inputPath = ".";
    string outDir = ".";
    if(argc > 1) inputPath = argv[1];
    if(argc > 2) outDir = argv[2];

    vs files;
    if(fs::is_directory(inputPath)){
        for(const auto& entry : fs::directory_iterator(inputPath)){
            if(entry.is_regular_file()){
                string ext = entry.path().extension().string();
                if(ext == ".ttv" || ext == ".tattva" || ext == ".web"){
                    files.pb(entry.path().string());
                }
            }
        }
        sort(files.begin(), files.end());
    } else if(fs::is_regular_file(inputPath)){
        files.pb(inputPath);
    } else {
        if(fs::exists("src") && fs::is_directory("src")){
            for(const auto& entry : fs::directory_iterator("src")){
                if(entry.is_regular_file()){
                    string ext = entry.path().extension().string();
                    if(ext == ".ttv" || ext == ".tattva" || ext == ".web"){
                        files.pb(entry.path().string());
                    }
                }
            }
            sort(files.begin(), files.end());
        }
    }

    if(files.empty()){
        cerr << "no .ttv, .tattva, or .web files found in " << inputPath << "\n";
        return 1;
    }

    vtt allTokens;
    for(const auto& fpath : files){
        ifstream file(fpath);
        if(!file.is_open()){
            cerr << "failed to open " << fpath << "\n";
            continue;
        }
        ostringstream ss;
        ss << file.rdbuf();
        string contents = ss.str();
        file.close();

        vtt curTokens = Tokenize(contents);
        for(const auto& tk : curTokens){
            if(tk.tkn != TokenType::EndOfFile){
                allTokens.pb(tk);
            }
        }
    }
    allTokens.pb(token{TokenType::EndOfFile, "", 0});

    Parser p(allTokens);
    Program prog = p.parse();

    cout << "compiled " << files.size() << " files (" << prog.prog.size() << " top-level nodes)\n";
    if(prog.appIdx >= 0) cout << "app at index " << prog.appIdx << "\n";
    if(prog.layoutIdx >= 0) cout << "layout at index " << prog.layoutIdx << "\n";

    fs::create_directories(outDir);
    emitHtml(prog, outDir + "/index.html");
    emitCss(prog, outDir + "/style.css");
    emitJs(prog, outDir + "/app.js");
    cout << "generated " << outDir << "/index.html, " << outDir << "/style.css, " << outDir << "/app.js\n";
    return 0;
}
