# Felix Zielinski 272336

include("./metody.jl")
using .metody 

delta::Float64 = 10^(-5)
epsilon::Float64 = 10^(-5)

f1(x) = exp(1-x) - 1
f2(x) = x*exp(-x)

pf1(x) = -exp(1-x)
pf2(x) = -exp(-x) * (x-1)

maxit::Int = 100

a1::Float64 = 0.0
b1::Float64 = 1.0

a2::Float64 = -1.0
b2::Float64 = 1.0

a3::Float64 = -3.0
b3::Float64 = 3.0

a4::Float64 = -0.0
b4::Float64 = 2.0

x0_1::Float64 = 0.0
x0_2::Float64 = 0.5
x0_3::Float64 = 0.9999
x0_4::Float64 = 1.0
x0_5::Float64 = 2.0
x0_6::Float64 = 10.0

x1_1::Float64 = 0.5
x1_2::Float64 = 0.6
x1_3::Float64 = 0.999999
x1_4::Float64 = 1.05
x1_5::Float64 = 1.5
x1_6::Float64 = 14.0

println("\nDla 1. funkcji:")
println("\nMetoda bisekcji dla a = ", a1," i b = ", b1, ":")
println(mbisekcji(f1, a1, b1, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a2," i b = ", b2, ":")
println(mbisekcji(f1, a2, b2, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a3," i b = ", b3, ":")
println(mbisekcji(f1, a3, b3, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a4," i b = ", b4, ":")
println(mbisekcji(f1, a4, b4, delta, epsilon))

println("\nMetoda Newtona dla x0 = ", x0_1, ":")
println(mstycznych(f1, pf1, x0_1, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_2, ":")
println(mstycznych(f1, pf1, x0_2, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_3, ":")
println(mstycznych(f1, pf1, x0_3, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_4, ":")
println(mstycznych(f1, pf1, x0_4, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_5, ":")
println(mstycznych(f1, pf1, x0_5, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_6, ":")
println(mstycznych(f1, pf1, x0_6, delta, epsilon, maxit))

println("\nMetoda siecznych dla x0 = ", x0_1, " i x1 = ", x1_1, ":")
println(msiecznych(f1, x0_1, x1_1, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_2, " i x1 = ", x1_2, ":")
println(msiecznych(f1, x0_2, x1_2, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_3, " i x1 = ", x1_3, ":")
println(msiecznych(f1, x0_3, x1_3, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_4, " i x1 = ", x1_4, ":")
println(msiecznych(f1, x0_4, x1_4, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_5, " i x1 = ", x1_5, ":")
println(msiecznych(f1, x0_5, x1_5, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_6, " i x1 = ", x1_6, ":")
println(msiecznych(f1, x0_6, x1_6, delta, epsilon, maxit))

a3 = -0.4
b3 = 0.5

a4 = -0.5
b4 = 0.5

x0_1 = -1.0
x0_2 = -0.00001
x0_3 = 0.0
x0_4 = 0.5
x0_5 = 1.0
x0_6 = 10.0

x1_1 = -0.5
x1_2 = -0.0000001
x1_3 = 0.5
x1_4 = 0.3
x1_5 = 0.0
x1_6 = 15.0

println("\nDla 2. funkcji:")
println("\nMetoda bisekcji dla a = ", a1," i b = ", b1, ":")
println(mbisekcji(f2, a1, b1, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a2," i b = ", b2, ":")
println(mbisekcji(f2, a2, b2, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a3," i b = ", b3, ":")
println(mbisekcji(f2, a3, b3, delta, epsilon))
println("\nMetoda bisekcji dla a = ", a4," i b = ", b4, ":")
println(mbisekcji(f2, a4, b4, delta, epsilon))

println("\nMetoda Newtona dla x0 = ", x0_1, ":")
println(mstycznych(f2, pf2, x0_1, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_2, ":")
println(mstycznych(f2, pf2, x0_2, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_3, ":")
println(mstycznych(f2, pf2, x0_3, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_4, ":")
println(mstycznych(f2, pf2, x0_4, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_5, ":")
println(mstycznych(f2, pf2, x0_5, delta, epsilon, maxit))
println("\nMetoda Newtona dla x0 = ", x0_6, ":")
println(mstycznych(f2, pf2, x0_6, delta, epsilon, maxit))

println("\nMetoda siecznych dla x0 = ", x0_1, " i x1 = ", x1_1, ":")
println(msiecznych(f2, x0_1, x1_1, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_2, " i x1 = ", x1_2, ":")
println(msiecznych(f2, x0_2, x1_2, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_3, " i x1 = ", x1_3, ":")
println(msiecznych(f2, x0_3, x1_3, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_4, " i x1 = ", x1_4, ":")
println(msiecznych(f2, x0_4, x1_4, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_5, " i x1 = ", x1_5, ":")
println(msiecznych(f2, x0_5, x1_5, delta, epsilon, maxit))
println("\nMetoda siecznych dla x0 = ", x0_6, " i x1 = ", x1_6, ":")
println(msiecznych(f2, x0_6, x1_6, delta, epsilon, maxit))
