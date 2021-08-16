#ifndef TYPEDEFS
#define TYPEDEFS

#include <vector>

typedef unsigned int literal;
typedef std::vector<literal> clause;

typedef struct mapped_clause
{
    unsigned int num_unfalsified_lits;
    clause cls;
} mapped_clause;

typedef struct propping_literal
{
    literal lit;
    clause* cls;
} propping_literal;

#endif //TYPEDEFS
