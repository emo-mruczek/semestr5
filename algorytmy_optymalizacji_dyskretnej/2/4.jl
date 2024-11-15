# Felix Zieliński 272336

import Pkg
Pkg.add("JuMP")
Pkg.add("HiGHS")
using JuMP, HiGHS

function solve(T::Int, G::Matrix, c::Matrix, t::Matrix, i::Int, j::Int, N::Int)
        
    model = Model(HiGHS.Optimizer)

    @variable(model, 0 <= x[1:N, 1:N] <= 1, Int)
    println(typeof(x))
    
    for k in 1:N, l in 1:N
        if G[k, l] == 0
            @constraint(model, x[k, l] == 0)
        end
    end

    @constraint(model, vec(sum(x, dims = 1))[j] == 1)
    @constraint(model, vec(sum(x, dims = 2))[i] == 1)

    for k in 1:N
        if k != i && k != j
            @constraint(model, vec(sum(x, dims = 1))[k] == vec(sum(x, dims = 2))[k])
        end
    end

    @constraint(model, sum(x .* t) <= T)
    
    @objective(model, Min, sum(x .* c))

    optimize!(model)

    println("\nConnections matrix\n")
	for k in 1:N, l in 1:N
		if value.(x[k, l]) == 1
			println(" - [$k, $l, $(c[k, l]), $(t[k, l])]")
		end
	end
	println("\nTime\n")
	println(sum(value.(x) .* t))
	println("\nCost\n")
	println(objective_value(model))
end

struct Input
    N::Int
    i::Int
    j::Int
    T::Int
    connections::Vector
end

function construct_and_solve(in::Input)
    G = zeros(in.N, in.N)
    c = zeros(in.N, in.N)
    t = zeros(in.N, in.N)

    for con in in.connections
        G[con[1], con[2]] = 1
	    c[con[1], con[2]] = con[3]
        t[con[1], con[2]] = con[4]
    end
    solve(in.T, G, c, t, in.i, in.j, in.N)
end

a::Input = Input(10, 1, 10, 15, [[1, 2, 3, 4], [1, 3, 4, 9], [1, 4, 7, 10], [1, 5, 8, 12], [2, 3, 2, 3], [3, 4, 4, 6], [3, 5, 2, 2], [3, 10, 6, 11], [4, 5, 1, 1], [4, 7, 3, 5], [5, 6, 5, 6], [5, 7, 3, 3], [5, 10, 5, 8], [6, 1, 5, 8], [6, 7, 2, 2], [6, 10, 7, 11], [7, 3, 4, 6], [7, 8, 3, 5], [7, 9, 1, 1], [8, 9, 1, 2], [9, 10, 2, 2]])

b::Input = Input(10, 1, 5, 9, [
    [1, 2, 10, 2],
    [2, 3, 15, 3],
    [3, 4, 20, 5],
    [4, 5, 10, 2],
    [1, 6, 25, 4],
    [6, 7, 15, 3],
    [7, 5, 10, 2],
    [1, 8, 30, 6],
    [8, 9, 20, 3],
    [9, 10, 25, 4],
    [10, 5, 15, 3]
]
)

construct_and_solve(b)
