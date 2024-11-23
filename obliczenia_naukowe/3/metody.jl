# Felix Zielinski 272336

module metody

export mbisekcji, mstycznych, msiecznych

# funckcja rozwiązująca równanie f (x) = 0 metodą Newtona 
# Dane:
#   f, pf – funkcją f (x) oraz pochodną f ′(x) zadane jako anonimowe funkcje,
#   x0 – przybliżenie początkowe,
#   delta,epsilon – dokładności obliczeń,
#   maxit – maksymalna dopuszczalna liczba iteracji,
# Wyniki:
#   (r,v,it,err) – czwórka, gdzie
#   r – przybliżenie pierwiastka równania f (x) = 0,
#   v – wartość f (r),
#   it – liczba wykonanych iteracji,
#   err – sygnalizacja błędu
#   0 - metoda zbieżna
#   1 - nie osiągnięto wymaganej dokładności w maxit iteracji,
#   2 - pochodna bliska zeru

function mstycznych(f::Function, pf::Function, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)::Tuple{Float64, Float64, Int, Int} 
    val::Float64 = f(x0)

    if abs(val) < epsilon return x0, val, 0, 0 end

    if abs(pf(x0)) < epsilon return NaN, NaN, 0, 2 end

    x::Float64 = zero(Float64)

    for i::Int = 1:maxit
        x = x0 - ( val / pf(x0) )
        val = f(x)

        if abs(val) < epsilon || abs(x - x0) < delta return x, val, i, 0 end

        x0 = x
    end

    return NaN, NaN, 0, 1
end

# funckcja rozwiązująca równanie f (x) = 0 metodą siecznych 
# Dane:
#   f – funkcja f (x) zadana jako anonimowa funkcja,
#   x0,x1 – przybliżenia początkowe,
#   delta,epsilon – dokładności obliczeń,
#   maxit – maksymalna dopuszczalna liczba iteracji,
# Wyniki:
#   (r,v,it,err) – czwórka, gdzie
#   r – przybliżenie pierowiastka równania f (x) = 0,
#   v – wartość f (r),
#   it – liczba wykonanych iteracji,
#   err – sygnalizacja błędu
#   0 - metoda zbieżna
#   1 - nie osiągnięto wymaganej dokładności w maxit iteracji

function msiecznych(f::Function, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64,
maxit::Int)::Tuple{Float64, Float64, Int, Bool} 
f_a::Float64 = f(x0)
f_b::Float64 = f(x1)

for i::Int = 1:maxit
    if abs(f_a) > abs(f_b)
        # legal syntax for swapping variables lol https://docs.julialang.org/en/v1/manual/functions/#destructuring-assignment
        f_a, f_b = f_b, f_a
        x0, x1 = x1, x0
    end

    s = (x1 - x0) / (f_b - f_a)
    x1 = x0
    f_b = f_a
    x0 = x0 - (f_a * s)
    f_a = f(x0)

    if abs(x1 - x0) < delta || abs(f_a) < epsilon return x0, f_a, i, 0 end

    end

    return NaN, NaN, NaN, 1

end

# funckcja rozwiązująca równanie f (x) = 0 metodą bisekcji
# Dane:
#   f – funkcja f (x) zadana jako anonimowa funkcja (ang. anonymous function),
#   a,b – końce przedziału początkowego,
#   delta,epsilon – dokładności obliczeń,
# Wyniki:
#   (r,v,it,err) – czwórka, gdzie
#   r – przybliżenie pierwiastka równania f (x) = 0,
#   v – wartość f (r),
#   it – liczba wykonanych iteracji,
#   err – sygnalizacja błędu
#   0 - brak błędu
#   1 - funkcja nie zmienia znaku w przedziale [a,b]

function mbisekcji(f::Function, a::Float64, b::Float64, delta::Float64, epsilon::Float64)::Tuple{Float64, Float64, Int, Bool} 
    a_val::Float64 = f(a)
    b_val::Float64 = f(b)
    interval::Float64 = b - a 

    if sign(a_val) == sign(b_val) return NaN, NaN, 0, 1 end

    iterations::Int = 0
    c::Float64 = zero(Float64)
    middle_val::Float64 = zero(Float64)

    while interval > epsilon 
        iterations += 1

        interval /= 2
        c = a + interval
        middle_val = f(c)

        if abs(middle_val) < epsilon || abs(interval) < delta
            return c, middle_val, iterations, 0
        end

        if sign(middle_val) == sign(a_val)
            a = c 
            a_val = middle_val
        else
            b = c 
            b_val = middle_val
        end
    end
end

end
