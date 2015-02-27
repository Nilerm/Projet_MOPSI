function area=trapeze(f,a,b,n)
    step=(b-a)/n;
    area=step/2*(f(a)+f(b));
    for i=1:n
        area=area+step*f(a+i*step);
    end
endfunction
