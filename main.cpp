#include <iostream>
#include <vector>

#include "typedefs.h"
#include "literal_operations.h"
#include "propping_operations.h"

int main()
{
    std::vector<clause> cnf;
    cnf.push_back({ 2, 1});    
    cnf.push_back({ 4, 3, 1});    
    cnf.push_back({ 6, 5, 3, 1});    
    cnf.push_back({ 8, 7, 5, 3, 1});    
    cnf.push_back({ 0 });

    std::vector<mapped_clause> m_cnf;
    m_cnf.push_back({2,cnf[0]});
    m_cnf.push_back({3,cnf[1]});
    m_cnf.push_back({4,cnf[2]});
    m_cnf.push_back({5,cnf[3]});

    for(int i = 0; i < m_cnf.size(); i++)
    {
        std::cout << m_cnf[i].num_unfalsified_lits << " ";
    }
    std::cout << "\n\n";

    std::vector<std::vector<mapped_clause*>> literal_clause_map(10, std::vector<mapped_clause*>(0));

    for(int i = 0; i < 4; i++)
    {
        for(int j = 3; j >= i; j--)
        {
            literal_clause_map[2*i+1].push_back(&(m_cnf[j]));
        }
        literal_clause_map[2*i+2].push_back(&(m_cnf[i]));
    }

    std::vector<propping_literal> lits_to_prop = { {0, &(cnf[4])} }; 
    std::vector<propping_literal> propped_literals;
    clause* conflict_clause = nullptr;
    std::vector<bool> is_assigned(8,0);
    std::vector<bool> assignment(8,0);



    /*
    std::cout << propogate(literal_clause_map,
                                   lits_to_prop,
                                   propped_literals,
                                   conflict_clause,
                                   is_assigned,
                                   assignment)
     << "\n\n";
     */
 
    
    bool is_conflict = false;
    while(lits_to_prop.size() > 0)
    {
        is_conflict = !prop_next_literal(literal_clause_map,
                                              lits_to_prop,
                                              propped_literals,
                                              conflict_clause,
                                              is_assigned,
                                              assignment);

        std::cout << (conflict_clause == nullptr) << "\n\n";

        for(int i = 0; i < m_cnf.size(); i++)
        {
            std::cout << m_cnf[i].num_unfalsified_lits << " ";
        }
        std::cout << "\n\n";

        for(int i = 0; i < lits_to_prop.size(); i++)
        {
            std::cout << (lits_to_prop[i]).lit << "\n"; 
        }
        std::cout << "\n";

        for(int i = 0; i < propped_literals.size(); i++)
        {
            std::cout << (propped_literals[i]).lit << "\n"; 
        }
        std::cout << "\n";

        for(int i = 0; i < is_assigned.size(); i++)
        {
            std::cout << is_assigned[i];
        }
        std::cout << "\n\n";

        for(int i = 0; i < assignment.size(); i++)
        {
            std::cout << assignment[i];
        }
        std::cout << "\n\n";

        if(is_conflict) { break; }
    }

    std::cout << is_conflict;
    

    return 0;
}
