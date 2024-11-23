# Felix Zielinski 272336

include("./metody.jl")
using .metody

f(x) = sin(x) - (1/2*x)^2

a::Float64 = 1.5
b::Float64 = 2.0

delta::Float64 = 1/2*10^(-5)
epsilon::Float64 = 1/2*10^(-5)

x0_newton::Float64 = 1.5

x0_sieczne::Float64 = 1 
x1_sieczne::Float64 = 2 

pf(x) = cos(x) - (1/2)x 

maxit = 20 

println("\nMedota bisekcji:")
println(mbisekcji(f, a, b, delta, epsilon))

println("\nMetoda Newtona:")
println(mstycznych(f, pf, x0_newton, delta, epsilon, maxit))

println("\nMetoda siecznych:")
println(msiecznych(f, x0_sieczne, x1_sieczne, delta, epsilon, maxit))

