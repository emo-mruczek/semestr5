# Felix Zieliński 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(p::Vector{Int64}, z::Vector{Int64}, k::Matrix{Int64})
    airport, company = size(k)

    model::Model = Model(HiGHS.Optimizer)

    @variable(model, x[1:airport, 1:company] >= 0, Int)

    @constraint(model, vec(sum(x, dims = 1)) .<= p)

    @constraint(model, vec(sum(x, dims = 2)) .== z)

    @objective(model, Min, sum(k .*  x))

    optimize!(model)

    println("\nFuel sent matrix\n")
	display(value.(x))
	println("\nSum 1.\n")
	println(vec(sum(value.(x), dims = 1)))
	println("\nSum 2.\n")
	println(vec(sum(value.(x), dims = 2)))
	println("\nMin cost\n")
	println(objective_value(model))
end

k = [10 7 8; 10 11 14; 9 12 4; 11 13 9]
p = [275000, 550000, 660000]
z = [110000, 220000, 330000, 440000]

solve(p, z, k)
