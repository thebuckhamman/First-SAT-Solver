#ifndef INIT_PROP_INFORMATION
#define INIT_PROP_INFORMATION

#include <vector>

#include "typedefs.h"
#include "literal_operations.h"

void convert_cnf_to_literal(std::vector<std::vector<int>> const &file_cnf,
                            std::vector<clause> &literal_cnf);

void map_cnf(std::vector<clause> const &unmapped_cnf,
             std::vector<mapped_clause> &mapped_cnf);

void init_cv_map(const unsigned int num_lits,
                 std::vector<mapped_clause> &mapped_cnf,
                 std::vector<std::vector<mapped_clause*>> &cv_map,
                 std::vector<propping_literal> &init_assignment);

void init_prop_information(const unsigned int num_lits,
                           std::vector<std::vector<int>> const &file_cnf,
                           std::vector<mapped_clause> &mapped_cnf,
                           std::vector<std::vector<mapped_clause*>> &cv_map,
                           std::vector<propping_literal> &init_assignment);

#endif
