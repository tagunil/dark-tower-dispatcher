#include "charactertable.h"

#include <cstring>
#include <cstdlib>

CharacterTable::CharacterTable()
    : character_count_(0)
{
}

void CharacterTable::init(void *file_context,
                          CsvTable *table,
                          const char *character_name)
{
    if (!table->open(file_context)) {
        return;
    }

    memset(characters_, 0, sizeof(characters_));
    character_count_ = 0;

    while (table->parse_line()) {
        size_t id;
        const char *name;

        const char *id_field = table->field("rID");
        if (!id_field) {
            continue;
        }

        int id_value = atoi(id_field);
        if (id_value < FIRST_CHARACTER) {
            continue;
        }

        id = static_cast<size_t>(id_value) - FIRST_CHARACTER;
        if (id >= MAX_CHARACTER_COUNT) {
            continue;
        }

        name = table->field("shortName");
        if (!name) {
            continue;
        }
        if (name[0] == '\0') {
            continue;
        }

        if (strcmp(name, character_name) == 0) {
            //TODO: fill my own parameters
        }

        characters_[id].valid = true;
        memset(characters_[id].name, 0, MAX_CHARACTER_NAME_LENGTH + 1);
        strncpy(characters_[id].name, name, MAX_CHARACTER_NAME_LENGTH);
        if (id > character_count_) {
            character_count_ = id + 1;
        }
    }

    //TODO: ka-tet linking

    table->close();
}

uint8_t CharacterTable::find(const char *name) const
{
    for (uint8_t id = 0; id < character_count_; id++) {
        if (!characters_[id].valid) {
            continue;
        }

        if (strcmp(name, characters_[id].name) == 0) {
            return id;
        }
    }

    return INVALID_CHARACTER;
}
