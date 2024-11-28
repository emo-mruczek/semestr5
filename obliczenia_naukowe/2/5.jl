# Felix Zieliński 272336

# function model
# params: 
#   r - variable
#   p - variable
# returns results of one iteration of the model 

function model(r::T, p::T)::T where T <: AbstractFloat
    return p + r * p * (one(T) - p)
end

# function experiment_1a
# params: 
#   T - Type of an AbstractFloat
# returns vector with a results of the 1. experiment

function experiment_1a(T::Type{<: AbstractFloat})::Vector{T}
    res::Vector{T} = Vector{T}()
    p::T = 0.01
    r::T = 3.0
    push!(res, p)

    for _ in 1:40
        p = model(r, p)
        push!(res, p)
    end
    
    return res
end

# function experiment_1b
# 
# returns vector with a results of the 2. experiment

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


p_1::Vector{Float32} = experiment_1a(Float32)
p_2::Vector{Float32} = experiment_1b()
p_3::Vector{Float64} = experiment_1a(Float64)

println("\nResults: n --- p_1 --- p_2 --- p_3\n")
for n in 1:41
    println(n-1, " --- ", p_1[n], " --- ", p_2[n], " --- ", p_3[n])
end

