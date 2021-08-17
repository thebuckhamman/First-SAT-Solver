#include <vector>

#include "typedefs.h"
#include "literal_operations.h"

void convert_cnf_to_literal(std::vector<std::vector<int>> const &file_cnf,
                            std::vector<clause> &literal_cnf)
{
    for(int i = 0; i < file_cnf.size(); i++)
    {
        clause next_clause(0);
        for(int j = 0; j < file_cnf[j].size(); j++)
        {
            int curr_var = file_cnf[i][j];
            literal curr_literal;

            if(curr_var < 0)
               curr_literal = curr_var*(-2) - 2;
            else 
                curr_literal = curr_var*2 - 1; 
        }
        literal_cnf.push_back(next_clause);
    }
}

void map_cnf(std::vector<clause> const &unmapped_cnf,
             std::vector<mapped_clause> &mapped_cnf)
{
    for(int i = 0; i < unmapped_cnf.size(); i++)
    {
        mapped_cnf.push_back({ unmapped_cnf.size(), unmapped_cnf[i] });
    }
}

void init_cv_map(const unsigned int num_lits,
                 std::vector<mapped_clause> &mapped_cnf,
                 std::vector<std::vector<mapped_clause*>> &cv_map,
                 std::vector<propping_literal> &init_assignment)
{
    std::vector<std::vector<mapped_clause*>> init_empty_cv_map(num_lits, std::vector<mapped_clause*>(0));
    cv_map = init_empty_cv_map;

    for(int i = 0; i < mapped_cnf.size(); i++)
    {
        if(mapped_cnf[i].cls.size() == 1)
        {
            literal curr_literal = mapped_cnf[i].cls[0];
            clause* curr_clause_pointer = &(mapped_cnf[i].cls);
            init_assignment.push_back({curr_literal, curr_clause_pointer});
            continue;
        }    

        for(int j = 0; j < mapped_cnf[i].cls.size(); j++)
        {
            literal curr_literal = mapped_cnf[i].cls[j];
            mapped_clause* curr_clause_pointer = &(mapped_cnf[i]);
            cv_map[curr_literal].push_back(curr_clause_pointer);
        }
    }
}

void init_prop_information(const unsigned int num_lits,
                           std::vector<std::vector<int>> const &file_cnf,
                           std::vector<mapped_clause> &mapped_cnf,
                           std::vector<std::vector<mapped_clause*>> &cv_map,
                           std::vector<propping_literal> &init_assignment)
{
    std::vector<clause> literal_cnf;
    convert_cnf_to_literal(file_cnf,literal_cnf);
    map_cnf(literal_cnf, mapped_cnf);
    init_cv_map(num_lits,mapped_cnf,cv_map,init_assignment); 
}
