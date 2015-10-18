/**
 @author SriKrishna
 @version 1.0.7
 IIIT-Allahabad, 2013, India
 */
#include<iostream>
#include<conio.h>
#include<vector>
#include<ctime>
#include<string>
#include<cstdio>
#include<time.h>
#include<algorithm>
using namespace std;

//returns a float between 0 & 1
#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))
#define cross_rate            0.8
#define mutation_rate         0.008




// for comparing and sorting  the values of the vector pair

int min(int a,int b)
{
    return a<b ? (double)a :(double)b;
}
int max(int a,int b)
{
    return a>b ? (double)a : (double)b;
}

bool isTerminate=false;

bool myfunction( const pair< vector<int>, int>& i, const pair<vector<int>, int>& j ) 
{
    return i.second > j.second;
}

struct compare 
{
       bool operator()(const int& l,const int& r)
       {
            return l<r;
       }
};  
// Generate a random number between 0 and 1
// return a uniform number in [0,1].
double unifRand()
{
    return rand() / double(RAND_MAX);
}
// Generate a random number in a real interval.
// param a one end point of the interval
// param b the other end of the interval
// return a inform rand numberin [a,b].
double unifRand(double a, double b)
{
    return (b-a)*unifRand() + a;
}
// Generate a random integer between 1 and a given value.
// param n the largest value 
// return a uniform random value in [1,...,n]

//
// Reset the random number generator with the system clock.

void seed()
{
    srand(time(0));
}

vector< vector<int> > GEN_POP(int n,int m,int no_pop)
{
     vector<vector<int> >pop;
     vector<int> a;
     int x;
     for(int i=0;i<no_pop;i++)
     {
             for(int j=0;j<n;j++)
             {
                     x=rand()%m;
                     a.push_back(x);
             }
             pop.push_back(a);
             a.clear();
     }
     return pop;
}

vector< pair<vector<int>,int> > COMPUTE(vector< vector<int> > adj,vector< vector<int> > pop,int n,int m,int no_pop,int gen)
{
             vector< pair< vector<int>, int> > v_fitness;
             pair< vector<int>, int > temp;
             vector<int> a;
             int i=0;
             while(i<pop.size())
             {
                                a=pop[i];
                                int count=0;
                                for(int j=0;j<a.size();j++)
                                {
                                        int color=a[j];
                                        for(int k=j,h=0;h<n;h++)
                                        {
                                                if(adj[j][h] && color==a[h])
                                                count++;
                                        }
                                }
                                int s=n*n;
                                int fitness=s-count;
                                if(count==0)
                                {
                                            cout<<"generation "<<gen<<endl;
                                            cout<<"no.of diff needed is "<<m<<endl;
                                            cout<<"termination is met ";
                                            for(int q=0;q<n;q++)
                                            cout<<" "<<a[q];
                                            isTerminate=true;
                                            break;
                                }
                                
                                temp=make_pair(a,fitness);
                                v_fitness.push_back(temp);
                                
                                a.clear();
                                i++;
             }
             
             return v_fitness;
}

vector< vector<int> > SELECT(vector< pair<vector<int>,int> >fitness,int n,int m,int no_pop)
{
        int k=3,fit=0;
        vector< vector<int> > selection;
        for(int i=0;i<no_pop;i++)
        {
                for(int j=0;j<k;j++)
                {
                        int random1=rand()%no_pop;
                        int random2=rand()%no_pop;
                        int random3=rand()%no_pop;
                        int e,f,g;
                        e=fitness[random1].second;
                        f=fitness[random2].second;
                        g=fitness[random3].second;
                        if(e==max(e,max(f,g)))
                        selection.push_back(fitness[random1].first);
                        else if(f==max(e,max(f,g)))
                        selection.push_back(fitness[random2].first);
                        else if(g==max(e,max(f,g)))
                        selection.push_back(fitness[random3].first);
                }
        }
        return selection;
}
vector<vector<int> > CROSSOVER (vector< vector<int> >selection,int n,int m, double cros_rate,double BLX_rate,vector< vector<int> > adj)
{
                   vector< vector<int> > cross;
                   
                   for(int i=0;i<selection.size()-1;i+=2)
                   {
                           vector<int> a,b,c1,c2;
                           a=selection[i];
                           b=selection[i+1];
                           double t=(double)unifRand(0,1);

                           if( t < cros_rate )
                           {
                                                    
                                  	 for(int j=0;j<a.size();j++)
        	                           {
        	                                   double cmin=min(a[j],b[j]);
        	                                   double cmax=max(a[j],b[j]);
        	                                   double interval=cmax-cmin;
        	                                   double s1=cmin-(interval*BLX_rate);
        	                                   double s2=cmax+(interval*BLX_rate);
        	                                    if(s1<0)
        	                                   s1=0;
        	                                   if(s2>m)
        	                                   s2=m;
        	                                   double h1=unifRand(s1,s2);
        	                                   c1.push_back(h1);
        	                                   double h2=unifRand(s1,s2);
        	                                   c2.push_back(h2);
        	                           }
        	                            cross.push_back(c1);
	                                    cross.push_back(c2);
        	                            c1.clear();
        	                            c2.clear();
                           }
                           else
                           {
                               cross.push_back(a);
                               cross.push_back(b);
                           }
                            c1.clear();
                            c2.clear();
                           a.clear();
                           b.clear();
                           
                          
                   }
              
                   return cross;
}


