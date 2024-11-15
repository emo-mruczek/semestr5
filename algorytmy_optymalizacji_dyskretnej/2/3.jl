# Felix Zieliński 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(m::Vector, c::Vector, a::Vector, o::Vector, d::Vector, s::Int, km::Int, mp::Int)
    period = length(m)
    model = Model(HiGHS.Optimizer)

    @variable(model, x[1:period] >= 0, Int)
    @variable(model, y[1:period] >= 0, Int)
    @variable(model, z[1:period+1] >= 0, Int)

    @constraint(model, x .<= m)
    @constraint(model, y .<= a)
    @constraint(model, z .<= s)

    @constraint(model, z[1] == mp)
    @constraint(model, z[period+1] == 0)

    for i in 1:period
        @constraint(model, z[i+1] == x[i] + y[i] + z[i] - d[i])
    end
    
    @objective(model, Min, sum(x .* c) + sum(y .* o) + sum(z[2:period] .* km))

    optimize!(model)

    println("\nBasic production\n")
	println(value.(x))
	println("\nAdditional production\n")
	println(value.(y))
	println("\nIn storage\n")
	println(value.(z))
	println("\nSales\n")
	println(d)
    println("\nCost\n")
	println(objective_value(model))
end    

m = [100, 100, 100, 100]
c = [6000, 4000, 8000, 9000]
a = [60, 65, 70, 60]
o = [8000, 6000, 10000, 11000]
d = [130, 80, 125, 195]
km = 1500
mp = 15
s = 70

solve(m, c, a, o, d, s, km, mp)
