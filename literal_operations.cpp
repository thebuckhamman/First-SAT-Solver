
#include "typedefs.h"

// returns negation of literal (if it were in int form)
literal negate_literal(const literal input_lit)
{
    return input_lit + 1 - 2*(input_lit%2);
}

// compares literals to see if they're the same, opposites, or neither
// returns: 1 if the same, -1 if they're opposites, 0 if neither
int compare_literals(const literal lit1, const literal lit2);
{
    if(lit1 == lit2)
        return 1;
    else if (lit1 == negate_literal(lit2))
        return -1
    else
        return 0;
}

void assign_literal(const literal l,
                    std::vector<bool> &is_assigned,
                    std::vector<bool> &assignment)
{
    is_assigned[l] = true;
    is_assigned[negate_literal(l)] = true;
    assignment[l] = true;
    assignment[negate_literal(l)] = false;

}

void unassign_literal(const literal l,
                      std::vector<bool> &is_assigned);
{
    is_assigned[l] = false;
    is_assigned[negate_literal(l)] = false;
}
