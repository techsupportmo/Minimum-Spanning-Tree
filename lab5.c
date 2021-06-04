//  Mohammed Ahmed
//  1001655176
//  Lab 5
//  gcc lab5.c -lm


// Kruskal's MST using union-find trees
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numVertices,numEdges;
int *parent,numTrees;
double *weight;


//----INPUT STRUCT------
struct input
{
  int tail,head;
};
typedef struct input inputType;
inputType *inputTab;
//-------------------------



//---- EDGE STRUCT-----
struct edge 
{
  int tail,head;
  double weight;
};
typedef struct edge edgeType;
edgeType *edgeTab;
//---------------------------


// Find root of tree containing x
int find(int x)
{
    int i,j,root;

    // Find root
    for (i=x; parent[i]!=i; i=parent[i]);
    root=i;
    // path compression - make all nodes on path
    // point directly at the root
    for (i=x; parent[i]!=i; j=parent[i],parent[i]=root,i=j);

    return root;
}


// i and j must be roots!
void unionFunc(int i,int j)
{
    if (weight[i]>weight[j])
    {
        parent[j]=i;
        weight[i]+=weight[j];
    }
    else
    {
        parent[i]=j;
        weight[j]+=weight[i];
    }
    numTrees--;
}


// Used in call to qsort()
int weightAscending(const void* xin,const void* yin)
{
    edgeType *x,*y;

    x=(edgeType*) xin;
    y=(edgeType*) yin;
    
    if(x->weight > y->weight)
    {
        return 1;
    }
    else if(x->weight < y->weight)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


int main()
{
    int i;
    double MSTweight=0;
    int root1,root2;

    //INPUT # OF VERTICES
    scanf("%d",&numVertices);

    //CALCULATE # OF EDGES 
    //FORMULA: [n(n-1)]/2
    numEdges = (numVertices * (numVertices - 1))/2;


    //initializing input table
    inputTab=(inputType*) malloc(numEdges*sizeof(inputType));

    edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
    parent=(int*) malloc(numVertices*sizeof(int));
    weight=(double*) malloc(numVertices*sizeof(double));

    if (!edgeTab || !parent || !weight)
    {
        printf("error 2\n");
        exit(0);
    }



    //INPUT X AND Y COORDINATES AND STORE IT INTO STRUCT
    //X is the tail
    //Y is the head
    for (i=0;i< (numVertices * 2);i++)
    {
        scanf("%d %d",&inputTab[i].tail,&inputTab[i].head);
    }

    //-----------------PRINT OUT INPUT------------------
    //print out x and y coordinates
    for(i = 0; i < numVertices; i++)
    {
      printf("%d  %d  %d\n",i,inputTab[i].tail,inputTab[i].head);
    }

   

    printf("\n");

    double edgeWeight;
    int count = 0;
    int j;
    int index = 0;

    //Fill up edge table
    //outer loops checks each tail
    for(i = 0; i < numVertices; i++)
    {
      //inner loop checks each head
      for(j = count; j < (numVertices - 1);j++)
      {


        //STORES EDGE
        // tail
        edgeTab[index].tail = i;
        // head
        edgeTab[index].head = j+1;
        // weight
        //calculate weight with distance formula
        edgeWeight = sqrt(pow((inputTab[j+1].tail-inputTab[i].tail),2)+pow((inputTab[j+1].head-inputTab[i].head),2));
        edgeTab[index].weight = edgeWeight;
        


        //increases index position of edgeTab
        index++;
        

      }
      //increments count
      count++;
      
    }
  

//-------------------------
    

  
    for (i=0;i<numVertices;i++)
    {
        parent[i]=i;
        weight[i]=1;
    }

    numTrees=numVertices;
    qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);

    count = 0;

    
    for (i=0;i<numEdges;i++)
    {

        //checks if count will exit out of loop
        if(count == numVertices-1)
        {
          break;
        }
            

        root1=find(edgeTab[i].tail);
        root2=find(edgeTab[i].head);
        if (root1==root2)
            printf("%d %d \t%.3lf discarded\n",edgeTab[i].tail,edgeTab[i].head,
            edgeTab[i].weight);
        else
        {
            printf("%d %d \t%.3lf included\n",edgeTab[i].tail,edgeTab[i].head,
            edgeTab[i].weight);
            MSTweight+=edgeTab[i].weight;
            unionFunc(root1,root2);
            count++;
        }
    }

    if (numTrees!=1)
    {
        printf("MST does not exist\n");
    }

    //prints sum of weights
    printf("\nSum of weights of spanning edges %.3lf\n",MSTweight);

    //Free memory
    free(inputTab);
    free(edgeTab);
    free(parent);
    free(weight);
}


