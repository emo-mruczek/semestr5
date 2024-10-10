# its broken probably

# a
function a(x, y)

    #TODO: assert length
    len = length(x)
    S = 0.0
    for i in 1:len
        S += x[i] * y[i]
    end
    
    return S
end

# b
function b(x, y)

    len = length(x)
    S = 0.0
    for i in len:-1:1 # specyfying the negative step
        S += x[i] * y[i]
    end

    return S
end

# c
function c(x, y, T)

    len = length(x)
    S = Vector{T}(undef, len)

    for i in 1:len
        S[i] = x[i] * y[i]
    end
    
    # vectorized dot operators
    S_pos = S[S .>= 0]
    S_neg = S[S .< 0]

    println(S)
    println(S_pos)
    println(S_neg)

    # https://docs.julialang.org/en/v1/base/sort/
    sort!(S_pos, rev=true)
    sort!(S_neg)

    println(S_pos)
    println(S_neg)

    sum_pos = sum(S_pos)
    sum_neg = sum(S_neg)

    println(sum_pos)
    println(sum_neg)

    return sum_pos + sum_neg
end

# d
function d(x, y, T)

    len = length(x)
    S = Vector{T}(undef, len)

    for i in 1:len
        S[i] = x[i] * y[i]
    end

    # vectorized dot operators
    S_pos = S[S .>= 0]
    S_neg = S[S .< 0]

    # https://docs.julialang.org/en/v1/base/sort/
    sort!(S_pos)
    sort!(S_neg, rev=true)

    sum_pos = sum(S_pos)
    sum_neg = sum(S_neg)

    return sum_pos + sum_neg
end

x_32::Vector{Float32} = [2.718281828, −3.141592654, 1.414213562, 0.5772156649, 0.3010299957]
y_32::Vector{Float32} = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

x_64::Vector{Float64} = [2.718281828, −3.141592654, 1.414213562, 0.5772156649, 0.3010299957]
y_64::Vector{Float64} = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

println("For Float32: a --- b --- c --- d")
println(a(x_32, y_32), " --- ", b(x_32, y_32), " --- ", c(x_32, y_32, Float32), " --- ", d(x_32, y_32, Float32))
println("\nFor Float64: a --- b --- c --- d")
println(a(x_64, y_64), " --- ", b(x_64, y_64), " --- ", c(x_64, y_64, Float64), " --- ", d(x_64, y_64, Float64))

