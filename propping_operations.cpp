#include <iostream>
#include <vector>

#include "typedefs.h"
#include "literal_operations.h"

// reduce set of mapped_clauses from literal assignment
// find unit clauses and add them to unit_propping_clauses to propogate later
// if conflict found, set conflict_clause to it
// return true if no conflict found, false otherwise
  
bool reduce(std::vector<mapped_clause*> &clauses_to_reduce,
            std::vector<clause*> &unit_propping_clauses,
            clause* &conflict_clause)
{
    conflict_clause = nullptr;

    for(int i = 0; i < clauses_to_reduce.size(); i++)
    {
        // reduce number of unfalsified lits in each clause
        (clauses_to_reduce[i])->num_unfalsified_lits--;

        // no unfalsified_lits -> conflict! If not assigned already, assign clause as the conflict_clause
        // one unfalsified_lits -> unit clause. Add to unit clause vector. 

        if((clauses_to_reduce[i]->num_unfalsified_lits == 0) && (conflict_clause != nullptr)) 
            conflict_clause = &(clauses_to_reduce[i]->cls);
        else if(clauses_to_reduce[i]->num_unfalsified_lits == 1)
            unit_propping_clauses.push_back(&(clauses_to_reduce[i]->cls));
    }
    
    // return true iff no conflict found
    if(conflict_clause == nullptr)
        return true;
    else
        return false;
}

// Convets all unsatisfied reduced (or normal) unit clauses to propping_literals.
// Determines satisfactions implicity: if reduce makes num_unfalsified_lits=1, but
// no unassigned literals are found, the unfalsified literal must be satisfied. 
// Appends propping literals to lits_to_prop.
void prop_unit_reduced_clauses(std::vector<clause*> const &unit_reduced_clauses,
                               std::vector<bool> const &is_assigned,
                               std::vector<propping_literal> &lits_to_prop)
{
    for(int i = 0; i < unit_reduced_clauses.size(); i++)
    {
        clause curr_clause = *(unit_reduced_clauses[i]);
        literal curr_clause_p_literal;
        bool is_satisfied = false;

        // loop through clause literals to find unassigned literal
        for(int j = 0; j < curr_clause.size(); j++)
        {
            // unassigned literal is propping literal
            if(!is_assigned[curr_clause[j]])
            {
                curr_clause_p_literal = curr_clause[j];
                break;
            }
            else if(j == curr_clause.size() - 1) // no unassigned lit found, must be satisfied
                is_satisfied = true;
        }

        // if not satisfied, add to propping_literal list to prop later 
        if(!is_satisfied)
        {
            propping_literal curr_propping_literal { curr_clause_p_literal, &curr_clause };
            lits_to_prop.push_back(curr_propping_literal);
        }
    }
}

bool prop_assigned_literal(const literal l, 
                           std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
                           std::vector<propping_literal> &lits_to_prop,
                           std::vector<bool> const &is_assigned,
                           clause* &conflict_clause)
{
    std::vector<mapped_clause*> clauses_to_reduce = literal_clause_map[negate_literal(l)];

    std::vector<clause*> unit_propping_clauses;

    if( !(reduce(clauses_to_reduce, unit_propping_clauses, conflict_clause)) )
            return false;

    prop_unit_reduced_clauses(unit_propping_clauses,
                              is_assigned,
                              lits_to_prop);

    return true;
}

bool prop_next_literal(std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
                       std::vector<propping_literal> &lits_to_prop,
                       std::vector<propping_literal> &propped_literals,
                       clause* &conflict_clause,
                       std::vector<bool> &is_assigned,
                       std::vector<bool> &assignment)
{
    propping_literal p_l = lits_to_prop.back();
    literal l = p_l.lit;
    lits_to_prop.pop_back();
    assign_literal(l, is_assigned, assignment);

    bool is_conflict = !prop_assigned_literal(l, 
                                              literal_clause_map, 
                                              lits_to_prop,
                                              is_assigned,
                                              conflict_clause);

    propped_literals.push_back(p_l);

    return !is_conflict;
}

bool propogate(std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
               std::vector<propping_literal> &lits_to_prop,
               std::vector<propping_literal> &propped_literals,
               clause* &conflict_clause,
               std::vector<bool> &is_assigned,
               std::vector<bool> &assignment)
{
    while(lits_to_prop.size() > 0)
    {
        bool is_conflict = !prop_next_literal(literal_clause_map,
                                              lits_to_prop,
                                              propped_literals,
                                              conflict_clause,
                                              is_assigned,
                                              assignment);
        if(is_conflict) { return false; }
    }
    return true;
}
