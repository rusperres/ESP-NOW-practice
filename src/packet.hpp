#include <cstdint>

struct __attribute__((packed)) Packet{
    uint64_t article_id_hi;
    uint64_t article_id_lo;
    uint16_t fragment_id;
    uint8_t payload[180];
};