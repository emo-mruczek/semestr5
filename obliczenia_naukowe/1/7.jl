# Felix Zieliński 272336

# parametry funkcji:
#   x - wartość argumentu x

function f(x)
    return sin(x) + cos(3.0 * x)
end

# parametry funkcji:
#   n - wartość, do której wartości ujemnej podnoszone jest 2

function calc_derivative(n)

    h::Float64 = 2.0^(-n)
    x = one(Float64)

    return ( f(x + h) - f(x) ) / h
    
end

# dokładna wartość pochodnej

global exact_derivative = cos(1.0) - 3.0 * sin(3.0 * 1.0)

# parametry funkcji:
#   derivative - pochodna, która używana jest do obliczenia błędu

function calc_error(derivative)
    return abs(exact_derivative - derivative)
end

println("h --- h + 1 --- derivative --- error")
for n in 0:54
    derivative = calc_derivative(n)
    println("2^(-", n, ") --- ", 2.0^(-n) + 1, " --- ", derivative, " --- ", calc_error(derivative))
end

println("Exact derivative: ", exact_derivative)
