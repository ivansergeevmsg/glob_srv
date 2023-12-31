#pragma once
#include "hashs.h"


char GUIDKey[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"; //36

unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

typedef struct
 {
   uint32_t state[5];
   uint32_t count[2];
   unsigned char buffer[64];
 } SHA1_CTX;


/////////////////////////////////////////////// SHA1 /////////////////////////////////////////////////////////////
void SHA1Transform( uint32_t state[5], const unsigned char buffer[64])
 {
    uint32_t a, b, c, d, e;
    typedef union
     {
       unsigned char c[64];
       uint32_t l[16];
     } CHAR64LONG16;

    CHAR64LONG16 block[1];    
    memcpy(block, buffer, 64);

    a = state[0]; b = state[1]; c = state[2]; d = state[3]; e = state[4];

    R0(a, b, c, d, e, 0); R0(e, a, b, c, d, 1); R0(d, e, a, b, c, 2); R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4); R0(a, b, c, d, e, 5); R0(e, a, b, c, d, 6); R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8); R0(b, c, d, e, a, 9); R0(a, b, c, d, e, 10); R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12); R0(c, d, e, a, b, 13); R0(b, c, d, e, a, 14); R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16); R1(d, e, a, b, c, 17); R1(c, d, e, a, b, 18); R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20); R2(e, a, b, c, d, 21); R2(d, e, a, b, c, 22); R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24); R2(a, b, c, d, e, 25); R2(e, a, b, c, d, 26); R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28); R2(b, c, d, e, a, 29); R2(a, b, c, d, e, 30); R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32); R2(c, d, e, a, b, 33); R2(b, c, d, e, a, 34); R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36); R2(d, e, a, b, c, 37); R2(c, d, e, a, b, 38); R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40); R3(e, a, b, c, d, 41); R3(d, e, a, b, c, 42); R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44); R3(a, b, c, d, e, 45); R3(e, a, b, c, d, 46); R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48); R3(b, c, d, e, a, 49); R3(a, b, c, d, e, 50); R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52); R3(c, d, e, a, b, 53); R3(b, c, d, e, a, 54); R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56); R3(d, e, a, b, c, 57); R3(c, d, e, a, b, 58); R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60); R4(e, a, b, c, d, 61); R4(d, e, a, b, c, 62); R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64); R4(a, b, c, d, e, 65); R4(e, a, b, c, d, 66); R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68); R4(b, c, d, e, a, 69); R4(a, b, c, d, e, 70); R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72); R4(c, d, e, a, b, 73); R4(b, c, d, e, a, 74); R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76); R4(d, e, a, b, c, 77); R4(c, d, e, a, b, 78); R4(b, c, d, e, a, 79);

    state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
    a = b = c = d = e = 0;
    memset(block, 0, sizeof(block));
 }


void SHA1Init( SHA1_CTX * context)
 {
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
 }


void SHA1Update( SHA1_CTX * context, const unsigned char *data, uint32_t len)
 {
    uint32_t i;
    uint32_t j;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j) context->count[1]++;

    context->count[1] += (len >> 29);
    j = (j >> 3) & 63;
    if((j + len) > 63)
     {
       memcpy(&context->buffer[j], data, (i = 64 - j));

       SHA1Transform(context->state, context->buffer);
       for(; i + 63 < len; i += 64)
        {
          SHA1Transform(context->state, &data[i]);
        }

       j = 0;
     }

    else i = 0;

    memcpy(&context->buffer[j], &data[i], len - i);
 }


void SHA1Final( unsigned char digest[20], SHA1_CTX * context)
 {
    unsigned i;
    unsigned char c, finalcount[8];

    for(i = 0; i < 8; i++)
     {
       finalcount[i] = (unsigned char) ((context->count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);     
     }

    c = 0200;
    SHA1Update(context, &c, 1);

    while((context->count[0] & 504) != 448)
     {
       c = 0000;
       SHA1Update(context, &c, 1);
     }

    SHA1Update(context, finalcount, 8); 

    for(i = 0; i < 20; i++)
     {
       digest[i] = (unsigned char) ((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
     }

    memset(context, 0, sizeof(*context));
    memset(&finalcount, 0, sizeof(finalcount));
 }


void SHA1(unsigned char *hash_out, const char *str, unsigned int len)
 {
    SHA1_CTX ctx;
    unsigned int ii;
    SHA1Init(&ctx);
    for (ii=0; ii<len; ii+=1) SHA1Update(&ctx, (const unsigned char*)str + ii, 1);
    SHA1Final((unsigned char *)hash_out, &ctx);
    hash_out[20] = 0;
 }


////////////////////////////////////// base64_encode ////////////////////////////////////////////
int base64_encode(unsigned char sha_key_in[], unsigned char base64_key_out[], int len)
 {
   int idx, idx2, blks, left_over;

   blks = (len / 3) * 3;
   for(idx=0, idx2=0; idx < blks; idx += 3, idx2 += 4) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[((sha_key_in[idx] & 0x03) << 4) + (sha_key_in[idx+1] >> 4)];
      base64_key_out[idx2+2] = charset[((sha_key_in[idx+1] & 0x0f) << 2) + (sha_key_in[idx+2] >> 6)];
      base64_key_out[idx2+3] = charset[sha_key_in[idx+2] & 0x3F];
    }

   left_over = len % 3;

   if(left_over == 1) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[(sha_key_in[idx] & 0x03) << 4];
      base64_key_out[idx2+2] = '=';
      base64_key_out[idx2+3] = '=';
      idx2 += 4;
    }

   else if(left_over == 2) 
    {
      base64_key_out[idx2] = charset[sha_key_in[idx] >> 2];
      base64_key_out[idx2+1] = charset[((sha_key_in[idx] & 0x03) << 4) + (sha_key_in[idx+1] >> 4)];
      base64_key_out[idx2+2] = charset[(sha_key_in[idx+1] & 0x0F) << 2];
      base64_key_out[idx2+3] = '=';
      idx2 += 4;
    }

   base64_key_out[idx2] = 0;
   return(idx2);
 }

