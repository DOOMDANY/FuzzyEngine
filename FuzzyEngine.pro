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
                "fuzzy/util" \
                "linkedContainers"

INCLUDEPATH +=  "fuzzy" \
                "fuzzy/exceptions" \
                "fuzzy/inferenceModule" \
                "fuzzy/knowledgeModule" \
                "fuzzy/knowledgeModule/memberFunctions" \
                "fuzzy/memoryModule" \
                "fuzzy/util" \
                "linkedContainers"

SOURCES += main.cpp \
    fuzzy/fuzzyengine.cpp

HEADERS += \
    fuzzy/fuzzyengine.hpp

