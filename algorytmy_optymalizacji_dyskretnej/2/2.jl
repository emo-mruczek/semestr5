#Felix Zielinski 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(z::Vector, cp::Matrix, C::Vector, sp::Vector, kp::Vector, km::Vector)
    product, machine = size(cp)
    model = Model(HiGHS.Optimizer)

    @variable(model, x[1:product] >= 0, Int)

    @constraint(model, sum(repeat(x, 1, machine) .* cp, dims = 1) .<= C)

    @constraint(model, x .<= z)

    @objective(model, Max, sum((sp .- km) .* x) - sum(kp .* vec(sum(repeat(x, 1, machine) .* cp, dims = 1 ))))

    optimize!(model)

    println("\nKg per machine\n")
	display(value.(x))
    println("\nTime per machine (in minutes)\n")
    display(value.(x) .* cp)
	println("\nProfit\n")
	println(objective_value(model))

end

C = [60 * 60, 60 * 60, 60 * 60]
kp = [2 / 60, 2 / 60, 3 / 60]
km = [4, 1, 1, 1]
z = [400, 100, 150, 500]
sp = [9, 7, 6, 5]
cp = 
    [5 10 6; 
     3 6 4; 
     4 5 3; 
     4 2 1]


solve(z, cp, C, sp, kp, km)
