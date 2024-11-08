# Felix Zieliński 272336

function model(r::T, p::T)::T where T <: AbstractFloat
    return p + r * p * (one(T) - p)
end

# no idea how to make it T
# its so ugly do not look at it

function experiment_1a_32()::Vector{Float32}
    res::Vector{Float32} = Vector{Float32}()
    p::Float32 = 0.01
    r::Float32 = 3.0
    push!(res, p)

    for _ in 1:40
        p = model(r, p)
        push!(res, p)
    end
    
    return res
end

function experiment_1a_64()::Vector{Float64}
    res::Vector{Float64} = Vector{Float64}()
    p::Float64 = 0.01
    r::Float64 = 3.0
    push!(res, p)

    for _ in 1:40
        p = model(r, p)
        push!(res, p)
    end
    
    return res
end


function experiment_1b()::Vector{Float32}
    res::Vector{Float32} = Vector{Float32}()
    p::Float32 = 0.01
    r::Float32 = 3.0
    push!(res, p)

    for _ in 1:10
        p = model(r, p)
        push!(res, p)
    end

    p = trunc(p, digits = 3)
    println("P after truncating: ", p)

    for _ in 1:30
        p = model(r, p)
        push!(res, p)
    end
    
    return res
end


p_1::Vector{Float32} = experiment_1a_32()
p_2::Vector{Float32} = experiment_1b()
p_3::Vector{Float64} = experiment_1a_64()

println("\nResults: n --- p_1 --- p_2 --- p_3\n")
for n in 1:41
    println(n-1, " --- ", p_1[n], " --- ", p_2[n], " --- ", p_3[n])
end

