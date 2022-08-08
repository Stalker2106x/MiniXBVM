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
        
        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("(^|\\s)[0-9]+", TextEditor::PaletteIndex::Number));
        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\"[^\"]*\"?", TextEditor::PaletteIndex::String));
        langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("(^|\\s)(db|dw|dw)(\\s|$)", TextEditor::PaletteIndex::Punctuation));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z0-9]+", TextEditor::PaletteIndex::Identifier));
		langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z]{3}", TextEditor::PaletteIndex::Keyword));

        langDef.mCommentStart = "[None][";
        langDef.mCommentEnd = "][None]";
        langDef.mSingleLineComment = ";";

        langDef.mCaseSensitive = false;
        langDef.mAutoIndentation = false;

        langDef.mName = "ASM";

        inited = true;
    }
    return langDef;
}

const TextEditor::Palette & ExtTextEditor::GetCustomPalette()
{
	const static TextEditor::Palette p = { {
			0xff7f7f7f,	// Default
			0xffd69c56,	// Keyword	 #569CD6
			0xff00ff00,	// Number
			0xff7070e0,	// String
			0xff70a0e0, // Char literal
			0xffffffff, // Punctuation
			0xff408080,	// Preprocessor
			0xffc8c8c8, // Identifier
			0xff9bc64d, // Known identifier
			0xffc040a0, // Preproc identifier
			0xff206020, // Comment (single line)
			0xff406020, // Comment (multi line)
			0xff101010, // Background
			0xffe0e0e0, // Cursor
			0x80a06020, // Selection
			0x800020ff, // ErrorMarker
			0x40f08000, // Breakpoint
			0xff707000, // Line number
			0x40000000, // Current line fill
			0x40808080, // Current line fill (inactive)
			0x40a0a0a0, // Current line edge
		} };
	return p;
}