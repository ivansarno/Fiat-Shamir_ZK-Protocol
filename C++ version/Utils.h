//
//  ZK-Fiat-Shamir.cpp
//  Zero Knowledge Fiat-Shamir Protocol
//
//  Created by ivan sarno on 24/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//version V.3.6

#ifndef __ZK__Utils__
#define __ZK__Utils__
#include <gmpxx.h>
#include <time.h>
#include <stdlib.h>

namespace ZKFS
{
    namespace Utils
    {
        typedef mpz_class BigInteger;
        BigInteger pow(BigInteger base, BigInteger exp);
        BigInteger mod_pow(BigInteger base, BigInteger exp, const BigInteger &mod);
        bool coprime (BigInteger a, BigInteger b);
        BigInteger byte2biginteger(uint8_t *byte, unsigned int size);
        
        
        class Generator
        {
        public:
            virtual BigInteger get(unsigned int size)=0;//return a positive BigInteger of size bit
        };
        
        class TestGenerator: public Generator
        {
        private:
            gmp_randstate_t rstate;
            mpz_t rand;
            unsigned long long seed;
        public:
            TestGenerator();
            TestGenerator(unsigned long long seed);
            ~TestGenerator();
            BigInteger get(unsigned int size);//return a positive BigInteger of size bit
        };
    }
}

#endif /* defined(__ZK__Utils__) */
