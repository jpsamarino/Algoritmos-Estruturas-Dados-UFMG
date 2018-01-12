#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,d;
    int i,j,k,l,m,m2;
    int num_casos, num_op;
    char s[10001],s2[10001];
    char s_bin[10001];
    int buffer[10001],buffer2[10001];
    int desloc_v, desloc_c;

    int tam,tam_v,tam_c;


    scanf ("%d",&num_casos);

    for (i=0; i<num_casos; i++)
    {
        tam=0;
        tam_c=0;
        tam_v=0;
        j=0;
        k=0;
        desloc_v =0;
        desloc_c =0;

        printf("Caso #%d:\n",i+1);
        c = getc(stdin);
        while(1)
        {
            c = getc(stdin);
            if (c == '\n' || c =='\0') break;
            if (c == 'a' || c == 'e' ||c == 'i' ||c == 'o' ||c == 'u')
            {
                s[j+k] = c;
                s2[j+k] = c;
                s_bin[j+k] = '0';
                buffer[j] = j+k;
                j++;
            }
            else
            {
                s[j+k] = c;
                s2[j+k] = c;
                s_bin[j+k] = '1';
                buffer2[k] = j+k;
                printf("-%d-",buffer2[k]);
                k++;
            }
        }
        tam = j+k;
        tam_c = k;
        tam_v =j;



        scanf("%d",&num_op);
        for (l=0; l<num_op; l++)
        {
            scanf("%d",&a);

            if(a==2)
            {   m2 =0 ;
            if(!d){
                for(m=0;m<tam;m++)
                {
                    if(s_bin[m]=='0')
                    {
                    s2[buffer[((m2+desloc_v)%tam_v)]] = s[m];
                    m2++;
                    }

                }
                printf ("%s \n",s2);
                }
                else{



                for(m=0;m<tam;m++)
                {
                    if(s_bin[m]=='1')
                    {
                    s2[buffer2[((m2+desloc_c)%tam_c)]] = s[m];
                    m2++;
                    }

                }
                printf ("%s \n",s2);
















                }
            }
            else if(a==0)
            {
                scanf("%d",&b);
                desloc_v = desloc_v + b;
                d=0;
            }
            else
            {
                scanf("%d",&b);
                desloc_c = desloc_c + b;
                d=1;
            }
        }
    }
    return 0;
}
