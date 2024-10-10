#TODO: be consistent in one(T) throughout ex

function f(x, T)
    return sqrt(x^2 + one(T)) - one(T)
end

function g(x, T)
    return x^2 / ( sqrt(x ^ one(T)) + one(T) )
end

x = 8
for p in 1:5
    prinln("f(", x, "^-", p, "): ", f(x^(-p)))
end
