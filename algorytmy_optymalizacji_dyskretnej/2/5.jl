# Felix Zieliński 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(min::Matrix, max::Matrix, zmin::Vector, dmin::Vector)
    m, n = size(min)

    model = Model(HiGHS.Optimizer)

    @variable(model, 0 <= x[1:m, 1:n], Int)

    @constraint(model, min .<= x .<= max)
    @constraint(model, vec(sum(x, dims = 1)) .>= zmin)
    @constraint(model, vec(sum(x, dims = 2)) .>= dmin)

    @objective(model, Min, sum(x))

    optimize!(model)

    println("\nRadio-despached cars placement\n")
	display(value.(x))
	println("\nNumber of radio-despached cars\n")
	println(objective_value(model))
end

min = 
   [2 4 3;
	3 6 5;
	5 7 8]

max = 
   [3 5 7;
	5 7 10;
	8 12 10]

zmin = [10, 20, 18]
dmin = [10, 14, 13]

solve(min, max, zmin, dmin)
