//
//  FS_aux_fun.cpp
//  Fiat-Shamir
//
//  Created by ivan sarno on 24/01/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include "FS_aux_fun.h"

Intero fastexp( Intero base, Intero esp)
{
    if (esp==0)
        return 1;
    if (esp == 1)
        return base;
    else if (esp%2==0)
    {
        Intero temp = fastexp(base, esp/2);
        return temp * temp;
    }
    else
    {
        Intero temp = fastexp(base, esp/2);
        return temp * temp * base;
    }
}

Intero modexp( Intero base, Intero esp, Intero mod)
{
    if (esp==0)
        return 1;
    if (esp == 1)
        return base;
    else if (esp%2==0)
    {
        Intero temp = modexp(base, esp/2, mod);
        return temp * temp % mod;
    }
    else
    {
        Intero temp = modexp(base, esp/2, mod);
        return temp * temp * base % mod;
    }
}

bool MRpredicate1 (Intero y, Intero z, Intero N)
{
    if (modexp(y,z,N)==1)
        return true;
    else return false;
}

bool MRpredicate2(Intero y, Intero N, Intero z, Intero w)
{
    Intero i=0;
    bool cond = (modexp(y,fastexp(2,i)*z, N) == N-1);
    
    while (!cond && i < w)
    {
        i++;
        cond = (modexp(y,fastexp(2,i)*z, N) == N-1);
    }
    
    if (i==w)
        return false;
    else return true;
    
}

bool MRtest(Intero N)  //Miller-rabin test for prime number
{
    Intero w; Intero z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;
    int i=0;
    
    
    Intero y;
    
    while (ris && i < Precision)
    {
        y = RandNum;
        y= y % N;
        while(y<2)
        {
            y = RandNum;
            y= y % N;
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N)|| MRpredicate2(y, N, z, w));
        i++;
    }
    return ris;
}

void MRscomposition(Intero N, Intero &w, Intero &z)
{
    Intero i=1;
    Intero acc=2;
    N--;
    Intero r;
    
    while (acc < N)
    {
        r=N/acc;
        if ((N%acc==0) && (r%2==1))
        {
            w=i;
            z=r;
        }
        i++;
        acc = acc * 2;
    }
}

//extract a random number and search a early prime
Intero Primegenerator()
{
    Intero P = RandNum;
    if (P%2==0)
        P++;
    
    while (!MRtest(P))//test primality
    {
        P = P+2;
    }
    
    return P;
}

/*
 implementation of Extended Euclide algorithm to find the inverse of a numbere in module and coprime number
 */

typedef struct
{
    Intero x;
    Intero y;
    Intero z;
} triple;




triple ExtendedEuclide(Intero a, Intero b)
{
    triple result;
    triple temp;
    
    if (b == 0)
    {
        result.x = a;
        result.y = 1;
        result.z = 0;
        
        return result;
    }
    else temp = ExtendedEuclide(b, a % b);
    
    result.x = temp.x;
    result.y = temp.z;
    result.z = temp.y - ((a / b) * temp.z);
    
    return result;
}

Intero inverso(Intero n,Intero Modulo)
{
    triple ris = ExtendedEuclide(n,Modulo);
    if (ris.y<0)
        ris.y=Modulo+ris.y;
    
    return  ris.y;
}

bool coprime (Intero a, Intero b)
{
    triple temp = ExtendedEuclide(a, b);
    if (temp.x == 1)
        return true;
    else return false;
}