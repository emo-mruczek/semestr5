
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


println("Calculated machine epsilions - values returned by eps")
println("For Float16 ", calc_macheps(Float16), " - ", eps(Float16))
println("For Float32 ", calc_macheps(Float32), " - ", eps(Float32))
println("For Float64 ", calc_macheps(Float64), " - ", eps(Float64))
