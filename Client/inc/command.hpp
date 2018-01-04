#pragma once

#if defined(__linux__)
# define PACKED_STRUCT(name)	struct __attribute__((packed)) \
				name
#elif defined(WIN32)
# pragma pack(push, 1)
# define PACKED_STRUCT(name)	struct \
				name
#endif

namespace	player_move
{
  enum
    {
      UP = 0x1,
      DOWN = 0x2,
      LEFT = 0x4,
      RIGHT = 0x8
    };
};

namespace				command
{

  enum
    {
      ZERO = 0x00,
      OK = 0x01,
      KO = 0x02,
      TIMEOUT = 0x03,
      DISCONNECT = 0x04,
      LIST_ROOM = 0x05,
      JOIN_ROOM = 0x06,
      CREATE_ROOM = 0x07,
      LEAVE_ROOM = 0x08,
      READY = 0x09,
      START = 0x0a,
      DATA = 0x0b,
      NEW_ENEMY = 0x0c,
      COUNT
    };

  PACKED_STRUCT(player_info)
  {
    uint32_t				id;
    char				name[16];
  };

  PACKED_STRUCT(player_dataServ)
  {
    uint32_t				id;
    int x;
    int y;
  };

  PACKED_STRUCT(player_dataCli)
  {
    uint16_t        dir;
    bool            fire;
  };

  PACKED_STRUCT(room_info)
  {
    uint32_t				id;
    bool				ingame;
    char				name[32];
    player_info				players[4];
  };

  PACKED_STRUCT(player_data)
  {
    uint32_t				id;
    uint16_t dir;
    int x;
    int y;
  };

};

#if defined(WIN32)
# pragma pack(pop)
#endif
