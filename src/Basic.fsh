#define max_size 15

uniform float LP = 1.0;
uniform sampler2D tex_real, tex_cood;
uniform float FilterWeight[max_size*max_size];
uniform float width, height;
uniform int row, col;
varying float LP_sum;

void main()
{
    float tmp_sum = 0;
    vec3 mix_color = vec3(0.0);
    float weight_sum=0;


    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {

            if(FilterWeight[i*col+j]!=0)
            {
                 mix_color += exp(log(FilterWeight[i*col+j]*texture2D(tex_real, vec2(gl_TexCoord[0].s+(i-(row-1)/2)/width, gl_TexCoord[0].t+(j-(col-1)/2)/height)).rgb )*LP );
     weight_sum =exp(log(FilterWeight[i*col+j])*LP);
            }

        }

    if(LP == 0)
    {
        gl_FragColor = vec4(exp(log(mix_color)*vec3(1.0)), 1.0);
    }
    else
    {
        gl_FragColor =   	 		vec4(exp(log(mix_color)*vec3(1.0/LP)),1.0)/(exp(log(weight_sum)/LP));
    }
}
