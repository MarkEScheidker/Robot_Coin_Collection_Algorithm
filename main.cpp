#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
std::ofstream outfile;  //global file variabale

void RobotCoinCollection(std::vector<std::vector<int>> C)
{
    int N = C.size()-1;       //get the size of the array and convert it to 0 based array
    int M = C[0].size()-1;
    std::vector<std::vector<int> > F(   //create a 2d vector to store the paths that's the same size as the input array
            N+1,
            std::vector<int>(M+1));
    int i;         //declare iterator variables
    int j;
    
    F[0][0] = C[0][0];  //if there's a coin on the starting space, then automatically the robot collects it

    for(j=1; j<=M; j++) //for the width of the array
    {
        F[0][j] = F[0][j-1] + C[0][j];  //move the previous value in row 0 into the next space in row 0 plus any coins in that space
    }
    
    for(i=1; i<=N; i++)  //for the length of the array
    {
        F[i][0] = F[i-1][0] + C[i][0];   //move the previous value in collumn 0 into the next space in row 0 plus any coins in that space
        for(j=1; j<=M; j++)           //for the width of the array
        {
            if(F[i-1][j] > F[i][j-1])   //if the item on the left is larger than the item above
            {
                F[i][j] = F[i-1][j] + C[i][j];  // the space = the item on the left plus 1 if there's a coin
            }
            else
            {
                F[i][j] = F[i][j-1] + C[i][j]; //the space - the item above plus 1 if there's a coin
            }
        }
    }

    std::cout<<"F=  ";   //formatting for clean output
    outfile<<"F=  ";
    
    for(j=0; j<M+1; j++)     //for the width of the array
    {
        std::cout<<F[0][j]<<"  ";   //output the first row
        outfile<<F[0][j]<<"  ";
    }
    std::cout<<std::endl;
    outfile<<std::endl;    //formatting

    for(i=1; i<N+1; i++)   //for the length of the array
    {
        std::cout<<"   ";  //formatting
        outfile<<"   ";
        for(j=0; j<M+1; j++)  //for the width of the array
        {
            std::cout<<std::setw(2)<<F[i][j]<<" ";   //output the value of the item in the array
            outfile<<std::setw(2)<<F[i][j]<<" ";
        }
        std::cout<<std::endl;     //formatting
        outfile<<std::endl;
    }

    std::vector<int> path;  //create 1d vector to store path
    i = N; //set up iterators
    j = M;

    path.push_back(j+1);  //add bottom right coordinates to the vector
    path.push_back(i+1);

    while (i!=0 || j!=0) {    //iterate through array F until you reach (0,0)
        if (i == 0) {     //if I is zero, then only J can be changed
            j--;
        } else if (j == 0) {  //if J is zero then only I can be changed
            i--;
        } else if (F[i - 1][j] >= F[i][j - 1]) {  //if left space is less than or equal to space above
            i--;     // move up
        } else {
            j--;     // move left
        }
        path.push_back(j+1);  //put current coordinates into vector
        path.push_back(i+1);
    }

    std::cout<<"path=";    //formatting
    outfile<<"path=";
    i = path.size()-1;     //i = size of the array-1
    while(i>=0)    //while i is greater than zero
    {
        std::cout<<"("<<path[i]<<", ";  //output path[i]
        outfile<<"("<<path[i]<<", ";
        i--;                            //subtract 1 from i
        std::cout<<path[i]<<") ";       //output path[i]
        outfile<<path[i]<<") ";
        i--;                            //subtract 1 from i
    }
}

int main() {
    std::vector<std::vector<int>> C1
        {{0,0,0,0,1,0},           //declare matrices
         {0,1,0,1,0,0},
         {0,0,0,1,0,1},
         {0,0,1,0,0,1},
         {1,0,0,0,1,0}};

    std::vector<std::vector<int>> C2
        {{0,0,0,0,1,0},
         {1,1,0,1,0,0},
         {1,0,0,1,0,1},
         {1,0,1,0,0,1},
         {1,1,1,1,1,0}};

    std::vector<std::vector<int>> C3
        {{1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
         {1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
         {1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
         {0, 1, 1, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
         {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
         {1, 0, 0, 0, 0, 1, 1, 0, 1, 0}};
         
    outfile.open("output.txt"); //open global output file

    RobotCoinCollection(C1);    //run robot coin collection algorithm for each matrix
    std::cout<<"\n\n";
    outfile<<"\n\n";
    RobotCoinCollection(C2);
    std::cout<<"\n\n";
    outfile<<"\n\n";
    RobotCoinCollection(C3);
}
