function area=simpson(f,a,b,n)
    step=(b-a)/n;
    area=f(a)+f(b);
    for i=1:n
        if(modulo(i,2)==0)
            area=area+4*f(a+i*step);
        else
            area=area+2*f(a+i*step);
        end
    end
    area=step/3*area;
endfunction
