#pragma once

#include <cstddef>
#include <cstdint>

#include "influencetable.h"
#include "emotiontable.h"

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
              const EmotionTable *emotion_table);

    void handle_radio_packet(uint8_t influence_id,
                             uint8_t parameter,
                             int8_t strength);

    void begin_influence(size_t id,
                         uint8_t parameter = 0,
                         int8_t timeout = -1);
    void end_influence(size_t id);

    void tick();

private:
    InfluenceState influence_states_[InfluenceTable::MAX_INFLUENCE_COUNT];

    const InfluenceTable *influence_table_;
    const EmotionTable *emotion_table_;
};
