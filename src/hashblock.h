#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "crypto/sph_skein.h"
#include "crypto/sph_cubehash.h"
#include "crypto/sph_fugue.h"
#include "crypto/sph_gost.h"
#include "crypto/raptor.h"
#include "crypto/sph_echo.h"
#include "crypto/sph_shavite.h"
#include "crypto/sph_luffa.h"

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_skein512_context     z_skein; //
GLOBAL sph_cubehash512_context  z_cubehash; //
GLOBAL sph_fugue512_context     z_fugue;
GLOBAL sph_gost512_context      z_gost; //
GLOBAL sph_echo512_context      z_echo; //
GLOBAL sph_shavite512_context   z_shavite; //
GLOBAL sph_luffa512_context     z_luffa; //

#define fillz() do { \
    sph_skein512_init(&z_skein); \
    sph_cubehash512_init(&z_cubehash); \
    sph_fugue512_init(&z_fugue); \
    sph_gost512_init(&z_gost); \
	sph_echo512_init(&z_echo); \
	sph_shavite512_init(&z_shavite); \
	sph_luffa512_init(&z_luffa); \
} while (0) 

#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))
#define ZFUGUE (memcpy(&ctx_fugue, &z_fugue, sizeof(z_fugue)))
#define ZGOST (memcpy(&ctx_gost, &z_gost, sizeof(z_gost)))


template<typename T1>
inline uint256 Vitalium(const T1 pbegin, const T1 pend)

{
    sph_skein512_context     ctx_skein;
    sph_cubehash512_context   ctx_cubehash;
    sph_fugue512_context      ctx_fugue;
    sph_gost512_context      ctx_gost;
	sph_echo512_context      ctx_echo;
	sph_shavite512_context   ctx_shavite;
	sph_luffa512_context     ctx_luffa;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[17];

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[0]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[0]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[1]));
        
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[1]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[2]));

    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, static_cast<const void*>(&hash[2]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[3]));
	
	sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[3]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[4]));
	
	sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[4]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[5]));
	
	sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[5]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[6]));
	
	sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, static_cast<const void*>(&hash[6]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[7]));
	
	sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[7]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[8]));
        
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[8]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[9]));

    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, static_cast<const void*>(&hash[9]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[10]));
	
	sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[10]), 64);
    sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[11]));
	
	sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[11]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[12]));
	
	sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[12]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[13]));
	
    return hash[13].trim256();
}

#endif // HASHBLOCK_H
