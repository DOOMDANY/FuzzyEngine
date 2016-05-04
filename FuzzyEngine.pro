TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH +=   "fuzzy" \
                "fuzzy/exceptions" \
                "fuzzy/inferenceModule" \
                "fuzzy/knowledgeModule" \
                "fuzzy/knowledgeModule/memberFunctions" \
                "fuzzy/memoryModule" \
                "util" \
                "linkedContainers"

INCLUDEPATH +=  "fuzzy" \
                "fuzzy/exceptions" \
                "fuzzy/inferenceModule" \
                "fuzzy/knowledgeModule" \
                "fuzzy/knowledgeModule/memberFunctions" \
                "fuzzy/memoryModule" \
                "util" \
                "linkedContainers"

SOURCES += main.cpp \
    fuzzy/fuzzyengine.cpp \
    fuzzy/knowledgeModule/knowledgebase.cpp \
    fuzzy/knowledgeModule/memberFunctions/membershipfunction.cpp \
    fuzzy/knowledgeModule/memberFunctions/imemberfunction.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfbell.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfexception.cpp \
    fuzzy/knowledgeModule/linguisticvariable.cpp \
    fuzzy/exceptions/duplicateditemexception.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfcustom.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfgaussian.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfsigmoid.cpp \
    fuzzy/knowledgeModule/memberFunctions/mfsingleton.cpp \
    fuzzy/knowledgeModule/memberFunctions/mftrapezoid.cpp \
    fuzzy/knowledgeModule/memberFunctions/mftriangle.cpp \
    fuzzy/knowledgeModule/irulepart.cpp \
    fuzzy/knowledgeModule/logicaloperator.cpp \
    fuzzy/knowledgeModule/rule.cpp \
    fuzzy/exceptions/badinstanceexception.cpp \
    util/stringtokenizer.cpp \
    util/util.cpp

HEADERS += \
    fuzzy/fuzzyengine.hpp \
    fuzzy/fuzzy.hpp \
    fuzzy/knowledgeModule/knowledgebase.hpp \
    fuzzy/knowledgeModule/knowledgemodule.hpp \
    fuzzy/knowledgeModule/memberFunctions/memberfunctions.hpp \
    fuzzy/knowledgeModule/memberFunctions/membershipfunction.hpp \
    fuzzy/knowledgeModule/memberFunctions/imemberfunction.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfbell.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfexception.hpp \
    fuzzy/knowledgeModule/linguisticvariable.hpp \
    fuzzy/exceptions/exceptions.hpp \
    fuzzy/exceptions/duplicateditemexception.hpp \
    fuzzy/exceptions/nonexistentelementexception.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfcustom.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfgaussian.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfsigmoid.hpp \
    fuzzy/knowledgeModule/memberFunctions/mfsingleton.hpp \
    fuzzy/knowledgeModule/memberFunctions/mftrapezoid.hpp \
    fuzzy/knowledgeModule/memberFunctions/mftriangle.hpp \
    fuzzy/knowledgeModule/irulepart.hpp \
    fuzzy/knowledgeModule/logicaloperator.hpp \
    fuzzy/knowledgeModule/rule.hpp \
    linkedContainers/linkedcontainers.hpp \
    linkedContainers/lstack.hpp \
    fuzzy/exceptions/badinstanceexception.hpp \
    util/stringtokenizer.hpp \
    util/util.hpp


