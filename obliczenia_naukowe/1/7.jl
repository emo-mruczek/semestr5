function f(x)

    return sin(x) + cos(3.0 * x)

end

function calc_derivative(n)

    h::Float64 = 2.0^(-n)
    x = 0.0

    return ( f(x + h) - f(x) ) / h
    
end

global exact_derivative = cos(1.0) + 3.0 * sin(3.0 * 1.0)

function calc_error(derivative)

    return abs(exact_derivative - derivative)
    
end

for n in 0:54
    derivative = calc_derivative(n)
    println("For n = ", n, " - ", derivative, ", error: ", calc_error(derivative))
end
