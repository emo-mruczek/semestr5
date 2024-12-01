# Felix Zieliński 272336
import Pkg
Pkg.add("Plots")
using Plots
module metody

export ilorazyRoznicowe, warNewton, naturalna, rysujNnfx


# funckja obliczająca ilorazy różnicowe
# Dane:
#   x – wektor długości n + 1 zawierający węzły x0, . . . , xn
#   x[1]=x0,..., x[n+1]=xn
#   f – wektor długości n + 1 zawierający wartości interpolowanej
#   funkcji w węzłach f (x0), . . . , f (xn)
# Wyniki:
#   fx – wektor długości n + 1 zawierający obliczone ilorazy różnicowe
#   fx[1]=f [x0],
#   fx[2]=f [x0, x1],..., fx[n]=f [x0, . . . , xn−1], fx[n+1]=f [x0, . . . , xn].

function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})::Vector{Float64}
    len::Int64 = length(x)
    ret::Vector{Float64} = copy(f)

    for i::Int64 in 2:len 
        for j::Int64 = len:-1:i 
            ret[j] = (ret[j] - ret[j-1]) / (x[j] - x[1 + j - i])
        end
    end

    return ret
end

# funkcja obliczająca wartość wielomianu interpolacyjnego metodą Hornera
# Dane:
#   x – wektor długości n + 1 zawierający węzły x0, . . . , xn
#   x[1]=x0,..., x[n+1]=xn
#   fx – wektor długości n + 1 zawierający ilorazy różnicowe
#   fx[1]=f [x0],
#   fx[2]=f [x0, x1],..., fx[n]=f [x0, . . . , xn−1], fx[n+1]=f [x0, . . . , xn]
#   t – punkt, w którym należy obliczyć wartość wielomianu
# Wyniki:
#   nt – wartość wielomianu w punkcie t.

function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)::Float64
    len::Int64 = length(x)
    ret::Float64 = fx[len]
    
    for i::Int64 in n-1:-1:1 
        ret = fx[i] + ret * (t - x[i])
    end

    return ret 
end

# funkcja obliczająca współczynniki postaci naturalnej wielomaniu interpolacyjnego w postaci Newtona
# Dane:
#   x – wektor długości n + 1 zawierający węzły x0, . . . , xn
#   x[1]=x0,..., x[n+1]=xn
#   fx – wektor długości n + 1 zawierający ilorazy różnicowe
#   fx[1]=f [x0],
#   fx[2]=f [x0, x1],..., fx[n]=f [x0, . . . , xn−1], fx[n+1]=f [x0, . . . , xn]
# Wyniki:
#   a – wektor długości n + 1 zawierający obliczone współczynniki postaci naturalnej
#   a[1]=a0,
#   a[2]=a1,..., a[n]=an−1, a[n+1]=an.

function naturalna(x::Vector{Float64}, fx::Vector{Float64})::Vector{Float64}
    len::Int46 = length(fx)
    ret::Vector{Float64} = Vector{Float64}(len)
    ret[len] = fx[len]

    for i::Int46 in len-1:-1:1 
        ret[i] = fx[i] - x[i] * ret[i + 1]

        for j::Int46 in i+1:len-1 
            ret[j] = ret[j] - x[i] * ret[j + 1]
        end
    end

    return ret
end

# funkcja interpolująca zadaną funkcję na przedziale [a, b] przy użyciu węzłów równodległych oraz funkcji ilorazyRoznicowe i warNewton
# Dane:
#   f – funkcja f (x) zadana jako anonimowa funkcja,
#   a,b – przedział interpolacji
#   n – stopień wielomianu interpolacyjnego
# Wyniki:
#   – funkcja rysuje wielomian interpolacyjny i interpolowaną
#   funkcję w przedziale [a, b].

function rysujNnfx(f::Function, a::Float64, b::Float64, n::Int)
    c::Vector{Float64} = Vector{Float64}(n + 1)
    d::Vector{Float64} = Vector{Float64}(n + 1)
    dist::Float64 = (b - a) / n # odleglosc od wezlow

    for i::Int64 in 1:n+1 
        c[i] = a + disc * (i - 1)
        x::Float64 = c[i]
        d[i] = f(x)
    end

    quo::Vector{Float64} = ilorazyRoznicowe(c, d)

    # do zmiany wedle uznania
    density::Int64 = 50
    acc_dist::Float64 = (b - a) / density

    # wyniki do rysowania
    int_val::Vector{Float64}(density)
    func_val::Vector{Float64}(density)

    p::Float64 = 0;
    for i::Int64 in 1:density
        p = acc_dist * (i - 1) + a 
        int_val[i] = warNewton(c, quo, p)
        func_val[i] = f(p) 
    end

    plot!(linspace(a, b, density), int_val, color ="blue", label="w(x)")
    plot(linspace(a, b, density), func_val, color ="red", label = "f(x)")
    savefig("plot_$a$b$n.png")

    return nothing
end

end
