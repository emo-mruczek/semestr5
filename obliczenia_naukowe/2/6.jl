# Felix Zieliński 272336

c::Vector{Float64} = [-2.0, -2.0, -2.0, -1.0, -1.0, -1.0, -1.0]
x::Vector{Float64} = [1.0, 2.0, 1.99999999999999, 1.0, -1.0, 0.75, 0.25]

function experiment(x::Float64, c::Float64)::Vector{Float64} 
    res::Vector{Float64} = Vector{Float64}()
    push!(res, x)

    for _ in 1:40
        x = x * x + c
        push!(res, x)
    end

    return res
end

function get_results()
    for i::Int64 in 1:7
        res::Vector{Float64} = experiment(x[i], c[i])
        println("\nResults for c = ", c[i], " and x = ", x[i])
        for n::Int64 in 1:41
            println(n - 1, " --- ", res[n])
        end
    end

    return nothing
end

get_results()
