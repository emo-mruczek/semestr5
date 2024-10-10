
function find_float(b, e, T) 
    x = nextfloat(T(b))
    res = 0.0

    while x < T(e) 
        res =  x * ( one(T) / x) 
        if res != 1
            return x
        end
        x = nextfloat(x)
    end

    return -1
end

println("Moje: ", find_float(1, 2, Float64))

