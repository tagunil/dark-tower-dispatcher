#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "csvtable.h"
#include "emotiontable.h"
#include "influencetable.h"
#include "charactertable.h"
#include "dispatcher.h"

size_t read_callback(void *file_context, uint8_t *buffer, size_t length)
{
    return fread(buffer,
                 1,
                 length,
                 reinterpret_cast<FILE *>(file_context));
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <character_name>\n", argv[0]);
        return 1;
    }

    CsvTable csv_table(&read_callback);
    EmotionTable emotion_table;
    InfluenceTable influence_table;
    CharacterTable character_table;

    FILE *emotion_file = fopen("Emotions.csv", "r");
    if (!emotion_file) {
        fprintf(stderr, "Cannot open emotion file!\n");
        return 1;
    }

    emotion_table.init(emotion_file, &csv_table);

    fclose(emotion_file);

    FILE *influence_file = fopen("Reasons.csv", "r");
    if (!influence_file) {
        fprintf(stderr, "Cannot open influence file!\n");
        return 1;
    }

    influence_table.init(influence_file, &csv_table, &emotion_table);

    fclose(influence_file);

    FILE *character_file = fopen("Reasons.csv", "r");
    if (!character_file) {
        fprintf(stderr, "Cannot open character file!\n");
        return 1;
    }

    character_table.init(character_file, &csv_table, argv[1]);

    fclose(character_file);

    printf("Influences:\n");

    for (size_t index = 0;
         index < influence_table.influence_count();
         index++) {
        const InfluenceTable::Influence *influence;
        influence = influence_table.influence(index);
        if (influence && influence->valid) {
            printf("%s = %zu\n", influence->name, index);
        }
    }

    printf("\n");

    printf("Emotions:\n");

    for (size_t index = 0;
         index < emotion_table.emotion_count();
         index++) {
        const EmotionTable::Emotion *emotion;
        emotion = emotion_table.emotion(index);
        if (emotion && emotion->valid) {
            printf("%s = %zu\n", emotion->name, index);
        }
    }

    printf("\n");

    printf("Characters:\n");

    for (size_t index = 0;
         index < character_table.character_count();
         index++) {
        const CharacterTable::Character *character;
        character = character_table.character(index);
        if (character && character->valid) {
            printf("%s = %zu\n", character->name, index);
        }
    }

    printf("\n");

    Dispatcher dispatcher;
    dispatcher.init(&influence_table, &emotion_table, &character_table);

    return 0;
}
