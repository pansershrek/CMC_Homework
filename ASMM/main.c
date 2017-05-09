#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef  double ld;
typedef long long ll;
const ld E=0.0001;
extern ld ff1(ld x);
extern ld ff2(ld x);
extern ld ff3(ld x);
extern ld fd1(ld x);
extern ld fd2(ld x);
extern ld fd3(ld x);
ll num_iter = 0;
ld get_val_str(char *sc)//pars str to double
{
	int m,j=0,len=1,mode =0;
	ld w1=0,w2=0,w3=0,sgn=1;
	m = strlen(sc);
	while (sc[j]=='-' || sc[j]=='+')
	{
		if (sc[j]=='-')
		sgn*=-1;
		j++;
	}
	for (j;(j<m);j++)
    {
			
    	if (sc[j]=='.')
        {
        	mode = 1;
        }
        else if (!mode)
                {
                    w1*=10;
                    w1=w1+(int)(sc[j])-(int)('0');
                }
				else
                if (mode)
                {
                    len*=10;
					w2*=10;
                    w2=w2+(int)(sc[j])-(int)('0');
                }
            }
           	w2/=len;
			w3=w1+w2;
	return w3*sgn;
}
ll max(ll w1,ll w2)
{
    return (w1>w2)?w1:w2;
}
ld f1(int mode,ld x)
{
    /*if (mode)
    {
        return -8*x/(x*x+1)/(x*x+1);
    }
    else
        return 1+4/(x*x+1);*/
    if (mode) {
        return fd1(x); //function f1
    } 
    else
        return ff1(x);//determine of function f1
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
        return -pow(2,-x)*1.442695041;
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
    ll n_iter = 1;
    ld x0 = (a+b)/2,x1;
	
    x1 = x0 - (f(0,x0) - g(0,x0)) / (f(1,x0) - g(1,x0)); // determine first vers of x
	    
	if (fabs(f(0,x0)- g(0,x0)) < eps1 ) // maybe i find a root
    {
        num_iter = max(num_iter,n_iter);
        return x0;
    }
    n_iter++;
    if (fabs(f(0,x1)- g(0,x1)) < eps1 ) // or maybe now
    {
        num_iter = max(num_iter,n_iter);
        return x1;
    }
    while ((fabs(f(0,x1)- g(0,x1)) > eps1) && (fabs(x1-x0) > eps1))  // find root
    {
        x0 = x1;
        x1 = x0 - (f(0,x0) - g(0,x0)) / (f(1,x0) - g(1,x0));
		        
		n_iter++;
    }
    num_iter = max(num_iter,n_iter);
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
		sum2 = 0;
        k *= 10;
        delt = (b-a) / k;
        for (ll i = 0;i < k;i++)
        {
            sum2 += (f(0,a + i * delt) + f(0,a + (i+1) * delt)) * delt / 2;
        }
    }
    return sum2;
}
int main(int argc,char *argv[])
{
    char h[5] = "-help";
    char it[5]= "-iter";
    char ab[5]= "-absp";
	char an[5]= "-ans";
	char tr[5]= "-t_r";
	char ti[5]= "-t_i";
    for (int i = 0;i < argc; i++)
    {
        if (strstr(h,argv[i])-h == 0)
        {
            printf("-absp :: Print the abscissas of the intersection points of the curves\n");
            printf("-iter :: Prints the number of iterations required for an approximate solution of the equations when searching for intersection points\n");
			printf("-ans :: The area of a plane figure bounded by three curves\n");
			printf("-t_r :: Test finding root function.Get 2 numb of function and line segment\n");
			printf("-t_i :: Test finding integral function.Get numb of function and 2 points\n");
			return 0;
        }
    }
	for (int i = 0;i < argc; i++)
    {
		
        if (strstr(tr,argv[i])-tr == 0)
        {
			int g1,g2;
            g1=(int)(*argv[i+1])-(int)('0');
            g2=(int)(*argv[i+2])-(int)('0');
			if (g1>g2)
			{int mid=g1;g1=g2;g2=g1;}
			ld w1,w2,ans;
			w1=get_val_str(argv[i+3]);
			w2=get_val_str(argv[i+4]);
			if (g1==1 && g2==2)
			ans=root(f1,f2,w1,w2,E);
			if (g1==1 && g2==3)
			ans=root(f1,f3,w1,w2,E);
			if (g1==2 && g2==3)
			ans=root(f2,f3,w1,w2,E);
			if (ans==NAN)
			printf("No root");
			else
			printf("%lf\n",ans);
		
			
		}
	}
    ld X1,X2,X3;
 	X1=root(f1,f2,0,2,E);
   	X2=root(f1,f3,-2,-1,E);
	X3=root(f2,f3,-2,2,E);
    ld S1,S2,S3,Ans; // sqaer of first,second and therd figure
    S1=fabs(integral(f1,X2,X1,E));
    S2=fabs(integral(f2,X1,X3,E));
    S3=fabs(integral(f3,X2,X3,E));
    Ans=S1-S2-S3;
    for (int i = 0;i < argc; i++)
    {
        if (strstr(ab,argv[i])-ab == 0)
        {
            printf("The abscissas of the intersection points are %lf %lf %lf\n",X1,X2,X3);
        }
        if (strstr(it,argv[i])-it == 0)
        {
            printf("The number of iterations are %lld\n",num_iter);
        }
		if (strstr(an,argv[i])-an == 0)
        {
            printf("The area of a plane figure bounded by three curves is %lf\n",Ans);
        }
    }

    
    return 0;
}
