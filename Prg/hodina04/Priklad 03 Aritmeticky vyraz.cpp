// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <iostream>
#include "stack.hxx"
#include "queue.hxx"

enum class Element
{
    Op, PostfixOp, Num
};

static inline void pushStringCopy(stack *st, const std::string &from)
{
    std::string *copy{ new std::string{ from }};
    stackPush(st, (void*)copy); 
}

static inline void enqueueStringCopy(queue *q, const std::string &from)
{
    std::string *copy{ new std::string{ from }};
    enqueue(q, (void*)copy);
}

static inline const std::string &strPeek(stack *st)
{
    return *(std::string*)stackPeek(st);
}

static inline int* intPtrPeek(stack * st)
{
    return (int*)stackPeek(st);
}

const std::string rlOps[]{ "u-", "abs", "sgn", "nsd", "nsn" };
constexpr size_t rlOpsLen{ sizeof(rlOps) / sizeof(std::string) };

//mimics C Operator Precedence
const std::string opsPrecTwo[]{"u-", "abs", "sgn", "nsd", "nsn"};
const std::string opsPrecThree[]{"*", "/"};
const std::string opsPrecFour[]{"+", "-"};

constexpr size_t opsPrecTwoLen{ sizeof(opsPrecTwo) / sizeof(std::string) };
constexpr size_t opsPrecThreeLen{ sizeof(opsPrecThree) / sizeof(std::string) };
constexpr size_t opsPrecFourLen{ sizeof(opsPrecFour) / sizeof(std::string) };

bool isRLOp(const std::string &op)
{
    for (size_t i{ 0 }; i < rlOpsLen; i++)
        if (op == rlOps[i])
            return true;

    return false;
}

bool isOpPrecTwo(const std::string &op)
{
    for (size_t i{ 0 }; i < opsPrecTwoLen; i++)
        if (op == opsPrecTwo[i])
            return true;

    return false;

}

bool isOpPrecThree(const std::string &op)
{
    for (size_t i{ 0 }; i < opsPrecThreeLen; i++)
        if (op == opsPrecThree[i])
            return true;

    return false;

}

bool isOpPrecFour(const std::string &op)
{
    for (size_t i{ 0 }; i < opsPrecFourLen; i++)
        if (op == opsPrecFour[i])
            return true;

    return false;

}

bool hasHeigherPrec(const std::string &opA, const std::string &opB)
{
    if (opB == "|" && opA != "|")
        return true;
    if (isOpPrecThree(opB) && isOpPrecFour(opA))
        return true;
    else if (isOpPrecTwo(opB) && (isOpPrecFour(opA) || isOpPrecThree(opA)))
        return true;

    return false;
}

bool isSimpleOperator(const char op)
{
    switch(op)
    {
        case '+':
        case '-':
        case '/':
        case '*':
        case ',':
        case '!':
        case ')':
        case '(':
            return true;
    }

    return false;
}

bool isFunctionOp(const std::string &op)
{
    return op == "abs" || op == "sgn" 
        || op == "nsd" || op == "nsn" 
        || op == "max" || op == "min";  
}


std::string readNum(const std::string &str, size_t &pos)
{
    std::stringstream strstream{};
    std::size_t j{ 0 };

    for (j = pos; j < str.length() && isdigit(str[j]); j++)
        strstream << str[j];
                
    j--;
    pos = j;

    return strstream.str();
}

std::string readOp(const std::string &str, size_t &pos, Element &prevEl)
{
    std::stringstream strstream{};

    if (isSimpleOperator(str[pos]))
    {
        if (prevEl == Element::Op && str[pos] == '-')
            strstream << "u-";
        else if (prevEl == Element::Op && str[pos] == '+')
            return strstream.str();
        else
            strstream << str[pos];
    }
    else if (str.length() - pos - 1 >= 3)
    {
        std::string op{ str.substr(pos, 3) };

        if (isFunctionOp(op))
        {
            strstream << op;
            pos += 2;
        }
    }
    else
        return strstream.str();

    std::string op{ strstream.str() };

    if (op == "!")
        prevEl = Element::PostfixOp;
    else
        prevEl = Element::Op;

    return op;
}

bool pipeOnTop(stack *operators)
{
    return strPeek(operators) == "|";
}

bool opBracketOnTop(stack *operators)
{
    return strPeek(operators) == "(";
}