vector< vector<int> > MUTATION(vector< vector<int> > crossover,int n,int m,float mut_rate)
{
           //  cout<<"in mutation \n";
             int random1,random2,random3,random4;
             vector< vector<int> > mutation;
             for(int i=0;i<crossover.size();i++)
             {
                     double a=(double)unifRand(1,1000)/10000;
                     if( a < mut_rate )
                     {
                       
                     	   random1=rand()%n;
                      
                         random2=rand()%m;
                         random3=rand()%n;
                      
                         random4=rand()%m;
                         crossover[i][random1]=random2;
                         crossover[i][random3]=random4;
                         mutation.push_back(crossover[i]);
                     }
                     else
                     {
                         mutation.push_back(crossover[i]);
                     }
             }
           
             return mutation;
}

int main()
{
    
	seed();
    int n,m,no_pop,generation;
    cout<<"enter the no.of nodes ";
    cin>>n;
    vector< vector<int> > adj,adj_2;
    vector<int> a;
    cout<<"enter the adjacency matrix ";
    int x;
    int adj_connect=0;
    int max_connect=0;
    for(int i=0;i<n;i++)
    {
            adj_connect=0;
            for(int j=0;j<n;j++)
            {
                    cin>>x;
                    a.push_back(x);
                    if(x==1)
                    {
                            adj_connect++;
                    }
            }
            if(max_connect < adj_connect)
            max_connect=adj_connect;
            adj.push_back(a);
            a.clear();
    }
    cout<<"HELLO\n";
    for(int i=0;i<n;i++)
    {
            for(int j=0;j<n;j++)
            {
                    a.push_back(adj[i][j]);
            }
            adj_2.push_back(a);
            a.clear();
    }
    int max=0,max_degree=0;
    for(int i=0;i<n;i++)
    {
            for(int j=0;j<n;j++)
            {
                    if(adj[i][j]==1)
                    {
                                  for(int k=0;k<n;k++)
                                  {
                                          if(adj[j][k]==1 && i!=j && i!=k && j!=k )
                                          {
                                                          adj_2[i][k]=1;            
                                          }

                                  }
                    }
            }
    }
   
    for(int i=0;i<n;i++)
    {
            max=0;
            for(int j=0;j<n;j++)
            {
                    if(adj_2[i][j]==1)
                    max++;
                    cout<<adj_2[i][j]<<" ";
            }
            if(max>max_degree)
            max_degree=max;
            cout<<endl;
    }
     cout<<"maximum 2 hop connectivity is "<<max_degree<<endl;
   
    cout<<"enter the no.of populations ";  
    cin>>no_pop;
    cout<<"enter the no.of generations ";
    cin>>generation;
  
    
   m=2;
    
    int gen=0;
    vector< vector<int> > pop,selection,crossover,mutation;
    pop=GEN_POP(n,m,no_pop);
    
    clock_t t1,t2;
    t1=clock();
   
    while(gen<=generation && isTerminate==false)
    {
                        //  cout<<"generation is "<<gen<<endl;
                   vector< pair< vector<int>, int> > fitness; 
                   fitness=COMPUTE(adj,pop,n,m,no_pop,gen);
                   //cout<<"fitness size is "<<fitness.size()<<endl;
                   if(!isTerminate)
                   {
                       selection=SELECT(fitness,n,m,no_pop);
                       crossover=CROSSOVER(selection,n,m,cross_rate,0.4,adj);
                      // cout<<"crossover size is "<<crossover.size()<<endl;
                       mutation=MUTATION(crossover,n,m,mutation_rate);  
                       /*for(int i=0;i<mutation.size();i++)
                       {
                               vector<int> a;
                               a=mutation[i];
                               for(int j=0;j<a.size();j++)
                               cout<<a[j];
                               cout<<endl;
                       }*/     
                   }
                   pop=mutation;
                   selection.clear();
                   crossover.clear();
                   mutation.clear();
                   
                   ++gen;
                   if(gen==generation)
                   {
                                      if(m<=max_connect+1)
                                      ++m;
                                      else
                                      break;
                                      gen=0;
                                      pop=GEN_POP(n,m,no_pop);
                   }                                 
    }
    t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds=diff/CLOCKS_PER_SEC;
    cout<<endl;
    cout<<"time taken is "<<seconds<<endl;
    cout<<"termination is met ";
    getch();
    return 0;
}
                   
                                             
                                        
                                                      
