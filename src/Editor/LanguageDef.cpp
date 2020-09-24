#include "Editor/LanguageDef.hh"

const TextEditor::LanguageDefinition& ExtTextEditor::LanguageDefinition::ASM()
{
    static bool inited = false;
    static TextEditor::LanguageDefinition langDef;
    if (!inited)
    {
        static const char* const keywords[] = {
            "LDA", "ADD", "SUB", "OUT", "HLT"
        };

        for (auto& k : keywords)
            langDef.mKeywords.insert(k);

        static const char* const identifiers[] = {
            "void"
        };

        for (auto& k : identifiers)
        {
            TextEditor::Identifier id;
            id.mDeclaration = "Built-in function";
            langDef.mIdentifiers.insert(std::make_pair(std::string(k), id));
        }

        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\b(\\d+)\\b", TextEditor::PaletteIndex::Number));
        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\b0[xX][0-9a-fA-F]+\\b", TextEditor::PaletteIndex::Number));
        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\b0[bB][0-1]+\\b", TextEditor::PaletteIndex::Number));
        
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[A-Z]+", TextEditor::PaletteIndex::Keyword));

        langDef.mCommentStart = "/*";
        langDef.mCommentEnd = "*/";
        langDef.mSingleLineComment = ";";

        langDef.mCaseSensitive = false;
        langDef.mAutoIndentation = false;

        langDef.mName = "ASM";

        inited = true;
    }
    return langDef;
}