std::string infixToPostfix(const std::string &str)
{
    stack *operators{ createStack() };
    queue *output{ createQueue() };

    Element prevEl{ Element::Op };

    for (std::size_t i{ 0 }; i < str.length(); i++)
    {
        if (isblank(str[i]))
            continue;

        if (isdigit(str[i]))
        {
            std::string num{ readNum(str, i) };
            enqueueStringCopy(output, num);

            prevEl = Element::Num;
        }
        else
        {
            std::string op{ readOp(str, i, prevEl) };

            if (op == "")
                continue;
            else if (op == ",")
                while(!isStackEmpty(operators) && !opBracketOnTop(operators))
                    enqueue(output, stackPop(operators));
            else if (op == ")")
            {
                while(!isStackEmpty(operators) && !opBracketOnTop(operators))
                {
                    if (pipeOnTop(operators))
                        delete (std::string*)stackPop(operators);
                    else
                        enqueue(output, stackPop(operators));
                }

                delete (std::string*)stackPop(operators);

                prevEl = Element::Num;

            }
            else if (op == "!")
            {
                while(!isStackEmpty(operators) && !opBracketOnTop(operators) && isRLOp(strPeek(operators)))
                    enqueue(output, stackPop(operators));
                
                enqueueStringCopy(output, op);
            }
            else
            {
                if (op == "min" || op == "max")
                {
                    std::string pipeOp{ "|" };
                    enqueueStringCopy(output, pipeOp);
                    pushStringCopy(operators, pipeOp);
                }

                if (!isRLOp(op) && op != "(")
                    while(!isStackEmpty(operators) && !opBracketOnTop(operators) && !pipeOnTop(operators) && !hasHeigherPrec(strPeek(operators), op))
                        enqueue(output, stackPop(operators));

                pushStringCopy(operators, op);
            }
        }
    }

    while(operators->count > 0)
    {
        if (pipeOnTop(operators)) //removes all pipes left after min and max 
            delete (std::string*)stackPop(operators);
        else
            enqueue(output, stackPop(operators));
    }

    std::stringstream strstream{};

    while(!isQueueEmpty(output))
    {
        std::string *el{ (std::string*)dequeue(output) };

        if (output->count == 0)
            strstream << *el;
        else
            strstream << *el << ' ';

        delete el;
    }

    destroyStack(operators);
    destroyQueue(output);

    return strstream.str(); 
}

bool isUnaryOp(const std::string &op)
{
    return ((op == "u-") || (op == "abs") || (op == "sgn"));
}

int sgn(int val)
{
    return (val < 0) ? -1 : ((val > 0) ? 1 : 0);
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    else if (n < 0)
        return -1;
    
    return n * factorial(n - 1);
}

int nsd(int a, int b)
{
    if (b == 0)
        return a;

    return nsd(b, a % b);
}

int nsn(int a, int b)
{
    if (b == 0 || a == 0)
        return 0;

    return (a * b) / nsd(a, b);
}

void interpretOp(const std::string &op, int *a, int *b)
{
    if (op == "+")
        *a += *b;
    else if (op == "-")
        *a -= *b;
    else if (op == "*")
        *a *= *b;
    else if (op == "/")
        *a /= *b;
    else if (op == "max")
        *a = std::max(*a, *b);
    else if (op == "min")
        *a = std::min(*a, *b);
    else if (op == "nsd")
        *a = nsd(*a, *b);
    else if (op == "nsn")
        *a = nsn(*a, *b);
    else if (op == "abs")
        *b = std::abs(*b);
    else if (op == "sgn")
        *b = sgn(*b);
    else if (op == "!")
        *b = factorial(*b);
    else if (op == "u-")
        *b = -*b;
}


int calcExpression(const std::string &infix) //a), b), c), d)
{
    std::stringstream postfix{ infixToPostfix(infix) };
    std::string val{};
    stack *values{ createStack() };
    stack *pipeElCounter{ createStack() }; //used for multiparameter functions like min and max

    while(postfix >> val)
    {
        if (isdigit(val[0]))
        {
            if (!isStackEmpty(pipeElCounter))
                (*intPtrPeek(pipeElCounter))++;
             
            int *num { new int{ atoi(val.c_str()) }};
            stackPush(values, (void*)num);
        }
        else if (val == "|")
        {
            int *count{ new int{ 0 } };
            stackPush(pipeElCounter, (void*)count);
        }
        else if (val == "min" || val == "max")
        {
            while((*intPtrPeek(pipeElCounter)) > 1)
            {
                int *b{ (int*)stackPop(values) };
                int *a{ (int*)stackPeek(values) };
                interpretOp(val, a, b);
                delete b;
                
                (*intPtrPeek(pipeElCounter))--;
            }

            int *elCounter{ (int*)stackPop(pipeElCounter) };

            if (!isStackEmpty(pipeElCounter))
                (*intPtrPeek(pipeElCounter))++;

            delete elCounter;
        }
        else
        {
            int *b{ (int*)stackPeek(values) };

            if (isUnaryOp(val) || val == "!")
                interpretOp(val, nullptr, b);
            else
            {
                if (!isStackEmpty(pipeElCounter))
                    (*intPtrPeek(pipeElCounter))--;

                stackPop(values);
                int *a{ (int*)stackPeek(values) };
                interpretOp(val, a, b);
                delete b;
            }
        }
    }

    int *outptr{ (int*)stackPop(values) };
    int result{ *outptr };

    destroyStack(values);
    destroyStack(pipeElCounter);
    delete outptr;
    
    return result;
}


int main()
{
    std::string expression{ "abs(-sgn(5! / ((5 - 2)! * 2!))) + 10 / (+---+2) + nsn(abs(-5)!, nsd(10 * 5 - 1,20)) + nsd(10,20) * max(10 + 20, 50, min(5!, 4!))" };
    std::cout << infixToPostfix(expression) << '\n';
    std::cout << calcExpression(expression) << '\n';
}