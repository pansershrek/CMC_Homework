#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef  double ld;
typedef long long ll;
const ld E=0.001;
extern ld ff1(ld x);
extern ld ff2(ld x);
extern ld ff3(ld x);
extern ld fd1(ld x);
extern ld fd2(ld x);
extern ld fd3(ld x);

ld f1(int mode,ld x)
{
    /*if (mode)
    {
        return -8*x/(x*x+1)/(x*x+1);
    }
    else
        return 1+4/(x*x+1);*/
    if (mode) {
        return fd1(x);
    }
    else
        return ff1(x);
}
ld f2(int mode,ld x)
{
    /*if (mode)
    {
        return 3*x*x;
    }
    else
        return x*x*x;*/
    if (mode) {
        return fd2(x);
    }
    else
        return ff2(x);
}
ld f3(int mode,ld x)
{
    /*if (mode)
    {
        return -pow(2,-x)*0.693147181;
    }
    else
        return pow(2,-x);*/
    if (mode) {
        return fd3(x);
    }
    else
        return ff3(x);
}
ld root(ld (*f)(int,ld),ld (*g)(int,ld),ld a,ld b,ld eps1) //find root by Newton's method
{
    ld x0 = (a+b)/2,x1;
    x1 = x0 - (f(0,x0) - g(0,x0)) / (f(1,x0) - g(1,x0)); // determine first vers of x
    if (fabs(f(0,x0)- g(0,x0)) < eps1 ) // maybe i find a root
        return x0;
    if (fabs(f(0,x1)- g(0,x1)) < eps1 ) // or maybe now
        return x1;
    while ((fabs(f(0,x1)- g(0,x1)) > eps1) && (fabs(x1-x0) > eps1))  // find root
    {
        x0 = x1;
        x1 = x0 - (f(0,x0) - g(0,x0)) / (f(1,x0) - g(1,x0));
    }
    return x1;
}
ld integral(ld (*f)(int,ld),ld a,ld b,ld eps2) // find integral by Trapezoid's method
{
    ld sum1 = 0,sum2 = 0;
    ll k = 100;
    ld delt = (b-a) / k; // determine first split
    for (ll i = 0;i < k;i++) // calc first integral sum
    {
        sum1 += (f(0,a + i * delt) + f(0,a + (i+1) * delt)) * delt / 2;
    }
    k *= 10;
    delt = (b-a) / k; // determine second split
    for (ll i = 0;i < k;i++) //calc second integral sum
    {
        sum2 += (f(0,a + i * delt) + f(0,a + (i+1) * delt)) * delt / 2;
    }
    while (fabs(sum2-sum1) > eps2) //calc finish integral sum
    {
        sum1 = sum2;
        k *= 10;
        delt = (b-a) / k;
        for (ll i = 0;i < k;i++)
        {
            sum2 += (f(0,a + i * delt) + f(0,a + (i+1) * delt)) * delt / 2;
        }
    }
    return sum2;
}
int main(void)
{

    ld X1,X2,X3;
    X1=root(f1,f2,0,2,E);
    X2=root(f1,f3,-2,0,E);
    X3=root(f2,f3,0,1,E);
    ld S1,S2,S3,Ans;
    S1=fabs(integral(f1,X2,X1,E));
    S2=fabs(integral(f2,X1,X3,E));
    S3=fabs(integral(f3,X2,X3,E));
    Ans=S1-S2-S3;
    printf("%lf",Ans);
    return 0;
}
