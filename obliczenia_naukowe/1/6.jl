#TODO: be consistent in one(T) throughout ex
#TODO: check the results

function f(x, T)
    return sqrt(x^2 + one(T)) - one(T)
end

function g(x, T)
    return x^2 / ( sqrt(x ^ one(T)) + one(T) )
end

x::Float64 = 8.0
for p in 1:10
    println("f(", x, "^-", p, "): ", f(x^(-p), Float64))
    println("g(", x, "^-", p, "): ", g(x^(-p), Float64))
    println("\n")
end
