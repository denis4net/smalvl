#ifndef _BASE_INSTRUCTIONS_H
#define _BASE_INSTRUCTIONS_H

#include "exceptions.h"
#include "acs.h"
#include "heap_manager.h"
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <map>
#include <list>

#ifdef DEBUG_ENABLED
#define SEMANTIC_NODE(x, ...) printf("SEMANTIC NODE %p: ", this);\
				printf(x, ##__VA_ARGS__); printf("\n");
#else
#define SEMANTIC_NODE(x, ...) ;
#endif




class instr_t  {
protected:
    instr_t() {}
public:
    virtual ~instr_t() {}
};

//base expression class
class expr_t: public instr_t {
protected:
    expr_t() {}
public:
    virtual ~expr_t() {}
    virtual void print()=0;
};

//base operation class
class oper_t: public instr_t {
protected:
    oper_t() {}
public:
    virtual ~oper_t() {}
    virtual void print(int indent)=0;
    virtual std::string get_decl()=0;
};

typedef std::list<oper_t*> instructions_list_t;

//represent logical commands block
//all source tree will be represented by this node
class block_t: public oper_t {
private:
    instructions_list_t operators;

public:
    block_t() {
        SEMANTIC_NODE("Created block");
    }
    block_t(oper_t* op) {
        append(op);
    }
    block_t(oper_t* op1, oper_t* op2) {
        append(op1);
        append(op2);
    }
    virtual ~block_t() {
        for(std::list<oper_t*>::iterator i=operators.begin(); i!=operators.end(); i++)
            delete (*i);
    }
    int size() {
        operators.size();
    }

    virtual void print(int indent=0) {
        for(std::list<oper_t*>::iterator i=operators.begin(); i!=operators.end(); i++)
        {
            std::cout << std::string(indent, '\t');
            (*i)->print(indent);
        }
    }

    void append(oper_t* op) {
        block_t * b = dynamic_cast<block_t*>(op);
        if(b) {
            //splice two list of operations oper_t
            SEMANTIC_NODE("Adding %d commands from block %p [delete it] to block %p", b->size(), b, this);
            operators.splice(operators.end(), b->operators, b->operators.begin(), b->operators.end());
            delete b;
        }
        else
        {
            SEMANTIC_NODE("Adding command %p to block %p", op, this);
            operators.push_back(op);
        }
    }
    
    void append_safe(oper_t* op) {
        block_t * b = dynamic_cast<block_t*>(op);
        if(b) {
            //splice two list of operations oper_t
            SEMANTIC_NODE("Adding safe %d commands from block %p [delete it] to block %p", b->size(), b, this);
            operators.splice(operators.end(), b->operators, b->operators.begin(), b->operators.end());
        }
        else
        {
            SEMANTIC_NODE("Adding safe command %p to block %p", op, this);
            operators.push_back(op);
        }
    }
    instructions_list_t* get_operators() { return &operators; }
    
    virtual std::string get_decl()
    {
      return std::string("instruction block");
    }
};

#endif
