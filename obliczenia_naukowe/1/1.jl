
# macheps for Float16, Float32, Float64
# macheps > 0 that fl(1.0+macheps) > 1.0 i fl(1.0+macheps) = 1+macheps
function calc_macheps(T)
    # one(T) can take a type T, in which case one returns a multiplicative identity for any x of type T.
    macheps = one(T)
    while one(T) + macheps > one(T)
        macheps /= 2
    end

    # return previous value
    return macheps * 2
end

# eta for Float16, Float32, Float64
function calc_eta(T)
    eta = one(T)
    prev = eta

    while eta > 0.0
        prev = eta
        eta /= 2
    end

    return prev
end

# MAX for Float16, Float32, Float64
function calc_max(T)
    max = prevfloat(one(T))
    # prevfloat(f) Get the previous floating point number in lexicographic order
    prev = max

    while !isinf(max)
        prev = max
        max *= 2
    end

    return prev
end

println("Calculated macheps - values returned by eps")
println("For Float16 ", calc_macheps(Float16), " - ", eps(Float16))
println("For Float32 ", calc_macheps(Float32), " - ", eps(Float32))
println("For Float64 ", calc_macheps(Float64), " - ", eps(Float64))

println("\nCalculated eta - values returned by nextfloat")
println("For Float16 ", calc_eta(Float16), " - ", nextfloat(Float16(0.0)))
println("For Float32 ", calc_eta(Float32), " - ", nextfloat(Float32(0.0)))
println("For Float64 ", calc_eta(Float64), " - ", nextfloat(Float64(0.0)))

println("\nValues returned by floatmin")
println("For Float32 ", floatmin(Float32))
println("For Float64 ", floatmin(Float64))

println("\nCalculated max - values returned by floatmax")
println("For Float16 ", calc_max(Float16), " - ", floatmax(Float16(0.0)))
println("For Float32 ", calc_max(Float32), " - ", floatmax(Float32(0.0)))
println("For Float64 ", calc_max(Float64), " - ", floatmax(Float64(0.0)))




