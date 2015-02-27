function []=give_err()
    for i=1:1000:10000
        printf("Iteration n°%d\n",i)
        err_t=abs(trapeze(cos,-%pi,%pi,i));
        printf("error with trapeze rule is : %e \n",err_t);
        err_s=abs(simpson(cos,-%pi,%pi,i));
        printf("error with Simpson''s rule is : %e \n\n",err_s);
    end
endfunction
