function []=plot_err()
    deff('[y1]=homer(x)','y1=log(abs(simpson(cos,-%pi,%pi,x)))')
    deff('[y2]=trap(x)','y2=log(abs(trapeze(cos,-%pi,%pi,x)))')
    n=[1:100:10000];
    plot(1:1000:100000,homer,'b')
    plot(1:1000:100000,trap,'r')
endfunction
