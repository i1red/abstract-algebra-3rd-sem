#include "Gen_of_G.h"

std::vector<BigInt> generator(std::vector<BigInt> G)
{
    std::vector<BigInt> result;
    long int i,j;
    BigInt y,a,step,Big1("1"),Big0;

    long int IntN=G.size();
    BigInt N=getBigInt(IntN);
    ModArithmetic<BigInt> M(N);

    factorization f=factorize_naive(N);
    long int k=f.p.size();
    bool gg;

    for(i=0;i<IntN;i++)
    {
        gg=0;
        for(j=0;j<k;j++)
        {
            a=Big0;
            step=N/f.p[j];
            y=M.multiply(y,Big0,N);
            while(y<step)
            {
                a = M.add(a, G[i],N);
                y=M.add(y,Big1,N);
            }
            if(a==Big0)
                gg=1;
        }
        if (gg==0)
            result.push_back(G[i]);
    }
    return result;

}

BigInt getBigInt(int a)
{
    char c[20];
    _itoa(a,c, 10);
    std::string s=c;
    return BigInt(s);
}

factorization factorize_naive(BigInt divided) {
    std::vector<BigInt> _base;
    std::vector<BigInt> _power;
    factorization out;
    out.p = _base;
    out.e = _power;

    BigInt zero("0");
    BigInt one("1");
    BigInt iterator("2");
    if(iterator > divided){
        out.p.push_back(one);
        out.e.push_back(one);
        return out;
    }
    else {
        int pos = 0;
        while(divided >= iterator){
            if(divided % iterator == zero){
                out.p.push_back(iterator);
                out.e.push_back(zero);
                while(divided % iterator == zero){
                    if (divided == zero)
                        return out;
                    divided = divided / iterator;
                    out.e[pos] = out.e[pos] + one;
                }
                pos++;
            }
            iterator = iterator + one;
        }
    }
    return out;
}