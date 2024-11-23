# Felix Zielinski 272336

include("./metody.jl")
using .metody

delta::Float64 = 10^(-4)
epsilon::Float64 = 10^(-4)

f(x) = 3*x - exp(x)

a1::Float64 = 0.0
b1::Float64 = 1.0

a2::Float64 = 1.0
b2::Float64 = 2.0

println("\nMetoda bisekcji dla a = 0.0 i b = 1.0:")
println(mbisekcji(f, a1, b1, delta, epsilon))

println("\nMetoda bisekcji dla a = 1.0 i b = 2.0:")
println(mbisekcji(f, a2, b2, delta, epsilon))
