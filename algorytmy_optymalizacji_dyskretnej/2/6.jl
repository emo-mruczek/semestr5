# Felix Zieliński 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(G::Matrix, k)
    m, n = size(G)
    
    model = Model(HiGHS.Optimizer)

    @variable(model, 0 <= x[1:m, 1:n] <= 1, Int)

    for i in 1:m, j in 1:n
        if G[i,j] == 1
            @constraint(model, x[i,j] == 0)
            @constraint(model, sum(x[i, max(j - k, 1):min(j + k, n)]) + sum(x[max(i - k, 1):min(i + k, m), j]) >= 1)
        end
    end

    @objective(model, Min, sum(x))

    optimize!(model)

    println("\nCameras placement\n")
    display( G -= value.(x))
	println("\nNumber of cameras\n")
	println(objective_value(model))
end

struct Input 
    G::Matrix
    k::Int
end

minea::Input = Input( [1 0 1 0 0;
	0 1 0 0 0;
	0 1 0 0 0;
	1 0 0 1 0;
	0 1 1 0 1;
	1 0 1 0 1],
    2
)

mineb::Input = Input( [1 0 1 0 0;
	0 1 0 0 0;
	0 1 0 0 0;
	1 0 0 1 0;
	0 1 1 0 1;
	1 0 1 0 1],
    4
)

solve(mineb.G, mineb.k)
