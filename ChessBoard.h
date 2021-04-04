//
//  ChessBoard.h
//  queens
//
//  Created by Simona Ivanova on 23.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef ChessBoard_h
#define ChessBoard_h
#include <iostream>
#include<vector>
#include<iomanip>

using namespace std;

class ChessBoard{
public:
    
    ChessBoard(){
        size=0;
        rowOfQueen=nullptr;
        numberOfQueenInRow=nullptr;
        numberOfQueenInMainDiag=nullptr;
        numberOfQueenInOtherDiag=nullptr;
    }
    
    ChessBoard(int s){
        size=s;
        rowOfQueen=new int[size];
        numberOfQueenInRow=new int[2*size-1];
        numberOfQueenInMainDiag=new int[2*size-1];
        numberOfQueenInOtherDiag=new int[2*size-1];

        setValues();
        calculateConflict();
    }
    
    ~ChessBoard(){
        delete []rowOfQueen;
        delete []numberOfQueenInRow;
        delete []numberOfQueenInOtherDiag;
        delete []numberOfQueenInMainDiag;
    }
    
    void print() const{
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(i==rowOfQueen[j]){
                    cout<<"* ";
                }
                else{
                    cout<<"- ";
                }
            }
            cout<<endl;
        }
    }
    
    void solve(){
        if(hasConflict()){
            int steps=0;
            int stepsLimit=2*size;
            while(steps<stepsLimit){
                int randomIndexQueenMaxConflict=findIndexOfQueenMaxConflict();
                setNewRowForQueen(randomIndexQueenMaxConflict);
                if(!hasConflict()){
                    cout<<"We found solution. Let's see time."<<endl;
                    break;
                }
                steps++;
                if(steps==stepsLimit && hasConflict()){
                    steps=0;
                    nulity();
                }
                
            }
        }
    }
    
private:
    int size;
    //Въпросната дъск с цриците.
    int* rowOfQueen;
    //Броят на цариците в редовете.
    int* numberOfQueenInRow;
    //Броят на цариците по главния диагонал.
    int* numberOfQueenInMainDiag;
    //Броят на цариците по второстепенния диагонал.
    int* numberOfQueenInOtherDiag;
    
    void setValues()
    {
        for (int i = 0; i < size; i++) {
            rowOfQueen[i] = i;
        }

        for (int i = 0; i < size; i++) {
            int j = rand() % size;
            int temp=rowOfQueen[i];
            rowOfQueen[i]=rowOfQueen[j];
            rowOfQueen[j]=temp;
        }
    }
    
    void initDefaultValues(){
        for(int i=0;i<2*size-1;i++){
            if(i<size){
                numberOfQueenInRow[i]=(0);
            }
            numberOfQueenInMainDiag[i]=(0);
            numberOfQueenInOtherDiag[i]=(0);
        }
    }
    
    void calculateConflict(){
        initDefaultValues();
        for(int i=0;i<size;i++){
            int currentRow=rowOfQueen[i];
            numberOfQueenInRow[currentRow]++;
            numberOfQueenInMainDiag[size-(currentRow-i)-1]++;
            numberOfQueenInOtherDiag[currentRow+i]++;
        }
    }
    
    void nulity(){
        setValues();
        calculateConflict();
    }
    
    int findConflictForQueen(int columnOfQueen){
        int currentRow=rowOfQueen[columnOfQueen];
        int conflRow=numberOfQueenInRow[currentRow]-1;
        //cout<<"The queen has "<<conflRow<<" conflicts on the row."<<endl;
        int confMainDiag=numberOfQueenInMainDiag[size-(currentRow-columnOfQueen)-1]-1;
       // cout<<"The queen has "<<confMainDiag<<" conflict on the main diaginal."<<endl;
        int confOtherDiag=numberOfQueenInOtherDiag[columnOfQueen+currentRow]-1;
       // cout<<"The queen has "<<confOtherDiag<<" conflicts on the other diagonal."<<endl;

        return conflRow+confMainDiag+confOtherDiag;
    }
    
    bool hasConflict()const{
        for(int i=0;i<2*size-1;i++){
            if(i<size){
                if(numberOfQueenInRow[i]>1){
                    return true;
                }
            }
            if(numberOfQueenInMainDiag[i]>1){
                return true;
            }
            if(numberOfQueenInOtherDiag[i]>1){
                return true;
            }
        }
        return false;
    }
    
    int findIndexOfQueenMaxConflict(){
        vector<int>indexOfQueenMaxConflict;
        int max=0;
        for(int i=0;i<size;i++){
            int currentConflict=findConflictForQueen(i);
            if(max==currentConflict){
                indexOfQueenMaxConflict.push_back(i);
            }
            else if(max<currentConflict){
                max=currentConflict;
                indexOfQueenMaxConflict.clear();
                indexOfQueenMaxConflict.push_back(i);
            }
        }
        int randomIndexOfQueenMaxConf=rand()%indexOfQueenMaxConflict.size();
        //cout<<"Index of random queen, which has max conflicts : "<<indexOfQueenMaxConflict[ randomIndexOfQueenMaxConf]<<endl;
        return indexOfQueenMaxConflict[randomIndexOfQueenMaxConf];
    }
    
    int findConflictsOnOtherRow(int otherRow, int colOfQueen)
    {
        return numberOfQueenInRow[otherRow] + numberOfQueenInMainDiag[size - (otherRow - colOfQueen + 1)] + numberOfQueenInOtherDiag[otherRow + colOfQueen];
    }
    
    int randomRowMinConflict(int colOfQueen){
        vector<int> conflictDiffRow;
        int minConf=size;
        vector<int> indexMinConf;
        for(int i=0;i<size;i++){
            if(i!=rowOfQueen[colOfQueen]){
                int currentConflict=findConflictsOnOtherRow(i, colOfQueen);
                if(minConf==currentConflict){
                    indexMinConf.push_back(i);
                }
                else if(currentConflict<minConf){
                    minConf=currentConflict;
                    indexMinConf.clear();
                    indexMinConf.push_back(i);
                }
            }
        }
         int randomIndex=rand()%indexMinConf.size();
         return indexMinConf[randomIndex];
    }
    
    
    void setNewRowForQueen(int colOfQueen){
        int oldRow=rowOfQueen[colOfQueen];
        int newRow=randomRowMinConflict(colOfQueen);

        rowOfQueen[colOfQueen]=newRow;
        numberOfQueenInRow[oldRow]--;
        numberOfQueenInMainDiag[size-(oldRow-colOfQueen+1)]--;
        numberOfQueenInOtherDiag[oldRow+colOfQueen]--;
        
        numberOfQueenInRow[newRow]++;
        numberOfQueenInMainDiag[size-(newRow-colOfQueen)-1]++;
        numberOfQueenInOtherDiag[newRow+colOfQueen]++;
    }
};

#endif /* ChessBoard_h */
