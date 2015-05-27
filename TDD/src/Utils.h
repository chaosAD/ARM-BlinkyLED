#ifdef __GNUC__
    typedef unsigned int        uint32_t;
    typedef unsigned short int  uint16_t;
    typedef unsigned char       uint8_t;
    typedef int                 int32_t;
    typedef short int           int16_t;
    typedef char                int8_t;

#else
    typedef unsigned long       uint32_t;
    typedef unsigned short      uint16_t;
    typedef unsigned char       uint8_t;
    typedef long                int32_t;
    typedef short               int16_t;
    typedef char                int8_t;

#endif