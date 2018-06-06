function kernel = derivative_kernel (num)
     horizontal filter kernel
if num == 1
    kernel = [1 0 -1];
elseif num == 2
    kernel = [0 1 -1];
elseif num == 3
    kernel = [1 0 -1 ; 1 0 -1 ; 1 0 -1];
elseif num == 4
    kernel = [1 0 -1 ; 2 0 -2 ; 1 0 -1];    
elseif num == 5
    kernel = [1 4 7 4 1; 4 20 33 20 4; 7 33 55 33 7; 4 20 33 20 4; 1 4 7 4 1];    
end

end
