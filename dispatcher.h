#pragma once

#include <cstddef>
#include <cstdint>

#include "influencetable.h"
#include "emotiontable.h"
#include "charactertable.h"

#define BEGIN_ID(id) (id)
#define END_ID(id) (BEGIN_ID(id) + InfluenceTable::MAX_INFLUENCE_COUNT + 1)

#define BEGIN(name) (BEGIN_ID(name ## _ID))
#define END(name) (END_ID(name ## _ID))

#define DISPATCH_BEGIN(name) me->dispatcher->begin_influence((name ## _ID))
#define DISPATCH_END(name) me->dispatcher->end_influence((name ## _ID))

class Dispatcher
{
public:
    struct InfluenceState
    {
        bool active;
        int8_t remaining_time;
    };

public:
    Dispatcher();

    void init(const InfluenceTable *influence_table,
              const EmotionTable *emotion_table,
              const CharacterTable *character_table);

    void handle_radio_packet(uint8_t influence_id,
                             uint8_t parameter,
                             int8_t strength);

    void begin_influence(size_t id,
                         uint8_t parameter = 0,
                         int8_t timeout = -1);
    void end_influence(size_t id);

    bool influence_active(size_t id);

    void tick();

private:
    InfluenceState influence_states_[InfluenceTable::MAX_INFLUENCE_COUNT];

    const InfluenceTable *influence_table_;
    const EmotionTable *emotion_table_;
    const CharacterTable *character_table_;
};
