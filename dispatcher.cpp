#include "dispatcher.h"

#include "reasons.h"

Dispatcher::Dispatcher()
{   
}

void Dispatcher::init(const InfluenceTable *influence_table,
                      const EmotionTable *emotion_table,
                      const CharacterTable *character_table,
                      LocalCharacter *local_character)
{
    influence_table_ = influence_table;
    emotion_table_ = emotion_table;
    character_table_ = character_table;

    local_character_ = local_character;
}

void Dispatcher::handle_radio_packet(uint8_t influence_id,
                                     uint8_t parameter,
                                     int8_t strength)
{
    const InfluenceTable::Influence *influence;
    influence = influence_table_->influence(influence_id);
    if (!influence || !(influence->valid)) {
        return;
    }

    if (strength < influence->strength) {
        return;
    }

    begin_influence(influence_id, parameter, influence->timeout);
}

void Dispatcher::handle_nfc_packet(uint8_t influence_id)
{
    const InfluenceTable::Influence *influence;
    influence = influence_table_->influence(influence_id);
    if (!influence || !(influence->valid)) {
        return;
    }

    begin_influence(influence_id, 0, 0);
}

void Dispatcher::begin_influence(size_t id,
                                 uint8_t parameter,
                                 int8_t timeout)
{
    //TODO: send begin with respect to character codes
    (void)parameter;

    if (timeout != 0) {
        influence_states_[id].active = true;
        influence_states_[id].remaining_time = timeout;
    } else {
        end_influence(id);
    }
}

void Dispatcher::end_influence(size_t id)
{
    //TODO: send end with respect to character codes

    influence_states_[id].active = false;
    influence_states_[id].remaining_time = -1;
}

bool Dispatcher::influence_active(size_t id)
{
    return influence_states_[id].active;
}

void Dispatcher::tick()
{
    const size_t influence_count = influence_table_->influence_count();

    int dogan_effect = 0;

    for (size_t influence_id = 0;
         influence_id < influence_count;
         influence_id++) {
        if (influence_states_[influence_id].active) {
            const InfluenceTable::Influence *influence;
            influence = influence_table_->influence(influence_id);
            if (influence && influence->valid) {
                dogan_effect += influence->dogan_effect;
            }

            if (influence_states_[influence_id].remaining_time > 0) {
                influence_states_[influence_id].remaining_time--;
            }
            if (influence_states_[influence_id].remaining_time == 0) {
                end_influence(influence_id);
            }
        }
    }

    //TODO: send tick event with dogan effect
}
