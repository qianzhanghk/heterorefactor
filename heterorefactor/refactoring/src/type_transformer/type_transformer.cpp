#include "type_transformer.h"

TypeTransformer::TypeTransformer(SgProject* project,
        misc_utils::RefactorType t) {
    m_project = project;
    m_transform_type = NULL;
    m_type = t;
}

void TypeTransformer::set_exclusion(const std::set<SgNode *> *excluded) {
    m_excluded = excluded;
}

void TypeTransformer::transform(void) {
    transform_func_return();
    transform_func_param();
    ast_utils::transform_func_decl_matching_def(m_project);

    transform_var_decl();
    transform_typecast();

    if (m_type == misc_utils::RefactorType::fp)
        transform_binary_operations();
}

SgType *TypeTransformer::get_transformation_fp(SgScopeStatement *scope) {
    if (!m_transform_type) {
        m_transform_type = SageInterface::lookupTypedefSymbolInParentScopes(
            "__fpt_t", scope)->get_type();
    }
    return m_transform_type;
}
