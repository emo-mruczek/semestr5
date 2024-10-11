# bitstring(n) A string giving the literal bit representation of a primitive type. 

function is_evenly(step, b::Float64, e::Float64)

    x = b
    y = b

    while x < e
        println(bitstring(x))
        println(bitstring(y))
        x += step
        y = nextfloat(y)
    end
end

println(is_evenly(2.0^(-52), 1.0, 2.0))

