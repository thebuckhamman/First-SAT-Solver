#include <vector>

#include "typedefs.h"
#include "literal_operations.h"

bool reduce(std::vector<mapped_clause*> &clauses_to_reduce,
            std::vector<clause*> &unit_propping_clauses,
            clause* &conflict_clause);

void prop_unit_reduced_clauses(std::vector<clause*> const &unit_reduced_clauses,
                               std::vector<bool> const &is_assigned,
                               std::vector<propping_literal> &lits_to_prop);

bool prop_assigned_literal(const literal l, 
                           std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
                           std::vector<propping_literal> &lits_to_prop,
                           std::vector<bool> const &is_assigned,
                           clause* &conflict_clause);

bool prop_next_literal(std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
                       std::vector<propping_literal> &lits_to_prop,
                       std::vector<propping_literal> &propped_literals,
                       clause* &conflict_clause,
                       std::vector<bool> &is_assigned,
                       std::vector<bool> &assignment);

bool propogate(std::vector<std::vector<mapped_clause*>> &literal_clause_map,  
               std::vector<propping_literal> &lits_to_prop,
               std::vector<propping_literal> &propped_literals,
               clause* &conflict_clause,
               std::vector<bool> &is_assigned,
               std::vector<bool> &assignment);
