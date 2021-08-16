#ifndef LITERAL_OPERATIONS
#define LITERAL_OPERATIONS

#include "typedefs.h"

// returns negation of literal (if it were in int form)
literal negate_literal(const literal input_lit);

// compares literals to see if they're the same, opposites, or neither
// returns: 1 if the same, -1 if they're opposites, 0 if neither
int compare_literals(const literal lit1, const literal lit2);


void assign_literal(const literal l,
                    std::vector<bool> &is_assigned,
                    std::vector<bool> &assignment);

void unassign_literal(const literal l,
                      std::vector<bool> &is_assigned);

#endif //LITERAL_OPERATIONS
