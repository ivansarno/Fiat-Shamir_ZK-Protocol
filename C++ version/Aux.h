//
//  ZK-Fiat-Shamir.cpp
//  Zero Knoledge Fiat-Shamir Protocol
//
//  Created by ivan sarno on 24/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//version V.3.0

#ifndef __RSA__Aux__
#define __RSA__Aux__
#include <gmpxx.h>
#include <time.h>
#include <stdlib.h>

namespace ZKFS
{
    namespace Aux
    {
        typedef mpz_class BigInteger;
        BigInteger pow( BigInteger base, BigInteger exp, int size);
        BigInteger mod_pow( BigInteger base, BigInteger exp, BigInteger mod, int size);
        BigInteger inverse(BigInteger n, BigInteger modulus);
        bool coprime (BigInteger a, BigInteger b);
        
        class Generator
        {
        public:
            Generator();
            virtual BigInteger get(int size);//return a positive BigInteger of size bit
        };
        
    }
}

#endif /* defined(__RSA__Aux__) */
