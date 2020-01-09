#define max_size 15

uniform float FilterWeight[max_size*max_size];
uniform float LP = 1.0;
uniform int col, row;
varying float LP_sum;

void main()
{
//    if(v_row == 1)
//        row = 1;
//    if(v_row == 3)
//        row = 3;
//    if(v_row == 5)
//        row = 5;
//    if(v_row == 7)
//        row = 7;
//    if(v_row == 9)
//        row = 9;
//    if(v_row == 11)
//        row = 11;
//    if(v_row == 13)
//        row = 13;
//    if(v_row == 15)
//        row = 15;


//    if(v_col == 1)
//        col = 1;
//    if(v_col == 3)
//        col = 3;
//    if(v_col == 5)
//        col = 5;
//    if(v_col == 7)
//        col = 7;
//    if(v_col == 9)
//        col = 9;
//    if(v_col == 11)
//        col = 11;
//    if(v_col == 13)
//        col = 13;
//    if(v_col == 15)
//        col = 15;

    //calculate the LP sum of weights
    float temp_LP_sum = 0;
    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {
            if(FilterWeight[i*col+j]!=0)
                temp_LP_sum +=  exp( log( FilterWeight[i*col+j])*LP );
        }

    LP_sum = exp( log(temp_LP_sum)/LP );

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}


