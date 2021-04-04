//
//  main.cpp
//  queens
//
//  Created by Simona Ivanova on 23.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include "ChessBoard.h"

int main() {
   int n;
    do{
        cout<<"Enter value for n: ";
        cin>>n;
        if(n<4){
            cout<<"N must be greater that 3."<<endl;
        }
    }while(n<4);
    ChessBoard b=ChessBoard(n);
    //b.print();
    clock_t start,end;
    start=clock();
    b.solve();
    end=clock();
    double time_taken=double(end-start)/double(CLOCKS_PER_SEC);
    cout<<"Time: "<<fixed<<time_taken<<setprecision(5)<<"sec"<<endl;
    cout<<"Do you want to see solution? ";
    char c;
    cin>>c;
    if(c=='y'){
        b.print();
    }
    return 0;
}
