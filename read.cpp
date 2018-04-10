#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;


double entropy(double a,double b){
    double p1 = -(a/b)*log2(a/b);
    return p1;
}



void minor(double a[4][4],double temp[4][4],int i,int j,int n){
    int p=0,q=0,x=0,y=0;
    for(p=0;p<n;p++){
        for(q=0;q<n;q++){
            if(p!=i && q!=j){
                temp[x][y++] = a[p][q];
                if(y==n-1){
                    y=0;x++;
                }
            }
        }
    }
}



double det(double a[4][4],int n){
    if(n==1)return a[0][0];
    //go along top row to calculate determinant
    int i,j;
    double d = 0;
    double sign = 1;
    double temp[4][4];
    for(j=0;j<n;j++){
        minor(a,temp,0,j,n);
        d+= sign*a[0][j]*det(temp,n-1);
        sign = -sign;
    }
    return d;
}


void inverse(double a[4][4],double inv[4][4]){
    //first,get matrix of cofactors
    int i,j;
    double a_det = det(a,4);//cout<<"\na_det="<<a_det<<"\n";
    double temp[4][4];
    double sign = 1;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            minor(a,temp,i,j,4);
            inv[i][j] =sign*det(temp,3)/a_det;
            sign = -sign;
        }
        sign = -sign;
    }

}





vector <double> add(vector <double> dest,vector <double> src){//add two vectors,ONLY UPTO 4TH ELEMENT
    int i;
    for(i=0;i<4;i++){
        dest[i]+=src[i];
    }
    return dest;
}

vector <vector <double> > add_2d(vector <vector <double> > m1, vector <vector <double> > m2){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            m1[i][j] += m2[i][j];
        }
    }
    return m1;
}

vector <double> sub(vector <double> dest,vector <double> src){//sub two vectors,ONLY UPTO 4TH ELEMENT
    int i;
    for(i=0;i<4;i++){
        dest[i]-=src[i];
    }
    return dest;
}

vector <vector <double> > mul_2d(vector <double> m1,vector <double> m2){
    int i=0,j=0;
    vector <vector <double> > f;
    vector <double> temp;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            temp.push_back(m1[i]*m2[j]);
        }
        f.push_back(temp);
        temp.clear();
    }
    return f;
}

double mul(double m1[],double m2[]){
    int i;
    double f = 0;
    for(i=0;i<4;i++){
        f += m1[i]*m2[i];
    }
    return f;
}


vector <vector <double> > transpose_2d(vector <vector <double> > original){
    int i,j;
    vector <double> temp;
    vector <vector <double> > f;
    for(i=0;i<original[0].size();i++){
        for(j=0;j<original.size();j++){
            temp.push_back(original[j][i]);
        }
        f.push_back(temp);
        temp.clear();
    }
    return f;
}

bool s_col( const vector<double>& v1,
               const vector<double>& v2 ) {
 return v1[0] < v2[0];
}


