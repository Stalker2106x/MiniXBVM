#ifndef LANGUAGEDEF_HH_
#define LANGUAGEDEF_HH_

#include <ImGuiColorTextEdit/TextEditor.h>

namespace ExtTextEditor {
    namespace LanguageDefinition {
        const TextEditor::LanguageDefinition& ASM();
    }

    const TextEditor::Palette & GetCustomPalette();
}

#endif /* !LANGUAGEDEF_HH_ */