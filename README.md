cs416
=====

Operating System Assignment Repo

Create a program that finds the transitive closure for a given graph. The Graph is given in the input file and we are expected to
output to stdout. I suggest we use a tree and store all the edges as nodes and relationships as parent child.


Warshall Algorithum : 

for (k=1 to n){
    for(i=1 to n){
        if(wik=1){
            for(j=1 to n){
                wij = wij or wjk}
        }
    }
}
return W

This algorium is slightly faster than the one the prof posted takes n^2 + n^3 instead of taking 2n^3