int main(){
    vector <vector <double> > c;
    int i,j;
    fstream infile;//file handler
    infile.open("/Users/vishnu/Desktop/train.txt");//File location
    string buff;//file read line by line buffer
    int cnt = 0;
    while(getline(infile,buff)){
        cnt++;
        vector <double> temp;
        int i=0;
        string t1 = "";
        double f_t1;
        while(buff[i]!=','){t1 += buff[i];i++;}//take double one at a time
        f_t1 = strtod((t1).c_str(),0);
        temp.push_back(f_t1);//push back each onto temp
        t1 = "";i++;
        while(buff[i]!=','){t1 += buff[i];i++;}
        f_t1 = strtod((t1).c_str(),0);
        temp.push_back(f_t1);
        t1 = "";i++;
        while(buff[i]!=','){t1 += buff[i];i++;}
        f_t1 = strtod((t1).c_str(),0);
        temp.push_back(f_t1);
        t1 = "";i++;
        while(buff[i]!=','){t1 += buff[i];i++;}
        f_t1 = strtod((t1).c_str(),0);
        temp.push_back(f_t1);
        t1 = "";i++;
        while(buff[i]!='\n'){t1 += buff[i];i++;}
        f_t1 = strtod((t1).c_str(),0);
        temp.push_back(f_t1);
        c.push_back(temp);//push back temp onto c and clear temp
        temp.clear();//repeat till all lines are read
    }
    /*for(i=0;i<c.size();i++){//checking
        for(j=0;j<c[i].size();j++){
            cout<<c[i][j]<<" ";
        }
        cout<<"\n";
    }*/
    //c is the vector of all training data;
    vector <double> m1;vector <double> m2;//store mean vectors of c1 and c2
    m1.push_back(0);m2.push_back(0);//initialising both,size = 4
    m1.push_back(0);m2.push_back(0);
    m1.push_back(0);m2.push_back(0);
    m1.push_back(0);m2.push_back(0);
    int c1_count=0,c2_count=0;//to get N1 and N2 so we can get average vectors
    for(i=0;i<c.size();i++){
        if(c[i][4]==0){m1 = add(m1,c[i]);c1_count++;}
        if(c[i][4]==1){m2 = add(m2,c[i]);c2_count++;}
    }
    for(i=0;i<4;i++){m1[i] = m1[i]/c1_count;}
    cout<<"\n\n";
    for(i=0;i<4;i++){m2[i] = m2[i]/c2_count;}
    cout<<"\n";
    vector <double> m;
    for(i=0;i<4;i++){
        m.push_back(m2[i]-m1[i]);
    }//M calculated,now for Sw
    vector <double> temp;
    for(i=0;i<4;i++){temp.push_back(0);}
    vector <vector <double> > S_w;
    for(i=0;i<4;i++){S_w.push_back(temp);}
    for(i=0;i<c.size();i++){
        if(c[i][4]==0){
            S_w = add_2d(S_w,mul_2d( sub(c[i],m1),sub(c[i],m1) ) );
        }
        if(c[i][4]==1){
            S_w = add_2d(S_w,mul_2d( sub(c[i],m2),sub(c[i],m2) ) );
        }
    }//Found Sw,now to get its inverse
    //cout<<"Sw....\n";
    double a[4][4];
    for(i=0;i<S_w.size();i++){
        for(j=0;j<S_w[i].size();j++){
            //cout<<S_w[i][j]<<" ";
            a[i][j] = S_w[i][j];
        }
        //cout<<"\n";
    }
    //a is in 2-d array,now bypass through inverse matrix function
    double inv[4][4];
    inverse(a,inv);//got the inverse of S_w,now to extrate w = S_w(-1) x (m)
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            //cout<<inv[i][j]<<" ";
        }
       // cout<<"\n";
    }
    //cout<<"\n------------------------------------\n";
    double w[4];
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            w[i] += inv[i][j]*m[j];
        }
    }
    double dn = 0;
    for(i=0;i<4;i++){
        dn += w[i] * w[i];
    }
    dn = sqrt(dn);

    for(i=0;i<4;i++){
        w[i] = w[i]/dn;

    }//got w,now to get y..
    vector <vector <double> > r;
    vector <double> t0;
    int curr_1 = 0,curr_2 = 0;
    for(i=0;i<c.size();i++){
        double y = 0;
        for(j=0;j<4;j++){
            y+= c[i][j] * w[j];
        }
        t0.push_back(y);t0.push_back(0);t0.push_back(0);
        if(c[i][4]==0){t0.push_back(0);}
        if(c[i][4]==1){t0.push_back(1);}
        r.push_back(t0);t0.clear();
    }
    sort(r.begin(),r.end(),s_col);//cout<<"R...\n\n\n\n";
    for(i=0;i<r.size();i++){
        if(r[i][3]==0){curr_1++;}
        if(r[i][3]==1){curr_2++;}
        r[i][1] = curr_1;
        r[i][2] = curr_2;
        //cout<<"y="<<r[i][0]<<";class1="<<r[i][1]<<";class2="<<r[i][2]<<"\n";
    }
    //sorted all points projected y,now to find y0 using min entropy
    double point;double min_entropy=1;double e;
    double l_c1,l_c2,r_c1,r_c2;
    int c_flag = 0;
    for(i=0;i<r.size();i++){
        r_c1 = c1_count - r[i][1];
        r_c2 = c2_count - r[i][2];
        l_c1 = r[i][1];
        l_c2 = r[i][2];
        e = entropy(l_c1+r_c2,r.size()) + entropy(l_c2+r_c1,r.size());
        if(min_entropy>e){min_entropy = e;point = ( (r[i][0]+r[i+1][0])/2 );}
    }
    cout<<"\n--------------\nw = ";
    for(i=0;i<4;i++)cout<<w[i]*dn<<" ";

    cout<<"\n-------------------------\ny0="<<point<<";min entropy ="<<min_entropy<<"\n\n\n\n";


    //NOW TO CHECK OVER TESTING DATA
    fstream test_file;//file handler
    test_file.open("/Users/vishnu/Desktop/test.txt");//File location
    vector <vector <double> > t_data;
    string buff2;//file read line by line buffer
    cnt = 0;
    while(getline(test_file,buff2)){
        cnt++;
        vector <double> temp2;
        i=0;
        string t1 = "";
        double f_t1 = 0;
        while(buff2[i]!=','){t1 += buff2[i];i++;}//take double one at a time
        f_t1 = strtod((t1).c_str(),0);
        temp2.push_back(f_t1);//push back each onto temp
        t1 = "";i++;
        while(buff2[i]!=','){t1 += buff2[i];i++;}//take double one at a time
        f_t1 = strtod((t1).c_str(),0);
        temp2.push_back(f_t1);//push back each onto temp
        t1 = "";i++;
        while(buff2[i]!=','){t1 += buff2[i];i++;}//take double one at a time
        f_t1 = strtod((t1).c_str(),0);
        temp2.push_back(f_t1);//push back each onto temp
        t1 = "";i++;
        while(buff2[i]!=','){t1 += buff2[i];i++;}//take double one at a time
        f_t1 = strtod((t1).c_str(),0);
        temp2.push_back(f_t1);//push back each onto temp
        t1 = "";i++;
        while(buff2[i]!='\n'){t1 += buff2[i];i++;}
        f_t1 = strtod((t1).c_str(),0);
        temp2.push_back(f_t1);
        t_data.push_back(temp2);//push back temp onto c and clear temp
        temp2.clear();//repeat till all lines are read
    }
    double tn=0,fn = 0,tp = 0,fp = 0;double y;
    for(i=0;i<t_data.size();i++){
        y=0;
        for(j=0;j<4;j++){
            y += t_data[i][j] * w[j];
        }
        if(y >= point ){
            if(t_data[i][4]==1){tp++;}
            else{fp++;}
        }
        else{
            if(t_data[i][4]==1){fn++;}
            else{tn++;}
        }
    }
    cout<<"-------Confusion Matrix---------\n"<<"\t\tPRED(N)\tPRED(Y)\n"<<"ACTUAL(N)\t"<<tn<<"\t\t"<<fp<<"\nACTUAL(Y)\t"<<fn<<"\t\t"<<tp<<"\n";
    cout<<"\n\nAccuracy:"<<(tn+tp)/412*100<<"%\n";
    cout<<"\nPrecision:"<<tp/(tp+fp)*100<<"%\n";
    cout<<"\nRecall:"<<tp/(tp+fn)*100<<"%\n";
    cout<<"\nfin.\n\n";
    return 0;


}


