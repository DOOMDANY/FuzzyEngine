#include "rulecompilerexception.hpp"

using namespace fuzzy::exceptions;

/**===================================== CONSTRUCTORS =====================================**/
RuleCompilerException::RuleCompilerException(const std::string &message) :
    _code(UNKNOWN_ERROR),
    _msg(message)
{

}

RuleCompilerException::RuleCompilerException(StateCodes state, const std::string &compilerMessage) :
    _code(state),
    _compilerMsg(compilerMessage)
{
    BuildMessage();
}

/**===================================== DESTRUCTOR =====================================**/
RuleCompilerException::~RuleCompilerException()
{

}

/**===================================== PUBLIC MEMBER FUNCTIONS =====================================**/
RuleCompilerException::StateCodes RuleCompilerException::stateCode() const
{
    return _code;
}

const char *RuleCompilerException::compilerMessage() const
{
    return _compilerMsg.c_str();
}

const char *RuleCompilerException::what() const throw()
{
    return _msg.c_str();
}

/**===================================== PROTECTED MEMBER FUNCTIONS =====================================**/
void RuleCompilerException::BuildMessage()
{
    switch(_code)
    {
        case UNKNOWN_MF:
            _msg = "UNKNOWN_MF: The membership function name could not be found in the knowledge base";
            break;
        case UNKNOWN_LV:
            _msg = "UNKNOWN_LV: The linguistic variable name could not be found in the knowledge base";
            break;
        case INVALID_OPERATOR:
            _msg = "INVALID_OPERATOR: The operator is not valid to compile a rule";
            break;
        case UNEXPECTED_SYMBOL:
            _msg = "UNEXPECTED_SYMBOL: The symbol did not be expected";
            break;
        default:
            _msg = "UNKNOWN_ERROR: error unknown";
    }
}
