#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "csvtable.h"
#include "emotiontable.h"
#include "influencetable.h"
#include "charactertable.h"
#include "dispatcher.h"

const size_t COMMAND_BUFFER_SIZE = 256;

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

    LocalCharacter local_character;

    FILE *emotion_file = fopen("Emotions.csv", "r");
    if (!emotion_file) {
        fprintf(stderr, "Cannot open emotion file!\n");
        return 1;
    }

    emotion_table.init(emotion_file,
                       &csv_table);

    fclose(emotion_file);

    FILE *influence_file = fopen("Reasons.csv", "r");
    if (!influence_file) {
        fprintf(stderr, "Cannot open influence file!\n");
        return 1;
    }

    influence_table.init(influence_file,
                         &csv_table,
                         &emotion_table);

    fclose(influence_file);

    FILE *character_file = fopen("Characters.csv", "r");
    if (!character_file) {
        fprintf(stderr, "Cannot open character file!\n");
        return 1;
    }

    character_table.init(character_file,
                         &csv_table,
                         argv[1],
                         &local_character);

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

    printf("Starting dispatcher...\n");
    Dispatcher dispatcher;
    dispatcher.init(&influence_table,
                    &emotion_table,
                    &character_table,
                    &local_character);

    char command[COMMAND_BUFFER_SIZE];

    while (true) {
        printf(">> ");

        if (fgets(command, COMMAND_BUFFER_SIZE, stdin) == nullptr) {
            break;
        }

        std::vector<const char *> tokens;
        char *handle = command;

        while (true) {
            char *token = strtok(handle, " \t\r\n");
            if (token == nullptr) {
                break;
            }

            handle = nullptr;

            if (strlen(token) > 0) {
                tokens.push_back(token);
            }
        }

        if (tokens.size() == 0) {
            continue;
        }

        switch (tokens[0][0]) {
        case 't':
            if (tokens.size() >= 2) {
                int ticks = atoi(tokens[1]);
                while (ticks > 0) {
                    printf("Dispatching tick...\n");
                    dispatcher.tick();
                    ticks--;
                }
            } else {
                printf("Dispatching tick...\n");
                dispatcher.tick();
            }
            break;
        case 'r':
            if (tokens.size() >= 2) {
                uint8_t influence_id = static_cast<uint8_t>(atoi(tokens[1]));
                uint8_t parameter = 0;
                int8_t strength = -1;

                if (tokens.size() >= 3) {
                    parameter = static_cast<uint8_t>(atoi(tokens[2]));

                    if (tokens.size() >= 4) {
                        strength = static_cast<int8_t>(atoi(tokens[3]));
                    }
                }

                printf("Dispatching radio packet...\n");
                dispatcher.handle_radio_packet(influence_id,
                                               parameter,
                                               strength);
            } else {
                printf("Insufficient parameters!\n");
            }
            break;
        case 'n':
            if (tokens.size() >= 2) {
                uint8_t influence_id = static_cast<uint8_t>(atoi(tokens[1]));

                printf("Dispatching nfc packet...\n");
                dispatcher.handle_nfc_packet(influence_id);
            } else {
                printf("Insufficient parameters!\n");
            }
            break;
        case 'b':
            if (tokens.size() >= 2) {
                uint8_t button_id = static_cast<uint8_t>(atoi(tokens[1]));
                bool long_press = false;

                if (tokens.size() >= 3) {
                    long_press = static_cast<bool>(atoi(tokens[2]));
                }

                printf("Dispatching button press...\n");
                dispatcher.handle_button(button_id, long_press);
            } else {
                printf("Insufficient parameters!\n");
            }
            break;
        case 'q':
            printf("Exiting...\n");
            return 0;
        default:
            printf("Unknown command!\n");
        }
    }

    return 0;
}
